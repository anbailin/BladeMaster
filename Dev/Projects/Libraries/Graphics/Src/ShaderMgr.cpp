#include "GraphicsPrivate.h"
#include "ShaderMgr.h"
#include "Shlwapi.h"

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
            PixelShaderPtr ps;
            VertexShaderPtr vs;
            CompileShader(fxName.c_str(), &macroes[0], NULL, 0, ps, vs);

            ShaderId shaderId = shaderIdx;
            shaderId = shaderId<<32;            
            ShaderHandle* shaderHandle = new ShaderHandle;
            mShaderMap[shaderId] = shaderHandle;
            shaderHandle->mPixelShader = ps;
            shaderHandle->mVertexShader = vs;
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

                PixelShaderPtr ps;
                VertexShaderPtr vs;
                CompileShader(fxName.c_str(), &macroes[0], NULL, 0, ps, vs);

                ShaderId shaderId = shaderIdx;
                shaderId = shaderId<<32;
                shaderId |= shaderMacroId;
                ShaderHandle* shaderHandle = new ShaderHandle;
                mShaderMap[shaderId] = shaderHandle;
                shaderHandle->mPixelShader = ps;
                shaderHandle->mVertexShader = vs;
            }
        }

        RENDER_LOG("finish compile shader %s\n", desc.name.c_str());
    }    
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

ShaderId ShaderMgr::GetShaderMacroId(const char* typeName, const char* macroName)const
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
                   VertexShaderPtr& vertexShader
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
    buffer->Release();

    assert(vsResult);

    return true;
}