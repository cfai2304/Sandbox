// ImageProcessing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

using namespace std;

// HELPERS AND DOERS
void readFile(string fileName, vector<Image> &imageList);
void genFile(string outFile, Image &outImage);

bool compareImages(Image &image1, Image &image2);

void TEST_FOR_EQUALITY(vector<Image> &outputImages);

void multiply(Image &image1, Image &image2, unsigned int normalFactor, vector<Image> &imageList);

void multiplyConst(Image &origImage, float scaleRed, float scaleGreen, float scaleBlue, unsigned int normalFactor, vector<Image> &imageList);

void add(Image &origImage, Image &filter, vector<Image> &imageList);

void subtract(Image &origImage, Image &filter, vector<Image> &imageList);

void addConst(Image &origImage, int addRed, int addBlue, int addGreen, vector<Image> &imageList);

void screen(Image &image1, Image &image2, unsigned int normalFactor, vector<Image> &imageList);

void overlay(Image &image1, Image &image2, unsigned int normalFactor, vector<Image> &imageList);

void rotate(Image &origImate, int degrees, vector<Image> &imageList);

void collage(Image &UL, Image &UR, Image &LL, Image &LR, vector<Image> &imageList);

int main(int argc, char **argv) {

	// Set up some containers for storing images, as well as the names of files they're going to
	vector<Image> inputImages;
	vector<Image> outputImages;
	vector<Image> tempImages;

	string car = "input\\car.tga";
	string circles = "input\\circles.tga";
	string layerBlue = "input\\layer_blue.tga";
	string layerGreen = "input\\layer_green.tga";
	string layerRed = "input\\layer_red.tga";
	string layer1 = "input\\layer1.tga";
	string layer2 = "input\\layer2.tga";
	string pattern1 = "input\\pattern1.tga";
	string pattern2 = "input\\pattern2.tga";
	string text1 = "input\\text.tga";
	string text2 = "input\\text2.tga";

	string part1 = "output\\part1.tga";
	string part2 = "output\\part2.tga";
	string part3 = "output\\part3.tga";
	string part4 = "output\\part4.tga";
	string part5 = "output\\part5.tga";
	string part6 = "output\\part6.tga";
	string part7 = "output\\part7.tga";
	string part8r = "output\\part8_r.tga";
	string part8g = "output\\part8_g.tga";
	string part8b = "output\\part8_b.tga";
	string part9 = "output\\part9.tga";
	string part10 = "output\\part10.tga";
	string partEC = "output\\extracredit.tga";

	// Do part 1
	cout << "Doing part 1...";
	try {
		readFile(layer1, inputImages);
		readFile(pattern1, inputImages);
		multiply(inputImages.at(0), inputImages.at(1), 255, outputImages);
		genFile(part1, outputImages.at(0));

	}
	catch (runtime_error e) {
		cerr << e.what() << endl;
		return 1;
	}
	// And reset the image lists (but not the outputs; we need those for testing later)
	inputImages.clear();
	cout << "finished" << endl;

	// Do part 2
	cout << "Doing part 2...";
	try {
		readFile(layer2, inputImages);
		readFile(car, inputImages);
		subtract(inputImages.at(1), inputImages.at(0), outputImages);
		genFile(part2, outputImages.at(1));
	}
	catch (runtime_error e) {
		cerr << e.what() << endl;
		return 1;
	}
	inputImages.clear();
	cout << "finished" << endl;

	// Do part 3
	cout << "Doing part 3...";
	try {
		readFile(layer1, inputImages);
		readFile(pattern2, inputImages);
		readFile(text1, inputImages);
		multiply(inputImages.at(0), inputImages.at(1), 255, tempImages);

		screen(inputImages.at(2), tempImages.at(0), 255, outputImages);

		genFile(part3, outputImages.at(2));
	}
	catch (runtime_error e) {
		cerr << e.what() << endl;
		return 1;
	}
	inputImages.clear();
	tempImages.clear();
	cout << "finished" << endl;

	// Do part 4
	cout << "Doing part 4...";
	try {
		readFile(layer2, inputImages);
		readFile(circles, inputImages);
		readFile(pattern2, inputImages);
		multiply(inputImages.at(0), inputImages.at(1), 255, tempImages);

		subtract(tempImages.at(0), inputImages.at(2), outputImages);

		genFile(part4, outputImages.at(3));
	}
	catch (runtime_error e) {
		cerr << e.what() << endl;
		return 1;
	}
	inputImages.clear();
	tempImages.clear();
	cout << "finished" << endl;

	// Do part 5
	cout << "Doing part 5...";
	try {
		readFile(layer1, inputImages);
		readFile(pattern1, inputImages);
		overlay(inputImages.at(0), inputImages.at(1), 255, outputImages);
		genFile(part5, outputImages.at(4));
	}
	catch (runtime_error e) {
		cerr << e.what() << endl;
		return 1;
	}
	inputImages.clear();
	cout << "finished" << endl;

	// Do part 6
	cout << "Doing part 6...";
	try {
		readFile(car, inputImages);
		addConst(inputImages.at(0), 0, 0, 200, outputImages);
		genFile(part6, outputImages.at(5));
	}
	catch (runtime_error e) {
		cerr << e.what() << endl;
		return 1;
	}
	inputImages.clear();
	cout << "finished" << endl;

	// Do part 7
	cout << "Doing part 7...";
	try {
		readFile(car, inputImages);
		multiplyConst(inputImages.at(0), 4.0f, 1.0f, 0.0f, 255, outputImages);
		genFile(part7, outputImages.at(6));
	}
	catch (runtime_error e) {
		cerr << e.what() << endl;
		return 1;
	}
	inputImages.clear();
	cout << "finished" << endl;

	// Do part 8
	cout << "Doing part 8...";
	try {
		readFile(car, inputImages);
		// Produce extremely red, green, and blue copies of car.tga
		multiplyConst(inputImages.at(0), 1.0f, 0.0f, 0.0f, 255, tempImages);
		multiplyConst(inputImages.at(0), 0.0f, 1.0f, 0.0f, 255, tempImages);
		multiplyConst(inputImages.at(0), 0.0f, 0.0f, 1.0f, 255, tempImages);

		// Fudge (or smear, I guess) the monochrome copies to get lovely grey prints
		tempImages.at(0).redFudge();
		tempImages.at(1).greenFudge();
		tempImages.at(2).blueFudge();

		outputImages.push_back(tempImages.at(0)); // Index #7
		outputImages.push_back(tempImages.at(1));
		outputImages.push_back(tempImages.at(2));


		genFile(part8r, outputImages.at(7));
		genFile(part8g, outputImages.at(8));
		genFile(part8b, outputImages.at(9));
	}
	catch (runtime_error e) {
		cerr << e.what() << endl;
		return 1;
	}
	inputImages.clear();
	tempImages.clear();
	cout << "finished" << endl;

	// Do part 9
	cout << "Doing part 9...";
	try {
		readFile(layerRed, inputImages);
		readFile(layerGreen, inputImages);
		readFile(layerBlue, inputImages);

		// Monochrom-ing for easier addition
		multiplyConst(inputImages.at(0), 1.0f, 0.0f, 0.0f, 255, tempImages);
		multiplyConst(inputImages.at(1), 0.0f, 1.0f, 0.0f, 255, tempImages);
		multiplyConst(inputImages.at(2), 0.0f, 0.0f, 1.0f, 255, tempImages);
		add(tempImages.at(0), tempImages.at(1), tempImages); // Saves R + G to tempImages(3)
		add(tempImages.at(2), tempImages.at(3), outputImages); // Saves B + (R + G) to outImages(10)
		genFile(part9, outputImages.at(10));

	}
	catch (runtime_error e) {
		cerr << e.what() << endl;
		return 1;
	}
	inputImages.clear();
	tempImages.clear();
	cout << "finished" << endl;

	// Do part 10
	cout << "Doing part 10...";
	try {
		readFile(text2, inputImages);
		rotate(inputImages.at(0), 180, outputImages);
		genFile(part10, outputImages.at(11));
	}
	catch (runtime_error e) {
		cerr << e.what() << endl;
		return 1;
	}
	inputImages.clear();
	cout << "finished" << endl;

	// Do EC
	cout << "Doing EC...";
	try {
		readFile(car, inputImages);
		readFile(circles, inputImages);
		readFile(text1, inputImages);
		readFile(pattern1, inputImages);
		collage(inputImages.at(0), inputImages.at(1), inputImages.at(2), inputImages.at(3), outputImages);
		genFile(partEC, outputImages.at(12));
	}
	catch (runtime_error e) {
		cerr << e.what() << endl;
		return 1;
	}
	inputImages.clear();
	cout << "finished" << endl;

	char testsOrNot = 'n';
	cout << "Accuracy check? (y/n)" << endl;
	cin >> testsOrNot;

	if (testsOrNot == 'y')
		TEST_FOR_EQUALITY(outputImages);

	return 0;
}
// SOME HELPERS
void TEST_FOR_EQUALITY(vector<Image> &outputImages) { // Toggleable testing mode

	vector<Image> exampleImages;
	const unsigned int numTests = 13;
	unsigned int passedTests = 0;
	unsigned int numPoints = 0;
	const unsigned int totalPoints = 110;
	string example1 = "examples\\EXAMPLE_part1.tga";
	string example2 = "examples\\EXAMPLE_part2.tga";
	string example3 = "examples\\EXAMPLE_part3.tga";
	string example4 = "examples\\EXAMPLE_part4.tga";
	string example5 = "examples\\EXAMPLE_part5.tga";
	string example6 = "examples\\EXAMPLE_part6.tga";
	string example7 = "examples\\EXAMPLE_part7.tga";
	string example8r = "examples\\EXAMPLE_part8_r.tga";
	string example8g = "examples\\EXAMPLE_part8_g.tga";
	string example8b = "examples\\EXAMPLE_part8_b.tga";
	string example9 = "examples\\EXAMPLE_part9.tga";
	string example10 = "examples\\EXAMPLE_part10.tga";
	string exampleec = "examples\\EXAMPLE_extracredit.tga";
	
	cout << "Loading example images..." << endl;
	readFile(example1, exampleImages);
	readFile(example2, exampleImages);
	readFile(example3, exampleImages);
	readFile(example4, exampleImages);
	readFile(example5, exampleImages);
	readFile(example6, exampleImages);
	readFile(example7, exampleImages);
	readFile(example8r, exampleImages);
	readFile(example8g, exampleImages);
	readFile(example8b, exampleImages);
	readFile(example9, exampleImages);
	readFile(example10, exampleImages);
	readFile(exampleec, exampleImages);

	for (unsigned int i = 0; i < numTests; i++) {
		if (compareImages(outputImages.at(i), exampleImages.at(i))) {
			cout << "Images match: Test #" << (i + 1) << " successful" << endl;
			passedTests++;
			if (i == 10)
				numPoints -= 10; // Corrections for point values of EC and multi-part 8
			else if (i == 12)
				numPoints -= 5;
			
			numPoints += 10;
			
		}
		else
			cout << "Images don't match: Test #" << (i + 1) << " not successful" << endl;
	}

	cout << passedTests << "/" << numTests << " passed" << endl;
	cout << "Score: " << numPoints << "/" << totalPoints << endl;

}
void readFile(string fileName, vector<Image> &imageList) {
	ifstream inFS(fileName, ios_base::binary);
	//inFS.open(fileName);
	if (!inFS.is_open()) {
		throw(runtime_error("Error opening file: " + fileName));
		return;
	}

	// Get the header
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

	inFS.read(&idLength, sizeof(idLength));
	inFS.read(&colorMapType, sizeof(colorMapType));
	inFS.read(&dataTypeCode, sizeof(dataTypeCode));
	inFS.read((char *)&colorMapOrigin, sizeof(colorMapOrigin));
	inFS.read((char *)&colorMapLength, sizeof(colorMapLength));
	inFS.read(&colorMapDepth, sizeof(colorMapDepth));
	inFS.read((char *)&xOrigin, sizeof(xOrigin));
	inFS.read((char *)&yOrigin, sizeof(yOrigin));
	inFS.read((char *)&width, sizeof(width));
	inFS.read((char *)&height, sizeof(height));
	inFS.read(&bitsPerPixel, sizeof(bitsPerPixel));
	inFS.read(&imageDescriptor, sizeof(imageDescriptor));

	Image::Header newHeader(idLength, colorMapType, dataTypeCode, colorMapOrigin, colorMapLength, colorMapDepth,
		xOrigin, yOrigin, width, height, bitsPerPixel, imageDescriptor);

	Image newImage(newHeader);
	unsigned int pixelNum = 0;
	unsigned char nextBlue;
	unsigned char nextGreen;
	unsigned char nextRed;

	//inFS.seekg(18);
	//cout << inFS.tellg() << endl;
	while (pixelNum < (unsigned int)(height * width)) {

		inFS.read((char *)&nextBlue, sizeof(nextBlue));
		inFS.read((char *)&nextGreen, sizeof(nextGreen));
		inFS.read((char *)&nextRed, sizeof(nextRed));

		if (inFS.fail()) {
			cout << "Error reading pixel #" << pixelNum << " at " << inFS.tellg() << endl;
		}
		Image::Pixel newPixel(nextBlue, nextGreen, nextRed);
		newImage.addPixel(newPixel, pixelNum);

		pixelNum++;

	}

	imageList.push_back(newImage);
	inFS.close();
}

