#include "skmediaplayer.h"
#include <Windows.h>

#define APP_INIT_WIDTH		900
#define APP_INIT_HEIGHT		600
#define SHADOW_WIDTH		1

static bool m_bUnableWindow = true;

SKMediaPlayer::SKMediaPlayer(QWidget *parent)
	: AbsFrameLessAutoSize(parent)
{
	Init();
	InitUi();
	InitSlot();
}

SKMediaPlayer::~SKMediaPlayer()
{
	if (vlcInstance)
		libvlc_release(vlcInstance);

	delete m_iTimer;
	delete m_bottomWidget;
	delete m_centerWidget;
	delete m_topWidget;
	delete m_bottomFloatWidget;
	delete m_systemWidget;
	delete m_simpleParamWidget;
	delete m_mainWidget;
	delete m_mainGridLayout;

	foreach (stuMediaTrack *track, m_iMediaTrackList)
		delete track;
	m_iMediaTrackList.clear();
}

void SKMediaPlayer::Init()
{
	m_bIsMax = false;
	m_iTimer = new QTimer(this);
	m_iTimer->setInterval(300);
	m_bPauseSliderTime = false;
	m_bClickSliderTime = false;
	m_iFullScrMouse = 0;
	m_bIsShowSystemTime = true;
	m_bIsShowParams = true;

	vlcPlayer = NULL;
	vlcInstance = libvlc_new(0, NULL);
	if (vlcInstance == NULL) 
	{
		QMessageBox::critical(this,"Error","SKMediaPlayer init error!");
		exit(1);
	}

	m_iMenu = new CCenterMenu(this);
}

void SKMediaPlayer::InitUi()
{
	setMinimumSize(APP_INIT_WIDTH,APP_INIT_HEIGHT);
	setWindowFlags(Qt::FramelessWindowHint);
	//setAttribute(Qt::WA_TranslucentBackground,true); //加上画面出不来
	setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	location = this->geometry();

	m_mainWidget = new CMainWidget();
	m_mainGridLayout = new QGridLayout;
	m_mainGridLayout->addWidget(m_mainWidget);
	m_mainGridLayout->setContentsMargins(SHADOW_WIDTH,SHADOW_WIDTH,SHADOW_WIDTH,SHADOW_WIDTH);
	setLayout(m_mainGridLayout);

	m_topWidget = new CTopWidget();
	QVBoxLayout *topLayout = new QVBoxLayout;
	topLayout->addWidget(m_topWidget);
	topLayout->setSpacing(0);
	topLayout->setContentsMargins(0,0,0,0);

	m_centerWidget = new CCenterWidget();
	m_centerWidget->SetApp(this);
	QVBoxLayout *centerLayout = new QVBoxLayout;
	centerLayout->addWidget(m_centerWidget);
	centerLayout->setSpacing(0);
	centerLayout->setContentsMargins(0,0,0,0);

	m_bottomWidget = new CBottomWidget();
	m_bottomWidget->SetApp(this);
	QVBoxLayout *bottomLayout = new QVBoxLayout;
	bottomLayout->addWidget(m_bottomWidget);
	bottomLayout->setSpacing(0);
	bottomLayout->setContentsMargins(0,0,0,0);

	QVBoxLayout *vLyout = new QVBoxLayout;
	vLyout->addLayout(topLayout);
	vLyout->addLayout(centerLayout);
	vLyout->addLayout(bottomLayout);
	vLyout->setSpacing(0);
	vLyout->setContentsMargins(0,0,0,0);
	m_mainWidget->setLayout(vLyout);

	m_bottomFloatWidget = new CBottomFloatWidget();
	m_bottomFloatWidget->SetApp(this);
	m_bottomFloatWidget->hide();

	m_systemWidget = new CSystemWidget();
	m_systemWidget->SetApp(this);
	m_systemWidget->hide();

	m_simpleParamWidget = new CSimpleParamWidget();
	m_simpleParamWidget->SetApp(this);
	m_simpleParamWidget->hide();

	m_aboutWidget = new CAboutWidget(this);
	m_aboutWidget->setSkin(m_mainWidget->GetCurSkin());
	m_aboutWidget->hide();

	m_centerWidget->setFocus(); //以中心窗口为焦点，避免键盘操作异常
}

