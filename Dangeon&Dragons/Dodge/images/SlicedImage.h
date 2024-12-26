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
	Image* image;
	boost::container::vector<
		boost::container::vector<
			std::pair<Coord, Coord>
		>
	> vertexes;

	Size frameSize;
	Size imageArraySize;

	void CalculateVertexes(int row_index, int start_column = 0, int max_column = -1);

	void Initilize();

	bool ValidateIndex(Coord& vertex_coord);
public:
	SlicedImage(Image* image, boost::container::vector<boost::container::vector<std::pair<Coord, Coord>>> vertexes, Size frameSize = DEFAULT_FRAME_SIZE);
	SlicedImage(Image* image, boost::container::vector<int> widths, int height, Size frameSize = DEFAULT_FRAME_SIZE);
	SlicedImage(Image* image, Size frameSize = DEFAULT_FRAME_SIZE);
	~SlicedImage();

	static std::pair<Coord, Coord> CalculateTextureVertexes(
		Size tileSize,
		Size textureSize,
		int columns,
		int columnIndex
	);

	void Slice(boost::container::vector<int> widths, int height);
	void Slice(Size size);
	void Slice();

	int GetHeight();

	Image* GetImage();
	void SetImage(Image* image, bool copy = false);

	void UseDiffuseMapVertexes(Material* material, Coord vertex_coord);
	void UseNormalMapVertexes(Material* material, Coord vertex_coord);
	void UseSpecularMapVertexes(Material* material, Coord vertex_coord);
	void UseEmissiveMapVertexes(Material* material, Coord vertex_coord);

	//vertex_row_index - vertex row index
	VertexAnimation* CreateVertexAnimation(int vertex_row_index);

	//vertex_row_index - vertex row index
	//frame_setting.first - frame name, frame_setting.second - duration
	VertexAnimation* CreateVertexAnimation(
		int vertex_row_index,
		std::pair<const char*, int> frame_setting
	);

	boost::container::vector<VertexAnimation*> CreateVertexAnimations();

	//frames_settings.first - frames names, frames_settings.second - duration
	boost::container::vector<VertexAnimation*> CreateVertexAnimations(
		std::pair<boost::container::vector<const char*>, boost::container::vector<int>> frames_settings
	);

	boost::container::vector<
		boost::container::vector<
		std::pair<Coord, Coord>
		>
	>::iterator begin();

	boost::container::vector<
		boost::container::vector<
		std::pair<Coord, Coord>
		>
	>::iterator end();

	boost::container::vector<std::pair<Coord, Coord>>* operator[](int index);
};