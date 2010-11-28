#include "GraphicsPrivate.h"
#include "ShaderMgr.h"
#include "Shlwapi.h"
#include "DCRenderer.h"

#define SHADER_ASSERT_ON_ERROR 1

SINGLETON_DEFINE(ShaderMgr);

ShaderMgr::ShaderMgr()
{

}

ShaderMgr::~ShaderMgr()
{

}


/*
 *	when meeting fx, search for xml for macro definition
 *  
 */
void ShaderMgr::LoadShaders()
{
    const wchar_t* shaderPath = L"..\\Engine\\Shader\\";    
    const wchar_t* allFilePath = L"..\\Engine\\Shader\\*.*";
    const wchar_t* xmlEx = L".xml";
    const wchar_t* fxEx = L".fx";

    /*
     *	construct name list
     */
    std::vector<std::wstring> fileNames;

    WIN32_FIND_DATA stData; 
    HANDLE hFind = FindFirstFile(allFilePath, &stData); 
    if (hFind  == INVALID_HANDLE_VALUE)  
    {
        return;
    }
    
    do 
    {        
        if(StrCmpW(stData.cFileName, L".")==0 || StrCmpW(stData.cFileName, L"..")==0)
        {
            continue;
        }

        fileNames.push_back(stData.cFileName);
    } while (FindNextFile(hFind, &stData));

    /*
     *	parse name list, construct description list
     */
    std::sort(fileNames.begin(), fileNames.end());

    for(u32 i=0; i<fileNames.size(); i++)    
    {
        const std::wstring& fileName = fileNames[i];
        size_t pos = fileName.find(fxEx);
        if(pos==std::wstring.npos)
        {
            continue;
        }

        mShaderDescs.push_back(ShaderDesc());
        ShaderDesc& shaderDesc = mShaderDescs[mShaderDescs.size()-1];

        std::wstring name = fileName.substr(0, fileName.size()-3);
        //name +=xmlEx;
        std::wstring descName = name+xmlEx;
        std::vector<std::wstring>::iterator result = std::find(fileNames.begin(), fileNames.end(), descName);
                
        if(result!=fileNames.end())
        {
            //parse xml for description
            std::wstring xmlNameW = shaderPath;
            xmlNameW+=descName;
            std::string xmlName;
            WStrToStr(xmlNameW, xmlName);

            ParseShaderDesc(xmlName, shaderDesc);
        }

        WStrToStr(name,shaderDesc.name);
    }

    /*
     *	load shader cache
     */
    LoadShaderCache();

    /*
     *	compile shaders
     */
    for (u32 shaderIdx=0; shaderIdx<mShaderDescs.size(); shaderIdx++)
    {
        const ShaderDesc& desc = mShaderDescs[shaderIdx];
        const u32 macroSize = desc.definitions.size();

        std::wstring fxName;
        StrToWStr(desc.name, fxName);        
        fxName+=fxEx;

        //LogToDebugA("compiling shader %s\n", desc.name.c_str());
        RENDER_LOG("compiling shader %s\n", desc.name.c_str());
        std::vector<D3DXMACRO> macroes;
        macroes.resize(macroSize+1);
        macroes[macroSize].Definition = NULL;
        macroes[macroSize].Name = NULL;

        for(u32 macroIdx=0; macroIdx<macroSize; macroIdx++)
        {
            macroes[macroIdx].Name = desc.definitions[macroIdx].c_str();
        }

        /*
         *	no macro def shader
         */
        if(desc.ids.size()==0)
        {
            ShaderId shaderId = (ShaderId)shaderIdx<<32;
            ShaderMap::iterator shaderHandleIt = mShaderMap.find(shaderId);

            ShaderHandle* shaderHandle = NULL;
            if(shaderHandleIt==mShaderMap.end())
            {
                shaderHandle = new ShaderHandle;
                mShaderMap[shaderId] = shaderHandle;
            }
            else
            {
                shaderHandle = shaderHandleIt->second;
            }            

            //compare the compiled shader's src with the current preprocessed shader src
            PreprocessShader(fxName.c_str(), &macroes[0], NULL, *shaderHandle);            
            const u32 preprocessShaderCrc= BMCrC::CreateCrc32((const char*)&shaderHandle->mPreprocessShader[0], (u32)shaderHandle->mPreprocessShader.size());

            //different, recompile
            if(preprocessShaderCrc!=shaderHandle->mPreprocessShaderCrc)
            {
                CompileShader(*shaderHandle, true);
                shaderHandle->mPreprocessShaderCrc = preprocessShaderCrc;
            }
            //same, just create shader
            else
            {
                CreateShader(*shaderHandle);
            }                                                    
        }
        else
        {
            for(u32 macroIdx = 0; macroIdx<desc.ids.size(); macroIdx++)
            {
                const ShaderId& shaderMacroId = desc.ids[macroIdx];

                for (u32 i=0; i<macroSize; i++)
                {
                    ShaderId shaderMacroBitMask = (u64)1<<i;
                    if((shaderMacroId&shaderMacroBitMask)!=0)
                    {
                        macroes[i].Definition = "1";
                    }
                    else
                    {
                        macroes[i].Definition = "0";
                    }
                }        

                ShaderId shaderId = shaderIdx;
                shaderId = shaderId<<32;
                shaderId |= shaderMacroId;

                /*
                 *	
                 */
                ShaderMap::iterator shaderHandleIt = mShaderMap.find(shaderId);

                ShaderHandle* shaderHandle = NULL;
                if(shaderHandleIt==mShaderMap.end())
                {
                    shaderHandle = new ShaderHandle;
                    mShaderMap[shaderId] = shaderHandle;
                }
                else
                {
                    shaderHandle = shaderHandleIt->second;
                }            

                //compare the compiled shader's src with the current preprocessed shader src
                PreprocessShader(fxName.c_str(), &macroes[0], NULL, *shaderHandle);            
                const u32 preprocessShaderCrc= BMCrC::CreateCrc32((const char*)&shaderHandle->mPreprocessShader[0], (u32)shaderHandle->mPreprocessShader.size());

                //different, recompile
                if(preprocessShaderCrc!=shaderHandle->mPreprocessShaderCrc)
                {
                    CompileShader(*shaderHandle, true);
                    shaderHandle->mPreprocessShaderCrc = preprocessShaderCrc;
                }
                //same, just create shader
                else
                {
                    CreateShader(*shaderHandle);
                }     
            }
        }

        RENDER_LOG("finish compile shader %s\n", desc.name.c_str());
    } 

    UpdateShaderCache();
}

