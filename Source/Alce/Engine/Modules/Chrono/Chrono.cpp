#include "Chrono.hpp"

using namespace alce;

Time::Time()
{
    ms = 0.0f;
}

Time::Time(float miliseconds)
{
    if (miliseconds < 0.0f)
        throw exception::time::InvalidMeasureValue("<?> Here -> alce::Time::Time(float miliseconds)\n<!> Reason -> Negative value for <miliseconds>");
}

Time::Time(Dictionary<String, float> measures)
{
    Add(measures);
}

Time& Time::Add(Dictionary<String, float> measures)
{
    if (measures.HasKey("hours")) AddHours(measures["hours"]);
    if (measures.HasKey("minutes")) AddMinutes(measures["minutes"]);
    if (measures.HasKey("seconds")) AddSeconds(measures["seconds"]);
    if (measures.HasKey("miliseconds")) AddMiliseconds(measures["miliseconds"]);

    return *this;
}

Time& Time::AddHours(float hours)
{
    if (hours < 0.0f)
        throw exception::time::InvalidMeasureValue("<?> Here -> alce::Time::AddHours(float hours)\n<!> Reason -> Negative value for <hours>");

    ms += hours * 3600000.0f;

    return *this;
}

Time& Time::AddMinutes(float minutes)
{
    if (minutes < 0.0f)
        throw exception::time::InvalidMeasureValue("<?> Here -> alce::Time::AddMinutes(float minutes)\n<!> Reason -> Negative value for <minutes>");

    ms += minutes * 60000.0f;

    return *this;
}

Time& Time::AddSeconds(float seconds)
{
    if (seconds < 0.0f)
        throw exception::time::InvalidMeasureValue("<?> Here -> alce::Time::AddSeconds(float seconds)\n<!> Reason -> Negative value for <seconds>");

    ms += seconds * 1000.0f;

    return *this;
}

Time& Time::AddMiliseconds(float miliseconds)
{
    if (miliseconds < 0.0f)
        throw exception::time::InvalidMeasureValue("<?> Here -> alce::Time::AddMiliseconds(float miliseconds)\n<!> Reason -> Negative value for <miliseconds>");

    ms += miliseconds;

    return *this;
}

float Time::ToHours()
{
    return ms / 3600000.0f;
}

float Time::ToMinutes()
{
    return ms / 60000.0f;
}

float Time::ToSeconds()
{
    return ms / 1000.0f;
}

float Time::ToMiliseconds()
{
    return ms;
}

Time& Time::Reset()
{
    ms = 0.0f;

    return *this;
}

Time Time::operator+(float miliseconds)
{
    if (miliseconds < 0.0f)
        throw exception::time::InvalidMeasureValue("<?> Here -> alce::Time::operator+(float miliseconds)\n<!> Reason -> Negative value for <miliseconds>");

    return Time({
        {"miliseconds", (ms + miliseconds)}
    });
}

Time Time::operator+(Time time)
{
    return Time({
        {"miliseconds", (ms + time.ms)}
    });
}

void Time::operator+=(float miliseconds)
{
    if (miliseconds < 0.0f)
        throw exception::time::InvalidMeasureValue("<?> Here -> alce::Time::operator+(float miliseconds)\n<!> Reason -> Negative value for <miliseconds>");

    ms += miliseconds;
}

void Time::operator+=(Time time)
{
    ms += time.ms;
}

Time Time::operator-(float miliseconds)
{
    float newMs = (ms >= miliseconds) ? (ms - miliseconds) : 0.0f;
    return Time({
        {"miliseconds", newMs}
    });
}

Time Time::operator-(Time time)
{
    float newMs = (ms >= time.ms) ? (ms - time.ms) : 0.0f;
    return Time({
        {"miliseconds", newMs}
    });
}

void Time::operator-=(float miliseconds)
{
    ms = (ms >= miliseconds) ? (ms - miliseconds) : 0.0f;
}

void Time::operator-=(Time time)
{
    ms = (ms >= time.ms) ? (ms - time.ms) : 0.0f;
}

bool Time::operator<(float miliseconds)
{
    return ms < miliseconds;
}

bool Time::operator<(Time time)
{
    return ms < time.ms;
}

bool Time::operator<=(float miliseconds)
{
    return ms <= miliseconds;
}

bool Time::operator<=(Time time)
{
    return ms <= time.ms;
}

bool Time::operator>(float miliseconds)
{
    return ms > miliseconds;
}

bool Time::operator>(Time time)
{
    return ms > time.ms;
}

bool Time::operator>=(float miliseconds)
{
    return ms >= miliseconds;
}

bool Time::operator>=(Time time)
{
    return ms >= time.ms;
}

bool Time::operator==(float miliseconds)
{
    return ms == miliseconds;
}

bool Time::operator==(Time time)
{
    return ms == time.ms;
}
