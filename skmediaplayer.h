#ifndef SKMEDIAPLAYER_H
#define SKMEDIAPLAYER_H

#include "AbsFrameLessAutoSize.h"
#include "common.h"
#include "cmainwidget.h"
#include "ctopwidget.h"
#include "ccenterwidget.h"
#include "cbottomwidget.h"
#include "cbottomfloatwidget.h"
#include "cskinwidget.h"
#include "csystemwidget.h"
#include "csimpleparamwidget.h"
#include "caboutwidget.h"
#include "cplistwidget.h"
#include "cplaylist.h"
#include <vlc/vlc.h>

class SKMediaPlayer : public AbsFrameLessAutoSize
{
	Q_OBJECT

public:
	SKMediaPlayer(QWidget *parent = 0);
	~SKMediaPlayer();

	libvlc_media_player_t *GetPlayer() { return vlcPlayer; }
	void SetSkin(QString s) { m_mainWidget->setSkin(s); }
	void Play(QString file);
	void SetCenterWidgetFocus() { m_centerWidget->setFocus(); }
	void ShowBottomFloatWidget(bool isShow);

public:
	bool m_bPauseSliderTime;
	bool m_bClickSliderTime;
	int  m_iFullScrMouse;
	CCenterMenu *m_iMenu;
	bool m_bIsShowSystemTime;
	bool m_bIsShowParams;
	int m_iMediaTrackCount;
	QList<stuMediaTrack *> m_iMediaTrackList;
	int m_iCurrentMediaTrackId;
	QString m_iMediaAspectRatio;
	float m_iMediaScale;

protected:
	virtual void mouseMoveEvent(QMouseEvent *);
	virtual void mouseDoubleClickEvent(QMouseEvent *);
	virtual void keyPressEvent(QKeyEvent *);
	virtual void closeEvent(QCloseEvent *);

private:
	virtual void paintEvent(QPaintEvent *);

private:
	bool m_bIsMax;
	QRect location;
	QTimer *m_iTimer;

	QGridLayout *m_mainGridLayout;
	CMainWidget *m_mainWidget;
	CTopWidget *m_topWidget;
	CCenterWidget *m_centerWidget;
	CBottomWidget *m_bottomWidget;
	CBottomFloatWidget *m_bottomFloatWidget;
	CSkinWidget *m_skinWidget;
	CSystemWidget *m_systemWidget;
	CSimpleParamWidget *m_simpleParamWidget;
	CAboutWidget *m_aboutWidget;
	CPlistWidget *m_pListWidget;

	libvlc_instance_t *vlcInstance;
	libvlc_media_player_t *vlcPlayer;

	QString m_iCurrentFile;
	CPlayList *m_playList;
	bool m_bStartJumpTime;
	quint32 m_iJumpTime;

	bool m_bPlaylist;
	int	m_iPlaylistRow;

private:
	void Init();
	void InitUi();
	void InitSlot();
	void InitMediaParams(libvlc_media_t *vlcMedia);
	QString _Utf8ToGb2312(QString text);

public slots:
	void SlotShowMax();
	void SlotShowMin();
	void SlotShowNormal();
	void SlotStartStop();
	void SlotPause();
	void SlotOpen();
	void SlotForward();
	void SlotRewind();
	void SlotTimeout();
	void SlotFullScreen();
	void SlotSkinWidget();
	void SlotAbout();
	void SlotPlaylist();
	void SlotSelectFile(QString path);

};

#endif // SKMEDIAPLAYER_H
