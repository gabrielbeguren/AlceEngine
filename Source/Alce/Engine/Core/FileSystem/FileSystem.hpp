#pragma once

#include <fstream>
#include <cstdio>
#include <sys/stat.h>
#include <filesystem>

#include "../Utils/Utils.hpp"
#include "../String/String.hpp"
#include "../Exceptions/Exceptions.hpp"

namespace alce
{
	class File
	{
	public:

		File(String path);

		bool Exists();

		void Create();

		void Delete();

		String Read();

		void Write(String str);

		void Append(String str);

		String GetFullPath();

		void Clear();

	private:

		String path;

	};

	class Folder
	{
	public:

		Folder(String path);

		bool Exists();

		void Create();

		void Delete();

		String GetFullPath();

	private:

		String path;
	};

	bool FolderExists(String path);

    bool FileExists(String path);
}