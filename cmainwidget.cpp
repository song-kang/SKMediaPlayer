#include "cmainwidget.h"

CMainWidget::CMainWidget(QWidget *parent)
	: QWidget(parent)
{
	Init();
	InitUi();
}

CMainWidget::~CMainWidget()
{

}

void CMainWidget::Init()
{
	m_curindex = 0;
	m_issetpix = false;
	m_isShowSingerBG = true;

	m_netPix = QPixmap("");
	m_localPix = QPixmap("");
	m_curPix = QPixmap("");

	setAutoFillBackground(true);
	
	QTime t= QTime::currentTime();
	qsrand(t.msec()+t.second()*1000);

	setSkin(tr(":/skin/skin%1").arg(qrand()%8));
}

void CMainWidget::InitUi()
{

}

void CMainWidget::setPixmap(const QPixmap &pix)
{
	m_localPix = pix;
	update();
}

void CMainWidget::setShowSingerBG(bool is)
{
	m_isShowSingerBG = is;
}

void CMainWidget::setCurrentIndex(int i)
{
	m_curindex = i;
	update();
}

void CMainWidget::clearBg()
{
	m_issetpix = false;
	m_localPix = QPixmap("");
	update();
}

void CMainWidget::setSkin(const QString &skin)
{
	m_netPix = QPixmap(skin);
	m_curPixPath = skin;
	update();
}

void CMainWidget::paintEvent(QPaintEvent *e)
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
