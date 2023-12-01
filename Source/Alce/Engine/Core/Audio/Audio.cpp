#include "Audio.hpp"

#ifdef __linux__
    #undef Status
#endif

using namespace alce;

#pragma region AudioChannel

void AudioChannel::Add(String name, String file)
{
    if(sounds.HasKey(name))
    {
        Debug.Warning("Audio Channel already contain a sound named {}", {name});
        return;
    }

    auto soundBuffer = Kernel.GetSoundBuffer(file);

    if(soundBuffer == nullptr)
    {
        Debug.Warning("Error loading file {}", {file});
        return;
    }

    SoundPtr sound = std::make_shared<sf::Sound>();
    sound->setVolume(volume);
    sound->setBuffer(*soundBuffer);
    sounds.Set(name, sound);
}

void AudioChannel::Delete(String name)
{
    if(!sounds.HasKey(name))
    {
        Debug.Warning("Audio Channel does not contain sound {}", {name});
        return;
    }

    sounds.RemoveByKey(name);
}

void AudioChannel::Play(String name)
{
    if(!sounds.HasKey(name))
    {
        Debug.Warning("Audio Channel does not contain sound {}", {name});
        return;
    }

    Debug.Log("playing {}", {name});
    sounds[name]->play();
}

void AudioChannel::Pause(String name)
{
    if(!sounds.HasKey(name))
    {
        Debug.Warning("Audio Channel does not contain sound {}", {name});
        return;
    }

    sounds[name]->pause();
}

void AudioChannel::Stop(String name)
{
    if(!sounds.HasKey(name))
    {
        Debug.Warning("Audio Channel does not contain sound {}", {name});
        return;
    }

    sounds[name]->stop();
}

void AudioChannel::SetAttenuation(String name, float attenuation)
{
    if(!sounds.HasKey(name))
    {
        Debug.Warning("Audio Channel does not contain sound {}", {name});
        return;
    }

    sounds[name]->setAttenuation(attenuation);
}

void AudioChannel::SetLoop(String name, bool flag)
{
    if(!sounds.HasKey(name))
    {
        Debug.Warning("Audio Channel does not contain sound {}", {name});
        return;
    }

    sounds[name]->setLoop(flag);
}

void AudioChannel::SetPitch(String name, float pitch)
{
    if(!sounds.HasKey(name))
    {
        Debug.Warning("Audio Channel does not contain sound {}", {name});
        return;
    }

    sounds[name]->setPitch(pitch);
}

void AudioChannel::SetRelativeToListener(String name, bool flag)
{
    if(!sounds.HasKey(name))
    {
        Debug.Warning("Audio Channel does not contain sound {}", {name});
        return;
    }

    sounds[name]->setRelativeToListener(flag);
}

SoundPtr AudioChannel::GetSound(String name)
{
    return sounds.HasKey(name) ? sounds[name] : nullptr;
}

bool AudioChannel::IsPlaying(String name)
{
    if(!sounds.HasKey(name))
    {
        Debug.Warning("Audio Channel does not contain sound {}", {name});
        return false;
    }

    return sounds[name]->getStatus() == sf::SoundSource::Status::Playing;
}

bool AudioChannel::IsPaused(String name)
{
    if(!sounds.HasKey(name))
    {
        Debug.Warning("Audio Channel does not contain sound {}", {name});
        return false;
    }

    return sounds[name]->getStatus() == sf::SoundSource::Status::Paused;
}

bool AudioChannel::IsStopped(String name)
{
    if(!sounds.HasKey(name))
    {
        Debug.Warning("Audio Channel does not contain sound {}", {name});
        return false;
    }

    return sounds[name]->getStatus() == sf::SoundSource::Status::Stopped;
}

float AudioChannel::GetAttenuation(String name)
{
    if(!sounds.HasKey(name))
    {
        Debug.Warning("Audio Channel does not contain sound {}", {name});
        return 0.0f;
    }

    return sounds[name]->getAttenuation();
}

bool AudioChannel::IsLooping(String name)
{
    if(!sounds.HasKey(name))
    {
        Debug.Warning("Audio Channel does not contain sound {}", {name});
        return false;
    }

    return sounds[name]->getLoop();
}

float AudioChannel::GetPitch(String name)
{
    if(!sounds.HasKey(name))
    {
        Debug.Warning("Audio Channel does not contain sound {}", {name});
        return 0.0f;
    }

    return sounds[name]->getPitch();
}

bool AudioChannel::IsRelativeToListener(String name)
{
    if(!sounds.HasKey(name))
    {
        Debug.Warning("Audio Channel does not contain sound {}", {name});
        return false;
    }

    return sounds[name]->isRelativeToListener();
}

float AudioChannel::GetVolume()
{
    return volume;
}

void AudioChannel::SetVolume(float volume)
{
    if(volume < 0.0f)
    {
        Debug.Warning("Volume cannot be less than 0");
        return;
    }

    for(auto& it: sounds)
    {
        it.second->setVolume(volume);
    }
}

bool AudioChannel::IsPlaying()
{
    return sounds.GetValueList().Filter([](SoundPtr sound) {
        return sound->getStatus() == sf::SoundSource::Status::Playing;
    }).Length() != 0;
}

void AudioChannel::Clear()
{
    sounds.Clear();
}

#pragma endregion

#pragma region AudioPipeline

void AUDIO::AddChannel(String name)
{
    if(channels.HasKey(name))
    {
        Debug.Warning("Audio Pipeline already contains channel {}", {name});
        return;
    }

    channels.Set(name, std::make_shared<AudioChannel>());
}

void AUDIO::DeleteChannel(String name)
{
    if(!channels.HasKey(name))
    {
        Debug.Warning("Audio Pipeline does not contain channel {}", {name});
        return;
    }

    channels.RemoveByKey(name);
}

AudioChannelPtr AUDIO::GetChannel(String name)
{
    if(!channels.HasKey(name))
    {
        Debug.Warning("Audio Pipeline does not contain channel {}", {name});
        return nullptr;
    }

    return channels[name];
}

#pragma endregion