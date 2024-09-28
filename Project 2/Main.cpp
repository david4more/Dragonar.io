#include "App.h"

int main() {
	App app;
	// asdads
	while(app.isRunning())
	{
		app.update();
		app.render();
	}

	return 69;
}