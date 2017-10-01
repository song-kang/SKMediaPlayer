#include "cskinwidget.h"

//////////////////// CSkinTopWidget ////////////////////
CSkinTopWidget::CSkinTopWidget(QWidget *parent)
	: QWidget(parent)
{
	Init();
	InitUi();
	InitSlot();
}

CSkinTopWidget::~CSkinTopWidget()
{

}

void CSkinTopWidget::Init()
{
	setStyleSheet("CSkinTopWidget{background:transparent;}");
	setMouseTracking(true);
}

void CSkinTopWidget::InitUi()
{
	m_labelTitle = new QLabel(this);
	m_btnClose = new QPushButton(this);

	QFont m_font;
	m_font.setFamily("Microsoft YaHei");
	m_font.setPixelSize(13);
	m_font.setBold(true);
	m_labelTitle->setFont(m_font);
	m_labelTitle->setStyleSheet("color:white;");
	m_labelTitle->setText(tr("Skins"));

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

void CSkinTopWidget::InitSlot()
{
	connect(m_btnClose, SIGNAL(clicked()), this, SIGNAL(sigSkinClose()));
}

bool CSkinTopWidget::eventFilter(QObject *o, QEvent *e)
{
	return QObject::eventFilter(o,e);
}

void CSkinTopWidget::mousePressEvent(QMouseEvent *e)
{
	QWidget::mousePressEvent(e);
}

void CSkinTopWidget::mouseReleaseEvent(QMouseEvent *e)
{
	QWidget::mouseReleaseEvent(e);
}

void CSkinTopWidget::mouseMoveEvent(QMouseEvent *e)
{
	setCursor(Qt::ArrowCursor);
	QWidget::mouseMoveEvent(e);
}

void CSkinTopWidget::mouseDoubleClickEvent(QMouseEvent *e)
{
	QWidget::mouseDoubleClickEvent(e);
}

void CSkinTopWidget::paintEvent(QPaintEvent *e)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

//////////////////// CSkinCenterWidget ////////////////////
CSkinCenterWidget::CSkinCenterWidget(QWidget *parent)
	: QWidget(parent)
{
	Init();
	InitUi();
	InitSlot();
}

CSkinCenterWidget::~CSkinCenterWidget()
{

}

void CSkinCenterWidget::Init()
{
	setStyleSheet("background:rgb(255,255,255,200);");
	setMouseTracking(true);

	m_labelSkin0 = new QLabel(this);
	m_labelSkin1 = new QLabel(this);
	m_labelSkin2 = new QLabel(this);
	m_labelSkin3 = new QLabel(this);
	m_labelSkin4 = new QLabel(this);
	m_labelSkin5 = new QLabel(this);
	m_labelSkin6 = new QLabel(this);
	m_btnSkin0 = new QPushButton(this);
	m_btnSkin1 = new QPushButton(this);
	m_btnSkin2 = new QPushButton(this);
	m_btnSkin3 = new QPushButton(this);
	m_btnSkin4 = new QPushButton(this);
	m_btnSkin5 = new QPushButton(this);
	m_btnSkin6 = new QPushButton(this);
}

void CSkinCenterWidget::InitUi()
{
	QFont m_font;
	m_font.setFamily("Microsoft YaHei");
	m_font.setPixelSize(13);

	//第1排
	m_btnSkin0->setFixedSize(160,100);
	m_btnSkin0->setCursor(QCursor(Qt::PointingHandCursor));
	m_btnSkin0->setStyleSheet(
		"QPushButton{border-image:url(:/skin/s_skin0);}"
		"QPushButton::hover{border-image:url(:/skin/s_skin0);}"
		"QPushButton::pressed{border-image:url(:/skin/s_skin0);}");
	m_labelSkin0->setFont(m_font);
	m_labelSkin0->setStyleSheet("background:transparent;color:black;");
	m_labelSkin0->setText(tr("Luxuriantly Green"));
	QVBoxLayout *v1Layout = new QVBoxLayout();
	v1Layout->addWidget(m_btnSkin0,0,Qt::AlignHCenter);
	v1Layout->addWidget(m_labelSkin0,0,Qt::AlignHCenter);
	v1Layout->setSpacing(8);
	v1Layout->setContentsMargins(0,0,0,0);

	m_btnSkin1->setFixedSize(160,100);
	m_btnSkin1->setCursor(QCursor(Qt::PointingHandCursor));
	m_btnSkin1->setStyleSheet(
		"QPushButton{border-image:url(:/skin/s_skin1);}"
		"QPushButton::hover{border-image:url(:/skin/s_skin1);}"
		"QPushButton::pressed{border-image:url(:/skin/s_skin1);}");
	m_labelSkin1->setFont(m_font);
	m_labelSkin1->setStyleSheet("background:transparent;color:black;");
	m_labelSkin1->setText(tr("Black Notebook"));
	QVBoxLayout *v2Layout = new QVBoxLayout();
	v2Layout->addWidget(m_btnSkin1,0,Qt::AlignHCenter);
	v2Layout->addWidget(m_labelSkin1,0,Qt::AlignHCenter);
	v2Layout->setSpacing(8);
	v2Layout->setContentsMargins(0,0,0,0);

	m_btnSkin2->setFixedSize(160,100);
	m_btnSkin2->setCursor(QCursor(Qt::PointingHandCursor));
	m_btnSkin2->setStyleSheet(
		"QPushButton{border-image:url(:/skin/s_skin2);}"
		"QPushButton::hover{border-image:url(:/skin/s_skin2);}"
		"QPushButton::pressed{border-image:url(:/skin/s_skin2);}");
	m_labelSkin2->setFont(m_font);
	m_labelSkin2->setStyleSheet("background:transparent;color:black;");
	m_labelSkin2->setText(tr("Dreamy"));
	QVBoxLayout *v3Layout = new QVBoxLayout();
	v3Layout->addWidget(m_btnSkin2,0,Qt::AlignHCenter);
	v3Layout->addWidget(m_labelSkin2,0,Qt::AlignHCenter);
	v3Layout->setSpacing(8);
	v3Layout->setContentsMargins(0,0,0,0);

	m_btnSkin3->setFixedSize(160,100);
	m_btnSkin3->setCursor(QCursor(Qt::PointingHandCursor));
	m_btnSkin3->setStyleSheet(
		"QPushButton{border-image:url(:/skin/s_skin3);}"
		"QPushButton::hover{border-image:url(:/skin/s_skin3);}"
		"QPushButton::pressed{border-image:url(:/skin/s_skin3);}");
	m_labelSkin3->setFont(m_font);
	m_labelSkin3->setStyleSheet("background:transparent;color:black;");
	m_labelSkin3->setText(tr("Blue Deep Sea"));
	QVBoxLayout *v4Layout = new QVBoxLayout();
	v4Layout->addWidget(m_btnSkin3,0,Qt::AlignHCenter);
	v4Layout->addWidget(m_labelSkin3,0,Qt::AlignHCenter);
	v4Layout->setSpacing(8);
	v4Layout->setContentsMargins(0,0,0,0);

	QHBoxLayout *h1Layout = new QHBoxLayout();
	h1Layout->addStretch();
	h1Layout->addLayout(v1Layout);
	h1Layout->addLayout(v2Layout);
	h1Layout->addLayout(v3Layout);
	h1Layout->addLayout(v4Layout);
	h1Layout->addStretch();
	h1Layout->setSpacing(15);
	h1Layout->setContentsMargins(0,0,0,0);

	//第2排
	m_btnSkin4->setFixedSize(160,100);
	m_btnSkin4->setCursor(QCursor(Qt::PointingHandCursor));
	m_btnSkin4->setStyleSheet(
		"QPushButton{border-image:url(:/skin/s_skin4);}"
		"QPushButton::hover{border-image:url(:/skin/s_skin4);}"
		"QPushButton::pressed{border-image:url(:/skin/s_skin4);}");
	m_labelSkin4->setFont(m_font);
	m_labelSkin4->setStyleSheet("background:transparent;color:black;");
	m_labelSkin4->setText(tr("Starry Sky"));
	QVBoxLayout *v5Layout = new QVBoxLayout();
	v5Layout->addWidget(m_btnSkin4,0,Qt::AlignHCenter);
	v5Layout->addWidget(m_labelSkin4,0,Qt::AlignHCenter);
	v5Layout->setSpacing(8);
	v5Layout->setContentsMargins(0,0,0,0);

	m_btnSkin5->setFixedSize(160,100);
	m_btnSkin5->setCursor(QCursor(Qt::PointingHandCursor));
	m_btnSkin5->setStyleSheet(
		"QPushButton{border-image:url(:/skin/s_skin5);}"
		"QPushButton::hover{border-image:url(:/skin/s_skin5);}"
		"QPushButton::pressed{border-image:url(:/skin/s_skin5);}");
	m_labelSkin5->setFont(m_font);
	m_labelSkin5->setStyleSheet("background:transparent;color:black;");
	m_labelSkin5->setText(tr("Simple Blue"));
	QVBoxLayout *v6Layout = new QVBoxLayout();
	v6Layout->addWidget(m_btnSkin5,0,Qt::AlignHCenter);
	v6Layout->addWidget(m_labelSkin5,0,Qt::AlignHCenter);
	v6Layout->setSpacing(8);
	v6Layout->setContentsMargins(0,0,0,0);

	m_btnSkin6->setFixedSize(160,100);
	m_btnSkin6->setCursor(QCursor(Qt::PointingHandCursor));
	m_btnSkin6->setStyleSheet(
		"QPushButton{border-image:url(:/skin/s_skin6);}"
		"QPushButton::hover{border-image:url(:/skin/s_skin6);}"
		"QPushButton::pressed{border-image:url(:/skin/s_skin6);}");
	m_labelSkin6->setFont(m_font);
	m_labelSkin6->setStyleSheet("background:transparent;color:black;");
	m_labelSkin6->setText(tr("Sunrise First Day"));
	QVBoxLayout *v7Layout = new QVBoxLayout();
	v7Layout->addWidget(m_btnSkin6,0,Qt::AlignHCenter);
	v7Layout->addWidget(m_labelSkin6,0,Qt::AlignHCenter);
	v7Layout->setSpacing(8);
	v7Layout->setContentsMargins(0,0,0,0);

	QHBoxLayout *h2Layout = new QHBoxLayout();
	h2Layout->addStretch();
	h2Layout->addLayout(v5Layout);
	h2Layout->addLayout(v6Layout);
	h2Layout->addLayout(v7Layout);
	h2Layout->addStretch();
	h2Layout->setSpacing(15);
	h2Layout->setContentsMargins(0,0,0,0);

	//全排布
	QVBoxLayout *vLayout = new QVBoxLayout();
	vLayout->addLayout(h1Layout);
	vLayout->addStretch();
	vLayout->addLayout(h2Layout);
	vLayout->setSpacing(0);
	vLayout->setContentsMargins(20,20,20,20);
	setLayout(vLayout);
}

void CSkinCenterWidget::InitSlot()
{
	connect(m_btnSkin0, SIGNAL(clicked()), this, SIGNAL(sigSkin0()));
	connect(m_btnSkin1, SIGNAL(clicked()), this, SIGNAL(sigSkin1()));
	connect(m_btnSkin2, SIGNAL(clicked()), this, SIGNAL(sigSkin2()));
	connect(m_btnSkin3, SIGNAL(clicked()), this, SIGNAL(sigSkin3()));
	connect(m_btnSkin4, SIGNAL(clicked()), this, SIGNAL(sigSkin4()));
	connect(m_btnSkin5, SIGNAL(clicked()), this, SIGNAL(sigSkin5()));
	connect(m_btnSkin6, SIGNAL(clicked()), this, SIGNAL(sigSkin6()));
}

bool CSkinCenterWidget::eventFilter(QObject *o, QEvent *e)
{
	return QObject::eventFilter(o,e);
}

void CSkinCenterWidget::mousePressEvent(QMouseEvent *e)
{
	QWidget::mousePressEvent(e);
}

void CSkinCenterWidget::mouseReleaseEvent(QMouseEvent *e)
{
	QWidget::mouseReleaseEvent(e);
}

void CSkinCenterWidget::mouseMoveEvent(QMouseEvent *e)
{
	setCursor(Qt::ArrowCursor);
	QWidget::mouseMoveEvent(e);
}

void CSkinCenterWidget::mouseDoubleClickEvent(QMouseEvent *e)
{
	QWidget::mouseDoubleClickEvent(e);
}

void CSkinCenterWidget::paintEvent(QPaintEvent *e)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

//////////////////// CSkinWidget ////////////////////
#include "skmediaplayer.h"
CSkinWidget::CSkinWidget(QWidget *parent)
	: AbsFrameLessAutoSize(parent)
{
	SetApp((SKMediaPlayer*)parent);
	Init();
	InitUi();
	InitSlot();
}

CSkinWidget::~CSkinWidget()
{

}

void CSkinWidget::Init()
{
	m_curindex = 0;
	m_issetpix = false;
	m_isShowSingerBG = true;

	m_netPix = QPixmap("");
	m_localPix = QPixmap("");
	m_curPix = QPixmap("");

	setAutoFillBackground(true);
	//setSkin(":/skin/skin0");
}

void CSkinWidget::InitUi()
{
	setFixedSize(750,350);
	setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::X11BypassWindowManagerHint);
	setWindowModality(Qt::WindowModal);
	setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	setMouseTracking(true);

	m_skinTopWidget = new CSkinTopWidget();
	QVBoxLayout *topLayout = new QVBoxLayout;
	topLayout->addWidget(m_skinTopWidget);
	topLayout->setSpacing(0);
	topLayout->setContentsMargins(0,0,0,0);

	m_skinCenterWidget = new CSkinCenterWidget();
	QVBoxLayout *centerLayout = new QVBoxLayout;
	centerLayout->addWidget(m_skinCenterWidget);
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

void CSkinWidget::InitSlot()
{
	connect(m_skinTopWidget, SIGNAL(sigSkinClose()), this, SLOT(close()));

	connect(m_skinCenterWidget, SIGNAL(sigSkin0()), this, SLOT(SlotSkin0()));
	connect(m_skinCenterWidget, SIGNAL(sigSkin1()), this, SLOT(SlotSkin1()));
	connect(m_skinCenterWidget, SIGNAL(sigSkin2()), this, SLOT(SlotSkin2()));
	connect(m_skinCenterWidget, SIGNAL(sigSkin3()), this, SLOT(SlotSkin3()));
	connect(m_skinCenterWidget, SIGNAL(sigSkin4()), this, SLOT(SlotSkin4()));
	connect(m_skinCenterWidget, SIGNAL(sigSkin5()), this, SLOT(SlotSkin5()));
	connect(m_skinCenterWidget, SIGNAL(sigSkin6()), this, SLOT(SlotSkin6()));
}

void CSkinWidget::mouseMoveEvent(QMouseEvent *e)
{
	mouseMoveRect(mapFromGlobal(e->globalPos()));
	if (m_state.MousePressed)
	{
		this->move(m_state.WindowPos + (e->globalPos() - m_state.MousePos));
	}
}

void CSkinWidget::paintEvent(QPaintEvent *e)
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

void CSkinWidget::SlotSkin0()
{
	setSkin(":/skin/skin0");
	m_app->SetSkin(":/skin/skin0");
}

void CSkinWidget::SlotSkin1()
{
	setSkin(":/skin/skin1");
	m_app->SetSkin(":/skin/skin1");
}

void CSkinWidget::SlotSkin2()
{
	setSkin(":/skin/skin2");
	m_app->SetSkin(":/skin/skin2");
}

void CSkinWidget::SlotSkin3()
{
	setSkin(":/skin/skin3");
	m_app->SetSkin(":/skin/skin3");
}

void CSkinWidget::SlotSkin4()
{
	setSkin(":/skin/skin4");
	m_app->SetSkin(":/skin/skin4");
}

void CSkinWidget::SlotSkin5()
{
	setSkin(":/skin/skin5");
	m_app->SetSkin(":/skin/skin5");
}

void CSkinWidget::SlotSkin6()
{
	setSkin(":/skin/skin6");
	m_app->SetSkin(":/skin/skin6");
}

void CSkinWidget::setPixmap(const QPixmap &pix)
{
	m_localPix = pix;
	update();
}

void CSkinWidget::setShowSingerBG(bool is)
{
	m_isShowSingerBG = is;
}

void CSkinWidget::setCurrentIndex(int i)
{
	m_curindex = i;
	update();
}

void CSkinWidget::clearBg()
{
	m_issetpix = false;
	m_localPix = QPixmap("");
	update();
}

void CSkinWidget::setSkin(const QString &skin)
{
	m_netPix = QPixmap(skin);
	m_curPixPath = skin;
	update();
}
