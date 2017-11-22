#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include <vector>

#define GRABBER_WIDTH 320
#define GRABBER_HEIGHT 240
#define HUE_MARGIN 5
#define MIN_SIZE 50


class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();
	/*void newHue();*/

	void keyPressed(int key);
	void mousePressed(int x, int y, int button);


	ofVideoGrabber grabber;

	ofxCvColorImage rgbImage;
	ofxCvColorImage hsvImage;
	//hue saturation value (brightness)
	ofxCvGrayscaleImage hue;
	ofxCvGrayscaleImage saturation;
	ofxCvGrayscaleImage value;

	ofxCvGrayscaleImage filtered;

	ofxCvContourFinder contours;

	bool showHSVComponents = false;
	bool showVideo = true;
	bool showFiltered = true;
	bool showContours = true;

	bool testBool = true;


	int findHue;
	int findHue2;

	/*int hue1;
	int hue2;*/

	

};
