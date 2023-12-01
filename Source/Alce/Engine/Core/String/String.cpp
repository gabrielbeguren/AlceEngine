#include "String.hpp"

sf::String alce::String::ToSFMLString()
{
	return str;
}

std::string alce::String::ToAnsiString()
{
	return str.toAnsiString();
}

std::wstring alce::String::ToWideString()
{
	return str.toWideString();
}

const char* alce::String::ToCString()
{
	return str.toAnsiString().c_str();
}

const wchar_t* alce::String::ToWCString()
{
	return str.toWideString().c_str();
}

size_t alce::String::Length()
{
	return str.getSize();
}

alce::String& alce::String::Cut(unsigned int start, unsigned int end)
{
	alce::String substr1 = this->Substr(0, start - 1);
	alce::String substr2 = this->Substr(end + 1, this->Length());

	this->str = substr1.str + substr2.str;

	return *this;
}

alce::String alce::String::GetCut(unsigned int start, unsigned int end)
{
	alce::String substr1 = this->Substr(0, start - 1);
	alce::String substr2 = this->Substr(end + 1, this->Length());

	alce::String result = substr1 + substr2;

	return result;
}

alce::String alce::String::Substr(unsigned int start, unsigned int end)
{
	return alce::String(this->str.substring(start, (end - start) + 1));
}

alce::String& alce::String::Insert(unsigned int position, String ustr)
{
	this->str.insert(position, ustr.str);

	return *this;
}

alce::String& alce::String::Clear()
{
	this->str.clear();

	return *this;
}

alce::String& alce::String::Reverse()
{
	for(int i = 0; i < str.getSize() / 2; i++)
	{
		std::swap(str[i], str[str.getSize() - i - 1]);
	}

	return *this;
}

alce::String alce::String::GetReversed()
{
	auto copy = alce::String(str);

	return copy.Reverse();
}

alce::String& alce::String::ToUpperCase()
{
	auto _str = str.toWideString();

	std::transform(_str.begin(), _str.end(), _str.begin(), ::toupper);
	str = sf::String(_str);

	return *this;
}

alce::String alce::String::GetToUpperCase()
{
	auto copy = alce::String(str);

	return copy.ToUpperCase();
}

alce::String& alce::String::ToLowerCase()
{
	auto _str = str.toWideString();

	std::transform(_str.begin(), _str.end(), _str.begin(), ::tolower);
	str = sf::String(_str);

	return *this;
}

alce::String alce::String::GetToLowerCase()
{
	auto copy = alce::String(str);

	return copy.ToLowerCase();
}

alce::String& alce::String::ToUpperCase(unsigned int start, unsigned int end)
{
	alce::String substr1 = this->Substr(0, start);
	alce::String substr2 = this->Substr(start, end);
	alce::String substr3 = this->Substr(end, this->Length());

	substr2.ToUpperCase();

	this->str = substr1.str + substr2.str + substr3.str;

	return *this;
}

alce::String alce::String::GetToUpperCase(unsigned int start, unsigned int end)
{
	auto copy = alce::String(str);

	return copy.ToUpperCase(start, end);
}

alce::String& alce::String::ToLowerCase(unsigned int start, unsigned int end)
{
	alce::String substr1 = this->Substr(0, start);
	alce::String substr2 = this->Substr(start, end);
	alce::String substr3 = this->Substr(end, this->Length());

	substr2.ToLowerCase();

	this->str = substr1.str + substr2.str + substr3.str;

	return *this;
}

alce::String alce::String::GetToLowerCase(unsigned int start, unsigned int end)
{
	auto copy = alce::String(str);

	return copy.ToLowerCase(start, end);
}

alce::String& alce::String::Replace(alce::String original, alce::String replace)
{
	for (size_t pos = 0; ; pos += replace.Length())
	{
		pos = str.find(original.str, pos);
		if (pos == std::wstring::npos) break;

		str.erase(pos, original.Length());
		str.insert(pos, replace.str);
	}

	return *this;
}

alce::String alce::String::GetReplace(String original, String replace)
{
	auto copy = alce::String(str);

	return copy.Replace(original, replace);
}

alce::String& alce::String::ReplaceInRange(alce::String original, String replace, unsigned int start, unsigned int end)
{
	String substr1 = Substr(0, start - 1);
	String substr2 = Substr(start, end);
	String substr3 = Substr(end + 1, Length() - 1);

	substr2.Replace(original, replace);

	this->str = ~substr1 + ~substr2 + ~substr3;

	return *this;
}

alce::String alce::String::GetReplaceInRange(alce::String original, alce::String replace, unsigned int start, unsigned int end)
{
	auto copy = alce::String(str);

	return copy.ReplaceInRange(original, replace, start, end);
}