void SKMediaPlayer::InitSlot()
{
	connect(m_iTimer,SIGNAL(timeout()),this,SLOT(SlotTimeout()));

	connect(m_topWidget,SIGNAL(sigSkin()),this,SLOT(SlotSkinWidget()));
	connect(m_topWidget,SIGNAL(sigMainMenu()),this,SLOT(ShowMainMenu()));
	connect(m_topWidget,SIGNAL(sigMax()),this,SLOT(SlotShowMax()));
	connect(m_topWidget,SIGNAL(sigMin()),this,SLOT(SlotShowMin()));
	connect(m_topWidget,SIGNAL(sigClose()),this,SLOT(close()));

	connect(m_bottomWidget,SIGNAL(sigStartStop()),this,SLOT(SlotStartStop()));
	connect(m_bottomWidget,SIGNAL(sigPause()),this,SLOT(SlotPause()));
	connect(m_bottomWidget,SIGNAL(sigOpen()),this,SLOT(SlotOpen()));
	connect(m_bottomWidget,SIGNAL(sigForward()),this,SLOT(SlotForward()));
	connect(m_bottomWidget,SIGNAL(sigRewind()),this,SLOT(SlotRewind()));
	connect(m_bottomWidget,SIGNAL(sigFullscreen()),this,SLOT(SlotFullScreen()));

	connect(m_bottomFloatWidget,SIGNAL(sigStartStop()),this,SLOT(SlotStartStop()));
	connect(m_bottomFloatWidget,SIGNAL(sigPause()),this,SLOT(SlotPause()));
	connect(m_bottomFloatWidget,SIGNAL(sigOpen()),this,SLOT(SlotOpen()));
	connect(m_bottomFloatWidget,SIGNAL(sigForward()),this,SLOT(SlotForward()));
	connect(m_bottomFloatWidget,SIGNAL(sigRewind()), this,SLOT(SlotRewind()));
	connect(m_bottomFloatWidget,SIGNAL(sigFullscreen()),this,SLOT(SlotFullScreen()));

	connect(m_iMenu,SIGNAL(sigOpenFile()),this,SLOT(SlotOpen()));
	connect(m_iMenu,SIGNAL(sigClose()),this,SLOT(SlotPause()));
	connect(m_iMenu,SIGNAL(sigAbout()),this,SLOT(SlotAbout()));
}

void SKMediaPlayer::mouseMoveEvent(QMouseEvent *event)
{
	mouseMoveRect(mapFromGlobal(event->globalPos()));
	if (m_state.MousePressed)
	{
		if (m_bIsMax)
		{
			SlotShowMax();
			int curMonitor = QApplication::desktop()->screenNumber(this);
			QRect rect = QApplication::desktop()->availableGeometry(curMonitor);
			float xs;
			int fx;
			if (curMonitor <= 0) //主显示屏
			{
				xs = (float)m_state.MousePos.x()/(float)rect.right();
				fx = int((float)(location.right()-location.left()) * xs);
			}
			else //分显示屏
			{
				xs = (float)(m_state.MousePos.x()-rect.left())/(float)(rect.right()-rect.left());
				fx = int((float)(location.right()-location.left()) * xs);
			}

			xs = (float)m_state.MousePos.y()/(float)rect.bottom();
			int fy = int((float)(location.bottom()-location.top()) * xs);

			m_state.WindowPos.setX(m_state.MousePos.x()-fx);
			m_state.WindowPos.setY(m_state.MousePos.y()-fy);
		}

		this->move(m_state.WindowPos + (event->globalPos() - m_state.MousePos));
	}
}

void SKMediaPlayer::mouseDoubleClickEvent(QMouseEvent *e)
{
	QWidget::mouseDoubleClickEvent(e);
}

