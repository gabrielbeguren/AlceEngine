#include "Debug.hpp"
#include <thread>

using namespace alce;

void DEBUG::Persist(bool flag)
{
	persist = flag;

	if(!persist) return;

	if(!debugFolder.Exists()) debugFolder.Create();
	if(!logFile.Exists()) logFile.Create();

	logFile.Clear();
}

//Async task
void _log_task(String str, List<String> values, Folder* debugFolder, File* logFile, String message, std::string time)
{
	if (!debugFolder->Exists()) debugFolder->Create();
	if (!logFile->Exists()) logFile->Create();

	String out = ConcatString({String(time), message}, " >> ");
	logFile->Append(out);
}

void DEBUG::Log(String str, List<String> values, bool persist) 
{
	if(clock.getElapsedTime().asMilliseconds() < waitTime && initialized) return;
	if(!initialized) initialized = true;

	clock.restart();

	std::ostringstream oss, timess;
	auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

	timess << std::put_time(&tm, "(?) [%d/%m/%y %H:%M - %Ss]");
	oss << "\033[32m" << timess.str() << " >> " << "\033[0m\n";
	auto message = FormatString(str, values);

	std::wcout << "\033[32m" << String(timess.str()).ToWideString() 
	<< " >> " << message.ToWideString() << "\033[0m\n";

	if(this->persist || persist)
	{
		bool* _persist = &persist;
		File* _logFile = &logFile;
		Folder* _debugFolder = &debugFolder;

		std::thread task = std::thread([&]() {
			_log_task(str, values, _debugFolder, _logFile, message, timess.str());
		});

		task.join();
	}
}

void DEBUG::Warning(String str, List<String> values, bool persist)
{
	if(clock.getElapsedTime().asMilliseconds() < waitTime && initialized) return;
	if(!initialized) initialized = true;

	clock.restart();

	std::ostringstream oss, timess;
	auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

	timess << std::put_time(&tm, "(!) [%d/%m/%y %H:%M - %Ss]");
	auto message = FormatString(str, values);

	std::wcout << "\033[38;5;214m" << String(timess.str()).ToWideString() 
	<< " >> " << message.ToWideString() << "\033[0m\n";

	if(this->persist || persist)
	{
		bool* _persist = &persist;
		File* _logFile = &logFile;
		Folder* _debugFolder = &debugFolder;

		std::thread task = std::thread([&]() {
			_log_task(str, values, _debugFolder, _logFile, message, timess.str());
		});

		task.join();
	}
}


void DEBUG::ARLMessage(String str, List<String> values)
{
	if(clock.getElapsedTime().asMilliseconds() < waitTime && initialized) return;
	if(!initialized) initialized = true;

	clock.restart();

	std::ostringstream oss, timess;
	auto t = std::time(nullptr);
	auto tm = *std::localtime(&t);

	timess << std::put_time(&tm, "(ARL) [%d/%m/%y %H:%M - %Ss]");
	oss << "\033[35m" << timess.str() << ":" << "\033[0m\n";
	auto message = FormatString(str, values);

	std::wcout << "\033[35m" << String(timess.str()).ToWideString() 
			<< ":\033[93m " << message.ToWideString() << "\033[0m\n";

}

void DEBUG::ARLError(String str, List<String> values)
{
	if(clock.getElapsedTime().asMilliseconds() < waitTime && initialized) return;
	if(!initialized) initialized = true;

	clock.restart();

	std::ostringstream oss, timess;
	auto t = std::time(nullptr);
	auto tm = *std::localtime(&t);

	timess << std::put_time(&tm, "(ARL) [%d/%m/%y %H:%M - %Ss]");
	oss << "\033[35m" << timess.str() << ":" << "\033[0m\n";
	auto message = FormatString(str, values);

	std::wcout << "\033[35m" << String(timess.str()).ToWideString() 
			<< ":\033[91m " << message.ToWideString() << "\033[0m\n";
}