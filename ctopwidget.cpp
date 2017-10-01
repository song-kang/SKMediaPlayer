#include "ctopwidget.h"

#define TOPWIDGET_HEIGHT	30

CTopWidget::CTopWidget(QWidget *parent)
	: QWidget(parent)
{
	Init();
	InitUi();
}

CTopWidget::~CTopWidget()
{

}

void CTopWidget::Init()
{
	setStyleSheet("QWidget{background:transparent;}");
	setMouseTracking(true);
}

void CTopWidget::InitUi()
{
	m_labelLogo = new QLabel(this);
	m_labelTitle = new QLabel(this);
	m_btnSkin = new PushButton(this);
	m_btnMainMenu = new QPushButton(this);
	m_btnMinimize = new QPushButton(this);
	m_btnMaximize = new QPushButton(this);
	m_btnClose = new QPushButton(this);
	m_btnSplit = new QPushButton(this);

	m_labelLogo->setStyleSheet("background:transparent;");
	m_labelLogo->setPixmap(QPixmap(":/image/mediaplayer_24"));

	QFont m_font;
	m_font.setFamily("Microsoft YaHei");
	m_font.setPixelSize(13);
	m_font.setBold(true);
	m_labelTitle->setFont(m_font);
	m_labelTitle->setStyleSheet("color:white;");
	m_labelTitle->setText(" "+tr("SKMediaPlayer"));

	m_btnSkin->loadPixmap(":/image/Skin");
	m_btnSkin->setToolTip(tr("Skin"));

	m_btnMinimize->setFixedSize(34,24);
	m_btnMinimize->setToolTip(tr("Minimize"));
	m_btnMinimize->setStyleSheet(
		"QPushButton{border-image:url(:/image/MiniMize_Btn_nor);}"
		"QPushButton::hover{border-image:url(:/image/MiniMize_Btn_hover);}"
		"QPushButton::pressed{border-image:url(:/image/MiniMize_Btn_down);}");

	m_btnMaximize->setFixedSize(34,24);
	m_btnMaximize->setToolTip(tr("Maximize"));
	m_btnMaximize->setStyleSheet(
		"QPushButton{border-image:url(:/image/MaxMize_Btn_nor);}"
		"QPushButton::hover{border-image:url(:/image/MaxMize_Btn_hover);}"
		"QPushButton::pressed{border-image:url(:/image/MaxMize_Btn_down);}");

	m_btnClose->setFixedSize(34,24);
	m_btnClose->setToolTip(tr("Close"));
	m_btnClose->setStyleSheet(
		"QPushButton{border-image:url(:/image/Close_Btn_nor);}"
		"QPushButton::hover{border-image:url(:/image/Close_Btn_hover);}"
		"QPushButton::pressed{border-image:url(:/image/Close_Btn_down);}");

	m_btnSplit->setFixedSize(10,25);
	m_btnSplit->setStyleSheet(
		"QPushButton{border-image:url(:/image/splite_line);}"
		"QPushButton::hover{border-image:url(:/image/splite_line);}"
		"QPushButton::pressed{border-image:url(:/image/splite_line);}");

	QHBoxLayout *hLayout = new QHBoxLayout();
	hLayout->addWidget(m_labelLogo,0,Qt::AlignVCenter);
	hLayout->addWidget(m_labelTitle,0,Qt::AlignVCenter);
	hLayout->addStretch();
	hLayout->addWidget(m_btnSkin,0,Qt::AlignTop);
	hLayout->addWidget(m_btnSplit,0,Qt::AlignTop);
	hLayout->addWidget(m_btnMinimize,0,Qt::AlignTop);
	hLayout->addWidget(m_btnMaximize,0,Qt::AlignTop);
	hLayout->addWidget(m_btnClose,0,Qt::AlignTop);
	hLayout->setSpacing(0);
	hLayout->setContentsMargins(5,0,0,0);

	setLayout(hLayout);
	setFixedHeight(TOPWIDGET_HEIGHT);
	
	connect(m_btnSkin, SIGNAL(clicked()), this, SIGNAL(sigSkin()));
	connect(m_btnMainMenu, SIGNAL(clicked()), this, SIGNAL(sigMainMenu()));
	connect(m_btnMinimize, SIGNAL(clicked()), this, SIGNAL(sigMin()));
	connect(m_btnMaximize, SIGNAL(clicked()), this, SIGNAL(sigMax()));
	connect(m_btnClose, SIGNAL(clicked()), this, SIGNAL(sigClose()));
}

bool CTopWidget::eventFilter(QObject *o, QEvent *e)
{
	return QObject::eventFilter(o,e);
}

void CTopWidget::mousePressEvent(QMouseEvent *e)
{
	QWidget::mousePressEvent(e);
}

void CTopWidget::mouseReleaseEvent(QMouseEvent *e)
{
	QWidget::mouseReleaseEvent(e);
}

void CTopWidget::mouseMoveEvent(QMouseEvent *e)
{
	setCursor(Qt::ArrowCursor);
	QWidget::mouseMoveEvent(e);
}

void CTopWidget::mouseDoubleClickEvent(QMouseEvent *e)
{
	emit sigMax();
}

void CTopWidget::paintEvent(QPaintEvent *e)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