void genFile(string outFile, Image &outImage) {
	ofstream outFS(outFile, ios_base::binary);

	if (!outFS.is_open()) {
		throw("Error writing to file: " + outFile);
		return;
	}

	// Write the header
	outFS.write(&outImage.getHeader().idLength, sizeof(outImage.getHeader().idLength));
	outFS.write(&outImage.getHeader().colorMapType, sizeof(outImage.getHeader().colorMapType));
	outFS.write(&outImage.getHeader().dataTypeCode, sizeof(outImage.getHeader().dataTypeCode));
	outFS.write((char *)&outImage.getHeader().colorMapOrigin, sizeof(outImage.getHeader().colorMapOrigin));
	outFS.write((char *)&outImage.getHeader().colorMapLength, sizeof(outImage.getHeader().colorMapLength));
	outFS.write(&outImage.getHeader().colorMapDepth, sizeof(outImage.getHeader().colorMapDepth));
	outFS.write((char *)&outImage.getHeader().xOrigin, sizeof(outImage.getHeader().xOrigin));
	outFS.write((char *)&outImage.getHeader().yOrigin, sizeof(outImage.getHeader().yOrigin));
	outFS.write((char *)&outImage.getHeader().width, sizeof(outImage.getHeader().width));
	outFS.write((char *)&outImage.getHeader().height, sizeof(outImage.getHeader().height));
	outFS.write(&outImage.getHeader().bitsPerPixel, sizeof(outImage.getHeader().bitsPerPixel));
	outFS.write(&outImage.getHeader().imageDescriptor, sizeof(outImage.getHeader().imageDescriptor));
	if (outFS.fail())
		cout << "Error writing header" << endl;

	// Write da pixels
	unsigned char nextBlue;
	unsigned char nextGreen;
	unsigned char nextRed;
	for (unsigned int i = 0; i < outImage.getPixels().size(); i++) {
		for (unsigned int j = 0; j < outImage.getPixels().at(i).size(); j++) {

			nextBlue = outImage.getPixels().at(i).at(j).blue();
			nextGreen = outImage.getPixels().at(i).at(j).green();
			nextRed = outImage.getPixels().at(i).at(j).red();

			outFS.write((char *)&nextBlue, sizeof(nextBlue));
			outFS.write((char *)&nextGreen, sizeof(nextGreen));
			outFS.write((char *)&nextRed, sizeof(nextRed));
			if (outFS.fail())
				cout << "Error writing pixels" << endl;
		}
	}

	outFS.close();
}

