#ifndef CABOUTWIDGET_H
#define CABOUTWIDGET_H

#include <QWidget>
#include "common.h"
#include "AbsFrameLessAutoSize.h"

# define VERSION_MAJOR		2	/** major version number */
# define VERSION_MINOR		0	/** minor version number */
# define VERSION_REVISION	6	/** revision */

//////////////////// CAboutTopWidget ////////////////////
class CAboutTopWidget : public QWidget
{
	Q_OBJECT

public:
	CAboutTopWidget(QWidget *parent = 0);
	~CAboutTopWidget();

protected:
	bool eventFilter(QObject *, QEvent *);
	virtual void mousePressEvent(QMouseEvent *);
	virtual void mouseReleaseEvent(QMouseEvent *);
	virtual void mouseMoveEvent(QMouseEvent *);
	virtual void mouseDoubleClickEvent(QMouseEvent *);
	virtual void paintEvent(QPaintEvent *);

private:
	QLabel *m_labelTitle;		//±ÍÃ‚
	QPushButton *m_btnClose;	//πÿ±’

private:
	void Init();
	void InitUi();
	void InitSlot();

signals:
	void sigSkinClose();
};

//////////////////// CAboutCenterWidget ////////////////////
class CAboutCenterWidget : public QWidget
{
	Q_OBJECT

public:
	CAboutCenterWidget(QWidget *parent = 0);
	~CAboutCenterWidget();

protected:
	bool eventFilter(QObject *, QEvent *);
	virtual void mousePressEvent(QMouseEvent *);
	virtual void mouseReleaseEvent(QMouseEvent *);
	virtual void mouseMoveEvent(QMouseEvent *);
	virtual void mouseDoubleClickEvent(QMouseEvent *);
	virtual void paintEvent(QPaintEvent *);

private:
	QLabel *m_version;
	QLabel *m_copyright;
	QLabel *m_declare;
	QLabel *m_declare1;
	QLabel *m_declare2;
	QLabel *m_declare3;
	QLabel *m_declare4;
	QLabel *m_declare5;

private:
	void Init();
	void InitUi();
	void InitSlot();
};

//////////////////// CAboutWidget ////////////////////
class SKMediaPlayer;
class CAboutWidget : public AbsFrameLessAutoSize
{
	Q_OBJECT

public:
	CAboutWidget(QWidget *parent);
	~CAboutWidget();

	void SetApp(SKMediaPlayer *a) { m_app = a; }
	void setSkin(const QString &str);

protected:
	virtual void mouseMoveEvent(QMouseEvent *);
	virtual void paintEvent(QPaintEvent *);

private:
	CAboutTopWidget *m_aboutTopWidget;
	CAboutCenterWidget *m_aboutCenterWidget;

	QString m_curPixPath;
	QPixmap m_localPix;
	QPixmap m_netPix;
	QPixmap m_curPix;
	QRect m_rect;
	bool m_issetpix;
	bool m_isShowSingerBG;
	int m_curindex;

private:
	void Init();
	void InitUi();
	void InitSlot();

	void setPixmap(const QPixmap &);
	void setShowSingerBG(bool is = true);
	bool isShowSingerBG() { return m_isShowSingerBG; }
	void setCurrentIndex(int);
	inline int CurrentIndex() { return m_curindex; }
	void clearBg();
	inline QPixmap currentSkin() { return m_curPix; }
	const QString currentSkinPath() { return m_curPixPath; }
	inline QPixmap getRectPix(const QRect&rect) { update(); return m_curPix.copy(rect); }

private:
	SKMediaPlayer *m_app;
	
};

#endif // CABOUTWIDGET_H