bool alce::String::Contains(String substr)
{
	return wcsstr(str.toWideString().c_str(), substr.str.toWideString().c_str());
}

alce::List<alce::String> alce::String::Split(alce::String separator)
{
	std::vector<alce::String> strings;
	alce::String current_str = "";
	std::wstring _str = str.toWideString();

	for (int i = 0; i < this->Length(); i++)
	{
		if (_str[i] == separator[0])
		{
			bool match = true;

			for (int j = 0; j < separator.Length(); j++)
			{
				if (_str[i + j] != separator[j]) match = false;
			}

			if (match)
			{
				strings.push_back(current_str);
				current_str.Clear();

				i += separator.Length() - 1;
			}
		}
		else if (i == _str.size() - 1)
		{
			current_str.str += _str[i];
			strings.push_back(current_str);
		}
		else
		{
			current_str.str += _str[i];
		}
	}

	return strings;
}

unsigned int alce::String::Count(alce::String substr)
{
	unsigned int i = 0, j = 0, count = 0;
	std::wstring _substr = L"";
	std::wstring _str = str.toWideString();

	while (i < _str.length())
	{
		if (_str[i] == substr[j])
		{
			_substr += _str[i];
			j++;
		}

		if (j == substr.Length() && _substr == ~substr)
		{
			_substr = L"";
			count++;
			j = 0;
		}

		i++;
	}

	return count;
}

bool alce::String::IsInteger() 
{
    alce::String cpy = this->str;

    cpy.Replace("\"", "");
    std::wstring _str = cpy.str.toWideString();

    if (_str.empty() || ((!isdigit(_str[0])) && (_str[0] != '-') && (_str[0] != '+'))) return false;

    wchar_t* p;
    long int result = wcstol(_str.c_str(), &p, 10);

    return !(*p != L'\0'); 
}

int alce::String::ParseInt()
{
	if(!IsInteger()) throw exception::ParseException("<?> Here -> alce::String::ParseInt()\n<!> Reason -> Cannot parse a non integer value to int");

	alce::String copy = alce::String(str);
	copy.Replace("\"", "");

	return std::stoi(copy.ToAnsiString());
}

long alce::String::ParseLong()
{
	if(!IsInteger()) throw exception::ParseException("<?> Here -> alce::String::ParseLong()\n<!> Reason -> Cannot parse a non integer value to long");

	alce::String copy = alce::String(str);
	copy.Replace("\"", "");

	return std::stol(copy.ToAnsiString());
}

bool alce::String::IsFloat()
{
	alce::String copy = alce::String(str);

	copy.Replace("\"", "");

	std::istringstream iss(copy.str);
	float f;
	iss >> std::noskipws >> f;
	
	return iss.eof() && !iss.fail();
}

float alce::String::ParseFloat()
{
	if(!IsFloat()) throw exception::ParseException("<?> Here -> alce::String::ParseFloat()\n<!> Reason -> Cannot parse a non decimal value to float");

	alce::String copy = alce::String(str);
	copy.Replace("\"", "");

	return std::stof(copy.ToAnsiString());
}

bool alce::String::IsDouble()
{
	return IsFloat();
}

double alce::String::ParseDouble()
{
	if(!IsDouble()) throw exception::ParseException("<?> Here -> alce::String::ParseDouble()\n<!> Reason -> Cannot parse a non decimal value to double");

	alce::String copy = alce::String(str);
	copy.Replace("\"", "");

	return std::stod(copy.ToAnsiString());
}

bool alce::String::IsBoolean()
{
	return str == "true" || str == "false" || str == "\"true\"" || str == "\"false\"";
}

bool alce::String::ParseBoolean()
{
	if (!IsBoolean()) throw exception::ParseException("<?> Here -> alce::String::ParseBoolean()\n<!> Reason -> Cannot parse a non boolean value to bool");

	if (str == "true" || str == "\"true\"") return true;

	return false;
}

alce::String& alce::String::Trim()
{
	Replace(" ", "");
	Replace("\t", "");
	Replace("\n", "");

	return *this;
}

alce::String alce::String::GetTrim()
{
	auto copy = alce::String(str);

	return copy.Trim();
}

alce::String& alce::String::PopLast()
{
	this->str = ~Substr(0, Length() - 2);

	return *this;
}

wchar_t alce::String::First()
{
	if(Length() == 0) throw exception::collections::OutOfBoundsException("<?> Here -> alce::String::ParseFirst()\n<!> Reason -> Empty string");

	return str.toWideString()[0];
}

alce::String& alce::String::PopFirst()
{
	this->str = ~Substr(1, Length() - 1);

	return *this;
}

