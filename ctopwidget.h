#ifndef CTOPWIDGET_H
#define CTOPWIDGET_H

#include <QWidget>
#include "common.h"
#include "PushButton.h"

class CTopWidget : public QWidget
{
	Q_OBJECT

public:
	CTopWidget(QWidget *parent = 0);
	~CTopWidget();

	QLabel *GetLabelTitle() { return m_labelTitle; }
	QPushButton *GetBtnMaximize() { return m_btnMaximize; }

protected:
	bool eventFilter(QObject *, QEvent *);
	virtual void mousePressEvent(QMouseEvent *);
	virtual void mouseReleaseEvent(QMouseEvent *);
	virtual void mouseMoveEvent(QMouseEvent *);
	virtual void mouseDoubleClickEvent(QMouseEvent *);
	virtual void paintEvent(QPaintEvent *);

private:
	QLabel *m_labelLogo;		//标识
	QLabel *m_labelTitle;		//标题
	PushButton *m_btnSkin;		//换肤
	QPushButton *m_btnMainMenu;	//主菜单
	QPushButton *m_btnMinimize;	//最小化
	QPushButton *m_btnMaximize;	//最大化
	QPushButton *m_btnClose;	//关闭
	QPushButton *m_btnSplit;	//分隔符

private:
	void Init();
	void InitUi();

signals:
	void sigSkin();
	void sigMainMenu();
	void sigMin();
	void sigMax();
	void sigClose();

};

#endif // CTOPWIDGET_H
