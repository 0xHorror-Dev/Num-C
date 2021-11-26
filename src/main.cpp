#include "Application/App.h"

int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR,int) {
	
	App* application = new App();

	if (!application->Init()) {
		delete application;
		return -1;
	}

	delete application;

	return 0;
}