ShaderId ShaderMgr::GetShaderTypeId(const char* name)const
{
    for(u32 i=0; i<mShaderDescs.size(); i++)
    {
        if(mShaderDescs[i].name==name)
        {
            return (u64)i<<32;
        }
    }
    return InvalidShaderTypeId;
}

ShaderId ShaderMgr::GetShaderMacroMask(const char* typeName, const char* macroName)const
{
    for(u32 i=0; i<mShaderDescs.size(); i++)
    {
        const ShaderDesc& shaderDesc = mShaderDescs[i];
        if(shaderDesc.name==typeName)
        {            
            const std::vector<std::string>& definitions = shaderDesc.definitions;
            for(u32 macroIdx=0; macroIdx<definitions.size(); macroIdx++)
            {
                if(definitions[macroIdx]==macroName)                                
                {
                    return (ShaderId)1<<macroIdx;
                }
            }
        }
    }

    return InvalidShaderMacroId;
}

ShaderId ShaderMgr::GetShaderMacroMask(const ShaderId& typeId, const char* macroName)const
{
    u32 typeIdx = typeId>>32;
    assert(typeIdx<mShaderDescs.size());
    const ShaderDesc& shaderDesc = mShaderDescs[typeIdx];
    const TArray<BMStr>& definitions = shaderDesc.definitions;
    for (u32 i=0; i<definitions.size(); i++)
    {
        if(definitions[i]==macroName)
        {
            return (ShaderId)1<<i;
        }
    }
    return InvalidShaderMacroId;
}

const ShaderHandle* ShaderMgr::GetShader(const ShaderId& id)const
{
    typedef stdext::hash_map<ShaderId, ShaderHandle*> ShaderMap;
    typedef ShaderMap::const_iterator ShaderMapIt;
    ShaderMapIt result = mShaderMap.find(id);
    return result==mShaderMap.end()?NULL:result->second;
}