bool compareImages(Image &image1, Image &image2) {

	// Compare each RGB value of every pixel using an overloaded ==
	for (unsigned int i = 0; i < image1.getPixels().size(); i++) {

		for (unsigned int j = 0; j < image1.getPixels().at(i).size(); j++) {

			if (!(image1.getPixels().at(i).at(j) == image2.getPixels().at(i).at(j)))
				return false;
		}
	}

	return true;
}

// SOME DOERS
void multiply(Image &image1, Image &image2, unsigned int normalFactor, vector<Image> &imageList) {
	// Analogous to double filtration of one light stream
	Image newImage(image1.getHeader());
	unsigned char newRed;
	unsigned char newBlue;
	unsigned char newGreen;
	float normalRed;
	float normalBlue;
	float normalGreen;

	unsigned int pixelNum = 0;

	for (unsigned int i = 0; i < image1.getPixels().size(); i++) {

		for (unsigned int j = 0; j < image1.getPixels().at(i).size(); j++) {
			normalRed = ((float)(image1.getPixels().at(i).at(j).red()) / normalFactor) * ((float)(image2.getPixels().at(i).at(j).red()) / normalFactor);
			normalBlue = ((float)(image1.getPixels().at(i).at(j).blue()) / normalFactor) * ((float)(image2.getPixels().at(i).at(j).blue()) / normalFactor);
			normalGreen = ((float)(image1.getPixels().at(i).at(j).green()) / normalFactor) * ((float)(image2.getPixels().at(i).at(j).green()) / normalFactor);

			newRed = (unsigned char)(normalRed * normalFactor + 0.5f);
			newBlue = (unsigned char)(normalBlue * normalFactor + 0.5f);
			newGreen = (unsigned char)(normalGreen * normalFactor + 0.5f);
			Image::Pixel newPixel(newBlue, newGreen, newRed);

			newImage.addPixel(newPixel, pixelNum);
			pixelNum++;


		}
	}

	imageList.push_back(newImage);
}

