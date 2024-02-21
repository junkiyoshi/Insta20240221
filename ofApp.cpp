#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetCircleResolution(36);
}

//--------------------------------------------------------------
void ofApp::update() {

	for (int i = 0; i < 2; i++) {

		vector<glm::vec2> log;
		log.push_back(glm::vec2(0, 320));
		this->log_list.push_back(log);

		auto deg = ofRandom(250, 290);
		glm::vec2 velocity = glm::vec2(cos(deg * DEG_TO_RAD), sin(deg * DEG_TO_RAD));
		this->velocity_list.push_back(velocity);
	}

	for (int i = 0; i < this->log_list.size(); i++) {

		auto future = this->velocity_list[i] * 100;
		auto random_deg = ofMap(ofNoise(glm::vec3(this->log_list[i].front() * 0.01, ofGetFrameNum() * 0.01)), 0, 1, 0, 360);
		future += glm::vec2(30 * cos(random_deg * DEG_TO_RAD), 30 * sin(random_deg * DEG_TO_RAD));

		auto next = this->log_list[i].back() + glm::normalize(future) * 15;
		this->log_list[i].push_back(next);

		if (this->log_list[i].back().y < -300) {

			this->log_list.erase(this->log_list.begin() + i);
			this->velocity_list.erase(this->velocity_list.begin() + i);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	ofNoFill();
	for (int i = 0; i < this->log_list.size(); i++) {

		auto alpha = this->log_list[i].back().y > -200 ? 255 : ofMap(this->log_list[i].back().y, -200, -300, 255, 0);

		ofSetColor(39, alpha);
	
		ofBeginShape();
		ofVertices(this->log_list[i]);
		ofEndShape();
	}

	/*
	int start = 300;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}