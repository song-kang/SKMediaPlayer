#include "caboutwidget.h"
#include "skmediaplayer.h"

//////////////////// CAboutTopWidget ////////////////////
CAboutTopWidget::CAboutTopWidget(QWidget *parent)
	: QWidget(parent)
{
	Init();
	InitUi();
	InitSlot();
}

CAboutTopWidget::~CAboutTopWidget()
{

}

void CAboutTopWidget::Init()
{
	setStyleSheet("CSkinTopWidget{background:transparent;}");
	setMouseTracking(true);
}

void CAboutTopWidget::InitUi()
{
	m_labelTitle = new QLabel(this);
	m_btnClose = new QPushButton(this);

	QFont m_font;
	m_font.setFamily("Microsoft YaHei");
	m_font.setPixelSize(13);
	m_font.setBold(true);
	m_labelTitle->setFont(m_font);
	m_labelTitle->setStyleSheet("color:white;");
	m_labelTitle->setText(tr("About"));

	m_btnClose->setFixedSize(34,24);
	m_btnClose->setToolTip(tr("Close"));
	m_btnClose->setStyleSheet(
		"QPushButton{border-image:url(:/image/Close_Btn_nor);}"
		"QPushButton::hover{border-image:url(:/image/Close_Btn_hover);}"
		"QPushButton::pressed{border-image:url(:/image/Close_Btn_down);}");

	QHBoxLayout *hLayout = new QHBoxLayout();
	hLayout->addWidget(m_labelTitle,0,Qt::AlignVCenter);
	hLayout->addStretch();
	hLayout->addWidget(m_btnClose,0,Qt::AlignTop);
	hLayout->setSpacing(0);
	hLayout->setContentsMargins(5,0,0,0);

	setLayout(hLayout);
	setFixedHeight(30);
}

void CAboutTopWidget::InitSlot()
{
	connect(m_btnClose, SIGNAL(clicked()), this, SIGNAL(sigSkinClose()));
}

bool CAboutTopWidget::eventFilter(QObject *o, QEvent *e)
{
	return QObject::eventFilter(o,e);
}

void CAboutTopWidget::mousePressEvent(QMouseEvent *e)
{
	QWidget::mousePressEvent(e);
}

void CAboutTopWidget::mouseReleaseEvent(QMouseEvent *e)
{
	QWidget::mouseReleaseEvent(e);
}

void CAboutTopWidget::mouseMoveEvent(QMouseEvent *e)
{
	setCursor(Qt::ArrowCursor);
	QWidget::mouseMoveEvent(e);
}

void CAboutTopWidget::mouseDoubleClickEvent(QMouseEvent *e)
{
	QWidget::mouseDoubleClickEvent(e);
}

void CAboutTopWidget::paintEvent(QPaintEvent *e)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

//////////////////// CAboutCenterWidget ////////////////////
CAboutCenterWidget::CAboutCenterWidget(QWidget *parent)
	: QWidget(parent)
{
	Init();
	InitUi();
	InitSlot();
}

CAboutCenterWidget::~CAboutCenterWidget()
{

}

void CAboutCenterWidget::Init()
{
	setStyleSheet("background:rgb(255,255,255,200);");
	setMouseTracking(true);

	m_version = new QLabel(this);
	m_copyright = new QLabel(this);
	m_declare = new QLabel(this);
	m_declare1 = new QLabel(this);
	m_declare2 = new QLabel(this);
	m_declare3 = new QLabel(this);
	m_declare4 = new QLabel(this);
	m_declare5 = new QLabel(this);
}

