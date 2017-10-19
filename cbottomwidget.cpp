#include "cbottomwidget.h"
#include "skmediaplayer.h"
#include <vlc/vlc.h>

CBottomWidget::CBottomWidget(QWidget *parent)
	: QWidget(parent)
{
	Init();
	InitUi();
	InitSlot();
}

CBottomWidget::~CBottomWidget()
{

}

void CBottomWidget::Init()
{
	setStyleSheet("QWidget{background:transparent;}");
	setMouseTracking(true);
}

void CBottomWidget::InitUi()
{
	m_labelTime = new QLabel(this);
	m_labelVolume = new QLabel(this);
	m_btnOpen = new QPushButton(this);
	m_btnPause = new QPushButton(this);
	m_btnStartStop = new QPushButton(this);
	m_btnForward = new QPushButton(this);
	m_btnRewind = new QPushButton(this);
	m_btnFullscreen = new QPushButton(this);
	m_btnList = new PushButton(this);
	m_sliderTime = new QSlider(Qt::Horizontal,this);
	m_sliderVolume = new QSlider(Qt::Horizontal,this);

	QFont m_font;
	m_font.setFamily("Microsoft YaHei");
	m_font.setPixelSize(12);
	m_labelTime->setFont(m_font);
	m_labelTime->setStyleSheet("color:white;");
	m_labelTime->setText("00:00:00/00:00:00");

	m_labelVolume->setStyleSheet("background:transparent;");
	m_labelVolume->setPixmap(QPixmap(":/image/Speak2"));

	m_btnStartStop->setFixedSize(44,44);
	m_btnStartStop->setToolTip(tr("Play/Pause"));
	m_btnStartStop->setStyleSheet(
		"QPushButton{border-image:url(:/image/btn_play_nor);}"
		"QPushButton::hover{border-image:url(:/image/btn_play_hover);}"
		"QPushButton::pressed{border-image:url(:/image/btn_play_down);}");

	m_btnOpen->setFixedSize(32,32);
	m_btnOpen->setToolTip(tr("Open file"));
	m_btnOpen->setStyleSheet(
		"QPushButton{border-image:url(:/image/open_nor);}"
		"QPushButton::hover{border-image:url(:/image/open_hover);}"
		"QPushButton::pressed{border-image:url(:/image/open_down);}");

	m_btnPause->setFixedSize(32,32);
	m_btnPause->setToolTip(tr("Stop"));
	m_btnPause->setStyleSheet(
		"QPushButton{border-image:url(:/image/stop_nor);}"
		"QPushButton::hover{border-image:url(:/image/stop_hover);}"
		"QPushButton::pressed{border-image:url(:/image/stop_down);}");

	m_btnForward->setFixedSize(32,32);
	m_btnForward->setToolTip(tr("Forward"));
	m_btnForward->setStyleSheet(
		"QPushButton{border-image:url(:/image/forward_nor);}"
		"QPushButton::hover{border-image:url(:/image/forward_hover);}"
		"QPushButton::pressed{border-image:url(:/image/forward_down);}");

	m_btnRewind->setFixedSize(32,32);
	m_btnRewind->setToolTip(tr("Rewind"));
	m_btnRewind->setStyleSheet(
		"QPushButton{border-image:url(:/image/rewind_nor);}"
		"QPushButton::hover{border-image:url(:/image/rewind_hover);}"
		"QPushButton::pressed{border-image:url(:/image/rewind_down);}");

	m_btnFullscreen->setFixedSize(24,24);
	m_btnFullscreen->setToolTip(tr("Full Screen"));
	m_btnFullscreen->setStyleSheet(
		"QPushButton{border-image:url(:/image/fullscreen_nor);}"
		"QPushButton::hover{border-image:url(:/image/fullscreen_hover);}"
		"QPushButton::pressed{border-image:url(:/image/fullscreen_down);}");

	m_btnList->loadPixmap(":/image/list");
	m_btnList->setToolTip(tr("List"));

	m_sliderTime->setMaximumHeight(10);
	m_sliderTime->setCursor(QCursor(Qt::PointingHandCursor));
	m_sliderTime->setRange(0,0);
	m_sliderTime->installEventFilter(this);
	m_sliderTime->setStyleSheet("QSlider::groove:horizontal{border-radius:2px;height:3px;}"
		"QSlider::sub-page:horizontal{background:rgb(255, 255, 160);}"
		"QSlider::add-page:horizontal{background:rgb(200,200,209);}"
		"QSlider::handle:horizontal{background:rgb(255, 255, 160);width:8px;border-radius:4px;margin:-3px 0px -3px 0px;}");

	m_sliderVolume->setFixedSize(80,10);
	m_sliderVolume->setCursor(QCursor(Qt::PointingHandCursor));
	m_sliderVolume->setRange(0,100);
	m_sliderVolume->setValue(80);
	m_sliderVolume->installEventFilter(this);
	m_sliderVolume->setStyleSheet("QSlider::groove:horizontal{border-radius:2px;height:3px;}"
		"QSlider::sub-page:horizontal{background:rgb(255, 255, 160);}"
		"QSlider::add-page:horizontal{background:rgb(200,200,209);}"
		"QSlider::handle:horizontal{background:rgb(255, 255, 160);width:8px;border-radius:4px;margin:-3px 0px -3px 0px;}");

	QHBoxLayout *timeLayout = new QHBoxLayout();
	timeLayout->addWidget(m_sliderTime);
	timeLayout->setContentsMargins(10,0,10,0);

	QHBoxLayout *hLayout1 = new QHBoxLayout();
	hLayout1->addWidget(m_labelTime,0,Qt::AlignVCenter);
	hLayout1->addStretch();
	hLayout1->setSpacing(0);
	hLayout1->setContentsMargins(15,0,0,0);

	QHBoxLayout *hLayout2 = new QHBoxLayout();
	hLayout2->addStretch();
	hLayout2->addWidget(m_btnOpen,0,Qt::AlignVCenter);
	hLayout2->addWidget(m_btnRewind,0,Qt::AlignVCenter);
	hLayout2->addWidget(m_btnStartStop,0,Qt::AlignVCenter);
	hLayout2->addWidget(m_btnForward,0,Qt::AlignVCenter);
	hLayout2->addWidget(m_btnPause,0,Qt::AlignVCenter);
	hLayout2->addStretch();
	hLayout2->setSpacing(10);
	hLayout2->setContentsMargins(0,0,0,0);

	QHBoxLayout *hLayout3 = new QHBoxLayout();
	hLayout3->addStretch();
	hLayout3->addWidget(m_labelVolume,0,Qt::AlignVCenter);
	hLayout3->addWidget(m_sliderVolume,0,Qt::AlignVCenter);
	hLayout3->setSpacing(3);
	hLayout3->setContentsMargins(0,0,0,0);

	QHBoxLayout *hLayout4 = new QHBoxLayout();
	hLayout4->addStretch();
	hLayout4->addWidget(m_btnFullscreen,0,Qt::AlignVCenter);
	hLayout4->addWidget(m_btnList,0,Qt::AlignVCenter);
	hLayout4->setSpacing(10);
	hLayout4->setContentsMargins(0,0,0,0);

	QHBoxLayout *hLayout5 = new QHBoxLayout();
	hLayout5->addStretch();
	hLayout5->addLayout(hLayout3);
	hLayout5->addLayout(hLayout4);
	hLayout5->setSpacing(40);
	hLayout5->setContentsMargins(0,0,15,0);

	QHBoxLayout *hLayout = new QHBoxLayout();
	hLayout->addLayout(hLayout1);
	hLayout->addLayout(hLayout2);
	hLayout->addLayout(hLayout5);

	QVBoxLayout *vLayout = new QVBoxLayout();
	vLayout->addLayout(timeLayout);
	vLayout->addLayout(hLayout);
	vLayout->setSpacing(0);
	vLayout->setContentsMargins(0,1,0,0);

	setLayout(vLayout);
	setFixedHeight(65);
}

