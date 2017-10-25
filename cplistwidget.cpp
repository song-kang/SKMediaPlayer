#include "cplistwidget.h"
#include "skmediaplayer.h"

#define COLUMN_NAME			0
#define COLUMN_TIME			1
#define COLUMN_NAME_WIDTH	300
#define COLUMN_TIME_WIDTH	60

CPlistWidget::CPlistWidget(QWidget *parent)
	: QWidget(parent)
{
	Init();
	InitUi();
	InitSlot();
}

CPlistWidget::~CPlistWidget()
{
	delete m_itemDelegate;
}

void CPlistWidget::Init()
{
	m_mainGridLayout = new QGridLayout;
	m_iBtnPlus = new QPushButton(this);
	m_iBtnMinus = new QPushButton(this);
	m_iPlayListTableWidget = new QTableWidget(this);
	QStringList table_header;
	table_header << tr("Name") << tr("Time");
	m_iPlayListTableWidget->setColumnCount(2);
	m_iPlayListTableWidget->setHorizontalHeaderLabels(table_header);
	m_iPlayListTableWidget->setColumnWidth(COLUMN_NAME,COLUMN_NAME_WIDTH);
	m_iPlayListTableWidget->setColumnWidth(COLUMN_TIME,COLUMN_TIME_WIDTH);
	m_iPlayListTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);		//整行选择模式
	m_iPlayListTableWidget->setFocusPolicy(Qt::NoFocus);								//去除焦点，无虚框
	m_iPlayListTableWidget->verticalHeader()->setDefaultSectionSize(24);				//设置行高
	m_iPlayListTableWidget->verticalHeader()->setVisible(false);						//去除最前列
	m_iPlayListTableWidget->horizontalHeader()->setVisible(false);						//去除表头
	m_iPlayListTableWidget->setFrameShape(QFrame::NoFrame);								//设置无边框
	m_iPlayListTableWidget->setShowGrid(false);											//设置不显示格子线
	m_iPlayListTableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);		//可多选（Ctrl、Shift、  Ctrl+A都可以）
	m_iPlayListTableWidget->setStyleSheet("background-color:rgb(255,255,255,10);selection-background-color:rgb(255,255,255,50);");

	//设置水平、垂直滚动条样式
	m_iPlayListTableWidget->horizontalScrollBar()->setStyleSheet("QScrollBar{background:transparent; height: 10px;margin: 0px 2px 0px 0px;}"
		"QScrollBar::handle{background:rgb(217,217,217);border-radius:4px;}"
		"QScrollBar::handle:hover{background: rgb(191,191,191);}"
		"QScrollBar::add-line:horizontal{border:1px rgb(230,230,230);height: 1px;}"
		"QScrollBar::sub-line:horizontal{border:1px rgb(230,230,230);height: 1px;}"
		"QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal {background:transparent;}");

	m_iPlayListTableWidget->verticalScrollBar()->setStyleSheet("QScrollBar{background:transparent; width: 10px;margin: 0px 2px 0px 0px;}"
		"QScrollBar::handle{background:rgb(217,217,217);border-radius:4px;}"
		"QScrollBar::handle:hover{background: rgb(191,191,191);}"
		"QScrollBar::add-line:vertical{border:1px rgb(230,230,230);height: 1px;}"
		"QScrollBar::sub-line:vertical{border:1px rgb(230,230,230);height: 1px;}"
		"QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {background:transparent;}");

	m_itemDelegate = new ItemDelegate;
	QStandardItemModel *model = (QStandardItemModel *)m_iPlayListTableWidget->model();
	m_iPlayListTableWidget->setItemDelegate(m_itemDelegate);
}