void multiplyConst(Image &origImage, float scaleRed, float scaleGreen, float scaleBlue, unsigned int normalFactor, vector<Image> &imageList) {
	// Normalized multiplying of all channels by specified scale coefficients

	if ((scaleRed < 0.0f) || (scaleGreen < 0.0f) || (scaleBlue < 0.0f)) {
		throw runtime_error("Invalid multiplyConst scale factors!");
	}

	Image newImage(origImage.getHeader());
	unsigned int newRed;
	unsigned int newBlue;
	unsigned int newGreen;
	float normalRed;
	float normalBlue;
	float normalGreen;

	unsigned int pixelNum = 0;

	for (unsigned int i = 0; i < origImage.getPixels().size(); i++) {

		for (unsigned int j = 0; j < origImage.getPixels().at(i).size(); j++) {
			normalRed = ((float)(origImage.getPixels().at(i).at(j).red()) / normalFactor) * scaleRed;
			normalBlue = ((float)(origImage.getPixels().at(i).at(j).blue()) / normalFactor) * scaleBlue;
			normalGreen = ((float)(origImage.getPixels().at(i).at(j).green()) / normalFactor) * scaleGreen;

			newRed = (int)(normalRed * normalFactor + 0.5f);
			newBlue = (int)(normalBlue * normalFactor + 0.5f);
			newGreen = (int)(normalGreen * normalFactor + 0.5f);

			// NOTE: Refine normalFactor calculations for scales that don't start with 0
			if (newRed > normalFactor)
				newRed = normalFactor;
			if (newGreen > normalFactor)
				newGreen = normalFactor;
			if (newBlue > normalFactor)
				newBlue = normalFactor;


			Image::Pixel newPixel((unsigned char)newBlue, (unsigned char)newGreen, (unsigned char)newRed);

			newImage.addPixel(newPixel, pixelNum);
			pixelNum++;
		}
	}

	imageList.push_back(newImage);
}

