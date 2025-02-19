#pragma once

#include <iostream>
#include <memory>
#include <unordered_map>
#include <functional>
#include <stdexcept>

#include "../String/String.hpp"

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
            std::string _key = key.ToAnsiString();

            if (creators.find(_key) != creators.end()) 
            {
                throw std::runtime_error("Creator with key '" + _key + "' already exists.");
            }
            creators[_key] = std::move(creator);
        }

        template <typename T>
        std::shared_ptr<T> Create(String key) 
        {
            std::string _key = key.ToAnsiString();

            auto it = creators.find(_key);
            if (it == creators.end()) 
            {
                throw std::runtime_error("No creator registered for key '" + _key + "'.");
            }
            return std::static_pointer_cast<T>(it->second());
        }

    private:

        FactorySingleton() = default;

        FactorySingleton(const FactorySingleton&) = delete;
        FactorySingleton& operator=(const FactorySingleton&) = delete;

        std::unordered_map<std::string, Creator> creators;
    };

}