void SKMediaPlayer::keyPressEvent(QKeyEvent *e)
{
	if ((e->modifiers() == Qt::ControlModifier) && (e->key() == Qt::Key_Return))
	{
		SlotFullScreen();
	}
	else if (e->key() == Qt::Key_Escape && this->isFullScreen())
	{
		SlotShowNormal();
		m_iFullScrMouse = 0;
		//QApplication::setOverrideCursor(Qt::ArrowCursor);
		m_centerWidget->setCursor(Qt::BlankCursor);
		m_systemWidget->hide();
		m_simpleParamWidget->hide();
		ShowBottomFloatWidget(false);
	}
	else if (e->key() == Qt::Key_Left)
	{
		SlotRewind();
	}
	else if (e->key() == Qt::Key_Right)
	{
		SlotForward();
	}
	else if (e->key() == Qt::Key_Up)
	{
		int pos = m_bottomWidget->GetSliderVolume()->value()+10;
		if (pos > 100)
			pos = 100;
		m_bottomWidget->GetSliderVolume()->setValue(pos);
		m_bottomFloatWidget->GetSliderVolume()->setValue(pos);
		m_simpleParamWidget->GetLabelVolume()->setText(tr("volume %1").arg(pos));
	}
	else if (e->key() == Qt::Key_Down)
	{
		int pos = m_bottomWidget->GetSliderVolume()->value()-10;
		if (pos < 0)
			pos = 0;
		m_bottomWidget->GetSliderVolume()->setValue(pos);
		m_bottomFloatWidget->GetSliderVolume()->setValue(pos);
		m_simpleParamWidget->GetLabelVolume()->setText(tr("volume %1").arg(pos));
	}
	else if (e->key() == Qt::Key_Space)
	{
		SlotStartStop();
	}
}

void SKMediaPlayer::closeEvent(QCloseEvent *e)
{
	SlotPause();
	e->accept();
}

void SKMediaPlayer::paintEvent(QPaintEvent *e)
{
	AbsFrameLessAutoSize::paintEvent(e);

	QPainterPath path;
	path.setFillRule(Qt::WindingFill);
	path.addRect(SHADOW_WIDTH,SHADOW_WIDTH,this->width()-SHADOW_WIDTH*2,this->height()-SHADOW_WIDTH*2);
	
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.fillPath(path,QBrush(Qt::black));
	
	QColor color(0, 0, 0, 50);
	for (int i = 0; i < SHADOW_WIDTH; i++)
	{
		QPainterPath path;
		path.setFillRule(Qt::WindingFill);
		path.addRect(SHADOW_WIDTH-i, SHADOW_WIDTH-i, this->width()-(SHADOW_WIDTH-i)*2, this->height()-(SHADOW_WIDTH-i)*2);
		color.setAlpha(150 - qSqrt(i)*50);
		painter.setPen(color);
		painter.drawPath(path);
	}
}

void SKMediaPlayer::SlotShowMax()
{
	m_centerWidget->setFocus();
	int curMonitor = QApplication::desktop()->screenNumber(this); //获取当前显示屏
	if (m_bIsMax)
	{
		this->setGeometry(location);
		m_mainGridLayout->setContentsMargins(SHADOW_WIDTH,SHADOW_WIDTH,SHADOW_WIDTH,SHADOW_WIDTH);
		m_topWidget->GetBtnMaximize()->setStyleSheet(
			"QPushButton{border-image:url(:/image/MaxMize_Btn_nor);}"
			"QPushButton::hover{border-image:url(:/image/MaxMize_Btn_hover);}"
			"QPushButton::pressed{border-image:url(:/image/MaxMize_Btn_down);}");
	}
	else
	{
		location = this->geometry(); //最大化前，获取当前界面的位置
		this->setGeometry(QApplication::desktop()->availableGeometry(curMonitor));
		m_mainGridLayout->setContentsMargins(0,0,0,0);
		m_topWidget->GetBtnMaximize()->setStyleSheet(
			"QPushButton{border-image:url(:/image/MaxMize_Btn_nor2);}"
			"QPushButton::hover{border-image:url(:/image/MaxMize_Btn_hover2);}"
			"QPushButton::pressed{border-image:url(:/image/MaxMize_Btn_down2);}");
	}

	m_bIsMax = !m_bIsMax;
}

void SKMediaPlayer::SlotShowMin()
{
	m_centerWidget->setFocus();
	showMinimized();
}

