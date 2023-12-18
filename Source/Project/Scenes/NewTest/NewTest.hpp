#pragma once

#include "../../../Alce/Alce.hpp"

using namespace alce;

namespace NewTestScene
{
	class NewTest : public Scene
	{
	public:

		NewTest();

		void Init();

		void Start();

	};

	typedef std::shared_ptr<NewTest> NewTestPtr;
}