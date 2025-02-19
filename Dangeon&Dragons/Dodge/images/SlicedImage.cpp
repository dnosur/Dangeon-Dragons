#include "SlicedImage.h"

#include "../pawn/Pawn.h"

void SlicedImage::CalculateVertexes(int row_index, int start_column, int max_column)
{
	bool haveMaxColumn = max_column > 0;

	for (
		int i = (start_column >= 0 ? start_column : 0);
		i < (haveMaxColumn ? max_column : imageArraySize.width);
		i++
	) {
		if (!i) {
			vertexes.push_back(
				std::vector<std::pair<Coord, Coord>>()
			);
		}

		vertexes[row_index].push_back(
			CalculateTextureVertexes(
				frameSize,
				image->GetSize(),
				imageArraySize.width,
				i + (row_index * imageArraySize.width)
			)
		);
	}
}

void SlicedImage::Initilize()
{
	imageArraySize = Size(
		image->GetSize().width / frameSize.GetWidth(),
		image->GetSize().height / frameSize.GetHeight()
	);
}

bool SlicedImage::ValidateIndex(Coord& vertex_coord)
{
	if (vertex_coord.Y < 0 || vertex_coord.Y > vertexes.size() ||
		vertex_coord.X < 0 || vertex_coord.X > vertexes[vertex_coord.Y].size()) {
		return false;
	}
	return true;
}

SlicedImage::SlicedImage(std::shared_ptr<Image> image, std::vector<std::vector<std::pair<Coord, Coord>>> vertexes, Size frameSize)
{
	this->image = image;
	this->vertexes = vertexes;
	this->frameSize = frameSize;
	this->Initilize();
}

SlicedImage::SlicedImage(std::shared_ptr<Image> image, std::vector<int> widths, int height, Size frameSize)
{
	this->image = image;
	this->frameSize = frameSize;
	this->Initilize();
	Slice(widths, height);
}

SlicedImage::SlicedImage(std::shared_ptr<Image> image, Size frameSize)
{
	this->image = image;
	this->frameSize = frameSize;
	this->Initilize();
	Slice();
}

//SlicedImage::~SlicedImage()
//{
//	if (image != nullptr) {
//		delete image;
//	}
//
//	if (!vertexes.empty()) {
//		vertexes.clear();
//	}
//}

std::pair<Coord, Coord> SlicedImage::CalculateTextureVertexes(
	Size tileSize, 
	Size textureSize, 
	int columns, 
	int columnIndex)
{
	const int tileWidth = tileSize.width;
	const int tileHeight = tileSize.height;

	const int width = textureSize.width;
	const int height = textureSize.height;

	int atlasX = columnIndex % columns;
	int atlasY = columnIndex / columns;

	float tileU = (float)tileWidth / (float)width;
	float tileV = (float)tileHeight / (float)height;

	return {
		Coord(((float)atlasX + 1.0f) * tileU, 1.0f - ((float)(atlasY + 1) * (float)tileV)),
		Coord((float)atlasX * (float)tileU, 1.0f - ((float)atlasY * tileV))
	};
}

std::pair<Coord, Coord> SlicedImage::CalculateTextureVertexes(
	Size tileSize, 
	Size textureSize, 
	Coord vertex_coord
)
{
	const Size imageIndexSize = Size(
		std::roundf(textureSize.width / tileSize.width),
		std::roundf(textureSize.height / tileSize.height)
	);

	return CalculateTextureVertexes(
		tileSize,
		textureSize,
		imageIndexSize.width,
		vertex_coord.Y * imageIndexSize.width + vertex_coord.X
	);
}

void SlicedImage::Slice(std::vector<int> widths, int height)
{
	for (int i = 0; i < height; i++) {
		CalculateVertexes(i, 0, widths[i]);
	}
}

void SlicedImage::Slice(Size size)
{
	for (int i = 0; i < imageArraySize.height; i++) {
		CalculateVertexes(i, 0, size.width);
	}
}

void SlicedImage::Slice()
{
	for (int i = 0; i < imageArraySize.height; i++) {
		CalculateVertexes(i, 0);
	}
}

int SlicedImage::GetHeight()
{
	return vertexes.size();
}

std::weak_ptr<Image> SlicedImage::GetImage()
{
	return image;
}

