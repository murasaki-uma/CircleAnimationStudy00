#include "ofApp.h"



class LimpCircle 
{
public:
	LimpCircle(void) {};
	~LimpCircle(void) {};

	void setup(int VertexNum, float Radius, float RandomRange, ofVec2f Scale, float AnchorRange)
	{
		vertexNum = VertexNum;
		startRadius = Radius;
		radius = startRadius;
		randomRange = RandomRange;
		scale = Scale;
		startScale = Scale;
		anchorRange = AnchorRange;
		speed = ofRandom(1.0,3.0);
		createCircle();
	}

	void createCircle()
	{
		circle.clear();
		for (int i = 0; i < vertexNum; i++)
		{
			randomRaiuds.push_back(ofRandom(-randomRange, randomRange));
		}

		for (int i = 0; i < vertexNum; i++) {
			float x, y;
			float r = ofMap(i, 0, vertexNum, 0, TWO_PI);

			x = (radius*scale.x + randomRaiuds[i]) * cos(r);
			y = (radius*scale.y + randomRaiuds[i]) * sin(r);

			float start_anc_x = x + anchorRange * cos(TWO_PI / 4 * 1 + r);
			float start_anc_y = y + anchorRange * sin(TWO_PI / 4 * 1 + r);

			float next_r;
			if (i < vertexNum - 1) {
				next_r = ofMap(i + 1, 0, vertexNum, 0, TWO_PI);
			}
			else {

				next_r = ofMap(i + 1, 0, vertexNum, 0, TWO_PI);
			}
			circle.addVertex(x, y);

			float nextX, nextY;

			if (i < vertexNum - 1) {
				nextX = (radius*scale.x + randomRaiuds[i + 1])* cos(next_r);
				nextY = (radius*scale.y + randomRaiuds[i + 1])* sin(next_r);
			}
			else {
				nextX = (radius*scale.x + randomRaiuds[0])* cos(next_r);
				nextY = (radius*scale.y + randomRaiuds[0])* sin(next_r);
			}

			float next_anc_x = nextX + anchorRange * cos(TWO_PI / 4 * 3 + next_r);
			float next_anc_y = nextY + anchorRange * sin(TWO_PI / 4 * 3 + next_r);
			circle.bezierTo(start_anc_x, start_anc_y, next_anc_x, next_anc_y, nextX, nextY);

			if (DEBUG_MODE)
			{
				ofPushStyle();
				ofSetColor(240, 40, 40, 200);
				ofDrawLine(nextX, nextY, next_anc_x, next_anc_y);
				ofDrawLine(x, y, start_anc_x, start_anc_y);

				ofDrawCircle(next_anc_x, next_anc_y, 3);
				ofDrawCircle(start_anc_x, start_anc_y, 3);

				ofDrawBitmapString(ofToString(vertexNum) + " / " + ofToString(i), x, y);

				ofPopStyle();
			}
		}
		circle.close();
	}

	void init() 
	{
		scale = startScale;
		position.set(0, 0, 0);
		randomRaiuds.clear();
		radius = startRadius;
		setup(vertexNum,radius,randomRange,scale,anchorRange);
	}

	void setPosition(ofVec3f Position, float Radian) 
	{
		position = Position;
		radian = Radian;
	}

	void setPosition(float Dist, float Radian)
	{
		dist = Dist;
		radian = Radian;
	}

	void update() {
		speed *= 1.01;
		dist += speed;
		radius += speed*0.3;
		scale.y += speed*0.001;
		createCircle();
	}

	void draw()
	{
		ofPushMatrix();
		
		ofRotateZ(ofRadToDeg(radian));
		ofTranslate(0, dist);
		circle.draw();
		ofPopMatrix();
	}
private:
	int vertexNum;
	float radius;
	float startRadius;
	ofVec2f startScale;
	float randomRange;
	vector<float>randomRaiuds;
	ofVec2f scale;
	float anchorRange;
	ofPolyline circle;
	bool DEBUG_MODE;
	ofVec3f position;
	float radian;
	float dist;

	float speed;
};


vector<LimpCircle> limpCircles;
vector<float>limpCirclePosRadius;
vector<float>limpCirclePosRadian;
//--------------------------------------------------------------
void ofApp::setup(){
	
	MathValue.setName("Math Value");
	//MathValue.add(vertNum.set("vertNum", 100, 0, 500));
	MathValue.add(vert_num_test.set("vert_num_test", 10, 0, 100));
	MathValue.add(radius_base.set("radius_base", 300, 0, ofGetWidth()/2));
	MathValue.add(radiusScale.set("radiusScale", ofVec2f(1.0, 1.0), ofVec2f(0,0), ofVec2f(1.0,1.0)));
	//MathValue.add(radian_A.set("radian_A", 0.0, 0.0, 5.0));
	//MathValue.add(t1.set("t1", 0.00, 0.00, 1.0));
	//MathValue.add(t2.set("t2", 0.00, 0.00, 1.0));
	//MathValue.add(h2.set("h2", 0.5, 0.00, 1.0));
	MathValue.add(ancPosRad.set("ancPosRad", 60.0, 0.0, 200.0));
	MathValue.add(randomPosRange.set("randomPosRange", 30, 0, 200));
	MathValue.add(DEBUG_MODE.set("DEBUG_MODE", false));
	MathValue.add(resetRandomPos.set("resetRandomPos", false));
	
	gui.setup(MathValue);

	//limpcircle.setup(6, 100, 30, ofVec2f(0.6, 1), 40);

	for (int i = 0; i < 10; i++) 
	{
		LimpCircle l;
		l.setup(6, ofRandom(20, 40), ofRandom(20, 40), ofVec2f(0.6, 1), ofRandom(10,20));
		limpCircles.push_back(l);
		limpCirclePosRadius.push_back(0);
		limpCirclePosRadian.push_back(ofRandom(0,TWO_PI));
		limpCircles[i].setPosition(limpCirclePosRadius[i], limpCirclePosRadian[i]);
	}
	
}

//--------------------------------------------------------------
void ofApp::update(){
	
	for (int i = 0; i < 10; i++)
	{		
		limpCirclePosRadius[i]++;
		//float x = limpCirclePosRadius[i] * cos(limpCirclePosRadian[i]);
		//float y = limpCirclePosRadius[i] * sin(limpCirclePosRadian[i]);
		//limpCircles[i].setPosition(limpCirclePosRadius[i], limpCirclePosRadian[i]);
		limpCircles[i].update();
	}
	
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0);
	
	ofPushMatrix();
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
	

	for (int i = 0; i < 10; i++)
	{
		ofPushMatrix();
		limpCircles[i].draw();
		ofPopMatrix();
	}
		
	ofPopMatrix();

	
	gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}
//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	

	for (int i = 0; i < 10; i++)
	{
		limpCircles[i].init();
		limpCirclePosRadius.clear();
		limpCirclePosRadian.clear();
		for (int i = 0; i < 10; i++)
		{
			limpCirclePosRadius.push_back(0);
			limpCirclePosRadian.push_back(ofRandom(0, TWO_PI));
			limpCircles[i].setPosition(limpCirclePosRadius[i], limpCirclePosRadian[i]);
		}

	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
