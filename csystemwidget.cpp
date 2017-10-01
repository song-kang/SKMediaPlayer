#include "csystemwidget.h"
#include "skmediaplayer.h"

CSystemWidget::CSystemWidget(QWidget *parent)
	: QWidget(parent)
{
	Init();
	InitUi();
	InitSlot();

	m_iTimer->start();
}

CSystemWidget::~CSystemWidget()
{

}

void CSystemWidget::Init()
{
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool | Qt::X11BypassWindowManagerHint);
	setAttribute(Qt::WA_TranslucentBackground,true);

	m_iTimer = new QTimer(this);
	m_iTimer->setInterval(1000);
}

void CSystemWidget::InitUi()
{
	m_labelTime = new QLabel(this);

	QFont m_font;
	m_font.setFamily("Microsoft YaHei");
	m_font.setPixelSize(14);
	m_font.setBold(true);
	m_labelTime->setFont(m_font);
	m_labelTime->setStyleSheet("color:white;");
	m_labelTime->setText("00:00");

	QHBoxLayout *timeLayout = new QHBoxLayout();
	timeLayout->addStretch();
	timeLayout->addWidget(m_labelTime,0,Qt::AlignCenter);
	timeLayout->addStretch();
	timeLayout->setContentsMargins(0,0,0,0);

	setLayout(timeLayout);
}

void CSystemWidget::InitSlot()
{
	connect(m_iTimer, SIGNAL(timeout()), this, SLOT(SlotTimeout()));
}

void CSystemWidget::SlotTimeout()
{
	QTime time = QTime::currentTime();

	QString t;
	t.sprintf("%02d:%02d",time.hour(),time.minute());
	m_labelTime->setText(t);

	if (m_app->isFullScreen())
	{
		int curMonitor = QApplication::desktop()->screenNumber(m_app);
		QRect rect = QApplication::desktop()->screenGeometry(curMonitor);
		setFixedSize(50,20);
		move(rect.x()+rect.width()-70,10);
		if (m_app->m_bIsShowSystemTime)
			show();
		else
			hide();
	}
}
