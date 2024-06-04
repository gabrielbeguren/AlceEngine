#pragma once

#include "../Sample.hpp"

using namespace alce;

namespace SampleScene
{
	class Ground : public GameObject
	{
	public:

		Ground();

		void Init();

		void Start();

		void Update();

	private:

		Rigidbody2DPtr rigidbody2d;

	};
	typedef std::shared_ptr<Ground> GroundPtr;
}