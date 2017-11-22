#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	/*grabber.listDevices();
	grabber.setDeviceID();
	webcam selecteren*/

	grabber.setup(GRABBER_WIDTH, GRABBER_HEIGHT);

	rgbImage.allocate(GRABBER_WIDTH, GRABBER_HEIGHT);
	hsvImage.allocate(GRABBER_WIDTH, GRABBER_HEIGHT);
	hue.allocate(GRABBER_WIDTH, GRABBER_HEIGHT);
	saturation.allocate(GRABBER_WIDTH, GRABBER_HEIGHT);
	value.allocate(GRABBER_WIDTH, GRABBER_HEIGHT);
	filtered.allocate(GRABBER_WIDTH, GRABBER_HEIGHT);
}

//--------------------------------------------------------------
void ofApp::update() {
	grabber.update();
	if (grabber.isFrameNew()) {
		rgbImage.setFromPixels(grabber.getPixels().getData(), GRABBER_WIDTH, GRABBER_HEIGHT);
		//geef me de pixels binnen de grab. If == doet dit alleen als er een nieuwe frame binnenkomt om te veel werk te voorkomen

		rgbImage.mirror(false, true);

		hsvImage = rgbImage;
		hsvImage.convertRgbToHsv();

		hsvImage.convertToGrayscalePlanarImages(hue, saturation, value);

		if (testBool = true) {
			for (int i = 0; i < GRABBER_WIDTH*GRABBER_HEIGHT; i++) {
				if (ofInRange(hue.getPixels()[i], findHue - HUE_MARGIN, findHue + HUE_MARGIN)) {
					filtered.getPixels()[i] = 255;
				}
				else {
					filtered.getPixels()[i] = 0;
				}
			}
		}
		if (testBool = false) {
			for (int i = 0; i < GRABBER_WIDTH*GRABBER_HEIGHT; i++) {
				if (ofInRange(hue.getPixels()[i], findHue2 - HUE_MARGIN, findHue2 + HUE_MARGIN)) {
					filtered.getPixels()[i] = 255;
				}
				else {
					filtered.getPixels()[i] = 0;
				}

			}
			filtered.flagImageChanged();

			contours.findContours(filtered, MIN_SIZE, GRABBER_WIDTH * GRABBER_HEIGHT, 1, false);
			//blob minimaal 50 groot, en maximaal helft van het scherm
		
			}
		}
	}


//--------------------------------------------------------------
void ofApp::draw() {
	if (showVideo) {
		rgbImage.draw(0, 0, ofGetWidth(), ofGetHeight());
	}

	if (showHSVComponents) {
		hsvImage.draw(0, 0);
		hue.draw(0, 240);
		saturation.draw(320, 240);
		value.draw(640, 240);
	}

	if (showFiltered) {
		filtered.draw(0, 480);
		if (showContours) {
			contours.draw(0, 480);
		}
	}
}

//void ofApp::newHue()
//{
//	hue1 = findHue;
//	hue2 = findHue2;
//
//}


//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 'h') {
		showHSVComponents = !showHSVComponents;
	}
	else if (key == 'v') {
		showVideo = !showVideo;
	}
	else if (key == 'c') {
		showContours = !showContours;
	}
	else if (key == 'f') {
		showFiltered = !showFiltered;	
	}
	else if (key == 'i') {
		testBool = !testBool;
		ofLog() << "testBool =" << testBool;
	}
}


void ofApp::mousePressed(int x, int y, int button) {
	findHue = hue.getPixels()[y * GRABBER_WIDTH + x];
	ofLog() << "true hue 1 =" << findHue;
	findHue2 = hue.getPixels()[y * GRABBER_WIDTH + x];
	ofLog() << "false hue 2 =" << findHue2;

	
	
}

