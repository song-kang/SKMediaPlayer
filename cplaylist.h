#ifndef CPLAYLIST_H
#define CPLAYLIST_H

#include "common.h"

#define PLAYLIST_FILENAME	"skmediaplayer.plist"

struct stuPlayItem
{
	stuPlayItem::stuPlayItem()
	{
		path = QString::null;
		time = 0;
	}
	QString path;
	quint32 time;
};

class CPlayList : public QObject
{
	Q_OBJECT

public:
	CPlayList(QObject *parent);
	~CPlayList();

	bool ReadList();
	bool WriteList();
	quint32 AppendItem(QString path);
	void ReplaceItemTime(QString path, quint32 time);

private:
	QFile m_iFile;
	QList<stuPlayItem*> m_iPlayItems;
	
};

#endif // CPLAYLIST_H
