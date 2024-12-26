#include "AnimationsFactory.h"

VertexAnimation* AnimationsFactory::CreateVertexAnimation(
    const char* title, 
    int frameRate, bool repeat, bool stopOnEnd, 
    IGameObject* object, boost::container::vector<std::pair<int, boost::container::vector<Coord>>> frames)
{
    return new VertexAnimation(title, frameRate, repeat, stopOnEnd, object, frames);
}

SpriteAnimation* AnimationsFactory::CreateSpriteAnimation(
    const char* title, const char* folder, int frameRate, 
    Window* window, bool revere, boost::container::vector<FrameSound> frameSounds)
{
    return new SpriteAnimation(title, folder, frameRate, window, revere, frameSounds);
}

SpriteAnimation* AnimationsFactory::CreateSpriteAnimation(
    const char* title, Coord pos, Size size, const char* folder, 
    int frameRate, Window* window, bool revere, boost::container::vector<FrameSound> frameSounds)
{
    return new SpriteAnimation(title, pos, size, folder, frameRate, window, revere, frameSounds);
}

SpriteAnimation* AnimationsFactory::CreateSpriteAnimation(
    const char* title, boost::container::vector<Image> sprites, int frameRate, 
    Window* window, bool revere, boost::container::vector<FrameSound> frameSounds)
{
    return new SpriteAnimation(title, sprites, frameRate, window, revere, frameSounds);
}

SpriteAnimation* AnimationsFactory::CreateSpriteAnimation(
    const char* title, Coord pos, Size size, boost::container::vector<Image> sprites, 
    int frameRate, Window* window, bool revere, boost::container::vector<FrameSound> frameSounds)
{
    return new SpriteAnimation(title, pos, size, sprites, frameRate, window, revere, frameSounds);
}
