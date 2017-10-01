#include "csimpleparamwidget.h"
#include "skmediaplayer.h"

CSimpleParamWidget::CSimpleParamWidget(QWidget *parent)
	: QWidget(parent)
{
	Init();
	InitUi();
	InitSlot();
}

CSimpleParamWidget::~CSimpleParamWidget()
{
	
}

void CSimpleParamWidget::Init()
{
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool | Qt::X11BypassWindowManagerHint);
	setAttribute(Qt::WA_TranslucentBackground,true);
}

void CSimpleParamWidget::InitUi()
{
	m_labelTime = new QLabel(this);
	m_labelVolume = new QLabel(this);

	QFont m_font;
	m_font.setFamily("Microsoft YaHei");
	m_font.setPixelSize(14);
	m_font.setBold(true);
	m_labelTime->setFont(m_font);
	m_labelTime->setStyleSheet("color:white;");
	m_labelTime->setText("00:00:00");

	m_labelVolume->setFont(m_font);
	m_labelVolume->setStyleSheet("color:white;");
	m_labelVolume->setText(tr("volume 80"));

	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->addWidget(m_labelTime,0,Qt::AlignTop);
	layout->addStretch();
	layout->addWidget(m_labelVolume,0,Qt::AlignBottom);
	layout->setContentsMargins(0,0,0,0);

	setLayout(layout);
}

void CSimpleParamWidget::InitSlot()
{

}
