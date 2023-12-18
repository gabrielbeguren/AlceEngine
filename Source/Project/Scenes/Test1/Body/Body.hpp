#pragma once

#include "../Test1.hpp"

using namespace alce;

namespace Test1Scene
{
	class Body : public GameObject
	{
	public:

		Body();

		void Init();

		void Start();

		void Update();

	private: 

	 	Rigidbody2DPtr rb2d;
        SpriteRendererPtr sr;
        CameraPtr camera;
        ParticleSystemPtr ps;
        Raycast2DPtr raycast;
        Animation2dPtr animation;

	};
	typedef std::shared_ptr<Body> BodyPtr;
}