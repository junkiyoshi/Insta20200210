#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(2);
	ofEnableDepthTest();

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();
	this->frame.clear();

	auto x_span = 3;
	auto z_span = 10;
	for (auto z = -150; z <= 150; z += z_span) {

		auto noise_seed = ofRandom(39);
		auto start_index = this->face.getNumVertices();
		for (auto x = -300; x <= 300; x += x_span) {

			vector<glm::vec3> vertices;

			auto height = ofMap(ofNoise(noise_seed, x * 0.005, ofGetFrameNum() * 0.005), 0, 1, -150, z + 10);
			auto next_height = ofMap(ofNoise(noise_seed, (x + x_span) * 0.005, ofGetFrameNum() * 0.005), 0, 1, -150, z + 10);

			vertices.push_back(glm::vec3(x, -150, z - 5));
			vertices.push_back(glm::vec3(x + x_span, -150, z - 5));
			vertices.push_back(glm::vec3(x + x_span, next_height, z - 5));
			vertices.push_back(glm::vec3(x, height, z - 5));

			vertices.push_back(glm::vec3(x, -150, z + 5));
			vertices.push_back(glm::vec3(x + x_span, -150, z + 5));
			vertices.push_back(glm::vec3(x + x_span, next_height, z + 5));
			vertices.push_back(glm::vec3(x, height, z + 5));

			auto index = this->face.getNumVertices();
			this->face.addVertices(vertices);

			this->face.addIndex(index + 0); this->face.addIndex(index + 1); this->face.addIndex(index + 2);
			this->face.addIndex(index + 0); this->face.addIndex(index + 2); this->face.addIndex(index + 3);

			this->face.addIndex(index + 4); this->face.addIndex(index + 5); this->face.addIndex(index + 6);
			this->face.addIndex(index + 4); this->face.addIndex(index + 6); this->face.addIndex(index + 7);

			this->face.addIndex(index + 0); this->face.addIndex(index + 4); this->face.addIndex(index + 5);
			this->face.addIndex(index + 0); this->face.addIndex(index + 5); this->face.addIndex(index + 1);

			this->face.addIndex(index + 2); this->face.addIndex(index + 6); this->face.addIndex(index + 7);
			this->face.addIndex(index + 2); this->face.addIndex(index + 7); this->face.addIndex(index + 3);

			this->frame.addVertices(vertices);

			this->frame.addIndex(index + 0); this->frame.addIndex(index + 1);
			this->frame.addIndex(index + 2); this->frame.addIndex(index + 3);
			this->frame.addIndex(index + 4); this->frame.addIndex(index + 5);
			this->frame.addIndex(index + 6); this->frame.addIndex(index + 7);

			for (int i = index; i < index + 8; i++) {

				this->face.addColor(ofColor(39));
				this->frame.addColor(ofColor(239));
			}
		}

		this->face.addIndex(start_index + 0); this->face.addIndex(start_index + 4); this->face.addIndex(start_index + 7);
		this->face.addIndex(start_index + 0); this->face.addIndex(start_index + 7); this->face.addIndex(start_index + 3);

		this->frame.addIndex(start_index + 0); this->frame.addIndex(start_index + 3);
		this->frame.addIndex(start_index + 0); this->frame.addIndex(start_index + 4);
		this->frame.addIndex(start_index + 7); this->frame.addIndex(start_index + 3);
		this->frame.addIndex(start_index + 7); this->frame.addIndex(start_index + 4);

		auto index = this->face.getNumVertices() - 8;

		this->face.addIndex(index + 1); this->face.addIndex(index + 2); this->face.addIndex(index + 6);
		this->face.addIndex(index + 1); this->face.addIndex(index + 6); this->face.addIndex(index + 5);

		this->frame.addIndex(index + 1); this->frame.addIndex(index + 2);
		this->frame.addIndex(index + 1); this->frame.addIndex(index + 5);
		this->frame.addIndex(index + 6); this->frame.addIndex(index + 2);
		this->frame.addIndex(index + 6); this->frame.addIndex(index + 5);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	this->face.draw();
	this->frame.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(1280, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}