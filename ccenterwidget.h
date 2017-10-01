#ifndef CCENTERWIDGET_H
#define CCENTERWIDGET_H

#include <QWidget>
#include "common.h"
#include "ccentermenu.h"

class SKMediaPlayer;
class CCenterWidget : public QWidget
{
	Q_OBJECT

public:
	CCenterWidget(QWidget *parent = 0);
	~CCenterWidget();

	void SetApp(SKMediaPlayer *a) { m_app = a; }

protected:
	bool eventFilter(QObject *, QEvent *);
	virtual void mousePressEvent(QMouseEvent *);
	virtual void mouseReleaseEvent(QMouseEvent *);
	virtual void mouseMoveEvent(QMouseEvent *);
	virtual void mouseDoubleClickEvent(QMouseEvent *);
	virtual void paintEvent(QPaintEvent *);

protected:
	void dragEnterEvent(QDragEnterEvent *event);
	void dropEvent(QDropEvent *event);

private:
	QLabel *m_labelLogo;

private:
	void Init();
	void InitUi();

private:
	SKMediaPlayer *m_app;

};

#endif // CCENTERWIDGET_H