void add(Image &origImage, Image &filter, vector<Image> &imageList) {
	// Linear addition of all colors
	Image newImage(origImage.getHeader());
	int newRed;
	int newBlue;
	int newGreen;

	unsigned int pixelNum = 0;

	for (unsigned int i = 0; i < origImage.getPixels().size(); i++) {

		for (unsigned int j = 0; j < origImage.getPixels().at(i).size(); j++) {

			newRed = origImage.getPixels().at(i).at(j).red() + filter.getPixels().at(i).at(j).red();
			if (newRed > 255)
				newRed = 255;

			newBlue = origImage.getPixels().at(i).at(j).blue() + filter.getPixels().at(i).at(j).blue();
			if (newBlue > 255)
				newBlue = 255;

			newGreen = origImage.getPixels().at(i).at(j).green() + filter.getPixels().at(i).at(j).green();
			if (newGreen > 255)
				newGreen = 255;


			Image::Pixel newPixel((unsigned char)newBlue, (unsigned char)newGreen, (unsigned char)newRed);

			newImage.addPixel(newPixel, pixelNum);
			pixelNum++;


		}
	}
	imageList.push_back(newImage);
}

void subtract(Image &origImage, Image &filter, vector<Image> &imageList) {
	// Linear subtraction of all colors
	Image newImage(origImage.getHeader());
	int newRed;
	int newBlue;
	int newGreen;

	unsigned int pixelNum = 0;

	for (unsigned int i = 0; i < origImage.getPixels().size(); i++) {

		for (unsigned int j = 0; j < origImage.getPixels().at(i).size(); j++) {

			newRed = origImage.getPixels().at(i).at(j).red() - filter.getPixels().at(i).at(j).red();
			if (newRed < 0)
				newRed = 0;

			newBlue = origImage.getPixels().at(i).at(j).blue() - filter.getPixels().at(i).at(j).blue();
			if (newBlue < 0)
				newBlue = 0;

			newGreen = origImage.getPixels().at(i).at(j).green() - filter.getPixels().at(i).at(j).green();
			if (newGreen < 0)
				newGreen = 0;


			Image::Pixel newPixel((unsigned char)newBlue, (unsigned char)newGreen, (unsigned char)newRed);

			newImage.addPixel(newPixel, pixelNum);
			pixelNum++;


		}
	}
	imageList.push_back(newImage);
}

