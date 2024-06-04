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

		void OnImpact(GameObject* other);

		void OnImpactEnd(GameObject* other);

		void Update();

	private:

		CameraPtr camera;
		Rigidbody2DPtr rigidbody2d;
		SpriteRendererPtr spriteRenderer;
		Animation2dPtr animation;
		Raycast2DPtr leftRaycast2d;
		Raycast2DPtr rightRaycast2d;

		float velocity;
		bool grounded;
	};
	typedef std::shared_ptr<Player> PlayerPtr;
}