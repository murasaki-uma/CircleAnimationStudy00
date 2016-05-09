#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		

		ofxPanel gui;
		ofParameterGroup MathValue;
		ofParameter<int> vertNum;
		ofParameter<float> radian_A;
		ofParameter<float> radius_base;
		ofParameter<float> t1;
		ofParameter<float> t2;
		ofParameter<float> h2;
		ofParameter<int> vert_num_test;
		ofParameter<float> ancPosRad;
		ofParameter<bool> DEBUG_MODE;
		ofParameter<bool> resetRandomPos;
		ofParameter<float> randomPosRange;
		ofParameter<ofVec2f> radiusScale;
		
};