void SKMediaPlayer::SlotShowNormal()
{
	QRect rect;
	if (m_bIsMax)
	{
		int curMonitor = QApplication::desktop()->screenNumber(this);
		QRect dRect = QApplication::desktop()->availableGeometry(curMonitor);
		rect.setX((dRect.width()-APP_INIT_WIDTH)/2+dRect.x());
		rect.setY((dRect.height()-APP_INIT_HEIGHT)/2);
		m_bIsMax = !m_bIsMax;
	}
	else
	{
		rect.setX(location.x());
		rect.setY(location.y());
	}
	rect.setWidth(APP_INIT_WIDTH);
	rect.setHeight(APP_INIT_HEIGHT);
	this->setGeometry(rect);
	location = rect;
	m_mainGridLayout->setContentsMargins(SHADOW_WIDTH,SHADOW_WIDTH,SHADOW_WIDTH,SHADOW_WIDTH);
	m_topWidget->GetBtnMaximize()->setStyleSheet(
		"QPushButton{border-image:url(:/image/MaxMize_Btn_nor);}"
		"QPushButton::hover{border-image:url(:/image/MaxMize_Btn_hover);}"
		"QPushButton::pressed{border-image:url(:/image/MaxMize_Btn_down);}");
	m_topWidget->show();
	m_bottomWidget->show();
}

void SKMediaPlayer::SlotStartStop()
{
	m_centerWidget->setFocus();
	if (!vlcPlayer)
		return;

	if (libvlc_media_player_is_playing(vlcPlayer))
	{
		libvlc_media_player_pause(vlcPlayer);
		m_bottomWidget->GetBtnStartStop()->setStyleSheet(
			"QPushButton{border-image:url(:/image/btn_play_nor);}"
			"QPushButton::hover{border-image:url(:/image/btn_play_hover);}"
			"QPushButton::pressed{border-image:url(:/image/btn_play_down);}");
		m_bottomFloatWidget->GetBtnStartStop()->setStyleSheet(
			"QPushButton{border-image:url(:/image/btn_play_nor);}"
			"QPushButton::hover{border-image:url(:/image/btn_play_hover);}"
			"QPushButton::pressed{border-image:url(:/image/btn_play_down);}");
		m_iTimer->stop();
	}
	else
	{
		libvlc_media_player_play(vlcPlayer);
		m_bottomWidget->GetBtnStartStop()->setStyleSheet(
			"QPushButton{border-image:url(:/image/btn_pause_nor);}"
			"QPushButton::hover{border-image:url(:/image/btn_pause_hover);}"
			"QPushButton::pressed{border-image:url(:/image/btn_pause_down);}");
		m_bottomFloatWidget->GetBtnStartStop()->setStyleSheet(
			"QPushButton{border-image:url(:/image/btn_pause_nor);}"
			"QPushButton::hover{border-image:url(:/image/btn_pause_hover);}"
			"QPushButton::pressed{border-image:url(:/image/btn_pause_down);}");
		m_iTimer->start();
	}
}

void SKMediaPlayer::SlotPause()
{
	m_centerWidget->setFocus();
	if (vlcPlayer) 
	{
		libvlc_media_player_stop(vlcPlayer);
		libvlc_media_player_release(vlcPlayer);
		vlcPlayer = NULL;

		m_topWidget->GetLabelTitle()->setText(" "+tr("SKMediaPlayer"));
		m_bottomWidget->GetBtnStartStop()->setStyleSheet(
			"QPushButton{border-image:url(:/image/btn_play_nor);}"
			"QPushButton::hover{border-image:url(:/image/btn_play_hover);}"
			"QPushButton::pressed{border-image:url(:/image/btn_play_down);}");
		m_bottomFloatWidget->GetBtnStartStop()->setStyleSheet(
			"QPushButton{border-image:url(:/image/btn_play_nor);}"
			"QPushButton::hover{border-image:url(:/image/btn_play_hover);}"
			"QPushButton::pressed{border-image:url(:/image/btn_play_down);}");
		m_iTimer->stop();
		m_bottomWidget->GetLabelTime()->setText("00:00:00/00:00:00");
		m_bottomWidget->GetSliderTime()->setRange(0,0);
		m_bottomWidget->GetSliderTime()->setValue(0);
		m_bottomFloatWidget->GetLabelTime()->setText("00:00:00/00:00:00");
		m_bottomFloatWidget->GetSliderTime()->setRange(0,0);
		m_bottomFloatWidget->GetSliderTime()->setValue(0);

		m_bUnableWindow = true;
	}

	m_simpleParamWidget->hide();
}

