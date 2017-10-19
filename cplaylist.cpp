#include "cplaylist.h"

CPlayList::CPlayList(QObject *parent)
	: QObject(parent)
{

}

CPlayList::~CPlayList()
{
	foreach (stuPlayItem *item, m_iPlayItems)
		delete item;

	m_iPlayItems.clear();
}

bool CPlayList::ReadList()
{
	QString path = common::GetCurrentAppPath() + PLAYLIST_FILENAME;
	QFile file(path);
	if(!file.open(QIODevice::ReadWrite | QIODevice::Text)) 
		return false;

	QString content;
	QTextStream in(&file);
	while (!in.atEnd()) 
	{
		QString line = in.readLine().trimmed();
		QString path = line.split("::").at(0);
		quint32 time = line.split("::").at(1).toInt();
		if (path.isEmpty() || !common::FileExists(path))
			continue;

		stuPlayItem *item = new stuPlayItem();
		item->path = path;
		item->time = time;
		m_iPlayItems.append(item);
	}

	file.close();
	return true;
}

bool CPlayList::WriteList()
{
	QString path = common::GetCurrentAppPath() + PLAYLIST_FILENAME;
	path.replace(":/",":\\");
	QFile file(path);
	if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) 
		return false;

	QTextStream out(&file);
	foreach (stuPlayItem *item, m_iPlayItems)
	{
		QString s = QString("%1::%2").arg(item->path).arg(item->time);
		out << s << "\n";
	}

	file.close();
	return true;
}

quint32 CPlayList::AppendItem(QString path)
{
	bool bFind = false;
	foreach (stuPlayItem *item, m_iPlayItems)
	{
		if (item->path == path)
			return item->time;
	}

	if (!bFind)
	{
		stuPlayItem *item = new stuPlayItem();
		item->path = path;
		m_iPlayItems.append(item);
	}

	return 0;
}

void CPlayList::ReplaceItemTime(QString path, quint32 time)
{
	foreach (stuPlayItem *item, m_iPlayItems)
	{
		if (item->path == path)
			item->time = time;
	}
}