void ShaderMgr::ParseShaderDesc(const BMStr& descPath, ShaderDesc& shaderDesc)
{
    TiXmlDocument xmlDoc;
    bool result = xmlDoc.LoadFile(descPath);            
    assert(result);

    TiXmlElement *RootElement = xmlDoc.RootElement();        

    for(TiXmlElement* ele_it = RootElement->FirstChildElement(); ele_it; ele_it = (TiXmlElement*)ele_it->NextSibling())
    {
        if(strcmp(ele_it->Value(), "ShaderMacro")==0)
        {
            const char* macroName = ele_it->FirstChild()->Value();
            shaderDesc.definitions.push_back(std::string(macroName));
        }
        else if (strcmp(ele_it->Value(), "ShaderNation")==0)
        {
            std::vector<std::vector<ShaderId>> shaderCombinations;

            ParseShaderNation(ele_it, shaderDesc);
        }   
    }
}


namespace
{
    void ConstructShaderId(const TArray<TArray<ShaderId>>& src, TArray<ShaderId>& dst)
    {
        u32 idTotalSize = 1;
        for(u32 i=0; i<src.size(); i++)
        {
            idTotalSize*=src[i].size();
        }
        dst.resize(idTotalSize);

        for(u32 arrayIdx=0, baseDevider=1; arrayIdx<src.size(); arrayIdx++)
        {
            baseDevider*=src[arrayIdx].size();
            u32 cycleSize = idTotalSize/baseDevider;
            for(u32 eleIdx=0; eleIdx<idTotalSize; eleIdx++)
            {
                u32 macroIdx=(eleIdx/cycleSize)%src[arrayIdx].size();
                dst[eleIdx]|=src[arrayIdx][macroIdx];
            }
        }
    }
}

void ShaderMgr::ParseShaderNation(TiXmlElement* shaderNation, ShaderDesc& shaderDesc)
{
    TArray<TArray<ShaderId>> idNation;
    for(TiXmlNode* shaderProvince=shaderNation->FirstChild(); shaderProvince; shaderProvince=shaderProvince->NextSibling())
    {
        TArray<ShaderId> idProvince;
        for(TiXmlNode* shaderCity=shaderProvince->FirstChild();shaderCity; shaderCity=shaderCity->NextSibling())
        {     
            ShaderId shaderId = 0;
            std::string macros = shaderCity->FirstChild()->Value();
            StrTokenizer token(macros, ", ");
            TArray<BMStr> subStrings;
            token.GetSubStr(subStrings);
            for(u32 i=0; i<subStrings.size(); i++)
            {
                const BMStr& macroStr = subStrings[i];
                ShaderId shaderBitMask = shaderDesc.GetMacroBigMask(macroStr);
#if SHADER_ASSERT_ON_ERROR==1
                assert(shaderBitMask!=InvalidShaderId);
#endif
                shaderId|=shaderBitMask;
            }
            idProvince.push_back(shaderId);
        }
        idNation.push_back(idProvince);
    }
    ConstructShaderId(idNation, shaderDesc.ids);
}

void ShaderMgr::ParseShaderProvince(TiXmlElement* shaderProvince, ShaderDesc& shaderDesc, std::vector<ShaderId>& ids)
{

}

void ShaderMgr::ApplyShader(const ShaderHandle* shaderHandle)const
{
    DEVICEPTR->SetPixelShader(shaderHandle->mPixelShader);
    DEVICEPTR->SetVertexShader(shaderHandle->mVertexShader);
}

void ShaderMgr::ApplyShader(const ShaderId& shaderId)const
{
   const ShaderHandle* shaderHandle = GetShader(shaderId);
   ApplyShader(shaderHandle);
}


ShaderId ShaderDesc::GetMacroBigMask(const std::string& macro)
{
    if(macro=="")
    {
        return 0;           
    }

    TArray<BMStr>::iterator result = std::find(definitions.begin(), definitions.end(), macro);
    if(result == definitions.end())
    {
        return InvalidShaderId;
    }
    else
    {
        sword bias = result - definitions.begin();
        return (u64)1<<bias;
    }    
}

namespace
{
    std::wstring ShaderFullPath;
    const wchar_t* kShaderPath = L"..\\Data\\Shader\\";

    const char* kVSEntry = "MainVS";
    const char* kPSEntry = "MainPS";

    const char* VSProfile3 = "vs_3_0";
    const char* PSProfile3 = "ps_3_0";

