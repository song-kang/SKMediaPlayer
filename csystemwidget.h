#ifndef CSYSTEMWIDGET_H
#define CSYSTEMWIDGET_H

#include <QWidget>
#include "common.h"

class SKMediaPlayer;
class CSystemWidget : public QWidget
{
	Q_OBJECT

public:
	CSystemWidget(QWidget *parent = 0);
	~CSystemWidget();

	void SetApp(SKMediaPlayer *a) { m_app = a; }

private:
	QTimer *m_iTimer;
	QLabel *m_labelTime; //当前系统时间

private:
	void Init();
	void InitUi();
	void InitSlot();

public slots:
	void SlotTimeout();

private:
	SKMediaPlayer *m_app;
	
};

#endif // CSYSTEMWIDGET_H
