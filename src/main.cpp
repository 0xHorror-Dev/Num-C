#include "Application/App.h"

int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR,int) {
	
	App* application = new App();

	if (!application->Init()) {
		delete application;
		return -1;
	}

	int Res = application->Start();

	delete application;

	return Res;
}