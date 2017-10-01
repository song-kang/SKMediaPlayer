#ifndef CMAINWIDGET_H
#define CMAINWIDGET_H

#include <QWidget>
#include "common.h"

class CMainWidget : public QWidget
{
	Q_OBJECT

public:
	CMainWidget(QWidget *parent = 0);
	~CMainWidget();

	QString GetCurSkin() { return m_curPixPath; }

protected:
	void paintEvent(QPaintEvent *e);

private:
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
	void setSkin(const QString &str);

};

#endif // CMAINWIDGET_H
