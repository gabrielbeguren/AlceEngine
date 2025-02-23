#pragma once

#include <iostream>
#include <memory>
#include <functional>
#include <stdexcept>

#include "../String/String.hpp"
#include "../Collections/Collections.hpp"
#include "../Debug/Debug.hpp"

#define Factory FactorySingleton::getInstance()

namespace alce
{
    class FactorySingleton 
    {
    public:
        using Creator = std::function<std::shared_ptr<void>()>;

        static FactorySingleton& getInstance() 
        {
            static FactorySingleton instance;
            return instance;
        }

        void RegisterCreator(String key, Creator creator) 
        {
            if (creators.HasKey(key)) 
            {
                Debug.Warning("Creator with key '" + key.ToAnsiString() + "' already exists.");
                return;
            }
            creators.Set(key, std::move(creator));
        }

        template <typename T>
        std::shared_ptr<T> Create(String key) 
        {
            if (!creators.HasKey(key)) 
            {
                Debug.Warning("No creator registered for key '" + key.ToAnsiString() + "'.");
                return nullptr;
            }
            return std::static_pointer_cast<T>(creators.Get(key)());
        }

        bool Has(String key)
        {
            return creators.HasKey(key);
        }

    private:

        friend class ARL_PROCESSOR;
        
        FactorySingleton() = default;

        FactorySingleton(const FactorySingleton&) = delete;
        FactorySingleton& operator=(const FactorySingleton&) = delete;

        Dictionary<String, Creator> creators;
    };

}
