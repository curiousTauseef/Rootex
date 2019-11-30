#include "audio_source.h"

#include "audio_system.h"
#include "static_audio_buffer.h"
#include "streaming_audio_buffer.h"

AudioSource::AudioSource(bool isStreaming)
    : m_IsStreaming(isStreaming)
    , m_IsLooping(false)
{
	AudioSystem::GetSingleton()->registerInstance(this);
	AL_CHECK(alGenSources(1, &m_SourceID));
}

AudioSource::~AudioSource()
{
	AudioSystem::GetSingleton()->deregisterInstance(this);
	AL_CHECK(alDeleteSources(1, &m_SourceID));
}

void AudioSource::setLooping(bool enabled)
{
	m_IsLooping = enabled;
	AL_CHECK(alSourcei(m_SourceID, AL_LOOPING, enabled));
}

void AudioSource::queueNewBuffers()
{
	// Empty
}

void AudioSource::play()
{
	AL_CHECK(alSourcePlay(m_SourceID));
}

bool AudioSource::isLooping()
{
	return m_IsLooping;
}

ALuint AudioSource::getSourceID()
{
	return m_SourceID;
}

StaticAudioSource::StaticAudioSource(StaticAudioBuffer* audio)
    : AudioSource(false)
    , m_StaticAudio(audio)
{
	AL_CHECK(alSourcei(m_SourceID, AL_BUFFER, audio->getBuffer()));
}

StaticAudioSource::~StaticAudioSource()
{
	// TODO: Remove StaticAudioSource from being tracked in AudioSystem
	AudioSystem::GetSingleton()->deregisterInstance(this);
}

StreamingAudioSource::StreamingAudioSource(StreamingAudioBuffer* audio)
    : AudioSource(true)
    , m_StreamingAudio(audio)
{
	AL_CHECK(alSourceQueueBuffers(m_SourceID, m_StreamingAudio->getBufferQueueLength(), m_StreamingAudio->getBuffers()));
}

StreamingAudioSource::~StreamingAudioSource()
{
	AudioSystem::GetSingleton()->deregisterInstance(this);
}

void StreamingAudioSource::setLooping(bool enabled)
{
	m_IsLooping = enabled;
}

void StreamingAudioSource::queueNewBuffers()
{
	int numUsedUp;
	AL_CHECK(alGetSourcei(m_SourceID, AL_BUFFERS_PROCESSED, &numUsedUp));
	
	if (numUsedUp > 0)
	{
		AL_CHECK(alSourceUnqueueBuffers(m_SourceID, numUsedUp, m_StreamingAudio->getBuffers()));
		m_StreamingAudio->loadNewBuffers(numUsedUp, isLooping());
		AL_CHECK(alSourceQueueBuffers(m_SourceID, numUsedUp, m_StreamingAudio->getBuffers()));

		static ALint val;
		AL_CHECK(alGetSourcei(m_SourceID, AL_SOURCE_STATE, &val));
		if (val != AL_PLAYING)
		{
			AL_CHECK(alSourcePlay(m_SourceID));
		}
	}
}