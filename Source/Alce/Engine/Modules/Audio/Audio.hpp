#pragma once

#include <SFML/Audio.hpp>
#include "../Core/Core.hpp"

#define Audio alce::AUDIO::Instance()

namespace alce
{
    typedef std::shared_ptr<sf::Sound> SoundPtr;

    class AudioChannel
    {
    public:

        void Add(String name, String file);

        void Delete(String name);

        void Play(String name);

        void Pause(String name);

        void Stop(String name);

        void SetAttenuation(String name, float attenuation);

        void SetLoop(String name, bool flag = true);

        void SetPitch(String name, float pitch);

        void SetRelativeToListener(String name, bool flag = true);

        SoundPtr GetSound(String name);

        bool IsPlaying(String name);

        bool IsPaused(String name);

        bool IsStopped(String name);

        float GetAttenuation(String name);

        bool IsLooping(String name);

        float GetPitch(String name);

        bool IsRelativeToListener(String name);

        float GetVolume();

        void SetVolume(float volume);

        bool IsPlaying();

        void Clear();

    private:

        friend class AUDIO;

        Dictionary<String, SoundPtr> sounds;
        float volume = 15.0f;
    };

    typedef std::shared_ptr<AudioChannel> AudioChannelPtr;

    class AUDIO
    {
    public:

        static AUDIO& Instance()
	    {
		    static AUDIO ap;
		    return ap;
	    }

        void AddChannel(String name);

        void DeleteChannel(String name);

        AudioChannelPtr GetChannel(String name);

    private:

        Dictionary<String, AudioChannelPtr> channels;

        AUDIO() { };
    };
}