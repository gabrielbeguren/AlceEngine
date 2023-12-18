#pragma once

#include "../NewTest.hpp"

using namespace alce;

namespace NewTestScene
{
	class test : public GameObject
	{
	public:

		test();

		void Init();

		void Start();

		void Update();

	private:

		CameraPtr camera;
		ParticleSystemPtr ps;
	};
	typedef std::shared_ptr<test> testPtr;
}