void addConst(Image &origImage, int addRed, int addBlue, int addGreen, vector<Image> &imageList) {
	// Offsets all channels by specified constants
	Image newImage(origImage.getHeader());
	int newRed;
	int newBlue;
	int newGreen;

	unsigned int pixelNum = 0;

	for (unsigned int i = 0; i < origImage.getPixels().size(); i++) {

		for (unsigned int j = 0; j < origImage.getPixels().at(i).size(); j++) {

			newRed = origImage.getPixels().at(i).at(j).red() + addRed;
			if (newRed > 255)
				newRed = 255;

			else if (newRed < 0)
				newRed = 0;

			newBlue = origImage.getPixels().at(i).at(j).blue() + addBlue;
			if (newBlue > 255)
				newBlue = 255;

			else if (newBlue < 0)
				newBlue = 0;

			newGreen = origImage.getPixels().at(i).at(j).green() + addGreen;
			if (newGreen > 255)
				newGreen = 255;

			else if (newGreen < 0)
				newGreen = 0;

			Image::Pixel newPixel((unsigned char)newBlue, (unsigned char)newGreen, (unsigned char)newRed);

			newImage.addPixel(newPixel, pixelNum);
			pixelNum++;
		}
	}
	imageList.push_back(newImage);

}

void screen(Image &image1, Image &image2, unsigned int normalFactor, vector<Image> &imageList) {
	// Analogous to projecting two images on the same surface
	Image newImage(image1.getHeader());
	unsigned char newRed;
	unsigned char newBlue;
	unsigned char newGreen;
	float normalRed;
	float normalBlue;
	float normalGreen;

	unsigned int pixelNum = 0;

	for (unsigned int i = 0; i < image1.getPixels().size(); i++) {

		for (unsigned int j = 0; j < image1.getPixels().at(i).size(); j++) {
			normalRed = 1.0f - (1.0f - (float)(image1.getPixels().at(i).at(j).red()) / normalFactor) * (1.0f - (float)(image2.getPixels().at(i).at(j).red()) / normalFactor);
			normalBlue = 1.0f - (1.0f - (float)(image1.getPixels().at(i).at(j).blue()) / normalFactor) * (1.0f - (float)(image2.getPixels().at(i).at(j).blue()) / normalFactor);
			normalGreen = 1.0f - (1.0f - (float)(image1.getPixels().at(i).at(j).green()) / normalFactor) * (1.0f - (float)(image2.getPixels().at(i).at(j).green()) / normalFactor);

			newRed = (unsigned char)(normalRed * normalFactor + 0.5f);
			newBlue = (unsigned char)(normalBlue * normalFactor + 0.5f);
			newGreen = (unsigned char)(normalGreen * normalFactor + 0.5f);
			Image::Pixel newPixel(newBlue, newGreen, newRed);

			newImage.addPixel(newPixel, pixelNum);
			pixelNum++;


		}
	}

	imageList.push_back(newImage);
}

