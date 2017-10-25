#ifndef CPLISTWIDGET_H
#define CPLISTWIDGET_H

#include <QWidget>
#include "common.h"
#include "cplaylist.h"

class SKMediaPlayer;

class ItemDelegate : public QItemDelegate  
{  
	Q_OBJECT

public:  
	ItemDelegate() {}
	~ItemDelegate() {}

	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const  
	{  
		QStyleOptionViewItem viewOption(option);

		viewOption.palette.setColor(QPalette::HighlightedText,index.data(Qt::ForegroundRole).value<QColor>());

		QItemDelegate::paint(painter,viewOption,index);
	}  
};

class CPlistWidget : public QWidget
{
	Q_OBJECT

public:
	CPlistWidget(QWidget *parent = 0);
	~CPlistWidget();

	void Start();
	void SetApp(SKMediaPlayer *a) { m_app = a; }
	void SetPlayList(CPlayList *l) { m_playList = l; }

private:
	QWidget *m_mainWidget;
	QGridLayout *m_mainGridLayout;
	QPushButton *m_iBtnPlus;
	QPushButton *m_iBtnMinus;
	QTableWidget *m_iPlayListTableWidget;
	CPlayList *m_playList;
	ItemDelegate *m_itemDelegate;

private:
	void Init();
	void InitUi();
	void InitSlot();

signals:
	void sigSelectFile(QString);

private slots:
	void SlotPlaylistItemClicked(QTableWidgetItem *item);
	void SlotAddPlayItem();
	void SlotDeletePlayItem();

private:
	SKMediaPlayer *m_app;
	
};

#endif // CPLISTWIDGET_H
