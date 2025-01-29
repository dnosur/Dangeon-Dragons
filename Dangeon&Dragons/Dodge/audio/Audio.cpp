#include "Audio.h"

void Audio::Load()
{
    SF_INFO sfInfo;
    SNDFILE* sndFile = sf_open(path.c_str(), SFM_READ, &sfInfo);
    if (!sndFile) {
        std::cerr << "Error opening sound file: " << path << std::endl;
        return;
    }

    if (sfInfo.channels > 2) {
        std::cerr << "Unsupported number of channels: " << sfInfo.channels << std::endl;
        sf_close(sndFile);
        return;
    }

    ALenum format = (sfInfo.channels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
    short* bufferData = new short[sfInfo.frames * sfInfo.channels];

    sf_count_t numFrames = sf_readf_short(sndFile, bufferData, sfInfo.frames);
    if (numFrames < 1) {
        std::cerr << "Failed to read samples from sound file: " << path << std::endl;
        sf_close(sndFile);
        delete[] bufferData;
        return;
    }

    sf_close(sndFile);

    alGenBuffers(1, &buffer);

    alBufferData(buffer, format, bufferData, sfInfo.frames * sfInfo.channels * sizeof(short), sfInfo.samplerate);

    delete[] bufferData;
}

Audio::Audio()
{
    title = path = (char*)"Undefined";
    buffer = source = -1;

    volume = .0f;
    loop = false;

    state = AudioStates::FINISHED;
}

Audio::Audio(
    std::string title, std::string path,
    float radius, float volume,
    bool loop
)
{
    this->title = title;
    this->path = path;
    Load();

    state = AudioStates::FINISHED;

    this->loop = loop;
    this->radius = radius;

    alGenSources(1, &source);
    alSourcei(source, AL_BUFFER, buffer);

    SetVolume(volume);
}

void Audio::Play(bool loop)
{
    SetLoop(loop);
    alSourcePlay(source);
}

void Audio::SetVolume(float volume)
{
    this->volume = volume;
    baseVolume = volume;
    alSourcef(source, AL_GAIN, volume);
}

void Audio::SetDistanceVolume(Coord sourcePos, Coord listenerPos)
{
    float distance = CalculateDistance(sourcePos, listenerPos);

    if (distance <= radius)
    {
        volume = baseVolume;
        alSourcef(source, AL_GAIN, volume);
        return;
    }

    float falloffFactor = baseVolume - ((distance - radius) / radius);
    SetVolume(std::max(0.0f, falloffFactor));
}

float Audio::GetVolume()
{
    return volume;
}

void Audio::SetRadius(float radius)
{
    this->radius = radius;
}

float Audio::GetRadius()
{
    return radius;
}

void Audio::SetLoop(bool loop)
{
    this->loop = loop;
    alSourcei(source, AL_LOOPING, loop);
}

bool Audio::GetLoop()
{
    return loop;
}

std::string_view Audio::GetTitle()
{
    return title;
}

std::string_view Audio::GetPath()
{
    return path;
}

AudioStates Audio::GetState()
{
    ALint state;
    alGetSourcei(source, AL_SOURCE_STATE, &state);

    if (state == AL_PLAYING) {
        this->state = AudioStates::PLAYING;
    }

    if (state == AL_STOPPED) {
        this->state = AudioStates::STOPPED;
	}

    if (state == AL_PAUSED) {
        this->state = AudioStates::PAUSED;
	}

    ALint processedBuffers;
    alGetSourcei(source, AL_BUFFERS_PROCESSED, &processedBuffers);

    if (processedBuffers > 0) {
        this->state = AudioStates::FINISHED;
    }

    return this->state;
}

Audio::~Audio()
{
}

bool Audio::operator==(const Audio& other) const
{
    return other.source == source && other.buffer == buffer 
        && other.title == title && other.path == path;
}

bool Audio::operator!=(const Audio& other) const
{
    return !(*this == other);
}

Audio& Audio::operator=(const Audio& other)
{
    if (this != &other) {
        source = other.source;
        buffer = other.buffer;

        title = other.title;
        path = other.path;
    }
    return *this;
}
