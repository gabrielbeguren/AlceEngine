#pragma once

#include "../Sample.hpp"

using namespace alce;

namespace SampleScene
{
	class Player : public GameObject
	{
	public:

		Player();

		void Init();

		void Start();

		void Update();

	};
	typedef std::shared_ptr<Player> PlayerPtr;
}