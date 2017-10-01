#ifndef CBOTTOMFLOATWIDGET_H
#define CBOTTOMFLOATWIDGET_H

#include <QWidget>
#include "common.h"

class SKMediaPlayer;
class CBottomFloatWidget : public QWidget
{
	Q_OBJECT

public:
	CBottomFloatWidget(QWidget *parent = 0);
	~CBottomFloatWidget();

	void SetApp(SKMediaPlayer *a) { m_app = a; }

	QLabel *GetLabelTime() { return m_labelTime; }
	QLabel *GetLabelVolume() { return m_labelVolume; }
	QPushButton *GetBtnStartStop() { return m_btnStartStop; }
	QSlider *GetSliderTime() { return m_sliderTime; }
	QSlider *GetSliderVolume() { return m_sliderVolume; }

protected:
	bool eventFilter(QObject *, QEvent *);
	virtual void mousePressEvent(QMouseEvent *);
	virtual void mouseReleaseEvent(QMouseEvent *);
	virtual void mouseMoveEvent(QMouseEvent *);
	virtual void mouseDoubleClickEvent(QMouseEvent *);
	virtual void paintEvent(QPaintEvent *);

private:
	QLabel *m_labelTime;			//当前时间和总时间
	QLabel *m_labelVolume;			//音量
	QPushButton *m_btnOpen;			//打开
	QPushButton *m_btnStartStop;	//启停
	QPushButton *m_btnPause;		//关闭
	QPushButton *m_btnForward;		//前进
	QPushButton *m_btnRewind;		//后退
	QPushButton *m_btnFullscreen;	//全屏
	QSlider	*m_sliderTime;			//时间轴
	QSlider *m_sliderVolume;		//音量轴

private:
	void Init();
	void InitUi();
	void InitSlot();

signals:
	void sigStartStop();
	void sigPause();
	void sigOpen();
	void sigForward();
	void sigRewind();
	void sigFullscreen();

private:
	SKMediaPlayer *m_app;
	
};

#endif // CBOTTOMFLOATWIDGET_H
