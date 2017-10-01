#include "ccentermenu.h"
#include "skmediaplayer.h"

CCenterMenu::CCenterMenu(QWidget *parent)
	: QMenu(parent)
{
	m_app = (SKMediaPlayer *)parent;

	Init();
	InitUi();
}

CCenterMenu::~CCenterMenu()
{

}

void CCenterMenu::Init()
{
	m_eAspectRatio = enum_aspect_ratio_original;
	menu_track = NULL;
	CreateMenuItem();
}

void CCenterMenu::InitUi()
{
	setStyleSheet(
		"QMenu{ background-color:rgb(250,250,250); border:1px solid rgb(214,214,214); }"
		"QMenu::item{ height:28px; padding:0px 20px 0px 40px; font-size:12px; color:rgb(0, 0, 0); font-family: Microsoft Yahei; }"
		"QMenu::item:focus{ padding: -1; }"
		"QMenu::item:selected:enabled{ background:rgb(22, 154, 243); color:white; }"
		"QMenu::item:selected:!enabled{ color:transparent; }"
		"QMenu::icon{ position:absolute;left: 12px; }"
		"QMenu::separator{ height:1px; background:rgb(209,209,209); margin:4px 0px 4px 0px; }");
	setContentsMargins(2,4,2,4);
}

void CCenterMenu::InitSlot()
{
	connect(act_openFile,SIGNAL(triggered()),this,SLOT(SlotOpenFile()));
	connect(act_close,SIGNAL(triggered()),this,SLOT(SlotClose()));
	connect(act_sysTime,SIGNAL(triggered()),this,SLOT(SlotSystemTime()));
	connect(act_params,SIGNAL(triggered()),this,SLOT(SlotProgressVolume()));
	connect(act_about,SIGNAL(triggered()),this,SLOT(SlotAbout()));
	connect(act_aspect_ratio_original,SIGNAL(triggered()),this,SLOT(SlotAspectRatioOriginal()));
	connect(act_aspect_ratio_4_3,SIGNAL(triggered()),this,SLOT(SlotAspectRatio43()));
	connect(act_aspect_ratio_5_4,SIGNAL(triggered()),this,SLOT(SlotAspectRatio54()));
	connect(act_aspect_ratio_16_9,SIGNAL(triggered()),this,SLOT(SlotAspectRatio1609()));
	connect(act_aspect_ratio_16_10,SIGNAL(triggered()),this,SLOT(SlotAspectRatio1610()));
	connect(act_scale_normal,SIGNAL(triggered()),this,SLOT(SlotScaleNormal()));
	connect(act_scale_zoom_in,SIGNAL(triggered()),this,SLOT(SlotScaleZoomIn()));
	connect(act_scale_zoom_out,SIGNAL(triggered()),this,SLOT(SlotScaleZoomOut()));
	connect(act_snapshot,SIGNAL(triggered()),this,SLOT(SlotSnapshot()));
	connect(act_fileLink,SIGNAL(triggered()),this,SLOT(SlotAssociatedVideoFile()));
}

