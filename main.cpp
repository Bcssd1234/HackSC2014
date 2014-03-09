#include <QApplication>

/** Includes for this project go here **/
#include "main_window.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	/** Set up the game **/
	MainWindow* window = new MainWindow;

	int ret = app.exec();

	/** Clean up **/
	delete window;

	return ret;
}
