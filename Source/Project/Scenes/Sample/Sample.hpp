#pragma once

#include "../../../Alce/Alce.hpp"

using namespace alce;

namespace SampleScene
{
	class Sample : public Scene
	{
	public:

		Sample();

		void Init();

		void Start();

	};

	typedef std::shared_ptr<Sample> SamplePtr;
}