#include "SpriteAnimation.h"

void SpriteAnimation::LoadSpritesFromFolder()
{
	this->sprites.Clear();

	if (!fs::exists(folder) || !fs::is_directory(folder)) {
		std::cerr << "Directory does not exist: " << folder << std::endl;
		return;
	}

	for (const auto& entry : fs::directory_iterator(folder)) {
		if (fs::is_regular_file(entry.path())) {
			std::string name = std::string(title) + entry.path().filename().string();
			std::cout << "File: " << entry.path() << " " << name << std::endl;
			this->sprites.Load(entry.path().string().c_str(), name.c_str());
		}
	}
}

SpriteAnimation::SpriteAnimation()
{
	window = nullptr;
	folder = nullptr;
	title = (char*)"Undefined";

	rootTile = nullptr;
	currentFrameTitle = nullptr;
	timePassed = .0f;

	frameRate = 0;
	currentSpriteIndex = -1;
	play = pause = repeat = stopOnEnd = reverse = end = false;
}

SpriteAnimation::SpriteAnimation(
	std::string title, std::string folder, int frameRate, 
	Window* window, bool revere, 
	std::vector<FrameSound> frameSounds
)
{
<<<<<<< Updated upstream
	copyStr((char*)title, this->title);
	copyStr((char*)folder, this->folder);
=======
	this->title = title;
	this->folder = folder;
>>>>>>> Stashed changes

	play = pause = repeat = stopOnEnd = end = false;
	currentSpriteIndex = -1;

	this->frameRate = frameRate;
	this->window = window;
	this->reverse = revere;

	timePassed = .0f;

	this->frameSounds.SetFrameSounds(frameSounds);
	LoadSpritesFromFolder();
}

SpriteAnimation::SpriteAnimation(
	std::string title, Coord pos, Size size, 
	std::string folder, int frameRate, Window* window, bool revere,
	std::vector<FrameSound> frameSounds
){
<<<<<<< Updated upstream
	copyStr((char*)title, this->title);
	copyStr((char*)folder, this->folder);
=======
	this->title = title;
	this->folder = folder;
>>>>>>> Stashed changes

	this->pos = pos;
	this->size = size;

	play = pause = repeat = stopOnEnd = end = false;
	currentSpriteIndex = -1;

	this->frameRate = frameRate;
	this->window = window;
	this->reverse = revere;

	timePassed = .0f;

	this->frameSounds.SetFrameSounds(frameSounds);
	LoadSpritesFromFolder();
}

SpriteAnimation::SpriteAnimation(
	std::string title, std::vector<Image> sprites, 
	int frameRate, Window* window, bool revere,
	std::vector<FrameSound> frameSounds)
{
<<<<<<< Updated upstream
	copyStr((char*)title, this->title);
=======
	this->title = title;
>>>>>>> Stashed changes
	SetSprites(sprites);
	folder = nullptr;

	this->frameRate = frameRate;
	this->window = window;
	this->reverse = revere;

	currentSpriteIndex = -1;
	timePassed = .0f;

	play = pause = repeat = stopOnEnd = end = false;

	//this->frameSounds.SetFrameSounds(frameSounds);
	this->sprites.SetImages(sprites);
}

SpriteAnimation::SpriteAnimation(
	std::string title, Coord pos, Size size,
	std::vector<Image> sprites, int frameRate, 
	Window* window, bool revere, std::vector<FrameSound> frameSounds
)
{
<<<<<<< Updated upstream
	copyStr((char*)title, this->title);
=======
	this->title = title;
>>>>>>> Stashed changes
	SetSprites(sprites);

	this->pos = pos;
	this->size = size;

	folder = nullptr;

	this->frameRate = frameRate;
	this->window = window;
	this->reverse = revere;

	currentSpriteIndex = -1;
	timePassed = .0f;

	play = pause = repeat = stopOnEnd = end = false;

	//this->frameSounds.SetFrameSounds(frameSounds);
	this->sprites.SetImages(sprites);
}

void SpriteAnimation::SetWindow(Window* window)
{
	this->window = window;
}

void SpriteAnimation::SetTitle(std::string title)
{
<<<<<<< Updated upstream
	copyStr(title, this->title);
=======
	this->title = title;
>>>>>>> Stashed changes
}

std::string_view SpriteAnimation::GetTitle()
{
	return title;
}

std::string SpriteAnimation::GetStringTitle()
{
	return title;
}

std::vector<Image> SpriteAnimation::GetSprites()
{
	return sprites.GetImages();
}

void SpriteAnimation::SetSprites(std::vector<Image> sprites)
{
	this->sprites.SetImages(sprites);
}