void CPlistWidget::InitUi()
{
	setFixedWidth(COLUMN_NAME_WIDTH+COLUMN_TIME_WIDTH+10);

	m_iBtnPlus->setFixedSize(20,20);
	m_iBtnPlus->setToolTip(tr("Add Media Play"));
	m_iBtnPlus->setStyleSheet(
		"QPushButton{border-image:url(:/image/plus_normal);}"
		"QPushButton::hover{border-image:url(:/image/plus_hover);}"
		"QPushButton::pressed{border-image:url(:/image/plus_down);}");

	m_iBtnMinus->setFixedSize(20,20);
	m_iBtnMinus->setToolTip(tr("Delete Media Play"));
	m_iBtnMinus->setStyleSheet(
		"QPushButton{border-image:url(:/image/minus_normal);}"
		"QPushButton::hover{border-image:url(:/image/minus_hover);}"
		"QPushButton::pressed{border-image:url(:/image/minus_down);}");

	QHBoxLayout *hLayout = new QHBoxLayout();
	hLayout->addWidget(m_iBtnPlus,0,Qt::AlignVCenter);
	hLayout->addWidget(m_iBtnMinus,0,Qt::AlignVCenter);
	hLayout->addStretch();
	hLayout->setContentsMargins(6,0,0,0);

	QVBoxLayout *vLayout = new QVBoxLayout();
	vLayout->addLayout(hLayout);
	vLayout->addWidget(m_iPlayListTableWidget);
	vLayout->setContentsMargins(0,6,0,0);

	m_mainWidget = new QWidget();
	m_mainWidget->setLayout(vLayout);
	m_mainGridLayout->addWidget(m_mainWidget);
	m_mainGridLayout->setContentsMargins(0,0,0,0);
	setLayout(m_mainGridLayout);
	setCursor(Qt::ArrowCursor);
}

void CPlistWidget::InitSlot()
{
	connect(m_iBtnPlus,SIGNAL(clicked()),this,SLOT(SlotAddPlayItem()));
	connect(m_iBtnMinus,SIGNAL(clicked()),this,SLOT(SlotDeletePlayItem()));
	connect(m_iPlayListTableWidget,SIGNAL(itemDoubleClicked(QTableWidgetItem*)),this,SLOT(SlotPlaylistItemClicked(QTableWidgetItem*)));
}

void CPlistWidget::Start()
{
	m_iPlayListTableWidget->clearContents();
	m_iPlayListTableWidget->setRowCount(m_playList->m_iPlayItems.count());

	QFont m_font;
	m_font.setFamily("Microsoft YaHei");
	m_font.setPixelSize(12);
	m_font.setBold(true);

	int row = 0;
	QTableWidgetItem *item;
	foreach (stuPlayItem *it, m_playList->m_iPlayItems)
	{
		QFileInfo fi; 
		fi = QFileInfo(it->path);
		item = new QTableWidgetItem(fi.fileName());
		item->setBackgroundColor(QColor(0,0,0,0));
		item->setTextColor(QColor(255,255,255));
		item->setToolTip(fi.fileName());
		item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
		item->setFlags(item->flags() & (~Qt::ItemIsEditable));	//设置item项不可编辑
		item->setData(Qt::UserRole,QVariant(it->path));
		item->setFont(m_font);
		m_iPlayListTableWidget->setItem(row,COLUMN_NAME,item);

		QString sTotal;
		int hour = it->time / 3600;
		int minute = (it->time % 3600) / 60;
		int second = (it->time % 60);
		sTotal.sprintf("%02d:%02d:%02d",hour,minute,second);
		item = new QTableWidgetItem(sTotal);
		item->setBackgroundColor(QColor(0,0,0,0));
		item->setTextColor(QColor(255,255,255));
		item->setTextAlignment(Qt::AlignCenter);
		item->setFlags(item->flags() & (~Qt::ItemIsEditable));	//设置item项不可编辑
		item->setData(Qt::UserRole,QVariant(it->path));
		item->setFont(m_font);
		m_iPlayListTableWidget->setItem(row,COLUMN_TIME,item);

		row ++;
	}
}

void CPlistWidget::SlotPlaylistItemClicked(QTableWidgetItem *item)
{
	QString text = item->data(Qt::UserRole).toString();

	emit sigSelectFile(text);
}

void CPlistWidget::SlotAddPlayItem()
{
	QString filter = tr("Movie File(*.rmvb *.rm *.avi *.wmv *.mkv *.asf *.3gp *.mov *.mp4 *.ogv *.flv);;All File(*.*)");
	QStringList fileOpens = QFileDialog::getOpenFileNames(this,tr("Load File"),QString::null,filter);
	foreach (QString s, fileOpens)
	{
		s.replace("/","\\");
		m_playList->AppendItem(s);
	}
	Start();
}

void CPlistWidget::SlotDeletePlayItem()
{
	QList<QTableWidgetSelectionRange> ranges = m_iPlayListTableWidget->selectedRanges();
	if (ranges.count() == 0)
		return;

	for(int i = 0; i < ranges.count(); i++)
	{
		int topRow = ranges.at(i).topRow();
		int bottomRow = ranges.at(i).bottomRow();
		for(int row = topRow; row <= bottomRow; row++)
		{
			QString text = m_iPlayListTableWidget->item(row,COLUMN_NAME)->data(Qt::UserRole).toString();
			m_playList->DeleteItem(text);
		}
	}
	Start();
}
