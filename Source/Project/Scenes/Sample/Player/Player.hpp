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

		void SetterManager(String name, String value);

		String GetterManager(String name);

		void Update();


	private:

		CameraPtr camera;
		Rigidbody2DPtr rigidbody2d;
		Animation2dPtr animation;
		Raycast2DPtr leftRaycast2d;
		Raycast2DPtr rightRaycast2d;
		CanvasPtr canvas;

		void AnimationManager();

		float velocity;
		bool grounded;
		bool walking;
		bool jumping;

		String status;
	};
	
	typedef std::shared_ptr<Player> PlayerPtr;
}