wchar_t alce::String::Last()
{
	return str.toWideString()[Length() - 1];
}

bool alce::String::Matches(String _regex)
{
	std::regex regex(_regex.ToAnsiString());

	return std::regex_match(str.toAnsiString(), regex);
}


std::wstring alce::String::operator~()
{
	return ToWideString();
}

#pragma region operator=

void alce::String::operator=(const char* cstr)
{
	this->str = sf::String(cstr);
}

void alce::String::operator=(const wchar_t* cstr)
{
	this->str = sf::String(cstr);
}

void alce::String::operator=(std::string& str)
{
	this->str = sf::String(str);
}

void alce::String::operator=(std::wstring& str)
{
	this->str = sf::String(str);
}

void alce::String::operator=(alce::String str)
{
	this->str = str.str;
}

void alce::String::operator=(size_t size)
{
	this->str = sf::String(std::to_string(size));
}

void alce::String::operator=(bool boolean)
{
	boolean ? str = sf::String("true") : str = sf::String("false");
}

void alce::String::operator=(int integer)
{
	str = sf::String(std::to_string(integer));
}

void alce::String::operator=(long long_int)
{
	str = sf::String(std::to_string(long_int));
}

void alce::String::operator=(float dec)
{
	str = sf::String(std::to_string(dec));
}

#pragma endregion

#pragma region operator+

alce::String alce::String::operator+(const char* cstr)
{
	return alce::String(this->str + cstr);
}

alce::String alce::String::operator+(const wchar_t* cstr)
{
	return alce::String(this->str + cstr);
}

alce::String alce::String::operator+(std::string& str)
{
	return alce::String(this->str + str);
}

alce::String alce::String::operator+(std::wstring& str)
{
	return alce::String(this->str + str);
}

alce::String alce::String::operator+(alce::String str)
{
	return alce::String(this->str + str.str);
}

alce::String alce::String::operator+(size_t size)
{
	return alce::String(this->str + std::to_string(size));
}

alce::String alce::String::operator+(int integer)
{
	return alce::String(this->str + std::to_string(integer));
}

alce::String alce::String::operator+(long long_int)
{
	return alce::String(this->str + std::to_string(long_int));
}

alce::String alce::String::operator+(float dec)
{
	return alce::String(this->str + std::to_string(dec));
}

#pragma endregion

#pragma region operator+=

void alce::String::operator+=(const char* cstr)
{
	this->str += cstr;
}

void alce::String::operator+=(const wchar_t* cstr)
{
	this->str += cstr;
}

void alce::String::operator+=(std::string& str)
{
	this->str += str;
}

void alce::String::operator+=(std::wstring& str)
{
	this->str += str;
}

void alce::String::operator+=(alce::String str)
{
	this->str += str.str;
}

void alce::String::operator+=(size_t size)
{
	this->str += std::to_string(size);
}

void alce::String::operator+=(bool boolean)
{
	boolean ? this->str += "true" : this->str += "false";
}

void alce::String::operator+=(int integer)
{
	this->str += std::to_string(integer);
}

void alce::String::operator+=(long long_int)
{
	this->str += std::to_string(long_int);
}

void alce::String::operator+=(float dec)
{
	this->str += std::to_string(dec);
}

#pragma endregion

#pragma region operator[]

wchar_t& alce::String::operator[](unsigned int index)
{
	if(index > str.getSize()) 
	{
		throw exception::collections::OutOfBoundsException("<?> Here -> alce::String::operator[](unsigned int index)\n<!> Reason -> Index out of bounds");
	}

	return str.toWideString()[index];
}

#pragma endregion

#pragma region operator==

bool alce::String::operator==(const char* cstr)
{
	return str == cstr;
}

bool alce::String::operator==(const wchar_t* cstr)
{
	return str == cstr;
}

bool alce::String::operator==(std::string& str)
{
	return str == str;
}

bool alce::String::operator==(std::wstring& str)
{
	return str == str;
}

bool alce::String::operator==(alce::String str)
{
	return this->str == str.str;
}

bool alce::String::operator==(size_t size)
{
	if(!IsInteger()) return false;

	return ParseInt() == size;
}

bool alce::String::operator==(bool boolean)
{
	if(boolean && (str == "true" || str == "\"true\"")) return true;

	return false;
}

bool alce::String::operator==(int integer)
{
	if(!IsInteger()) return false;

	return ParseInt() == integer;
}

bool alce::String::operator==(long long_int)
{
	if(!IsInteger()) return false;

	return ParseLong() == long_int;
}

bool alce::String::operator==(float dec)
{
	if(!IsFloat()) return false;

	return ParseFloat() == dec;
}

#pragma endregion

