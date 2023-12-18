#pragma once

#include "../Test1.hpp"

using namespace alce;

namespace Test1Scene
{
	class Floor : public GameObject
	{
	public:

		Floor();

		void Init();

		void Start();

		void Update();

	private:

	  Rigidbody2DPtr rb2d;

	};
	typedef std::shared_ptr<Floor> FloorPtr;
}