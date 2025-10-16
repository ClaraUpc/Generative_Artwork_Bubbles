#include "ofApp.h"

//--------------------------------------------------------------
// Clase Bubble
class Bubble {
public:
    float x, y;
    float radius;
    ofColor c;

    Bubble(float _x, float _y, float _radius) {
        x = _x;
        y = _y;
        radius = _radius;
        c.set(ofRandom(150,255), ofRandom(100,255), ofRandom(255));
    }

    void move() {
		y += ofRandom(-0.4, 0.4);
		x += ofRandom(-0.4, 0.4);

		// Rebotar en bordes
		if (x < 0) x = ofGetWidth();
		if (x > ofGetWidth()) x = 0;
		if (y < 0) y = ofGetHeight();
		if (y > ofGetHeight()) y = 0;
	}


    void display() {
        ofEnableAlphaBlending();
        for (int i = 10; i > 0; i--) {
            float alpha = ofMap(i, 10, 0, 0, 255);
            float r = radius * (float)i / 10.0;
            ofSetColor(c, alpha * 0.15);
            ofDrawCircle(x, y, r);
        }
        ofDisableAlphaBlending();
    }
};

//--------------------------------------------------------------
std::vector<Bubble> bubbles;
int numBubbles = 80;

// Colores del degradado
ofColor topColor(255, 150, 80); // naranja suave
ofColor bottomColor(80, 0, 120); // violeta profundo


//--------------------------------------------------------------
void ofApp::setup() {
	ofSetWindowShape(800, 600);
	ofSetFrameRate(60);
	ofSetCircleResolution(80);

	for (int i = 0; i < numBubbles; i++) {
		float x = ofRandom(ofGetWidth());
		float y = ofRandom(ofGetHeight());
		float radius = ofRandom(20, 50);
		bubbles.push_back(Bubble(x, y, radius));
	}
}

//--------------------------------------------------------------
void ofApp::update() {
    for (auto &b : bubbles) {
        b.move();
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
	// Fondo con degradado
	ofBackgroundGradient(topColor, bottomColor, OF_GRADIENT_LINEAR);

	// Fondo semitransparente encima para estela (suave)
	ofEnableAlphaBlending(); //
	ofSetColor(0, 0, 0, 30); // color con alpha
	ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
	ofDisableAlphaBlending(); // <- devolver al estado previo

	// Modo aditivo para efecto glow
	ofEnableBlendMode(OF_BLENDMODE_ADD);

	// Líneas entre burbujas cercanas
	for (int i = 0; i < bubbles.size(); i++) {
		for (int j = i + 1; j < bubbles.size(); j++) {
			float dist = ofDist(bubbles[i].x, bubbles[i].y, bubbles[j].x, bubbles[j].y);
			if (dist < 150) {
				ofColor c1 = bubbles[i].c;
				ofColor c2 = bubbles[j].c;
				ofColor mix = c1.getLerped(c2, 0.5);
				ofSetColor(mix, ofMap(dist, 0, 150, 255, 0));
				ofSetLineWidth(1.5);
				ofDrawLine(bubbles[i].x, bubbles[i].y, bubbles[j].x, bubbles[j].y);
			}
		}
	}

	// Dibujar burbujas difuminadas
	for (auto & b : bubbles) {
		b.display();
	}

	ofDisableBlendMode();
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 'r') {
		bubbles.clear();
		for (int i = 0; i < numBubbles; i++) {
			float x = ofRandom(ofGetWidth());
			float y = ofRandom(ofGetHeight());
			float radius = ofRandom(20, 50);
			bubbles.push_back(Bubble(x, y, radius));
		}
	}
}



//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {
}
