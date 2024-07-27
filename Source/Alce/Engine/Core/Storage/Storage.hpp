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

        void Set(String name, Json data);

        void Set(String name, String data);

        void Set(String name, List<String> data);

        void Set(String name, List<Json> data);

        Json GetJson(String name);

        String Get(String name);

        List<String> GetStringList(String name);

        List<Json> GetJsonList(String name);

        void Delete(String name);

        void Clear();

        bool IsLoading()
        {
            return loading;
        }

    private:

        friend class KERNEL;

        void Init()
        {
            Folder storageFolder(path);

            if(!storageFolder.Exists())
                storageFolder.Create();

            File file(path + "storage.json");
            
            if(!file.Exists())
                json.SaveAsFile("storage", path);

            json.FromFile(path + "storage.json");
        }

        String path = "./Storage/";

        Json json;

        bool loading = false;

        STORAGE() { };
    };
}