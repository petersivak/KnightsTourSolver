#include <QApplication>
#include <QFont>

#include "mainwindow.hpp"
#include "fontloader.hpp"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	// Set application font
	FontLoader::loadFonts();
	//QApplication::setFont(QFont("Lato", 10, QFont::Normal, false));

	MainWindow w;
	w.show();
	
	return a.exec();
}
