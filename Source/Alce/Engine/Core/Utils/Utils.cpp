#include "Utils.hpp"

void alce::Shell(std::string cmd)
{
    #ifdef COMPILED_IN_WINDOWS
        cmd = "powershell " + cmd;
    #endif

    system(cmd.c_str());
}

alce::String alce::OS()
{
    #ifdef COMPILED_IN_WINDOWS
        return "WINDOWS";
    #endif
    #ifdef COMPILED_IN_LINUX    
        return "LINUX";
    #endif
    #ifdef COMPILED_IN_MACOS
        return "MACOS";
    #endif
}

alce::String alce::GenerateUUID() 
{
    static std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
    static std::uniform_int_distribution<> dis(0, 15);
    static std::uniform_int_distribution<> dis2(8, 11);

    std::stringstream ss;
    int i;
    ss << std::hex;

    for (i = 0; i < 8; i++) ss << dis(gen);
    ss << "-";
    for (i = 0; i < 4; i++) ss << dis(gen);
    ss << "-4";
    for (i = 0; i < 3; i++) ss << dis(gen);
    ss << "-";
    ss << dis2(gen);
    for (i = 0; i < 3; i++) ss << dis(gen);
    ss << "-";
    for (i = 0; i < 12; i++) ss << dis(gen);
    
    return alce::String(ss.str());
}

alce::String alce::FormatString(String format, List<String> values)
{
    if(values.Length() == 0) return format;

	sf::String res = "";
	auto chain = format.Split("{}");
	int i = 0;

	for(auto& str: chain)
	{
		res += str.ToSFMLString() + values.Get(i).ToSFMLString();
		i++;
	}

	return alce::String(res);
}

alce::String alce::ConcatString(List<String> strings, String join)
{
    sf::String str = "";

	for (int i = 0; i < strings.Length(); i++)
	{
		str += strings[i].ToSFMLString();

		if (i != strings.Length() - 1) str += join.ToSFMLString();
	}

	return alce::String(str);
}