void SKMediaPlayer::SlotOpen()
{
	m_centerWidget->setFocus();
	if (vlcPlayer/* && libvlc_media_player_is_playing(vlcPlayer)*/)
		return;

	QString filter = tr("Movie File(*.rmvb *.rm *.avi *.wmv *.mkv *.asf *.3gp *.mov *.mp4 *.ogv *.flv);;All File(*.*)");
	QString fileOpen = QFileDialog::getOpenFileName(this,tr("Load File"),QString::null,filter);
	if (fileOpen.isEmpty())
		return;

	Play(fileOpen);
}

void SKMediaPlayer::Play(QString file)
{
	file.replace(":/",":\\");
	libvlc_media_t *vlcMedia = libvlc_media_new_path(vlcInstance, file.toUtf8().constData());
	if (!vlcMedia)
		return;

	InitMediaParams(vlcMedia);
	vlcPlayer = libvlc_media_player_new_from_media(vlcMedia);
	libvlc_media_release(vlcMedia);
	libvlc_media_player_set_hwnd(vlcPlayer,(void*)m_centerWidget->winId());
	libvlc_media_player_play(vlcPlayer);

	QFileInfo fi(file);
	m_topWidget->GetLabelTitle()->setText(" "+tr("SKMediaPlayer")+tr(" - %1").arg(fi.fileName()));
	m_bottomWidget->GetBtnStartStop()->setStyleSheet(
		"QPushButton{border-image:url(:/image/btn_pause_nor);}"
		"QPushButton::hover{border-image:url(:/image/btn_pause_hover);}"
		"QPushButton::pressed{border-image:url(:/image/btn_pause_down);}");
	m_bottomFloatWidget->GetBtnStartStop()->setStyleSheet(
		"QPushButton{border-image:url(:/image/btn_pause_nor);}"
		"QPushButton::hover{border-image:url(:/image/btn_pause_hover);}"
		"QPushButton::pressed{border-image:url(:/image/btn_pause_down);}");

	m_iTimer->start();
}

void SKMediaPlayer::InitMediaParams(libvlc_media_t *vlcMedia)
{
	m_iMediaScale = 1.0;
	m_iMenu->SetEnumAspectRatio(enum_aspect_ratio_original);
	m_iMediaTrackList.clear();
	m_iMediaTrackCount = 0;

	libvlc_media_parse(vlcMedia);
	libvlc_media_track_t** media_tracks = NULL;
	int count = libvlc_media_tracks_get(vlcMedia, &media_tracks);
	for (int i = 0; i < count; i++)
	{
		libvlc_media_track_t* t = media_tracks[i];
		if (t->i_type == libvlc_track_audio)
		{
			//stuMediaTrack *track = new stuMediaTrack;
			//track->trackId = t->i_id;
			//if (t->psz_language)
			//	track->trackDesc = tr("%1").arg(t->psz_language);
			//m_iMediaTrackList.append(track);
			m_iMediaTrackCount++;
		}
		else if (t->i_type == libvlc_track_video)
		{
			m_iMediaAspectRatio = tr("%1:%2").arg(t->video->i_width).arg(t->video->i_height);
			m_iMediaTrackCount++;
		}
	}
	
	libvlc_media_tracks_release(media_tracks,count);
}

BOOL CALLBACK EnumerateVLC(HWND hWndvlc, LPARAM lParam)
{
	TCHAR szWndTitle[1024];
	int nLen = GetWindowText(hWndvlc, szWndTitle, 1024);
	if (0 != nLen)
	{
		EnableWindow(hWndvlc, FALSE);
		m_bUnableWindow = false;
	}

	return TRUE;
}

