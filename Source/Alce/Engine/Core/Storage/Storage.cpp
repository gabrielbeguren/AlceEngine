#include "Storage.hpp"

using namespace alce;

void STORAGE::Set(String name, Json data)
{
    json.Set(name, data);
    
    loading = true;
    json.SaveAsFile("storage", path);
    loading = false;
}

void STORAGE::Set(String name, String data)
{
    json.Set(name, data);

    loading = true;
    json.SaveAsFile("storage", path);
    loading = false;
}

void STORAGE::Set(String name, List<String> data)
{
    json.Set(name, data);

    loading = true;
    json.SaveAsFile("storage", path);
    loading = false;
}

void STORAGE::Set(String name, List<Json> data)
{
    json.Set(name, data);

    loading = true;
    json.SaveAsFile("storage", path);
    loading = false;
}

Json STORAGE::GetJson(String name)
{
    if(!json.Has(name)) throw exception::json::NullMemberException();
    return json.GetJson(name);
}

String STORAGE::Get(String name)
{
    if(!json.Has(name)) throw exception::json::NullMemberException();
    return json.Get(name);
}

List<String> STORAGE::GetStringList(String name)
{
    if(!json.Has(name)) throw exception::json::NullMemberException();
    return json.GetStringList(name);
}

List<Json> STORAGE::GetJsonList(String name)
{
    if(!json.Has(name)) throw exception::json::NullMemberException();
    return json.GetJsonList(name);
}

void STORAGE::Delete(String name)
{    
    if(!json.Has(name)) throw exception::json::NullMemberException();
    json.Delete(name);

    loading = true;
    json.SaveAsFile("storage", path);
    loading = false;
}

void STORAGE::Clear()
{
    json.Clear();

    loading = true;
    json.SaveAsFile("storage", path);
    loading = false;
}