    void GetFullShaderPath(const wchar_t* str)
    {       
        ShaderFullPath = L"..\\Engine\\Shader\\";
        ShaderFullPath += str;
    }
}

bool ShaderMgr::CompileShader(
                   const wchar_t* path, 
                   const D3DXMACRO* defines, 
                   LPD3DXINCLUDE includes,                    
                   DWORD flags,
                   /*
                    *	output
                    */
                   PixelShaderPtr& pixelShader,
                   VertexShaderPtr& vertexShader,                   
                   TArray<u8>& vsCode,
                   TArray<u8>& psCode
                   )
{
    /*
     *	pixel shader compile
     */
    const char* psEntry = kPSEntry;

    GetFullShaderPath(path);

    //if fail, buffer is still NULL, so not necessary to release buffer
    //if succeed, we need to release before return
    ID3DXBuffer* buffer = NULL;
    //if fail, we need to release before return
    //if succeed, errorMsg is still NULL, so not necessary to release buffer
    ID3DXBuffer* errorMsg = NULL;

    if(SUCCEEDED(D3DXCompileShaderFromFile(ShaderFullPath.c_str(), defines, includes, psEntry, PSProfile3, 0, &buffer, &errorMsg, NULL))==false)
    {
        //logout errors
        LogToDebug((const char*)errorMsg->GetBufferPointer());
        errorMsg->Release(); 
        assert(0);
        return false;
    }	    

    const bool psResult = SUCCEEDED( DEVICEPTR->CreatePixelShader(static_cast<DWORD*>(buffer->GetBufferPointer()), &pixelShader) );

    //record compiled shader
    const u32 psShaderSize = buffer->GetBufferSize();
    psCode.resize(psShaderSize);
    memcpy(&psCode[0], buffer->GetBufferPointer(), psShaderSize);

    //release buffer
    buffer->Release();
    
    assert(psResult);

    /*
     *	vertex shader compile
     */
    const char* vsEntry = kVSEntry;

    if(SUCCEEDED(D3DXCompileShaderFromFile(ShaderFullPath.c_str(), defines, includes, vsEntry, VSProfile3, 0, &buffer, &errorMsg, NULL))==false)
    {
        //logout errors
        LogToDebug((const char*)errorMsg->GetBufferPointer());
        errorMsg->Release(); 
        assert(0);
        return false;
    }	 

    const bool vsResult = SUCCEEDED( DEVICEPTR->CreateVertexShader(static_cast<DWORD*>(buffer->GetBufferPointer()), &vertexShader) );
    
    //record compiled shader
    const u32 vsShaderSize = buffer->GetBufferSize();
    vsCode.resize(vsShaderSize);
    memcpy(&vsCode[0], buffer->GetBufferPointer(), vsShaderSize);

    //release buffer
    buffer->Release();

    assert(vsResult);

    return true;
}

bool ShaderMgr::PreprocessShader(const wchar_t* path, const D3DXMACRO* defines, LPD3DXINCLUDE includes, ShaderHandle& shaderHandle)
{
    GetFullShaderPath(path);

    //if fail, buffer is still NULL, so not necessary to release buffer
    //if succeed, we need to release before return
    ID3DXBuffer* buffer = NULL;
    //if fail, we need to release before return
    //if succeed, errorMsg is still NULL, so not necessary to release buffer
    ID3DXBuffer* errorMsg = NULL;

    HRESULT hr = D3DXPreprocessShaderFromFile(ShaderFullPath.c_str(), defines, includes, &buffer, &errorMsg);        

    if(SUCCEEDED(hr)==false)
    {
        //logout errors
        LogToDebug((const char*)errorMsg->GetBufferPointer());
        errorMsg->Release(); 
        assert(0);
        return false;
    }

    const u32 shaderSize = buffer->GetBufferSize();
    shaderHandle.mPreprocessShader.resize(shaderSize);
    memcpy(&shaderHandle.mPreprocessShader[0], buffer->GetBufferPointer(), shaderSize);

    return true;

}

