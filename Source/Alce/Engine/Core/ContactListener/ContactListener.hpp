#pragma once

#include "../../../Libs/Libs.hpp"
#include "../GameObject/GameObject.hpp"

namespace alce
{
    class ContactListener : public b2ContactListener
    {
    private:

        void BeginContact(b2Contact* contact)
        {
            b2Body* bodyA = contact->GetFixtureA()->GetBody();
            b2Body* bodyB = contact->GetFixtureB()->GetBody();

            GameObject* goA = (GameObject*) bodyA->attachedObject;
            GameObject* goB = (GameObject*) bodyB->attachedObject;

            goA->OnCollisionEnter(goB);
            goB->OnCollisionEnter(goA);
        }

        void EndContact(b2Contact* contact)
        {
            b2Body* bodyA = contact->GetFixtureA()->GetBody();
            b2Body* bodyB = contact->GetFixtureB()->GetBody();

            GameObject* goA = (GameObject*) bodyA->attachedObject;
            GameObject* goB = (GameObject*) bodyB->attachedObject;

            goA->OnCollisionExit(goB);
            goB->OnCollisionExit(goA);
        }
    };

    typedef std::shared_ptr<ContactListener> ContactListenerPtr;
}