void overlay(Image &image1, Image &image2, unsigned int normalFactor, vector<Image> &imageList) {
	// See http://www.simplefilter.de/en/basics/mixmods.html
	Image newImage(image1.getHeader());
	unsigned char newRed;
	unsigned char newBlue;
	unsigned char newGreen;
	float normalRed;
	float normalBlue;
	float normalGreen;

	unsigned int pixelNum = 0;

	for (unsigned int i = 0; i < image1.getPixels().size(); i++) {

		for (unsigned int j = 0; j < image1.getPixels().at(i).size(); j++) {

			if (((float)(image2.getPixels().at(i).at(j).red()) / normalFactor) <= 0.5f)
				normalRed = 2.0f * ((float)(image1.getPixels().at(i).at(j).red()) / normalFactor) * ((float)(image2.getPixels().at(i).at(j).red()) / normalFactor);
			else
				normalRed = 1.0f - 2.0f * (1.0f - (float)(image1.getPixels().at(i).at(j).red()) / normalFactor) * (1.0f - (float)(image2.getPixels().at(i).at(j).red()) / normalFactor);

			if (((float)(image2.getPixels().at(i).at(j).blue()) / normalFactor) <= 0.5f)
				normalBlue = 2.0f * ((float)(image1.getPixels().at(i).at(j).blue()) / normalFactor) * ((float)(image2.getPixels().at(i).at(j).blue()) / normalFactor);
			else
				normalBlue = 1.0f - 2.0f * (1.0f - (float)(image1.getPixels().at(i).at(j).blue()) / normalFactor) * (1.0f - (float)(image2.getPixels().at(i).at(j).blue()) / normalFactor);

			if (((float)(image2.getPixels().at(i).at(j).green()) / normalFactor) <= 0.5f)
				normalGreen = 2.0f * ((float)(image1.getPixels().at(i).at(j).green()) / normalFactor) * ((float)(image2.getPixels().at(i).at(j).green()) / normalFactor);
			else
				normalGreen = 1.0f - 2.0f * (1.0f - (float)(image1.getPixels().at(i).at(j).green()) / normalFactor) * (1.0f - (float)(image2.getPixels().at(i).at(j).green()) / normalFactor);

			newRed = (unsigned char)(normalRed * normalFactor + 0.5f);
			newBlue = (unsigned char)(normalBlue * normalFactor + 0.5f);
			newGreen = (unsigned char)(normalGreen * normalFactor + 0.5f);
			Image::Pixel newPixel(newBlue, newGreen, newRed);

			newImage.addPixel(newPixel, pixelNum);
			pixelNum++;


		}
	}

	imageList.push_back(newImage);
}

void rotate(Image &origImage, int degrees, vector<Image> &imageList) {
	Image newImage(origImage.getHeader());
	unsigned int pixelNum = 0;

	if (degrees == 180) {
		for (int i = (int)origImage.getPixels().size() - 1; i > -1; i--) {
			for (int j = (int)origImage.getPixels().at(i).size() - 1; j > -1; j--) {
				newImage.addPixel(origImage.getPixels().at(i).at(j), pixelNum);
				pixelNum++;
			}
		}
		imageList.push_back(newImage);
	}

	else
		cout << "Sorry! " << degrees << " degree rotations are WIP!" << endl;

}

void collage(Image &UL, Image &UR, Image &LL, Image &LR, vector<Image> &imageList) {
	// Make a custom header
	Image::Header newHeader(UL.getHeader().idLength, UL.getHeader().colorMapType, UL.getHeader().dataTypeCode, UL.getHeader().colorMapOrigin, UL.getHeader().colorMapLength,
		UL.getHeader().colorMapDepth, UL.getHeader().xOrigin, UL.getHeader().yOrigin, UL.getHeader().width + UR.getHeader().width, UL.getHeader().height + UR.getHeader().height,
		UL.getHeader().bitsPerPixel, UL.getHeader().imageDescriptor);

	unsigned int midWidth = UL.getHeader().width;
	unsigned int midHeight = UL.getHeader().height;

	Image newCollage(newHeader);
	unsigned int pixelNum = 0;

	for (unsigned int i = 0; i < newCollage.getPixels().size(); i++) {
		for (unsigned int j = 0; j < newCollage.getPixels().at(i).size(); j++) {
			if ((i < midHeight) && (j < midWidth)) {
				newCollage.addPixel(LL.getPixels().at(i).at(j), pixelNum);
				pixelNum++;
			}

			else if ((i < midHeight) && (j >= midWidth)) {
				newCollage.addPixel(LR.getPixels().at(i).at(j - midWidth), pixelNum);
				pixelNum++;
			}

			else if ((i >= midHeight) && (j < midWidth)) {
				newCollage.addPixel(UL.getPixels().at(i - midHeight).at(j), pixelNum);
				pixelNum++;
			}
			else {
				newCollage.addPixel(UR.getPixels().at(i - midHeight).at(j - midWidth), pixelNum);
				pixelNum++;
			}
		}
	}
	imageList.push_back(newCollage);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
