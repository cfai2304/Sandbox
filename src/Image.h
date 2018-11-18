#pragma once
#include <vector>
using namespace std;

class Image {
public:

	struct Header {
		char idLength;
		char colorMapType;
		char dataTypeCode;
		short colorMapOrigin;
		short colorMapLength;
		char colorMapDepth;
		short xOrigin;
		short yOrigin;
		unsigned short width;
		unsigned short height;
		char bitsPerPixel;
		char imageDescriptor;

		Header();
		Header(char idLength,
			char colorMapType,
			char dataTypeCode,
			short colorMapOrigin,
			short colorMapLength,
			char colorMapDepth,
			short xOrigin,
			short yOrigin,
			unsigned short width,
			unsigned short height,
			char bitsPerPixel,
			char imageDescriptor);

	};

	class Pixel {
	public:
		Pixel();
		Pixel(unsigned char b, unsigned char g, unsigned char r);
		const unsigned char red() const;
		const unsigned char blue() const;
		const unsigned char green() const;

		void setRed(unsigned char newRed);
		void setBlue(unsigned char newBlue);
		void setGreen(unsigned char newGreen);
		friend const bool operator==(const Pixel &pixel1, const Pixel &pixel2);

	private:
		unsigned char r;
		unsigned char b;
		unsigned char g;
	};

	Image();
	Image(Header &Header);

	Header &getHeader();
	vector<vector<Pixel>> &getPixels();
	void addPixel(Pixel &pixel, unsigned int index);

	void redFudge();
	void greenFudge();
	void blueFudge();

private:

	Header header;
	unsigned int expSize;
	vector<vector<Pixel>> pixels;
	// Let's try a 2D vector to store a two dimensional image : outer vector stores a series of inner vectors, each of which represent rows of pixels
	// Elements of inner vectors are individual pixels in a row, so reading the vector from left to right is the same as reading the image from left to right


};