void CAboutCenterWidget::InitUi()
{
	QFont m_font;
	m_font.setFamily("Microsoft YaHei");
	m_font.setPixelSize(13);

	m_version->setFont(m_font);
	m_version->setStyleSheet("background:transparent;color:black;");
	m_version->setText(tr("Version: %1.%2.%3").arg(VERSION_MAJOR).arg(VERSION_MINOR).arg(VERSION_REVISION));
	QHBoxLayout *h1Layout = new QHBoxLayout();
	h1Layout->addWidget(m_version,0,Qt::AlignLeft);
	h1Layout->addStretch();
	h1Layout->setContentsMargins(0,0,0,0);

	m_copyright->setFont(m_font);
	m_copyright->setStyleSheet("background:transparent;color:black;");
	m_copyright->setText(tr("Copyright(C) 2017-2018 George.Song reserved all copyrights"));
	QHBoxLayout *h2Layout = new QHBoxLayout();
	h2Layout->addWidget(m_copyright,0,Qt::AlignLeft);
	h2Layout->addStretch();
	h2Layout->setContentsMargins(0,0,0,0);

	m_declare->setFont(m_font);
	m_declare->setStyleSheet("background:transparent;color:black;");
	m_declare->setText(tr("Declare:"));
	QHBoxLayout *h3Layout = new QHBoxLayout();
	h3Layout->addWidget(m_declare,0,Qt::AlignLeft);
	h3Layout->addStretch();
	h3Layout->setContentsMargins(0,0,0,0);

	m_declare1->setFont(m_font);
	m_declare1->setStyleSheet("background:transparent;color:black;");
	m_declare1->setText(tr("1.This software is free sharing software."));
	QHBoxLayout *h4Layout = new QHBoxLayout();
	h4Layout->addWidget(m_declare1,0,Qt::AlignLeft);
	h4Layout->addStretch();
	h4Layout->setContentsMargins(0,0,0,0);

	m_declare2->setFont(m_font);
	m_declare2->setStyleSheet("background:transparent;color:black;");
	m_declare2->setText(tr("2.Only for individual users and non commercial users free use."));
	QHBoxLayout *h5Layout = new QHBoxLayout();
	h5Layout->addWidget(m_declare2,0,Qt::AlignLeft);
	h5Layout->addStretch();
	h5Layout->setContentsMargins(0,0,0,0);

	m_declare3->setFont(m_font);
	m_declare3->setStyleSheet("background:transparent;color:black;");
	m_declare3->setText(tr("3.Prohibited for any form of commercial purpose."));
	QHBoxLayout *h6Layout = new QHBoxLayout();
	h6Layout->addWidget(m_declare3,0,Qt::AlignLeft);
	h6Layout->addStretch();
	h6Layout->setContentsMargins(0,0,0,0);

	m_declare4->setFont(m_font);
	m_declare4->setStyleSheet("background:transparent;color:black;");
	m_declare4->setText(tr("4.I allow you to maintain the integrity and integrity of the software,"));
	QHBoxLayout *h7Layout = new QHBoxLayout();
	h7Layout->addWidget(m_declare4,0,Qt::AlignLeft);
	h7Layout->addStretch();
	h7Layout->setContentsMargins(0,0,0,0);

	m_declare5->setFont(m_font);
	m_declare5->setStyleSheet("background:transparent;color:black;");
	m_declare5->setText(tr("distribute, copy, and distribute the software at will"));
	QHBoxLayout *h8Layout = new QHBoxLayout();
	h8Layout->addWidget(m_declare5,0,Qt::AlignLeft);
	h8Layout->addStretch();
	h8Layout->setContentsMargins(0,0,0,0);

	QVBoxLayout *v1layout = new QVBoxLayout();
	v1layout->addLayout(h1Layout);
	v1layout->addLayout(h2Layout);
	v1layout->addStretch();
	v1layout->setSpacing(8);
	v1layout->setContentsMargins(0,0,0,0);

	QVBoxLayout *v2layout = new QVBoxLayout();
	v2layout->addLayout(h3Layout);
	v2layout->addLayout(h4Layout);
	v2layout->addLayout(h5Layout);
	v2layout->addLayout(h6Layout);
	v2layout->addLayout(h7Layout);
	v2layout->addLayout(h8Layout);
	v2layout->addStretch();
	v2layout->setSpacing(2);
	v2layout->setContentsMargins(0,0,0,0);

	QVBoxLayout *vlayout = new QVBoxLayout();
	vlayout->addLayout(v1layout);
	vlayout->addLayout(v2layout);
	vlayout->addStretch();
	vlayout->setSpacing(20);
	vlayout->setContentsMargins(20,20,20,20);

	setLayout(vlayout);
}

void CAboutCenterWidget::InitSlot()
{

}

bool CAboutCenterWidget::eventFilter(QObject *o, QEvent *e)
{
	return QObject::eventFilter(o,e);
}

void CAboutCenterWidget::mousePressEvent(QMouseEvent *e)
{
	QWidget::mousePressEvent(e);
}

void CAboutCenterWidget::mouseReleaseEvent(QMouseEvent *e)
{
	QWidget::mouseReleaseEvent(e);
}

void CAboutCenterWidget::mouseMoveEvent(QMouseEvent *e)
{
	setCursor(Qt::ArrowCursor);
	QWidget::mouseMoveEvent(e);
}

