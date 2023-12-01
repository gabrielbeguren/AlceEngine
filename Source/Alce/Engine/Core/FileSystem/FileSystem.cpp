#include "FileSystem.hpp"

struct stat sb;

#pragma region File

alce::File::File(alce::String path)
{
	this->path = alce::String(std::filesystem::absolute(path.ToAnsiString()).string());
}

bool alce::File::Exists()
{
	return std::filesystem::exists(path.ToAnsiString());
}

void alce::File::Create()
{
	if (Exists())
	{
		throw exception::filesystem::InvalidOperationException("<?> Here -> alce::File::Create()\n<!> Reason -> The file \"" + path.ToAnsiString() + "\" already exists");
	}

	std::fstream f;

	f.open(path.ToAnsiString(), std::ios::out);

	if (!f) throw exception::filesystem::NullFileException("<?> Here -> alce::File::Create()\n<!> Reason -> Unable to create the file");
}

void alce::File::Delete()
{
	if (!Exists())
	{
		throw exception::filesystem::NullFileException("<?> Here -> alce::File::Delete()\n<!> Reason -> The file \"" + path.ToAnsiString() + "\" do not exists");
	}

	const int res = remove(path.ToCString());
}

alce::String alce::File::Read()
{
	if (!Exists())
    {
        throw exception::filesystem::NullFileException("<?> Here -> alce::File::Read()\n<!> Reason -> The file \"" + path.ToAnsiString() + "\" do not exists");
    }

    std::ifstream file(path.ToAnsiString());

    if (!file)
    {
        return alce::String("");
    }

    std::string fileContent;
    std::string line;

    while(std::getline(file, line))
    {
        fileContent += line + "\n";
    }

    file.close();

    return alce::String(fileContent);
}

void alce::File::Write(alce::String str)
{
	if (!Exists())
	{
		throw exception::filesystem::NullFileException("<?> Here -> alce::File::Write(alce::String str)\n<!> Reason -> The file \"" + path.ToAnsiString() + "\" do not exists");
	}

	std::ofstream file;
	file.open(path.ToAnsiString());

	file << str.ToAnsiString();

	file.close();
}

void alce::File::Append(alce::String str)
{
	if (!Exists())
	{
		throw exception::filesystem::NullFileException("<?> Here -> alce::File::Append(alce::String str)\n<!> Reason -> The file \"" + path.ToAnsiString() + "\" do not exists");
	}

	alce::String prev = Read();
	Write(ConcatString({prev, str}, ""));
}

void alce::File::Clear()
{
	Write("");
}

alce::String alce::File::GetFullPath()
{
	return path;
}

#pragma endregion

#pragma region Folder

alce::Folder::Folder(alce::String path)
{
	this->path = alce::String(std::filesystem::absolute(path.ToAnsiString()).string());
}

bool alce::Folder::Exists()
{
	return std::filesystem::exists(path.ToAnsiString());
}

void alce::Folder::Delete()
{
	if (!Exists())
    {
        throw exception::filesystem::NullFolderException("<?> Here -> alce::Folder::Delete()\n<!> Reason -> The folder \"" + path.ToAnsiString() + "\" do not exists");
    }

    std::filesystem::remove_all(path.ToAnsiString());
}

void alce::Folder::Create()
{
	std::filesystem::create_directory(path.ToAnsiString());
}

alce::String alce::Folder::GetFullPath()
{
	return path;
}

bool alce::FolderExists(String path)
{
    return alce::Folder(path).Exists();
}

bool alce::FileExists(String path)
{
    return alce::File(path).Exists();
}

#pragma endregion