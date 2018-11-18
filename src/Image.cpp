#include "pch.h"

using namespace std;

// HEADER CONSTRUCTORS
Image::Header::Header() {}

Image::Header::Header(char idLength, char colorMapType, char dataTypeCode, short colorMapOrigin, short colorMapLength, char colorMapDepth,
	short xOrigin, short yOrigin, unsigned short width, unsigned short height, char bitsPerPixel, char imageDescriptor) {
	this->idLength = idLength;
	this->colorMapType = colorMapType;
	this->dataTypeCode = dataTypeCode;
	this->colorMapOrigin = colorMapOrigin;
	this->colorMapLength = colorMapLength;
	this->colorMapDepth = colorMapDepth;
	this->xOrigin = xOrigin;
	this->yOrigin = yOrigin;
	this->width = width;
	this->height = height;
	this->bitsPerPixel = bitsPerPixel;
	this->imageDescriptor = imageDescriptor;
}

// PIXEL CONSTRUCTORS AND METHODS
// A .tga file is a header followed by a series of pixels; each of which is stored in a corresponding object
Image::Pixel::Pixel() {}

Image::Pixel::Pixel(unsigned char b, unsigned char g, unsigned char r) {
	this->b = b;
	this->g = g;
	this->r = r;
}

// Pixel getters
const unsigned char Image::Pixel::red() const {
	return this->r;
}

const unsigned char Image::Pixel::green() const {
	return this->g;
}

const unsigned char Image::Pixel::blue() const {
	return this->b;
}

void Image::Pixel::setRed(unsigned char newRed) {
	this->r = newRed;
}

void Image::Pixel::setBlue(unsigned char newBlue) {
	this->b = newBlue;
}

void Image::Pixel::setGreen(unsigned char newGreen) {
	this->g = newGreen;
}

// For comparing two pixels
const bool operator==(const Image::Pixel &pixel1, const Image::Pixel &pixel2) {
	// Pixels are equivalent iff their color components are perfect matches
	return((pixel1.blue() == pixel2.blue()) && (pixel1.green() == pixel2.green()) && (pixel1.red() == pixel2.red()));
}

// IMAGE CONSTRUCTORS AND METHODS
Image::Image() {}

Image::Image(Header &Header) {
	this->header = Header;
	this->expSize = this->header.width * this->header.height;

	// Fix number of rows and number of columns (these should not be changed during the operation of this program)
	this->pixels.resize(this->header.height);
	for (unsigned int i = 0; i < this->header.height; i++) {
		this->pixels.at(i).resize(this->header.width);
	}
}

// Image class getters
Image::Header &Image::getHeader() {
	return this->header;
}

vector<vector<Image::Pixel>> &Image::getPixels() {
	return this->pixels;
}

// Take incoming pixel object and place it into the this->pixels 2D array
void Image::addPixel(Pixel &pixel, unsigned int index) {
	int rowNum = (int)(index / this->header.width);
	int colNum = (int)(index % this->header.width);
	// Find the next available row; put the next pixel there
	if (index < (unsigned int)(this->header.width * this->header.height)) {
		//cout << "Adding to row " << rowNum << " col " << colNum << endl;
		this->pixels.at(rowNum).at(colNum) = pixel;
		return;
	}
	cout << "Error: pixel not added (trying to add too many pixels?)" << endl;
	return;

}

void Image::redFudge() {
	for (unsigned int i = 0; i < this->pixels.size(); i++) {
		for (unsigned int j = 0; j < this->pixels.at(i).size(); j++) {
			this->pixels.at(i).at(j).setBlue(this->pixels.at(i).at(j).red());
			this->pixels.at(i).at(j).setGreen(this->pixels.at(i).at(j).red());
		}
	}
}

void Image::greenFudge() {
	for (unsigned int i = 0; i < this->pixels.size(); i++) {
		for (unsigned int j = 0; j < this->pixels.at(i).size(); j++) {
			this->pixels.at(i).at(j).setRed(this->pixels.at(i).at(j).green());
			this->pixels.at(i).at(j).setBlue(this->pixels.at(i).at(j).green());
		}
	}
}

void Image::blueFudge() {
	for (unsigned int i = 0; i < this->pixels.size(); i++) {
		for (unsigned int j = 0; j < this->pixels.at(i).size(); j++) {
			this->pixels.at(i).at(j).setRed(this->pixels.at(i).at(j).blue());
			this->pixels.at(i).at(j).setGreen(this->pixels.at(i).at(j).blue());
		}
	}
}