void SKMediaPlayer::SlotTimeout()
{
	if (m_bUnableWindow)
		EnumChildWindows(m_centerWidget->winId(),EnumerateVLC,NULL);

	if (vlcPlayer)
	{
		if (libvlc_audio_get_track_count(vlcPlayer) == m_iMediaTrackCount && m_iMediaTrackList.count() == 0)
		{
			libvlc_track_description_t *t = libvlc_audio_get_track_description(vlcPlayer);
			while (t)
			{
				if (t->i_id >= 0 && t->psz_name != "Disable")
				{
					stuMediaTrack *track = new stuMediaTrack;
					track->trackId = t->i_id;
					track->trackDesc = tr("%1").arg(t->psz_name);
					track->trackDesc = _Utf8ToGb2312(track->trackDesc);
					m_iMediaTrackList.append(track);
				}
				t = t->p_next;
			}

			m_iCurrentMediaTrackId = libvlc_audio_get_track(vlcPlayer);
		}

		if (m_bClickSliderTime)
		{
			int time_cur,time_max;
			if (this->isFullScreen())
			{
				time_cur = m_bottomFloatWidget->GetSliderTime()->value();
				time_max = m_bottomFloatWidget->GetSliderTime()->maximum();
			}
			else
			{
				time_cur = m_bottomWidget->GetSliderTime()->value();
				time_max = m_bottomWidget->GetSliderTime()->maximum();
			}
			libvlc_media_player_set_position(vlcPlayer,(float)time_cur/time_max);
			m_bClickSliderTime = false;
		}

		int volume = m_bottomWidget->GetSliderVolume()->value();
		libvlc_audio_set_volume(vlcPlayer,volume);
		if (volume == 0)
		{
			m_bottomWidget->GetLabelVolume()->setPixmap(QPixmap(":/image/Speak0"));
			m_bottomFloatWidget->GetLabelVolume()->setPixmap(QPixmap(":/image/Speak0"));
		}
		else if (volume < 35)
		{
			m_bottomWidget->GetLabelVolume()->setPixmap(QPixmap(":/image/Speak1"));
			m_bottomFloatWidget->GetLabelVolume()->setPixmap(QPixmap(":/image/Speak1"));
		}
		else if (volume < 70)
		{
			m_bottomWidget->GetLabelVolume()->setPixmap(QPixmap(":/image/Speak2"));
			m_bottomFloatWidget->GetLabelVolume()->setPixmap(QPixmap(":/image/Speak2"));
		}
		else
		{
			m_bottomWidget->GetLabelVolume()->setPixmap(QPixmap(":/image/Speak3"));
			m_bottomFloatWidget->GetLabelVolume()->setPixmap(QPixmap(":/image/Speak3"));
		}
		
		libvlc_time_t total = libvlc_media_player_get_length(vlcPlayer)/1000;
		libvlc_time_t time = libvlc_media_player_get_time(vlcPlayer)/1000;
		if (total >= 0 && time >= 0)
		{
			if (!m_bPauseSliderTime) //拖动时间轴时，暂停时间轴更新
			{
				m_bottomWidget->GetSliderTime()->setRange(0,total);
				m_bottomWidget->GetSliderTime()->setValue(time);
				m_bottomFloatWidget->GetSliderTime()->setRange(0,total);
				m_bottomFloatWidget->GetSliderTime()->setValue(time);
			}

			QString sTotal;
			QString sTime;
			int hour = total / 3600;
			int minute = (total % 3600) / 60;
			int second = (total%60);
			sTotal.sprintf("%02d:%02d:%02d",hour,minute,second);

			hour = time / 3600;
			minute = (time % 3600) / 60;
			second = (time%60);
			sTime.sprintf("%02d:%02d:%02d",hour,minute,second);
			m_bottomWidget->GetLabelTime()->setText(sTime+"/"+sTotal);
			m_bottomFloatWidget->GetLabelTime()->setText(sTime+"/"+sTotal);
			m_simpleParamWidget->GetLabelTime()->setText(sTime);

			if (libvlc_media_player_get_state(vlcPlayer) == libvlc_Ended)
				SlotPause();
		}

		if (this->isFullScreen())
		{
			if ((++m_iFullScrMouse) > 4 && m_bottomFloatWidget->isHidden())
				//QApplication::setOverrideCursor(Qt::BlankCursor);
				m_centerWidget->setCursor(Qt::BlankCursor);
			else
				//QApplication::setOverrideCursor(Qt::ArrowCursor);
				m_centerWidget->setCursor(Qt::ArrowCursor);

			if (m_bIsShowParams)
				m_simpleParamWidget->show();
			else
				m_simpleParamWidget->hide();
		}
	}
}

