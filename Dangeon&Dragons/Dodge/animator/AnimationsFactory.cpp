#include "AnimationsFactory.h"

<<<<<<< Updated upstream
VertexAnimation* AnimationsFactory::CreateVertexAnimation(
    const char* title, 
=======
std::shared_ptr<VertexAnimation> AnimationsFactory::CreateVertexAnimation(
    std::string title, 
>>>>>>> Stashed changes
    int frameRate, bool repeat, bool stopOnEnd, 
    IGameObject* object, std::vector<std::pair<int, std::vector<Coord>>> frames)
{
    return new VertexAnimation(title, frameRate, repeat, stopOnEnd, object, frames);
}

<<<<<<< Updated upstream
SpriteAnimation* AnimationsFactory::CreateSpriteAnimation(
    const char* title, const char* folder, int frameRate, 
=======
std::shared_ptr<SpriteAnimation> AnimationsFactory::CreateSpriteAnimation(
    std::string title, std::string folder, int frameRate, 
>>>>>>> Stashed changes
    Window* window, bool revere, std::vector<FrameSound> frameSounds)
{
    return new SpriteAnimation(title, folder, frameRate, window, revere, frameSounds);
}

<<<<<<< Updated upstream
SpriteAnimation* AnimationsFactory::CreateSpriteAnimation(
    const char* title, Coord pos, Size size, const char* folder, 
=======
std::shared_ptr<SpriteAnimation> AnimationsFactory::CreateSpriteAnimation(
    std::string title, Coord pos, Size size, std::string folder, 
>>>>>>> Stashed changes
    int frameRate, Window* window, bool revere, std::vector<FrameSound> frameSounds)
{
    return new SpriteAnimation(title, pos, size, folder, frameRate, window, revere, frameSounds);
}

<<<<<<< Updated upstream
SpriteAnimation* AnimationsFactory::CreateSpriteAnimation(
    const char* title, std::vector<Image> sprites, int frameRate, 
=======
std::shared_ptr<SpriteAnimation> AnimationsFactory::CreateSpriteAnimation(
    std::string title, std::vector<Image> sprites, int frameRate, 
>>>>>>> Stashed changes
    Window* window, bool revere, std::vector<FrameSound> frameSounds)
{
    return new SpriteAnimation(title, sprites, frameRate, window, revere, frameSounds);
}

<<<<<<< Updated upstream
SpriteAnimation* AnimationsFactory::CreateSpriteAnimation(
    const char* title, Coord pos, Size size, std::vector<Image> sprites, 
=======
std::shared_ptr<SpriteAnimation> AnimationsFactory::CreateSpriteAnimation(
    std::string title, Coord pos, Size size, std::vector<Image> sprites, 
>>>>>>> Stashed changes
    int frameRate, Window* window, bool revere, std::vector<FrameSound> frameSounds)
{
    return new SpriteAnimation(title, pos, size, sprites, frameRate, window, revere, frameSounds);
}
