#ifndef COMMON_H
#define COMMON_H

#include <QAbstractButton>
#include <QApplication>
#include <QCoreApplication>
#include <QCryptographicHash>
#include <QCursor>
#include <QDate>
#include <QDateTime>
#include <QDesktopServices>
#include <QDesktopWidget>
#include <QDir>
//#include <QDomDocument>
#include <QFile>
#include <QFileDialog>
#include <QFileIconProvider>
#include <QFont>
#include <QFontMetrics>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QMessageBox>
#include <QObject>
#include <QPainter>
#include <QPaintEvent>
#include <QPainterPath>
#include <QPen>
#include <QPixmap>
#include <QProcess>
#include <QPushButton>
#include <QSettings>
#include <QSound>
#include <QStyleFactory>
#include <QStyleOption>
#include <QTextCodec>
#include <QTime>
#include <QTimer>
#include <QtGui>
#include <QUrl>
#include <QWidget>
#include <qmath.h>

#define	VERSION		"1.0.0"

#define qSafeDelete(p) do { if(p) delete (p); (p)=0; } while(0)

typedef enum{
	UI_ZH,
	UI_EN
}LANGUAGE;

typedef struct stuMediaTrack
{
	int trackId;
	QString trackDesc;
} stuMediaTrack;

class common
{
public:
	common();
	~common();

    static QString GetCurrentAppPath();
	static QString GetCurrentAppName();
	static QString GetLongDateTime();
	static bool FileExists(QString strFile);
	static int	FileLineCount(QString strFile);
	static bool FolderExists(QString strFolder);
	static bool CreateFolder(QString strFolder);

private:
	
};

#endif // COMMON_H