std::string_view SpriteAnimation::GetFolder()
{
	return folder;
}

void SpriteAnimation::LoadFromFolder(std::string folder)
{
<<<<<<< Updated upstream
	copyStr(folder, this->folder);
=======
	this->folder = folder;
>>>>>>> Stashed changes
	LoadSpritesFromFolder();
}

int SpriteAnimation::GetFrameRate()
{
	return frameRate;
}

void SpriteAnimation::SetFrameRate(int frameRate)
{
	if (frameRate < 0) {
		return;
	}
	this->frameRate = frameRate;
}

bool SpriteAnimation::IsRepeat()
{
	return repeat;
}

void SpriteAnimation::SetRepeat(bool repeat)
{
	this->repeat = repeat;
}

bool SpriteAnimation::IsStopOnEnd()
{
	return stopOnEnd;
}

void SpriteAnimation::SetStopOnEnd(bool stopOnEnd)
{
	this->stopOnEnd = stopOnEnd;
}

void SpriteAnimation::SetCurrentSprite(int spriteIndex)
{
	if (spriteIndex < 0 || spriteIndex >= sprites.GetImages().size()) {
		return;
	}
	currentSpriteIndex = spriteIndex;
}

int SpriteAnimation::GetCurrentSpriteIndex()
{
	return currentSpriteIndex;
}

void SpriteAnimation::Play()
{
	Play(pos, size);
}

void SpriteAnimation::Play(Coord coord, Size size)
{
	if (end) {
		Restart();
	}

	if (end || pause) {
		return;
	}

	timePassed += timer.GetDeltaTime();
	if (timePassed >= (1.0f / frameRate)) {
		timePassed = 0;

		if (!reverse) {
			currentSpriteIndex = (currentSpriteIndex + 1) % sprites.GetSize();

			if (currentSpriteIndex >= sprites.GetSize() - 1 && !repeat) {
				currentSpriteIndex = 0;
				play = false;
				end = true;
				return;
			}
		}
		else {
			if (currentSpriteIndex > 0) {
				currentSpriteIndex--;
			}
			else {
				if (!repeat) {
					play = false;
					end = true;
					return;
				}

				currentSpriteIndex = sprites.GetSize() - 1;
			}
		}
	}

	frameSounds.Update(currentSpriteIndex);

	if (currentSpriteIndex >= 0) {
		currentFrameTitle = sprites[currentSpriteIndex];
		sprites.DrawImage(currentFrameTitle->title, coord, size, window->GetSize(), Color(1, 1, 1), true);

		if (rootTile != nullptr) {
			*rootTile = *currentFrameTitle;
		}
	}

	play = true;
}

bool SpriteAnimation::IsEnd()
{
	return end;
}

bool SpriteAnimation::IsPlay()
{
	return play;
}

bool SpriteAnimation::IsReverse()
{
	return reverse;
}

void SpriteAnimation::Pause()
{
	pause = false;
}

void SpriteAnimation::Stop()
{
	end = true;
	play = false;
	pause = false;
	currentSpriteIndex = 0;
}

void SpriteAnimation::Restart()
{
	end = false;
	play = false;
	pause = false;

	currentSpriteIndex = 0;
	frameSounds.Restart();
}

void SpriteAnimation::Reverse()
{
	reverse = !reverse;
}

void SpriteAnimation::SetRootTile(Image* image)
{
	rootTile = image;
}

Image* SpriteAnimation::GetCurrentyFrame()
{
	return currentFrameTitle;
}

Image* SpriteAnimation::GetRootTile()
{
	return rootTile;
}

IAnimation* SpriteAnimation::Clone()
{
	return new SpriteAnimation(*this);
}

bool SpriteAnimation::operator=(const SpriteAnimation& other)
{
	if (this != &other) {
		this->currentFrameTitle = other.currentFrameTitle;
		this->currentSpriteIndex = other.currentSpriteIndex;
		this->frameRate = other.frameRate;

		this->pos = other.pos;
		this->size = other.size;

		this->end = other.end;
		this->pause = other.pause;
		this->play = other.play;
		this->repeat = other.repeat;
		this->reverse = other.reverse;

		this->sprites = other.sprites;

		this->stopOnEnd = other.stopOnEnd;
		this->timePassed = other.timePassed;

		this->timer = other.timer;

<<<<<<< Updated upstream
		copyStr(other.folder, this->folder);
		copyStr(other.title, this->title);
=======
		this->folder = other.folder;
		this->title = other.title;
>>>>>>> Stashed changes
	}
	return false;
}
