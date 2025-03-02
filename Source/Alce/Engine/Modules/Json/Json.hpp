#pragma once

#include "../../../Libs/Libs.hpp"
#include "../String/String.hpp"
#include "../Collections/Collections.hpp"
#include "../FileSystem/FileSystem.hpp"

namespace alce 
{
    class Json 
    {
    public:

        Json() 
        {
            document.SetObject();
        }

        Json(String json) 
        {
            document.SetObject();
            FromString(json);
        }

        Json(const Json& other) 
        {
            document.CopyFrom(other.document, document.GetAllocator());
        }

        bool FromString(String json);

        bool FromFile(String path);

        String Get(String key);

        Json GetJson(String key);

        List<String> GetStringList(String key);

        List<Json> GetJsonList(String key);

        void Set(String key, String value);

        void Set(String key, Json value);

        void Set(String key, List<String> value);

        void Set(String key, List<Json> value);

        bool Has(String key);

        void Delete(String key);

        void Clear();

        bool IsValid();

        String ToString();

        String ToPrettyString();

        File SaveAsFile(String name, String path = "./");

        Json& operator=(const Json& other) 
        {
            if (this != &other) 
            {
                document.CopyFrom(other.document, document.GetAllocator());
            }

            return *this;
        }
    
    private:

        rapidjson::Document document;

    };

    typedef std::shared_ptr<Json> JsonPtr;
}