#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "../Config.hpp"

NS_BEGIN

/// <summary>
/// Struct use for loading image data
/// </summary>
struct Image
{
	unsigned char* data;
	uint width;
	uint height;
	uint components;
};

NS_END

#endif