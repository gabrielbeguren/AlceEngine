#pragma once

#include <SFML/Graphics.hpp>

#include "../Exceptions/Exceptions.hpp"
#include "../../../Libs/Libs.hpp"

#define Chrono alce::CHRONO::Instance()

namespace alce
{
    class Time
    {
    public:

        Time();

        Time(float miliseconds);

        Time(Dictionary<String, float> measures);

        Time& Add(Dictionary<String, float> measures);

        Time& AddHours(float hours);

        Time& AddMinutes(float minutes);

        Time& AddSeconds(float seconds);

        Time& AddMiliseconds(float miliseconds);

        float ToHours();

        float ToMinutes();

        float ToSeconds();

        float ToMiliseconds();

        Time& Reset();

        Time operator+(float miliseconds);

        Time operator+(Time time);
        
        void operator+=(float miliseconds);

        void operator+=(Time time);

        Time operator-(float miliseconds);

        Time operator-(Time time);

        void operator-=(float miliseconds);

        void operator-=(Time time);

        bool operator<(float miliseconds);

        bool operator<(Time time);

        bool operator<=(float miliseconds);

        bool operator<=(Time time);

        bool operator>(float miliseconds);

        bool operator>(Time time);

        bool operator>=(float miliseconds);

        bool operator>=(Time time);

        bool operator==(float miliseconds);

        bool operator==(Time time);

    private:

        float ms = 0.0f;

    };

    class CHRONO
    {
    public:

        static CHRONO& Instance()
        {
            static CHRONO time;
            return time;
        }

        Time deltaTime = Time(0.0f);

    private:

        CHRONO() 
        {

        };
    };
}