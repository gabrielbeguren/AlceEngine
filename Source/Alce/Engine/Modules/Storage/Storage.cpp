#include "Storage.hpp"

using namespace alce;

void STORAGE::SetData(String name, Json tempJson, const std::function<void(Json&)>& setDataCallback)
{
    if(!IndexFileExists()) 
    {
        RestoreIndexFile();
    }

    Json fileJson;
    String fileId;

    if(fileMap.HasKey(name)) 
    {
        fileId = fileMap.Get(name);
        fileJson.FromFile("./Storage/" + fileId.ToAnsiString() + ".json");
    } 
    else 
    {
        fileJson.FromFile("./Storage/" + currentFile.ToAnsiString() + ".json");
        fileId = currentFile;
    }

    Json indexJson;
    indexJson.FromFile("./Storage/index.json");
    auto _fileMap = indexJson.GetStringList("fileMap");
    auto _fileIds = indexJson.GetStringList("fileIds");

    if(fileJson.ToString().GetBytes() + tempJson.ToString().GetBytes() > limit) 
    {
        _fileIds.FindAndRemove(fileId.ToAnsiString() + ":true");
        _fileIds.Add(fileId.ToAnsiString() + ":false");
        currentFile = GenerateUUID();
        _fileIds.Add(currentFile.ToAnsiString() + ":true");
        fileJson.Clear();
        fileId = currentFile;
    }

    _fileMap.FindAndRemove(name.ToAnsiString() + ":" + fileId.ToAnsiString());
    _fileMap.Add(name.ToAnsiString() + ":" + fileId.ToAnsiString());
    setDataCallback(fileJson);
    fileMap.Set(name, fileId);

    fileJson.SaveAsFile(fileId, "./Storage/");
    indexJson.Set("fileMap", _fileMap);
    indexJson.Set("fileIds", _fileIds);
    indexJson.SaveAsFile("index", "./Storage/");
}


void STORAGE::SetJson(String name, Json data)
{
    SetData(name, data, [&](Json& fileJson){
        fileJson.Set(name, data);
    });
}

void STORAGE::SetString(String name, String data)
{
    Json tempJson;
    tempJson.Set("temp", data);

    SetData(name, tempJson, [&](Json& fileJson){
        fileJson.Set(name, data);
    });
}

void STORAGE::SetStringList(String name, List<String> data)
{
    Json tempJson;
    tempJson.Set("check", data);

    SetData(name, tempJson, [&](Json& fileJson){
        fileJson.Set(name, data);
    });
}

void STORAGE::SetJsonList(String name, List<Json> data)
{
    Json tempJson;
    tempJson.Set("check", data);

    SetData(name, tempJson, [&](Json& fileJson){
        fileJson.Set(name, data);
    });
}

Json STORAGE::GetJson(String name)
{
    String fileId = fileMap.Get(name);

    Json fileJson;
    fileJson.FromFile("./Storage/" + fileId.ToAnsiString() + ".json");
    return fileJson.GetJson(name);
}

String STORAGE::GetString(String name)
{
    String fileId = fileMap.Get(name);

    Json fileJson;
    fileJson.FromFile("./Storage/" + fileId.ToAnsiString() + ".json");
    return fileJson.Get(name);
}

List<String> STORAGE::GetStringList(String name)
{
    String fileId = fileMap.Get(name);

    Json fileJson;
    fileJson.FromFile("./Storage/" + fileId.ToAnsiString() + ".json");
    return fileJson.GetStringList(name);
}

List<Json> STORAGE::GetJsonList(String name)
{    
    String fileId = fileMap.Get(name);

    Json fileJson;
    fileJson.FromFile("./Storage/" + fileId.ToAnsiString() + ".json");
    return fileJson.GetJsonList(name);
}

void STORAGE::Delete(String name)
{
    if(!IndexFileExists()) 
    {
        RestoreIndexFile();
    }

    if(!fileMap.HasKey(name)) return;

    String fileId = fileMap.Get(name);

    Json fileJson;
    fileJson.FromFile("./Storage/" + fileId.ToAnsiString() + ".json");
    fileJson.Delete(name);
    fileJson.SaveAsFile(fileId, "./Storage/");

    Json indexJson;
    indexJson.FromFile("./Storage/index.json");

    auto _fileMap = indexJson.GetStringList("fileMap");
    _fileMap.FindAndRemove(name.ToAnsiString() + ":" + fileId.ToAnsiString());
    indexJson.Set("fileMap", _fileMap);
    indexJson.SaveAsFile("index", "./Storage/");
}

void STORAGE::Clear()
{
    if(!IndexFileExists()) 
    {
        RestoreIndexFile();
    }

    Json indexJson;
    indexJson.FromFile("./Storage/index.json");

    auto _fileIds = indexJson.GetStringList("fileIds");

    for(auto& id: _fileIds)
    {
        File f("./Storage/" + id.Split(":")[0].ToAnsiString() + ".json");
        f.Delete();
    }

    fileMap.Clear();
    currentFile = GenerateUUID();

    indexJson.Set("fileIds", List<String>({currentFile.ToAnsiString() + ":true"}));
    indexJson.Set("fileMap", List<String>({}));

    indexJson.SaveAsFile("index", "./Storage/");
}