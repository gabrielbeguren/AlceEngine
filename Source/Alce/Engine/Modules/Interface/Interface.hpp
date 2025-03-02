#pragma once

#include <memory>

#include "../String/String.hpp"
#include "../Generic/Generic.hpp"
#include "../Utils/Utils.hpp"
#include "../Debug/Debug.hpp"
#include "../Color/Color.hpp"
#include "../Component/Component.hpp"

namespace alce
{
    class UIElement : public Object
    {
    public:

        enum PositionType
        {
            Fixed,
            Relative
        };

        UIElement(String id) : id(id)
        {
            this->id = id;
        }

        String GetId()
        {
            return this->id;
        }

        virtual void Init()
        {

        }

        virtual void Start()
        {

        }

        virtual void Render()
        {

        }

        virtual void Update()
        {

        }

        virtual void EventManager(sf::Event& event)
        {

        }

        Vector2 position = Vector2(0, 0);
        Vector2 size = Vector2(1, 1);
        Vector2 padding;

        PositionType positionType = PositionType::Fixed;

        bool enabled = true;
        unsigned int zIndex = 0;

    private:

        friend class Canvas;

        String id;
        Object* owner;

    protected:

        friend class Canvas;

        Transform transform;
    };

    typedef std::shared_ptr<UIElement> UIElementPtr;

    class Canvas : public Component
    {  
    public:

        Canvas();

        void Init();

        void Start();

        void Render();

        void Update();

        void AddElement(UIElementPtr element);

        template<typename T>
        void RemoveElement()
        {
            elements.RemoveIf([](Pair<UIElementPtr, unsigned int*> p) {
                return dynamic_cast<T*>(p.first.get());
            });
        }

        template<typename T>
        T* GetElement()
        {
            for(auto& p: elements)
            {
                if(dynamic_cast<T*>(p.first.get()))
                {
                    return dynamic_cast<T*>(p.first.get());
                }
                return nullptr;
            }
        }

        void EventManager(sf::Event& event);

        bool enabled = true;

    private:

        friend class Scene;

        String id;

        List<Pair<UIElementPtr, unsigned int*>> elements;
        std::unordered_map<unsigned int*, unsigned int> previousValues;

        sf::View* view;
        float* rotation;
        float* scale;

    protected:

        List<String> forbiddenElements;

    };

    typedef std::shared_ptr<Canvas> CanvasPtr;
};