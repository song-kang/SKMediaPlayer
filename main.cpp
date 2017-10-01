#include <QtGui/QApplication>
#include <QTextCodec>
#include "skmediaplayer.h"

#ifdef _DEBUG
#include "vld.h"
#endif

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
	QTextCodec *codec = QTextCodec::codecForName("System");
	QTextCodec::setCodecForLocale(codec);
	QTextCodec::setCodecForCStrings(codec);
	QTextCodec::setCodecForTr(codec);
#endif

	QTranslator translator;
	translator.load(":/translator/zh");
	a.installTranslator(&translator);

	SKMediaPlayer w;
	if (argc > 1)
		w.Play(argv[1]);
	w.show();
	return a.exec();
}