void CAboutCenterWidget::mouseDoubleClickEvent(QMouseEvent *e)
{
	QWidget::mouseDoubleClickEvent(e);
}

void CAboutCenterWidget::paintEvent(QPaintEvent *e)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

//////////////////// CAboutWidget ////////////////////
CAboutWidget::CAboutWidget(QWidget *parent)
	: AbsFrameLessAutoSize(parent)
{
	SetApp((SKMediaPlayer*)parent);
	Init();
	InitUi();
	InitSlot();
}

CAboutWidget::~CAboutWidget()
{

}

void CAboutWidget::Init()
{
	m_curindex = 0;
	m_issetpix = false;
	m_isShowSingerBG = true;

	m_netPix = QPixmap("");
	m_localPix = QPixmap("");
	m_curPix = QPixmap("");

	setAutoFillBackground(true);
}

void CAboutWidget::InitUi()
{
	setFixedSize(450,300);
	setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::X11BypassWindowManagerHint);
	setWindowModality(Qt::WindowModal);
	setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	setMouseTracking(true);

	m_aboutTopWidget = new CAboutTopWidget();
	QVBoxLayout *topLayout = new QVBoxLayout;
	topLayout->addWidget(m_aboutTopWidget);
	topLayout->setSpacing(0);
	topLayout->setContentsMargins(0,0,0,0);

	m_aboutCenterWidget = new CAboutCenterWidget();
	QVBoxLayout *centerLayout = new QVBoxLayout;
	centerLayout->addWidget(m_aboutCenterWidget);
	centerLayout->setSpacing(0);
	centerLayout->setContentsMargins(0,0,0,0);

	QVBoxLayout *vLyout = new QVBoxLayout;
	vLyout->addLayout(topLayout);
	vLyout->addLayout(centerLayout);
	vLyout->setSpacing(0);
	vLyout->setContentsMargins(0,0,0,0);

	setLayout(vLyout);

	int curMonitor = QApplication::desktop()->screenNumber(m_app);
	QRect rect = QApplication::desktop()->availableGeometry(curMonitor);
	move((rect.width()-this->width())/2+rect.x(),(rect.height()-this->height())/2);
}

void CAboutWidget::InitSlot()
{
	connect(m_aboutTopWidget, SIGNAL(sigSkinClose()), this, SLOT(close()));
}

void CAboutWidget::mouseMoveEvent(QMouseEvent *e)
{
	mouseMoveRect(mapFromGlobal(e->globalPos()));
	if (m_state.MousePressed)
	{
		this->move(m_state.WindowPos + (e->globalPos() - m_state.MousePos));
	}
}

void CAboutWidget::paintEvent(QPaintEvent *e)
{
	QWidget::paintEvent(e);

	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	p.setRenderHints(QPainter::SmoothPixmapTransform,true);	//消锯齿

	if (m_curindex == 5 && m_localPix.width() != 0)
		m_issetpix = true;
	else
		m_issetpix = false;

	double d = (double)m_netPix.height() / m_netPix.width();
	int h = d*width();
	int w = height() / d;
	p.drawPixmap(0,0,width(),h,m_netPix);
	m_curPix = m_netPix.scaled(width(),h);
	if (h < height())	//如果图片高度小于窗口高度
	{
		p.drawPixmap(0,0,w,height(),m_netPix);
		m_curPix = m_netPix.scaled(w,height());
	}

	if (m_issetpix && m_isShowSingerBG)
	{
		double d = (double)m_localPix.height() / m_localPix.width();
		int h = d*width();
		int w = height()/d;
		p.drawPixmap(0,0,width(),h,m_localPix);
		m_curPix = m_localPix.scaled(width(),h);
		if (h < height())	//如果图片高度小于窗口高度
		{
			p.drawPixmap(0,0,w,height(),m_localPix);
			m_curPix = m_localPix.scaled(w,height());
		}
	}
}

void CAboutWidget::setPixmap(const QPixmap &pix)
{
	m_localPix = pix;
	update();
}

void CAboutWidget::setShowSingerBG(bool is)
{
	m_isShowSingerBG = is;
}

void CAboutWidget::setCurrentIndex(int i)
{
	m_curindex = i;
	update();
}

void CAboutWidget::clearBg()
{
	m_issetpix = false;
	m_localPix = QPixmap("");
	update();
}

void CAboutWidget::setSkin(const QString &skin)
{
	m_netPix = QPixmap(skin);
	m_curPixPath = skin;
	update();
}
