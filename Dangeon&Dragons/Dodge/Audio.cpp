#include "Audio.h"

void Audio::Load()
{
    SF_INFO sfInfo;
    SNDFILE* sndFile = sf_open(path, SFM_READ, &sfInfo);
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
}

Audio::Audio(const char* title, const char* path)
{
    copyStr(title, this->title);
    copyStr(path, this->path);
    Load();

    alGenSources(1, &source);
    alSourcei(source, AL_BUFFER, buffer);
}

void Audio::Play()
{
    alSourcePlay(source);
}

char* Audio::GetTitle()
{
    return title;
}

char* Audio::GetPath()
{
    return path;
}

Audio::~Audio()
{

}

bool Audio::operator==(const Audio& other) const
{
    return other.source == source && other.buffer == buffer 
        && !strcmp(other.title, title) && !strcmp(other.path, path);
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

        copyStr(other.title, title);
        copyStr(other.path, path);
    }
    return *this;
}
