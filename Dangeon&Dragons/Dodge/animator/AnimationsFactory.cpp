#include "AnimationsFactory.h"

std::shared_ptr<VertexAnimation> AnimationsFactory::CreateVertexAnimation(
    std::string title, 
    int frameRate, bool repeat, bool stopOnEnd, 
    std::shared_ptr<IGameObject> object, std::vector<std::pair<int, std::vector<Coord>>> frames)
{
    return std::make_shared<VertexAnimation>(title, frameRate, repeat, stopOnEnd, object.get(), frames);
}

std::shared_ptr<SpriteAnimation> AnimationsFactory::CreateSpriteAnimation(
    std::string title, std::string folder, int frameRate, 
    Window* window, bool revere, std::vector<FrameSound> frameSounds)
{
    return std::make_shared<SpriteAnimation>(
        title, folder, frameRate, window, revere, frameSounds
    );
}

std::shared_ptr<SpriteAnimation> AnimationsFactory::CreateSpriteAnimation(
    std::string title, Coord position, Size size, std::string folder, 
    int frameRate, Window* window, bool revere, std::vector<FrameSound> frameSounds)
{
    return std::make_shared<SpriteAnimation>(
        title, position, size, folder, frameRate, window, revere, frameSounds
    );
}

std::shared_ptr<SpriteAnimation> AnimationsFactory::CreateSpriteAnimation(
    std::string title, std::vector<Image> sprites, int frameRate, 
    Window* window, bool revere, std::vector<FrameSound> frameSounds)
{
    return std::make_shared<SpriteAnimation>(
        title, sprites, frameRate, window, revere, frameSounds
    );
}

std::shared_ptr<SpriteAnimation> AnimationsFactory::CreateSpriteAnimation(
    std::string title, Coord position, Size size, std::vector<Image> sprites, 
    int frameRate, Window* window, bool revere, std::vector<FrameSound> frameSounds)
{
    return std::make_shared<SpriteAnimation>(
        title, position, size, sprites, frameRate, window, revere, frameSounds
    );
}
