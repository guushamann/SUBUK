#include "GLOW.h"
#include "ofAppGlutWindow.h"

//--------------------------------------------------------------
int main(){
	ofAppGlutWindow window; // create a window
	// set width, height, mode (OF_WINDOW or OF_FULLSCREEN)
	ofSetupOpenGL(&window, 1920, 1080, OF_FULLSCREEN);
	ofRunApp(new GLOW()); // start the app
}
