#include "common.h"

common::common()
{

}

common::~common()
{

}

//获取当前路径
QString common::GetCurrentAppPath()
{
    return QCoreApplication::applicationDirPath()+"/";
}

//获取当前路径
QString common::GetCurrentAppName()
{
	return QCoreApplication::applicationName();
}

//获取当前日期时间星期
QString common::GetLongDateTime()
{
	QDateTime time = QDateTime::currentDateTime();

	return time.toString("yyyy-MM-dd hh:mm:ss.dddd");
}

//文件是否存在
bool common::FileExists(QString strFile)
{
    QFile tempFile(strFile);
    if (tempFile.exists())
        return true;

    return false;
}

int	common::FileLineCount(QString strFile)
{
	int count = 0;

	QFile file(strFile);
    if(!file.open(QFile::ReadOnly | QFile::Text)) 
		return 0;

	QTextStream in(&file);
	while (!in.atEnd()) 
	{
		QString line = in.readLine();
		count++;
	}

	file.close();
	return count;
}

//文件夹是否存在
bool common::FolderExists(QString strFolder)
{
    QDir tempFolder(strFolder);
    if(tempFolder.exists())
        return true;

    return false;
}

//创建文件夹
bool common::CreateFolder(QString strFolder)
{
    QDir dir;
    return dir.mkdir(strFolder);
}
