#ifndef CCENTERMENU_H
#define CCENTERMENU_H

#include <QMenu>

enum eAspectRatio
{
	enum_aspect_ratio_original = 0,
	enum_act_aspect_ratio_4_3,
	enum_act_aspect_ratio_5_4,
	enum_act_aspect_ratio_16_9,
	enum_act_aspect_ratio_16_10
};

class SKMediaPlayer;
class CCenterMenu : public QMenu
{
	Q_OBJECT

public:
	CCenterMenu(QWidget *parent);
	~CCenterMenu();

	void CreateMenuItem();
	void SetEnumAspectRatio(eAspectRatio e) { m_eAspectRatio = e; }

private:
	QAction *act_openFile;
	QAction *act_close;
	QAction *act_sysTime;
	QAction *act_params;
	QAction *act_about;

	QMenu *menu_aspect_ratio;
	QAction *act_aspect_ratio_original;
	QAction *act_aspect_ratio_4_3;
	QAction *act_aspect_ratio_5_4;
	QAction *act_aspect_ratio_16_9;
	QAction *act_aspect_ratio_16_10;
	QAction *act_scale_normal;
	QAction *act_scale_zoom_in;
	QAction *act_scale_zoom_out;
	QAction *act_snapshot;
	QAction *act_fileLink;

	QMenu *menu_track;

private:
	void Init();
	void InitUi();
	void InitSlot();
	QString _FileTypeAssociated(QString type);

private:
	SKMediaPlayer *m_app;
	eAspectRatio m_eAspectRatio;

signals:
	void sigOpenFile();
	void sigClose();
	void sigAbout();

public slots:
	void SlotOpenFile();
	void SlotClose();
	void SlotSystemTime();
	void SlotProgressVolume();
	void SlotAbout();
	void SlotAspectRatioOriginal();
	void SlotAspectRatio43();
	void SlotAspectRatio54();
	void SlotAspectRatio1609();
	void SlotAspectRatio1610();
	void SlotScaleNormal();
	void SlotScaleZoomIn();
	void SlotScaleZoomOut();
	void SlotTrack();
	void SlotSnapshot();
	void SlotAssociatedVideoFile();
	
};

#endif // CCENTERMENU_H
