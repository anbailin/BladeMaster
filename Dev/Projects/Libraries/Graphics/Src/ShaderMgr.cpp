#include "GraphicsPrivate.h"
#include "ShaderMgr.h"
#include "Shlwapi.h"

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

            TiXmlDocument xmlDoc;
            bool result = xmlDoc.LoadFile(xmlName);            
            assert(result);

            TiXmlElement *RootElement = xmlDoc.RootElement();        

            for(TiXmlElement* ele_it = RootElement->FirstChildElement(); ele_it; ele_it = (TiXmlElement*)ele_it->NextSibling())
            {
                for(TiXmlAttribute* attr_it = ele_it->FirstAttribute(); attr_it; attr_it = attr_it->Next())
                {
                    const char* name = attr_it->Name();

                    if(strcmp("name", name)==0)
                    {
                        shaderDesc.definitions.push_back(attr_it->Value());
                    }
                }     
            }
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
        const u32 shaderSize = 1<<macroSize;

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

        for(u32 macroIdx = 0; macroIdx<shaderSize; macroIdx++)
        {
            std::vector<std::string> macroNames;
            for (u32 i=0; i<macroSize; i++)
            {
                if((macroIdx&(1<<i))==1)
                {
                    macroes[macroIdx].Definition = "1";
                }
                else
                {
                    macroes[macroIdx].Definition = "0";
                }
            }        

            PixelShaderPtr ps;
            VertexShaderPtr vs;
            ShaderLoader::GetInstance()->LoadPixelShader(fxName.c_str(), &macroes[0], NULL, "MainPS", 0, ps);
            ShaderLoader::GetInstance()->LoadVertexShader(fxName.c_str(), &macroes[0], NULL, "MainVS", 0, vs);

            ShaderId shaderId = shaderIdx;
            shaderId = shaderId<<32;
            shaderIdx |= macroIdx;
            ShaderHandle* shaderHandle = new ShaderHandle;
            mShaderMap[shaderId] = shaderHandle;
            shaderHandle->mPixelShader = ps;
            shaderHandle->mVertexShader = vs;
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
                    return (ShaderId)macroIdx;
                }
            }
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



void ShaderMgr::ParseShaderDesc(const std::wstring& shaderPath, const std::wstring& descPath, ShaderDesc& shaderDesc)
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
            for(TiXmlElement* shaderProvince=ele_it->FirstChildElement();shaderProvince; shaderProvince=(TiXmlElement*)shaderProvince->NextSibling())
            {
                
            }
        }
        for(TiXmlAttribute* attr_it = ele_it->FirstAttribute(); attr_it; attr_it = attr_it->Next())
        {
            const char* name = attr_it->Name();

            if(strcmp("name", name)==0)
            {
                shaderDesc.definitions.push_back(attr_it->Value());
            }
        }     
    }
}



void ShaderMgr::ParseShaderNation(TiXmlElement* shaderNation, ShaderDesc& shaderDesc)
{
    TArray<TArray<ShaderId>> idNation;
    for(TiXmlElement* shaderProvince=shaderNation->FirstChildElement(); shaderProvince; shaderProvince=(TiXmlElement*)shaderProvince->NextSibling())
    {
        std::vector<ShaderId> idProvince;
        for(TiXmlNode* shaderCity=shaderProvince->FirstChild();shaderCity; shaderCity=shaderCity->NextSibling())
        {            
            std::string macros = shaderCity->FirstChild()->Value();
            StrTokenizer token(macros, ", ");
            TArray<BMStr> subStrings;
            token.GetSubStr(subStrings);
        }
    }
}

void ShaderMgr::ParseShaderProvince(TiXmlElement* shaderProvince, ShaderDesc& shaderDesc, std::vector<ShaderId>& ids)
{

}


ShaderId ShaderDesc::GetMacroBigMask(const std::string& macro)
{
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