void SlicedImage::SetImage(std::shared_ptr<Image> image, bool copy)
{
	if (copy) {
		*this->image = *image;
		return;
	}

	this->image = image;
}

void SlicedImage::UseDiffuseMapVertexes(Material* material, Coord vertex_coord)
{
	if (!ValidateIndex(vertex_coord)) {
		return;
	}

	material->SetDiffuseMapVerticies(vertexes[vertex_coord.Y][vertex_coord.Y]);
}

void SlicedImage::UseNormalMapVertexes(Material* material, Coord vertex_coord)
{
	if (!ValidateIndex(vertex_coord)) {
		return;
	}

	material->SetNormalMapVerticies(vertexes[vertex_coord.Y][vertex_coord.Y]);
}

void SlicedImage::UseSpecularMapVertexes(Material* material, Coord vertex_coord)
{
	if (!ValidateIndex(vertex_coord)) {
		return;
	}

	material->SetSpecularMapVerticies(vertexes[vertex_coord.Y][vertex_coord.Y]);
}

void SlicedImage::UseEmissiveMapVertexes(Material* material, Coord vertex_coord)
{
	if (!ValidateIndex(vertex_coord)) {
		return;
	}

	material->SetEmissiveMapVerticies(vertexes[vertex_coord.Y][vertex_coord.Y]);
}

std::unique_ptr<VertexAnimation> SlicedImage::CreateVertexAnimation(int vertex_row_index)
{
	std::string name = "slice_" + GenerateRandomString(5);
	return CreateVertexAnimation(
		vertex_row_index, 
		std::make_pair(name.c_str(), 1)
	);
}

std::unique_ptr<VertexAnimation> SlicedImage::CreateVertexAnimation(
	int vertex_row_index, 
	std::pair<std::string, int> frame_setting
)
{
	if (vertex_row_index < 0 || vertex_row_index >= vertexes.size()) {
		return nullptr;
	}

	std::vector<std::pair<int, std::vector<Coord>>> frames;

	for (std::pair<Coord, Coord>& vertex : vertexes[vertex_row_index]) {
		frames.push_back(
			std::make_pair(
				frame_setting.second,
				std::vector<Coord>({
					vertex.first, vertex.second
					})
			)
		);
	}

	return std::make_unique<VertexAnimation>(
		frame_setting.first,
		(int)(frames.size() * .7),
		true, false, nullptr, frames
	);
}

std::vector<std::unique_ptr<VertexAnimation>> SlicedImage::CreateVertexAnimations()
{
	std::vector<std::string> names;
	std::vector<int> durations;

	for (int i = 0; i < vertexes.size(); i++) {
		std::string name = "slice_" + GenerateRandomString(5);
		names.push_back(name.c_str());
		durations.push_back(300);
	}

	return CreateVertexAnimations(
		std::make_pair(names, durations)
	);
}

std::vector<std::unique_ptr<VertexAnimation>> SlicedImage::CreateVertexAnimations(
	std::pair<std::vector<std::string>, std::vector<int>> frames_settings
)
{
	std::vector<std::unique_ptr<VertexAnimation>> vertex_animations;

	for (int i = 0; i < vertexes.size(); i++) {
		std::vector<std::pair<int, std::vector<Coord>>> frames;

		for (std::pair<Coord, Coord>& vertex : vertexes[i]) {
			frames.push_back(
				std::make_pair(
					frames_settings.second[i], 
					std::vector<Coord>({ 
						vertex.first, vertex.second 
					})
				)
			);
		}

		vertex_animations.push_back(
			CreateVertexAnimation(
				i, 
				std::make_pair(
					frames_settings.first[i], 
					frames_settings.second[i]
				)
			)
		);
	}

	return vertex_animations;
}

std::vector<std::vector<std::pair<Coord, Coord>>>::iterator SlicedImage::begin()
{
	return vertexes.begin();
}

std::vector<std::vector<std::pair<Coord, Coord>>>::iterator SlicedImage::end()
{
	return vertexes.end();
}

std::vector<std::pair<Coord, Coord>>* SlicedImage::operator[](int index)
{
	if (index >= 0 && index < vertexes.size()) {
		return &vertexes[index];
	}
	return nullptr;
}
