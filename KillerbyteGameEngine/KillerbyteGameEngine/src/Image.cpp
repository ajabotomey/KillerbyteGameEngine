#include "Image.h"

namespace KillerbyteGameEngine
{
	Image::Image()
	{

	}

	Image::~Image()
	{
		delete[] data;
	}

	bool Image::LoadPNGImage(const char* filename)
	{
		png_byte header[8];
		
		Open(filename, "rb");

		// Read the header and check if it is a png
		Read(header, 1, 8);
		if (png_sig_cmp(header, 0, 8))
		{
			goto error;
		}

		// Create the png struct
		png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
		if (!png_ptr)
		{
			goto error;
		}

		// Create the info struct
		png_infop info_ptr = png_create_info_struct(png_ptr);
		if (!info_ptr)
		{
			goto error;
		}

		// Figured I would declare these in advance so all the data gets cleaned up
		png_bytep* rowPtrs = NULL;
		png_byte* data = NULL;

		// Error Checking enabled. If there is an error, it will be handled here
		if (setjmp(png_jmpbuf(png_ptr)))
		{
			if (rowPtrs != NULL)
			{
				delete[] rowPtrs;
			}
			
			if (data != NULL)
			{
				delete[] data;
			}

			goto pngerror;
		}

		// Initialize reading the png
		png_init_io(png_ptr, file);

		// Tell libpng that we have already read the header
		png_set_sig_bytes(png_ptr, 8);

		// Read all the info about the png up to the image data
		png_read_info(png_ptr, info_ptr);

		int bitDepth, colourType;
		png_uint_32 tempWidth, tempHeight;

		// Now assign that info to variables we can use
		png_get_IHDR(png_ptr, info_ptr, &tempWidth, &tempHeight, &bitDepth, &colourType, NULL, NULL, NULL);

		// Update width and height
		width = tempWidth;
		height = tempHeight;

		// Set the image format using the colour format read in
		switch (colourType)
		{
			case PNG_COLOR_TYPE_RGBA:
				format = Image::RGBA;
				break;

			case PNG_COLOR_TYPE_RGB:
				format = Image::RGB;
				break;
		}

		// Update the info struct
		png_read_update_info(png_ptr, info_ptr);

		// Row size in bytes
		int rowBytes = png_get_rowbytes(png_ptr, info_ptr);

		// We need to allocate the image data to a big block so we can give it to opengl
		data = new png_byte[rowBytes * height];
		if (!data)
		{
			goto pngerror;
		}

		rowPtrs = new png_bytep[height];
		if (!rowPtrs)
		{
			delete[] data;
			goto pngerror;
		}

		// Now set the row pointers to point at the correct offsets of the image data
		for (int i = 0; i < height; ++i)
		{
			rowPtrs[height - 1 - i] = data + i * rowBytes;
		}

		// Now read the image data into rowPtrs
		png_read_image(png_ptr, rowPtrs);

		// Time for some cleanup - we are not deleting the data because we need that data for the texture class
		delete[] rowPtrs;
		rowPtrs = NULL;
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		CloseFile();

		return true;

		pngerror:
			png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
			goto error;

		error:
			CloseFile();
			return false;
	}
}