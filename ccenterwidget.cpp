#include "ccenterwidget.h"
#include "skmediaplayer.h"

CCenterWidget::CCenterWidget(QWidget *parent)
	: QWidget(parent)
{
	Init();
	InitUi();
}

CCenterWidget::~CCenterWidget()
{

}

void CCenterWidget::Init()
{
	setStyleSheet("background:rgb(255,255,255,50);");
	setMouseTracking(true);
	setAcceptDrops(true); //允许实现拖拽功能
}

void CCenterWidget::InitUi()
{
	QPixmap pix(":/image/mediaplayer_72");
	QPixmap temp(pix.size());
	temp.fill(Qt::transparent);
	QPainter p1(&temp);
	p1.setCompositionMode(QPainter::CompositionMode_Source);
	p1.drawPixmap(0, 0, pix);
	p1.setCompositionMode(QPainter::CompositionMode_DestinationIn);
	p1.fillRect(temp.rect(), QColor(0, 0, 0, 100));
	p1.end();
	pix = temp;
	m_labelLogo = new QLabel(this);
	m_labelLogo->setStyleSheet("background:transparent;");
	m_labelLogo->setPixmap(pix);

	QHBoxLayout *hLayout = new QHBoxLayout();
	hLayout->addWidget(m_labelLogo,0,Qt::AlignCenter);
	setLayout(hLayout);
}

bool CCenterWidget::eventFilter(QObject *o, QEvent *e)
{
	return QObject::eventFilter(o,e);
}

void CCenterWidget::mouseMoveEvent(QMouseEvent *e)
{
	setCursor(Qt::ArrowCursor);
	m_app->m_iFullScrMouse = 0;

	int curMonitor = QApplication::desktop()->screenNumber(this);
	QRect rect = QApplication::desktop()->screenGeometry(curMonitor);
	QPoint p = mapFromGlobal(e->globalPos());
	if (m_app->isFullScreen())
	{
		if (p.y() >= rect.height() - 65)
			m_app->ShowBottomFloatWidget(true);
		else
			m_app->ShowBottomFloatWidget(false);
	}

	QWidget::mouseMoveEvent(e);
}

void CCenterWidget::mousePressEvent(QMouseEvent *e)
{
	setFocus();
}

void CCenterWidget::mouseReleaseEvent(QMouseEvent *e)
{
	if (e->button() == Qt::LeftButton)
	{
		if (m_app->GetPlayer())
			m_app->SlotStartStop();
	}
	else if (e->button() == Qt::RightButton)
	{
		m_app->m_iMenu->clear();
		m_app->m_iMenu->CreateMenuItem();
		m_app->m_iMenu->popup(e->globalPos());
	}

	QWidget::mouseReleaseEvent(e);
}

void CCenterWidget::mouseDoubleClickEvent(QMouseEvent *e)
{
	if (e->button() == Qt::LeftButton)
	{
		m_app->SlotFullScreen();
	}
	
	QWidget::mouseDoubleClickEvent(e);
}

void CCenterWidget::paintEvent(QPaintEvent *e)
{
	QWidget::paintEvent(e);

	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void CCenterWidget::dragEnterEvent(QDragEnterEvent *event)
{
	if(event->mimeData()->hasFormat("text/uri-list"))
		event->acceptProposedAction();
}

void CCenterWidget::dropEvent(QDropEvent *event)
{
	QList<QUrl> urls = event->mimeData()->urls();
	if (urls.isEmpty())
	{
		qWarning() << QString(tr("Not found drag and drop file."));
		return;
	}

	QString file_name = urls.at(0).toLocalFile();
	if (m_app->GetPlayer())
		m_app->SlotPause();
	m_app->Play(file_name);
}