bool ShaderMgr::CompileShader(ShaderHandle& shaderHandle, bool recordCompiledResult/*=false*/)
{
    //if fail, buffer is still NULL, so not necessary to release buffer
    //if succeed, we need to release before return
    ID3DXBuffer* buffer = NULL;
    //if fail, we need to release before return
    //if succeed, errorMsg is still NULL, so not necessary to release buffer
    ID3DXBuffer* errorMsg = NULL;

    /*
     *	pixel shader
     */
    HRESULT hr = D3DXCompileShader((LPCSTR)&shaderHandle.mPreprocessShader[0], shaderHandle.mPreprocessShader.size(), NULL, NULL, kPSEntry, PSProfile3, 0, &buffer, &errorMsg, NULL);
    if(SUCCEEDED(hr)==false)
    {
        //logout errors
        LogToDebug((const char*)errorMsg->GetBufferPointer());
        errorMsg->Release(); 
        assert(0);
        return false;
    }

    if(recordCompiledResult)
    {
        const u32 shaderSize = buffer->GetBufferSize();
        shaderHandle.mPSCompiledShader.resize(shaderSize);
        const void* bufferAddr = buffer->GetBufferPointer();
        memcpy(&shaderHandle.mPSCompiledShader[0], bufferAddr, shaderSize);
    }

    //const bool psResult = SUCCEEDED( DEVICEPTR->CreatePixelShader(static_cast<DWORD*>(buffer->GetBufferPointer()), &shaderHandle.mPixelShader) );
    const bool psResult = SUCCEEDED( DEVICEPTR->CreatePixelShader((DWORD*)(&shaderHandle.mPSCompiledShader[0]), &shaderHandle.mPixelShader) );
    assert(psResult);

    /*
     *	vertex shader
     */

    hr = D3DXCompileShader((LPCSTR)&shaderHandle.mPreprocessShader[0], shaderHandle.mPreprocessShader.size(), NULL, NULL, kVSEntry, VSProfile3, 0, &buffer, &errorMsg, NULL);
    if(SUCCEEDED(hr)==false)
    {
        //logout errors
        LogToDebug((const char*)errorMsg->GetBufferPointer());
        errorMsg->Release(); 
        assert(0);
        return false;
    }

    if(recordCompiledResult)
    {
        const u32 shaderSize = buffer->GetBufferSize();
        shaderHandle.mVSCompiledShader.resize(shaderSize);
        memcpy(&shaderHandle.mVSCompiledShader[0], buffer->GetBufferPointer(), shaderSize);
    }
    
    const bool vsResult = SUCCEEDED( DEVICEPTR->CreateVertexShader(static_cast<DWORD*>(buffer->GetBufferPointer()), &shaderHandle.mVertexShader) );
    assert(vsResult);

    return true;
}