void CCenterMenu::CreateMenuItem()
{
	act_openFile = new QAction(QIcon(":/image/open"),tr("Open File..."),this);
	act_close = new QAction(QIcon(":/image/stop"),tr("Close"),this);
	act_sysTime = new QAction(tr("System Time"),this);
	if (m_app->m_bIsShowSystemTime)
		act_sysTime->setIcon(QIcon(":/image/check"));
	act_params = new QAction(tr("Progress and Volume"),this);
	if (m_app->m_bIsShowParams)
		act_params->setIcon(QIcon(":/image/check"));
	act_about = new QAction(QIcon(":/image/about"),tr("About..."),this);
	act_snapshot = new QAction(QIcon(":/image/camera"),tr("Snapshot"),this);
	act_fileLink = new QAction(QIcon(":/image/link"),tr("Associated video file"),this);

	menu_aspect_ratio = new QMenu(this);
	menu_aspect_ratio->setTitle(tr("Aspect Ratio"));
	menu_aspect_ratio->setIcon(QIcon(":/image/tv"));
	act_aspect_ratio_original = new QAction(tr("Original Scale"),menu_aspect_ratio);
	act_aspect_ratio_4_3 = new QAction(tr("4:3"),menu_aspect_ratio);
	act_aspect_ratio_5_4 = new QAction(tr("5:4"),menu_aspect_ratio);
	act_aspect_ratio_16_9 = new QAction(tr("16:9"),menu_aspect_ratio);
	act_aspect_ratio_16_10 = new QAction(tr("16:10"),menu_aspect_ratio);
	switch (m_eAspectRatio)
	{
	case enum_aspect_ratio_original:
		act_aspect_ratio_original->setIcon(QIcon(":/image/check"));
		break;
	case enum_act_aspect_ratio_4_3:
		act_aspect_ratio_4_3->setIcon(QIcon(":/image/check"));
		break;
	case enum_act_aspect_ratio_5_4:
		act_aspect_ratio_5_4->setIcon(QIcon(":/image/check"));
		break;
	case enum_act_aspect_ratio_16_9:
		act_aspect_ratio_16_9->setIcon(QIcon(":/image/check"));
		break;
	case enum_act_aspect_ratio_16_10:
		act_aspect_ratio_16_10->setIcon(QIcon(":/image/check"));
		break;
	}
	act_scale_normal = new QAction(tr("Original Size"),menu_aspect_ratio);
	act_scale_zoom_in = new QAction(QIcon(":/image/zoom_in"),tr("Zoom In"),menu_aspect_ratio);
	act_scale_zoom_out = new QAction(QIcon(":/image/zoom_out"),tr("Zoom Out"),menu_aspect_ratio);
	menu_aspect_ratio->addAction(act_aspect_ratio_original);
	menu_aspect_ratio->addAction(act_aspect_ratio_4_3);
	menu_aspect_ratio->addAction(act_aspect_ratio_5_4);
	menu_aspect_ratio->addAction(act_aspect_ratio_16_9);
	menu_aspect_ratio->addAction(act_aspect_ratio_16_10);
	menu_aspect_ratio->addSeparator();
	menu_aspect_ratio->addAction(act_scale_normal);
	menu_aspect_ratio->addAction(act_scale_zoom_in);
	menu_aspect_ratio->addAction(act_scale_zoom_out);

	if (m_app->m_iMediaTrackList.count() > 0)
	{
		menu_track = new QMenu(this);
		menu_track->setTitle(tr("Sound Language"));
		menu_track->setIcon(QIcon(":/image/map"));
		foreach (stuMediaTrack *track, m_app->m_iMediaTrackList)
		{
			QAction *action = menu_track->addAction(track->trackDesc);
			if (track->trackId == m_app->m_iCurrentMediaTrackId)
				action->setIcon(QIcon(":/image/check"));
			action->setData(track->trackId);
			connect(action,SIGNAL(triggered()),this,SLOT(SlotTrack()));
		}
	}

	addAction(act_openFile);
	addAction(act_close);
	addSeparator();
	addAction(act_sysTime);
	addAction(act_params);
	addSeparator();
	addMenu(menu_aspect_ratio);
	if (menu_track)
	{
		addMenu(menu_track);
		addAction(act_snapshot);
	}
	addSeparator();
	addAction(act_fileLink);
	addSeparator();
	addAction(act_about);

	InitSlot();
}

void CCenterMenu::SlotOpenFile()
{
	emit sigOpenFile();
}

void CCenterMenu::SlotClose()
{
	emit sigClose();
}

void CCenterMenu::SlotSystemTime()
{
	m_app->m_bIsShowSystemTime = !m_app->m_bIsShowSystemTime;
}

void CCenterMenu::SlotProgressVolume()
{
	m_app->m_bIsShowParams = !m_app->m_bIsShowParams;
}

void CCenterMenu::SlotAbout()
{
	emit sigAbout();
}

void CCenterMenu::SlotAspectRatioOriginal()
{
	if (!m_app->GetPlayer())
		return;

	libvlc_video_set_aspect_ratio(m_app->GetPlayer(),m_app->m_iMediaAspectRatio.toStdString().data());
	m_eAspectRatio = enum_aspect_ratio_original;
}

void CCenterMenu::SlotAspectRatio43()
{
	if (!m_app->GetPlayer())
		return;

	libvlc_video_set_aspect_ratio(m_app->GetPlayer(),"4:3");
	m_eAspectRatio = enum_act_aspect_ratio_4_3;
}

void CCenterMenu::SlotAspectRatio54()
{
	if (!m_app->GetPlayer())
		return;

	libvlc_video_set_aspect_ratio(m_app->GetPlayer(),"5:4");
	m_eAspectRatio = enum_act_aspect_ratio_5_4;
}

