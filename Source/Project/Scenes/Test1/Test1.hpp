#pragma once

#include "../../../Alce/Alce.hpp"

using namespace alce;

namespace Test1Scene
{
	class Test1 : public Scene
	{
	public:

		Test1();

		void Init();

		void Start();

	};

	typedef std::shared_ptr<Test1> Test1Ptr;
}