u64 StrRadix16ToU64(const wchar_t* value)
{
    BMStrW wValue = value;
    BMStr sValue;
    WStrToStr(wValue, sValue);
    u32 size = sValue.size();
    u64 result = 0;
    for (s32 i=0;i<size; i++)
    {
        result*=16;
        const char& v = sValue[i];
        if(v<='9')
        {
            result+=v-'0';
        }
        else 
        {
            assert(v<='f'&&v>='a');
            result+=v-'a'+9;
        }        
    }
    return result;
}
void ShaderMgr::LoadShaderCache()
{
    const wchar_t* shaderCacheFiles = L"..\\Engine\\ShaderCache\\*.*";
    const wchar_t* shaderCachePath = L"..\\Engine\\ShaderCache\\";
    std::vector<std::wstring> fileNames;

    WIN32_FIND_DATA stData; 
    HANDLE hFind = FindFirstFile(shaderCacheFiles, &stData); 
    if (hFind  == INVALID_HANDLE_VALUE)  
    {
        return;
    }

    do 
    {        
        if(StrCmpW(stData.cFileName, L".")==0 || StrCmpW(stData.cFileName, L"..")==0)
        {
            continue;
        }

        fileNames.push_back(stData.cFileName);        

    } while (FindNextFile(hFind, &stData));

    const u32 fileCount = fileNames.size();
    for(u32 i=0;i<fileCount; i++)
    {
        BMStrW path = shaderCachePath;
        path+=fileNames[i];
        HANDLE fileHandle = CreateFileW(path.c_str(), FILE_READ_DATA, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

        //id
        const wchar_t* fileName = fileNames[i].c_str();
        u64 intId = StrRadix16ToU64(fileName);

        //content
        LARGE_INTEGER sizeOfFile;
        sizeOfFile.QuadPart = 0ll;
        GetFileSizeEx(fileHandle, &sizeOfFile);
        const u64 fileSize = sizeOfFile.QuadPart;

        TArray<u8>& content = mShaderCache[intId];
        content.resize((u32)fileSize);

        u32 bytesRead = 0;

        BOOL result = ReadFile(fileHandle, &content[0], (u32)fileSize, &bytesRead, 0);
        assert(result!=0);
    }

    //fill shader map
    typedef ShaderCacheContent::const_iterator ShaderCacheIt;
    ShaderCacheIt it = mShaderCache.begin();
    ShaderCacheIt end = mShaderCache.end();
    for (;it!=end;it++)
    {
        const ShaderId& shaderId = it->first;        
        const TArray<u8>& content = it->second;
        
        u32 desc[3];
        u32* u32Addr = (u32*)&content[0];
        memcpy(desc, u32Addr, sizeof(desc));

        u32* preprocessShaderCrc = desc;
        u32* vsSize = desc+1;
        u32* psSize = desc+2;

        ShaderHandle* shaderHandle=NULL;
        ShaderMapIt result = mShaderMap.find(shaderId);
        if(result==mShaderMap.end())
        {
            shaderHandle = new ShaderHandle;
            mShaderMap[shaderId] = shaderHandle;            
        }
        else
        {
            shaderHandle = result->second;
        }

        shaderHandle->mPreprocessShaderCrc = *preprocessShaderCrc;
        shaderHandle->mVSCompiledShader.resize(*vsSize);
        memcpy(&shaderHandle->mVSCompiledShader[0], &content[sizeof(desc)], *vsSize);

        shaderHandle->mPSCompiledShader.resize(*psSize);
        memcpy(&shaderHandle->mPSCompiledShader[0], &content[sizeof(desc)+*vsSize], *psSize);
    }
}

/*
 *	store shader compile result
 */
void ShaderMgr::UpdateShaderCache()
{
    const wchar_t* shaderCachePath = L"..\\Engine\\ShaderCache\\";

    ShaderMapIt it = mShaderMap.begin();
    ShaderMapIt end = mShaderMap.end();

    wchar_t shaderIdName[96];
    for(;it!=end;it++)
    {
        //generate file name
        const ShaderId& shaderIt = it->first;
        _ui64tow(shaderIt,shaderIdName,16);
        BMStrW cachePath = shaderCachePath;
        cachePath+=shaderIdName;

        //open create file
        HANDLE fileHandle = CreateFile(cachePath.c_str(), FILE_WRITE_DATA, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        assert(fileHandle!=INVALID_HANDLE_VALUE);

        /*
         *write file	
         */
        //calc file size
        //src_crc:4byte
        // vs size:4byte
        // ps size:4byte
        const ShaderHandle& shaderHandle = *(it->second);
        const u32 vsSize = shaderHandle.mVSCompiledShader.size();
        const u32 psSize = shaderHandle.mPSCompiledShader.size();
        u32 desc[3] = {shaderHandle.mPreprocessShaderCrc, vsSize, psSize};
        u32 fileSize = sizeof(desc)+vsSize+psSize;

        //desc
        u32 sizeWritten=0;
        WriteFile(fileHandle, desc, sizeof(desc), &sizeWritten, 0);
        assert(sizeof(desc)==sizeWritten);

        //vs
        WriteFile(fileHandle, &shaderHandle.mVSCompiledShader[0], vsSize, &sizeWritten, 0);
        assert(sizeWritten==vsSize);

        //ps
        WriteFile(fileHandle, &shaderHandle.mPSCompiledShader[0], psSize, &sizeWritten, 0);
        assert(sizeWritten==psSize);

        BOOL closeResult = CloseHandle(fileHandle);
        assert(closeResult!=0);               
    } 
}

bool ShaderMgr::CreateShader(ShaderHandle& shaderHandle)
{
    HRESULT hr = DEVICEPTR->CreatePixelShader((DWORD*)(&shaderHandle.mPSCompiledShader[0]), &shaderHandle.mPixelShader);
    const bool psResult = SUCCEEDED(hr );
    assert(psResult);

    hr = DEVICEPTR->CreateVertexShader((DWORD*)(&shaderHandle.mVSCompiledShader[0]), &shaderHandle.mVertexShader);
    const bool vsResult = SUCCEEDED( hr );
    assert(vsResult);

    return true;    
}