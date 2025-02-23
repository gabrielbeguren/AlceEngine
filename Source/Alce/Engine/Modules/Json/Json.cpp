#include "Json.hpp"

using namespace alce;

bool Json::FromString(String json) 
{
    document.Parse(json.ToAnsiString().c_str());

    if (document.HasParseError()) 
    {
        return false;
    }

    return true;
}

bool alce::Json::FromFile(String path)
{
    File file(path);

    if(!file.Exists()) return false;

    return FromString(file.Read());
}

String Json::Get(String key)
{
    rapidjson::Value& value = document[key.ToAnsiString().c_str()];
    String stringValue = "";

    if(value.IsString()) stringValue = String(value.GetString());
    else if(value.IsInt()) stringValue = String(value.GetInt());
    else if(value.IsFloat()) stringValue = String(value.GetFloat());
    else if(value.IsDouble()) stringValue = String(value.GetDouble());
    else if(value.IsBool()) stringValue = String(value.GetBool());
    else if(value.IsNull()) throw exception::json::NullMemberException("<?> Here -> alce::Json::Get(alce::String key)\n<!> Reason -> Null member");
    else throw exception::json::UnsupportedTypeException("<?> Here -> alce::Json::Get(alce::String key)\n<!> Reason -> Unsupported data type");

    return stringValue;
}

Json Json::GetJson(String key)
{
    Json jsonResult;

    if (document.HasMember(key.ToAnsiString().c_str()) && document[key.ToAnsiString().c_str()].IsObject())
    {
        jsonResult.document.CopyFrom(document[key.ToAnsiString().c_str()], jsonResult.document.GetAllocator());
    }

    return jsonResult;
}

List<String> Json::GetStringList(String key) 
{
    List<String> result;
    
    if (document.HasMember(key.ToAnsiString().c_str()) && document[key.ToAnsiString().c_str()].IsArray()) 
    {
        const rapidjson::Value& array = document[key.ToAnsiString().c_str()];
        for (rapidjson::SizeType i = 0; i < array.Size(); i++) 
        {
            if (array[i].IsString()) 
            {
                result.Add(String(array[i].GetString()));
            } 
            else 
            {
                throw exception::json::UnsupportedTypeException("<?> Here -> alce::Json::GetStringList(alce::String key)\n<!> Reason -> Array contains non-string elements");
            }
        }
    } 
    else 
    {
        throw exception::json::NullMemberException("<?> Here -> alce::Json::GetStringList(alce::String key)\n<!> Reason -> Key not found or not an array");
    }
    
    return result;
}

List<Json> Json::GetJsonList(String key) 
{
    List<Json> result;
    
    if (document.HasMember(key.ToAnsiString().c_str()) && document[key.ToAnsiString().c_str()].IsArray()) 
    {
        const rapidjson::Value& array = document[key.ToAnsiString().c_str()];
        for (rapidjson::SizeType i = 0; i < array.Size(); i++) 
        {
            if (array[i].IsObject()) 
            {
                Json jsonItem;
                jsonItem.document.CopyFrom(array[i], jsonItem.document.GetAllocator());
                result.Add(jsonItem);
            } 
            else 
            {
                throw exception::json::UnsupportedTypeException("<?> Here -> alce::Json::GetJsonList(alce::String key)\n<!> Reason -> Array contains non-object elements");
            }
        }
    } 
    else 
    {
        throw exception::json::NullMemberException("<?> Here -> alce::Json::GetJsonList(alce::String key)\n<!> Reason -> Key not found or not an array");
    }
    
    return result;
}

void Json::Set(String key, String value)
{
    auto& allocator = document.GetAllocator();

    rapidjson::Value _value(value.ToAnsiString().c_str(), allocator);

    if(document.HasMember(key.ToAnsiString().c_str()))
    {
        document[key.ToAnsiString().c_str()] = _value;
    }
    else
    {
        rapidjson::Value _key(key.ToAnsiString().c_str(), allocator);
        document.AddMember(_key, _value, allocator);
    }
}

