#pragma once

#include <cwchar>
#include <cstring>
#include <string>
#include <vector>
#include <regex>
#include <ctime>
#include <map>
#include <sstream>
#include <iomanip>
#include <SFML/Graphics.hpp>

#include "../Exceptions/Exceptions.hpp"
#include "../Collections/Collections.hpp"

namespace alce
{
	class String
	{
	public:

		String(const char* cstr)
		{
			this->str = sf::String(cstr);
		}

		String(const wchar_t* cstr)
		{
			this->str = sf::String(cstr);
		}

		String(std::wstring str)
		{
			this->str = sf::String(str);
		}

		String(std::string str)
		{
			this->str = sf::String(str);
		}

		String(sf::String str)
		{
			this->str = str;
		}

		String(size_t size)
		{
			this->str = sf::String(std::to_string(size));
		}

		String(bool boolean)
		{
			boolean ? this->str = sf::String("true") : this->str = sf::String("false");
		}

		String(int integer)
		{
			this->str = sf::String(std::to_string(integer));
		}

		String(long long_int)
		{
			this->str = sf::String(std::to_string(long_int));
		}

		String(double dec)
		{
			this->str = sf::String(std::to_string(dec));
		}

		String(float dec)
		{
			this->str = sf::String(std::to_string(dec));
		}

		String()
		{
			this->str = sf::String("");
		}

		~String()
		{
			this->str.clear();
		}

		sf::String ToSFMLString();

		std::string ToAnsiString();

		std::wstring ToWideString();

		const char* ToCString();

		const wchar_t* ToWCString();

		size_t Length();

		String& Cut(unsigned int start, unsigned int end);

		String GetCut(unsigned int start, unsigned int end);

		String Substr(unsigned int start, unsigned int end);

		String& Insert(unsigned int position, String str);

		String& Clear();

		String& Reverse();

		String GetReversed();

		String& ToUpperCase();

		String GetToUpperCase();

		String& ToLowerCase();

		String GetToLowerCase();

		String& ToUpperCase(unsigned int start, unsigned int end);

		String GetToUpperCase(unsigned int start, unsigned int end);

		String& ToLowerCase(unsigned int start, unsigned int end);

		String GetToLowerCase(unsigned int start, unsigned int end);

		String& Replace(String original, String replace);

		String GetReplace(String original, String replace);

		String& ReplaceInRange(String original, String replace, unsigned int start, unsigned int end);

		String GetReplaceInRange(String original, String replace, unsigned int start, unsigned int end);

		bool Contains(String substr);

		List<String> Split(String separator);

		unsigned int Count(String substr);

		bool IsInteger();

		int ParseInt();

		long ParseLong();

		bool IsFloat();

		float ParseFloat();

		bool IsDouble();

		double ParseDouble();

		bool IsBoolean();

		bool ParseBoolean();

		String& Trim();

		String GetTrim();

		String& PopLast();

		wchar_t First();

		String& PopFirst();

		wchar_t Last();

		bool Matches(String regex);

		std::wstring operator~();

		void operator=(const char* cstr);

		void operator=(const wchar_t* cstr);

		void operator=(std::string& str);

		void operator=(std::wstring& str);

		void operator=(String str);

		void operator=(size_t size);

		void operator=(bool boolean);

		void operator=(int integer);

		void operator=(long long_int);

		void operator=(float dec);

		String operator+(const char* cstr);

		String operator+(const wchar_t* cstr);

		String operator+(std::string& str);

		String operator+(std::wstring& str);

		String operator+(String str);

		String operator+(size_t size);

		String operator+(int integer);

		String operator+(long long_int);

		String operator+(float dec);

		void operator+=(const char* cstr);

		void operator+=(const wchar_t* cstr);

		void operator+=(std::string& str);

		void operator+=(std::wstring& str);

		void operator+=(String str);

		void operator+=(size_t size);

		void operator+=(bool boolean);

		void operator+=(int integer);

		void operator+=(long long_int);

		void operator+=(float dec);

		wchar_t& operator[](unsigned int index);

		bool operator==(const char* cstr);

		bool operator==(const wchar_t* cstr);

		bool operator==(std::string& str);

		bool operator==(std::wstring& str);

		bool operator==(String str);

		bool operator==(size_t size);

		bool operator==(bool boolean);

		bool operator==(int integer);

		bool operator==(long long_int);

		bool operator==(float dec);

		bool operator!=(const char* cstr);

		bool operator!=(const wchar_t* cstr);

		bool operator!=(std::string& str);

		bool operator!=(std::wstring& str);

		bool operator!=(String str);

		bool operator!=(size_t size);

		bool operator!=(bool boolean);

		bool operator!=(int integer);

		bool operator!=(long long_int);

		bool operator!=(float dec);

	private:

		sf::String str;
	};
}