#pragma once

#include "../Json/Json.hpp"

#define Storage alce::STORAGE::Instance()

namespace alce
{
    class STORAGE
    {
    public:

        static STORAGE& Instance()
        {
            static STORAGE _storage;
            return _storage;
        }

        void SetJson(String name, Json data);

        void SetString(String name, String data);

        void SetStringList(String name, List<String> data);

        void SetJsonList(String name, List<Json> data);

        Json GetJson(String name);

        String GetString(String name);

        List<String> GetStringList(String name);

        List<Json> GetJsonList(String name);

        void Delete(String name);

        void Clear();

    private:

        friend class CORE;

        void Init()
        {
            Folder storageFolder("./Storage/");
            if(!storageFolder.Exists()) storageFolder.Create();

            File indexFile("./Storage/index.json");
            Json indexJson;

            if(!indexFile.Exists())
            {
                currentFile = GenerateUUID();
                indexJson.Set("fileIds", List<String>({currentFile.ToAnsiString() + ":true"}));
                indexJson.Set("fileMap", List<String>({}));

                indexJson.SaveAsFile("index", "./Storage/");
                fileIds.Set(currentFile, true);
            }
            else
            {
                indexJson.FromFile("./Storage/index.json");

                for(auto& obj: indexJson.GetStringList("fileMap"))
                {
                    auto name = obj.Split(":")[0];
                    auto id = obj.Split(":")[1];
                    fileMap.Set(name, id);
                }

                for(auto& file: indexJson.GetStringList("fileIds"))
                {
                    auto id = file.Split(":")[0];
                    auto current = file.Split(":")[1];

                    fileIds.Set(id, current.ToBoolean());

                    if(current == true) 
                        currentFile = id;
                }
                
            }

            indexJson.SaveAsFile("index", "./Storage/");
        }

        bool IndexFileExists()
        {
            File index("./Storage/index.json");
            return index.Exists();
        }

        void RestoreIndexFile()
        {
            List<String> _fileIds;

            for(auto& v: fileIds)
            {
                _fileIds.Add(v.first.ToAnsiString() + ":" + (v.second == true ? "true" : "false"));
            }

            List<String> _fileMap;
            
            for(auto& v: fileMap)
            {
                _fileMap.Add(v.first.ToAnsiString() + ":" + v.second.ToAnsiString());
            }

            Json indexJson;
            indexJson.Set("fileIds", _fileIds);
            indexJson.Set("fileMap", _fileMap);
            indexJson.SaveAsFile("index", "./Storage/");
        }

        void SetData(String name, Json tempJson, const std::function<void(Json&)>& setDataCallback);

        Dictionary<String, String> fileMap;
        Dictionary<String, bool> fileIds;

        String currentFile;

        size_t limit = 10 * 1024 * 1024;

        STORAGE() { };

    };
}