void CCenterMenu::SlotAspectRatio1609()
{
	if (!m_app->GetPlayer())
		return;

	libvlc_video_set_aspect_ratio(m_app->GetPlayer(),"16:9");
	m_eAspectRatio = enum_act_aspect_ratio_16_9;
}

void CCenterMenu::SlotAspectRatio1610()
{
	if (!m_app->GetPlayer())
		return;

	libvlc_video_set_aspect_ratio(m_app->GetPlayer(),"16:10");
	m_eAspectRatio = enum_act_aspect_ratio_16_10;
}

void CCenterMenu::SlotScaleNormal()
{
	if (!m_app->GetPlayer())
		return;

	libvlc_video_set_scale(m_app->GetPlayer(),0.0);
	m_app->m_iMediaScale = 1.0;
}

void CCenterMenu::SlotScaleZoomIn()
{
	if (!m_app->GetPlayer())
		return;

	if (m_app->m_iMediaScale >= 2.0)
		return;

	m_app->m_iMediaScale += 0.2;
	libvlc_video_set_scale(m_app->GetPlayer(),m_app->m_iMediaScale);
}

void CCenterMenu::SlotScaleZoomOut()
{
	if (!m_app->GetPlayer())
		return;

	if (m_app->m_iMediaScale <= 0.2)
		return;

	m_app->m_iMediaScale -= 0.2;
	libvlc_video_set_scale(m_app->GetPlayer(),m_app->m_iMediaScale);
}

void CCenterMenu::SlotTrack()
{
	QAction *action = qobject_cast<QAction *>(sender());
	if (action)
	{
		int id = action->data().toInt();
		libvlc_audio_set_track(m_app->GetPlayer(),id);
		m_app->m_iCurrentMediaTrackId = id;
	}
}

void CCenterMenu::SlotSnapshot()
{
	QString path = common::GetCurrentAppPath()+"snapshot";
	QDir dir(path);
	if (!dir.exists()) //目录不存在
	{
		if (!dir.mkdir(path)) //目录未创建成功
			return;
	}
	QTextCodec* utf8Codec = QTextCodec::codecForName("utf-8");
	QTextCodec* gb2312Codec = QTextCodec::codecForName("gb2312");
	QString strUnicode=gb2312Codec->toUnicode(path.toStdString().data());
	QByteArray ByteUtf8= utf8Codec->fromUnicode(strUnicode);
	path = ByteUtf8.data();

	int w = m_app->m_iMediaAspectRatio.split(":").at(0).toInt();
	int h = m_app->m_iMediaAspectRatio.split(":").at(1).toInt();
	int ret = libvlc_video_take_snapshot(m_app->GetPlayer(),0,path.toStdString().data(),w,h);
}

void CCenterMenu::SlotAssociatedVideoFile()
{
	_FileTypeAssociated("mp4");
	_FileTypeAssociated("mkv");
	_FileTypeAssociated("rmvb");
}

#include <Shlobj.h>
QString CCenterMenu::_FileTypeAssociated(QString type)
{
	QString sExe = common::GetCurrentAppPath()+"久为影音.exe";
	sExe.replace(":/",":\\");
	QString sIco = common::GetCurrentAppPath()+"SKMediaPlayer.ico";
	sIco.replace("/","\\");

	QSettings settings1(tr("HKEY_CLASSES_ROOT\\.%1").arg(type),QSettings::NativeFormat);  
	settings1.setValue(".",tr("JwYy.%1").arg(type));

	QSettings settings2(tr("HKEY_CLASSES_ROOT\\JwYy.%1\\Shell\\Open\\Command").arg(type),QSettings::NativeFormat);  
	settings2.setValue(".",sExe+" \"%1\"");

	QSettings settings3(tr("HKEY_CLASSES_ROOT\\JwYy.%1\\DefaultIcon").arg(type),QSettings::NativeFormat);  
	settings3.setValue(".",sIco);

	QSettings settings4(tr("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FileExts\\.%1").arg(type),QSettings::NativeFormat);  
	settings4.clear();

	QSettings settings5(tr("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FileExts\\.%1\\UserChoice").arg(type),QSettings::NativeFormat);  
	settings5.setValue("Progid",tr("JwYy.%1").arg(type));

	::SHChangeNotify(SHCNE_ASSOCCHANGED,SHCNF_IDLIST|SHCNF_FLUSH,0,0);

	return true;
}