void Json::Set(String key, Json value)
{
    auto& allocator = document.GetAllocator();

    if(document.HasMember(key.ToAnsiString().c_str()))
    {
        rapidjson::Value& existingValue = document[key.ToAnsiString().c_str()];

        if (existingValue.IsObject() && value.document.IsObject())
        {
            for(auto& member : value.document.GetObject())
            {
                existingValue[member.name] = member.value;
            }
        }
    }
    else
    {
        rapidjson::Value _key(key.ToAnsiString().c_str(), allocator);
        rapidjson::Value copyOfValue(value.document, allocator); 
        document.AddMember(_key, copyOfValue, allocator);
    }
}

void Json::Set(String key, List<String> value)
{
    auto& allocator = document.GetAllocator();

    if (document.HasMember(key.ToAnsiString().c_str()))
    {
        rapidjson::Value& existingValue = document[key.ToAnsiString().c_str()];

        if (existingValue.IsArray())
        {
            existingValue.Clear();

            for(auto& element : value)
            {
                rapidjson::Value jsonElement(element.ToAnsiString().c_str(), allocator);
                existingValue.PushBack(jsonElement, allocator);
            }
        }
        else
        {
            existingValue.SetArray();

            for(auto& element : value)
            {
                rapidjson::Value jsonElement(element.ToAnsiString().c_str(), allocator);
                existingValue.PushBack(jsonElement, allocator);
            }
        }
    }
    else
    {
        rapidjson::Value _key(key.ToAnsiString().c_str(), allocator);
        rapidjson::Value jsonArray(rapidjson::kArrayType);

        for (auto& element : value)
        {
            rapidjson::Value jsonElement(element.ToAnsiString().c_str(), allocator);
            jsonArray.PushBack(jsonElement, allocator);
        }

        document.AddMember(_key, jsonArray, allocator);
    }
}

void Json::Set(String key, List<Json> value)
{
    auto& allocator = document.GetAllocator();

    if (document.HasMember(key.ToAnsiString().c_str()))
    {
        rapidjson::Value& existingValue = document[key.ToAnsiString().c_str()];

        if (existingValue.IsArray())
        {
            existingValue.Clear();

            for (auto& element : value)
            {
                rapidjson::Value jsonObject(rapidjson::kObjectType);
                jsonObject.CopyFrom(element.document, allocator);
                existingValue.PushBack(jsonObject, allocator);
            }
        }
        else
        {
            existingValue.SetArray();

            for (auto& element : value)
            {
                rapidjson::Value jsonObject(rapidjson::kObjectType);
                jsonObject.CopyFrom(element.document, allocator);
                existingValue.PushBack(jsonObject, allocator);
            }
        }
    }
    else
    {
        rapidjson::Value _key(key.ToAnsiString().c_str(), allocator);
        rapidjson::Value jsonArray(rapidjson::kArrayType);

        for (auto& element : value)
        {
            rapidjson::Value jsonObject(rapidjson::kObjectType);
            jsonObject.CopyFrom(element.document, allocator);
            jsonArray.PushBack(jsonObject, allocator);
        }

        document.AddMember(_key, jsonArray, allocator);
    }
}

bool Json::Has(String key)
{
    return document.HasMember(key.ToAnsiString().c_str());
}

void Json::Delete(String key) 
{
    if (document.HasMember(key.ToAnsiString().c_str())) 
    {
        document.RemoveMember(key.ToAnsiString().c_str());
    } 
    else 
    {
        throw exception::json::NullMemberException("<?> Here -> alce::Json::Delete(alce::String key)\n<!> Reason -> Key not found in the JSON object");
    }
}

void Json::Clear()
{
    document.RemoveAllMembers();
}

bool Json::IsValid()
{
    if(document.HasParseError()) return false;

    return true;
}

String Json::ToString()
{
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);

    return String(buffer.GetString());
}

String Json::ToPrettyString()
{
    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);

    return String(buffer.GetString());
}

File Json::SaveAsFile(String name, String path)
{
    path += name + ".json";

    File file(path);
    if(!file.Exists()) file.Create();

    file.Write(ToPrettyString());

    return file;
}