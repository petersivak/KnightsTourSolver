#include "fontloader.hpp"

#include <QFontDatabase>

void FontLoader::loadFonts()
{
	QFontDatabase::addApplicationFont(":/fonts/lato.ttf");
}