void CBottomWidget::InitSlot()
{
	connect(m_btnStartStop, SIGNAL(clicked()), this, SIGNAL(sigStartStop()));
	connect(m_btnPause, SIGNAL(clicked()), this, SIGNAL(sigPause()));
	connect(m_btnOpen, SIGNAL(clicked()), this, SIGNAL(sigOpen()));
	connect(m_btnForward, SIGNAL(clicked()), this, SIGNAL(sigForward()));
	connect(m_btnRewind, SIGNAL(clicked()), this, SIGNAL(sigRewind()));
	connect(m_btnFullscreen, SIGNAL(clicked()), this, SIGNAL(sigFullscreen()));
	connect(m_btnList, SIGNAL(clicked()), this, SIGNAL(sigPlaylist()));
}

bool CBottomWidget::eventFilter(QObject *o, QEvent *e)
{
	if (o == m_sliderVolume)
	{
		QMouseEvent *ev=static_cast<QMouseEvent*>(e);
		if (e->type() == QEvent::MouseButtonPress)
		{
			if (ev->button() == Qt::LeftButton)
			{
				int dur = m_sliderVolume->maximum()- m_sliderVolume->minimum();
				int pos = m_sliderVolume->minimum() + dur * ((double)ev->x() / m_sliderVolume->width());
				if(pos != m_sliderVolume->sliderPosition())
					m_sliderVolume->setValue(pos);
				m_app->SetCenterWidgetFocus();
			}
		}
	}
	else if (o == m_sliderTime)
	{
		QMouseEvent *ev=static_cast<QMouseEvent*>(e);
		if (e->type() == QEvent::MouseButtonRelease)
		{
			if (ev->button() == Qt::LeftButton && m_app->GetPlayer())
			{
				int dur = m_sliderTime->maximum()- m_sliderTime->minimum();
				int pos = m_sliderTime->minimum() + dur * ((double)ev->x() / m_sliderTime->width());
				if(pos != m_sliderTime->sliderPosition())
				{
					m_sliderTime->setValue(pos);
					//libvlc_media_player_set_position(m_app->GetPlayer(),(float)pos/dur);
					//if (pos >= dur)
					//	m_app->SlotPause();
				}

				m_app->m_bPauseSliderTime = false;
				m_app->m_bClickSliderTime = true;
				m_app->SetCenterWidgetFocus();
			}
		}
		else if (e->type() == QEvent::MouseMove)
		{
			m_app->m_bPauseSliderTime = true;
		}
	}

	return QObject::eventFilter(o,e);
}

void CBottomWidget::mousePressEvent(QMouseEvent *e)
{
	QWidget::mousePressEvent(e);
}

void CBottomWidget::mouseReleaseEvent(QMouseEvent *e)
{
	QWidget::mouseReleaseEvent(e);
}

void CBottomWidget::mouseMoveEvent(QMouseEvent *e)
{
	setCursor(Qt::ArrowCursor);
	QWidget::mouseMoveEvent(e);
}

void CBottomWidget::mouseDoubleClickEvent(QMouseEvent *e)
{
	QWidget::mouseDoubleClickEvent(e);
}

void CBottomWidget::paintEvent(QPaintEvent *e)
{
	QWidget::paintEvent(e);
}