void SKMediaPlayer::SlotFullScreen()
{
	if (this->isFullScreen())
	{
		SlotShowNormal();
		m_iFullScrMouse = 0;
		//QApplication::setOverrideCursor(Qt::ArrowCursor);
		m_centerWidget->setCursor(Qt::BlankCursor);
		ShowBottomFloatWidget(false);
		m_systemWidget->hide();
		m_simpleParamWidget->hide();
	}
	else
	{
		location = this->geometry();
		m_topWidget->hide();
		m_bottomWidget->hide();
		m_centerWidget->setFocus();
		m_mainGridLayout->setContentsMargins(0,0,0,0);
		showFullScreen();

		int curMonitor = QApplication::desktop()->screenNumber(this);
		QRect rect = QApplication::desktop()->screenGeometry(curMonitor);
		m_simpleParamWidget->setFixedSize(90,30);
		m_simpleParamWidget->move(rect.x()+30,10);
	}
}

void SKMediaPlayer::SlotForward()
{
	m_centerWidget->setFocus();
	if (!vlcPlayer)
		return;

	int dur = m_bottomWidget->GetSliderTime()->maximum()- m_bottomWidget->GetSliderTime()->minimum();
	int pos = m_bottomWidget->GetSliderTime()->value()+5;
	if (pos >= dur)
	{
		SlotPause();
		return;
	}

	libvlc_media_player_set_position(vlcPlayer,(float)pos/dur);
	m_bottomWidget->GetSliderTime()->setValue(pos);
	m_bottomFloatWidget->GetSliderTime()->setValue(pos);
}

void SKMediaPlayer::SlotRewind()
{
	m_centerWidget->setFocus();
	if (!vlcPlayer)
		return;

	int dur = m_bottomWidget->GetSliderTime()->maximum()- m_bottomWidget->GetSliderTime()->minimum();
	int pos = m_bottomWidget->GetSliderTime()->value()-5;
	if (pos < 0)
		pos = 0;

	libvlc_media_player_set_position(vlcPlayer,(float)pos/dur);
	m_bottomWidget->GetSliderTime()->setValue(pos);
	m_bottomFloatWidget->GetSliderTime()->setValue(pos);
}

void SKMediaPlayer::SlotSkinWidget()
{
	m_centerWidget->setFocus();

	m_skinWidget = new CSkinWidget(this);
	m_skinWidget->SetApp(this);
	m_skinWidget->setSkin(m_mainWidget->GetCurSkin());
	m_skinWidget->show();
}

void SKMediaPlayer::ShowBottomFloatWidget(bool isShow)
{
	if (isShow)
	{
		int curMonitor = QApplication::desktop()->screenNumber(this);
		QRect rect = QApplication::desktop()->screenGeometry(curMonitor);
		m_bottomFloatWidget->setFixedSize(rect.width(),65);
		m_bottomFloatWidget->move(rect.x(),rect.height()-65);
		m_bottomFloatWidget->show();
	}
	else
	{
		m_bottomFloatWidget->hide();
	}

	SetCenterWidgetFocus();
}

void SKMediaPlayer::SlotAbout()
{
	int curMonitor = QApplication::desktop()->screenNumber(this);
	QRect rect = QApplication::desktop()->availableGeometry(curMonitor);
	m_aboutWidget->move((rect.width()-m_aboutWidget->width())/2+rect.x(),(rect.height()-m_aboutWidget->height())/2);

	m_aboutWidget->setSkin(m_mainWidget->GetCurSkin());
	m_aboutWidget->show();
}

QString SKMediaPlayer::_Utf8ToGb2312(QString text)
{
	QString t;

	QTextCodec* utf8Codec = QTextCodec::codecForName("utf-8");
	QTextCodec* gb2312Codec = QTextCodec::codecForName("gb2312");
	QString strUnicode = utf8Codec->toUnicode(text.toStdString().data());
	QByteArray ByteGb2312 = gb2312Codec->fromUnicode(strUnicode);
	t = ByteGb2312.data();

	return t;
}
