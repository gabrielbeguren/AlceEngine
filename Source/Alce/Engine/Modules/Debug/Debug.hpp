#pragma once

#include <iostream>
#include <iomanip>
#include <ctime>
#include <stdarg.h>
#include <map>
#include <string>
#include <typeinfo>
#include <cxxabi.h>

#include "../Math/Math.hpp"
#include "../FileSystem/FileSystem.hpp"
#include "../String/String.hpp"

#define Debug DEBUG::Instance()

namespace alce
{
	struct DEBUG
	{
	public:

		static DEBUG& Instance()
		{
			static DEBUG debug_;
			return debug_;
		}

		void Persist(bool flag = true);

		void Log(String str, List<String> values = {}, bool persist = false);

		void Warning(String str, List<String> values = {}, bool persist = false);

		void SetWaitTime(int waitTime)
		{
			if(waitTime < 0) Warning("Debug wait time cannot be less than 0");
			this->waitTime = waitTime;
		}

	private:

		friend class CORE;
		friend class ARL_PROCESSOR;

		void ARLMessage(String str, List<String> values = {});

		void ARLError(String str, List<String> values = {});

		bool initialized = false;
		bool persist = false;
		File logFile = File("Debug/logFile.txt");
		Folder debugFolder = Folder("Debug");

		int waitTime = 16;
		sf::Clock clock;

		DEBUG() { };

		DEBUG(DEBUG const&);

		void operator=(DEBUG const&);
	};
}