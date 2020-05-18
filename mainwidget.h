#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>

#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsPixmapItem>

#include <QTimer>

#include "Square.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class mainwidget;
}
QT_END_NAMESPACE


class Victim: public QGraphicsRectItem {
public:
	Victim(int pos);
};


class mainwidget : public QWidget
{
	Q_OBJECT
public:
	mainwidget(QWidget *parent = nullptr);
	~mainwidget();

private slots:
	void onGenerate ();
	void slotRebound(QGraphicsItem *item);
//	void slotDeleteVictim (QGraphicsItem *item);

private:
	Ui::mainwidget *ui;
	QGraphicsScene *scene;
	QTimer *animationTimer;
	QTimer *generanorTimer;
	QTimer *timer;
	Victim *victim;
	Flighting_ball *ball;

};
#endif // MAINWIDGET_H
