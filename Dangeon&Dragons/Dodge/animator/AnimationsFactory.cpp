#include "AnimationsFactory.h"

std::shared_ptr<VertexAnimation> AnimationsFactory::CreateVertexAnimation(
    const char* title, 
    int frameRate, bool repeat, bool stopOnEnd, 
    std::shared_ptr<IGameObject> object, std::vector<std::pair<int, std::vector<Coord>>> frames)
{
    return std::make_shared<VertexAnimation>(title, frameRate, repeat, stopOnEnd, object.get(), frames);
}

std::shared_ptr<SpriteAnimation> AnimationsFactory::CreateSpriteAnimation(
    const char* title, const char* folder, int frameRate, 
    Window* window, bool revere, std::vector<FrameSound> frameSounds)
{
    return std::make_shared<SpriteAnimation>(
        title, folder, frameRate, window, revere, frameSounds
    );
}

std::shared_ptr<SpriteAnimation> AnimationsFactory::CreateSpriteAnimation(
    const char* title, Coord pos, Size size, const char* folder, 
    int frameRate, Window* window, bool revere, std::vector<FrameSound> frameSounds)
{
    return std::make_shared<SpriteAnimation>(
        title, pos, size, folder, frameRate, window, revere, frameSounds
    );
}

std::shared_ptr<SpriteAnimation> AnimationsFactory::CreateSpriteAnimation(
    const char* title, std::vector<Image> sprites, int frameRate, 
    Window* window, bool revere, std::vector<FrameSound> frameSounds)
{
    return std::make_shared<SpriteAnimation>(
        title, sprites, frameRate, window, revere, frameSounds
    );
}

std::shared_ptr<SpriteAnimation> AnimationsFactory::CreateSpriteAnimation(
    const char* title, Coord pos, Size size, std::vector<Image> sprites, 
    int frameRate, Window* window, bool revere, std::vector<FrameSound> frameSounds)
{
    return std::make_shared<SpriteAnimation>(
        title, pos, size, sprites, frameRate, window, revere, frameSounds
    );
}
