#pragma once
#include <vector>

#include "../Coord.h"
#include "../Size.h"

#include "Image.h"
#include "../Material.h"
#include "../animator/VertexAnimation.h"

#define DEFAULT_FRAME_SIZE Size(32, 32)

class SlicedImage
{
	std::shared_ptr<Image> image;
	std::vector<
		std::vector<
			std::pair<Coord, Coord>
		>
	> vertexes;

	Size frameSize;
	Size imageArraySize;

	void CalculateVertexes(int row_index, int start_column = 0, int max_column = -1);

	void Initilize();

	bool ValidateIndex(Coord& vertex_coord);
public:
	SlicedImage(std::shared_ptr<Image> image, std::vector<std::vector<std::pair<Coord, Coord>>> vertexes, Size frameSize = DEFAULT_FRAME_SIZE);
	SlicedImage(std::shared_ptr<Image> image, std::vector<int> widths, int height, Size frameSize = DEFAULT_FRAME_SIZE);
	SlicedImage(std::shared_ptr<Image> image, Size frameSize = DEFAULT_FRAME_SIZE);

	static std::pair<Coord, Coord> CalculateTextureVertexes(
		Size tileSize,
		Size textureSize,
		int columns,
		int columnIndex
	);

	static std::pair<Coord, Coord> CalculateTextureVertexes(
		Size tileSize, 
		Size textureSize, 
		Coord vertex_coord
	);

	void Slice(std::vector<int> widths, int height);
	void Slice(Size size);
	void Slice();

	int GetHeight();

	std::weak_ptr<Image> GetImage();
	void SetImage(std::shared_ptr<Image> image, bool copy = false);

	void UseDiffuseMapVertexes(Material* material, Coord vertex_coord);
	void UseNormalMapVertexes(Material* material, Coord vertex_coord);
	void UseSpecularMapVertexes(Material* material, Coord vertex_coord);
	void UseEmissiveMapVertexes(Material* material, Coord vertex_coord);

	//vertex_row_index - vertex row index
	std::unique_ptr<VertexAnimation> CreateVertexAnimation(int vertex_row_index);

	//vertex_row_index - vertex row index
	//frame_setting.first - frame name, frame_setting.second - duration
	std::unique_ptr<VertexAnimation> CreateVertexAnimation(
		int vertex_row_index,
		std::pair<std::string, int> frame_setting
	);

	std::vector<std::unique_ptr<VertexAnimation>> CreateVertexAnimations();

	//frames_settings.first - frames names, frames_settings.second - duration
	std::vector<std::unique_ptr<VertexAnimation>> CreateVertexAnimations(
		std::pair<std::vector<std::string>, std::vector<int>> frames_settings
	);

	std::vector<
		std::vector<
		std::pair<Coord, Coord>
		>
	>::iterator begin();

	std::vector<
		std::vector<
		std::pair<Coord, Coord>
		>
	>::iterator end();

	std::vector<std::pair<Coord, Coord>>* operator[](int index);
};