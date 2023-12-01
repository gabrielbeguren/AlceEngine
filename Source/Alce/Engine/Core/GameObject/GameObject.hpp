#pragma once

#include "../Component/Component.hpp"
#include "../Debug/Debug.hpp"

namespace alce
{
    class GameObject;
    typedef std::shared_ptr<GameObject> GameObjectPtr;

    class GameObject : public Generic
    {
    public:

        GameObject();

        ~GameObject();

        void AddTag(String tag);

        void RemoveTag(String tag);

        bool HasTag(String tag);

        List<String> GetTags()
        {
            return tags;
        }

        unsigned int sortingLayer = 0;

        void Destroy();

        void AddComponent(ComponentPtr component);

        template<typename T>
        T* GetComponent()
        {
            for (auto& component : components)
            {
                if (dynamic_cast<T*>(component.get()))
                {
                    return dynamic_cast<T*>(component.get());
                }
            }
            return nullptr;
        }

        template<typename T>
        void RemoveComponent()
        {
            components.RemoveIf([](ComponentPtr component) {
                return dynamic_cast<T*>(component.get());
            });
        }

        List<ComponentPtr> GetComponents();

        void SetParent(GameObjectPtr gameObject);

        void SetParent(GameObject* gameObject);

        void DetachParent();

        GameObjectPtr GetParent();

        bool HasParent() 
        {
            return parent != nullptr;
        }

        template<typename Predicate>
        List<GameObjectPtr> FindParents(Predicate predicate)
        {
            List<GameObjectPtr> foundParents = {};
            GameObjectPtr currentParent = parent;

            while(currentParent != nullptr)
            {
                if(predicate(currentParent))
                {
                    foundParents.Add(currentParent);
                }

                currentParent = currentParent->parent;
            }

            return foundParents;
        }

        void Render();

        void DebugRender();

        virtual void OnCollisionEnter(GameObject* other)
        {

        }

        virtual void OnCollisionExit(GameObject* other)
        {

        }

        virtual void OnImpact(GameObject* other)
        {

        }

        bool enabled = true;

    private:

        friend class Scene;

        List<unsigned int> layers;
        List<String> tags;
        List<ComponentPtr> components;
        Dictionary<String, Vector2Ptr> cardinals;

        GameObjectPtr parent = nullptr;

        bool destroyed = false;

    protected:

        List<String> forbiddenComponents;
    };
}