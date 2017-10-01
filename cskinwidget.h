#ifndef CSKINWIDGET_H
#define CSKINWIDGET_H

#include <QWidget>
#include "common.h"
#include "AbsFrameLessAutoSize.h"

//////////////////// CSkinTopWidget ////////////////////
class CSkinTopWidget : public QWidget
{
	Q_OBJECT

public:
	CSkinTopWidget(QWidget *parent = 0);
	~CSkinTopWidget();

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

//////////////////// CSkinCenterWidget ////////////////////
class CSkinCenterWidget : public QWidget
{
	Q_OBJECT

public:
	CSkinCenterWidget(QWidget *parent = 0);
	~CSkinCenterWidget();

protected:
	bool eventFilter(QObject *, QEvent *);
	virtual void mousePressEvent(QMouseEvent *);
	virtual void mouseReleaseEvent(QMouseEvent *);
	virtual void mouseMoveEvent(QMouseEvent *);
	virtual void mouseDoubleClickEvent(QMouseEvent *);
	virtual void paintEvent(QPaintEvent *);

private:
	QLabel *m_labelSkin0;
	QLabel *m_labelSkin1;
	QLabel *m_labelSkin2;
	QLabel *m_labelSkin3;
	QLabel *m_labelSkin4;
	QLabel *m_labelSkin5;
	QLabel *m_labelSkin6;
	QLabel *m_labelSkin7;
	QPushButton *m_btnSkin0;
	QPushButton *m_btnSkin1;
	QPushButton *m_btnSkin2;
	QPushButton *m_btnSkin3;
	QPushButton *m_btnSkin4;
	QPushButton *m_btnSkin5;
	QPushButton *m_btnSkin6;
	QPushButton *m_btnSkin7;

private:
	void Init();
	void InitUi();
	void InitSlot();

signals:
	void sigSkin0();
	void sigSkin1();
	void sigSkin2();
	void sigSkin3();
	void sigSkin4();
	void sigSkin5();
	void sigSkin6();
	void sigSkin7();
};

//////////////////// CSkinWidget ////////////////////
class SKMediaPlayer;
class CSkinWidget : public AbsFrameLessAutoSize
{
	Q_OBJECT

public:
	CSkinWidget(QWidget *parent = 0);
	~CSkinWidget();

	void SetApp(SKMediaPlayer *a) { m_app = a; }
	void setSkin(const QString &str);

protected:
	virtual void mouseMoveEvent(QMouseEvent *);
	virtual void paintEvent(QPaintEvent *);

private:
	CSkinTopWidget *m_skinTopWidget;
	CSkinCenterWidget *m_skinCenterWidget;

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

public slots:
	void SlotSkin0();
	void SlotSkin1();
	void SlotSkin2();
	void SlotSkin3();
	void SlotSkin4();
	void SlotSkin5();
	void SlotSkin6();
	
private:
	SKMediaPlayer *m_app;
};

#endif // CSKINWIDGET_H
