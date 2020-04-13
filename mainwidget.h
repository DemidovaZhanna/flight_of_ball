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

QT_BEGIN_NAMESPACE
namespace Ui {
class mainwidget;
}
QT_END_NAMESPACE

class Flighting_ball : public QGraphicsEllipseItem {
public:
	Flighting_ball(int yspread);

public:
	virtual void advance(int phase);
private:
	double V_x = 4,
		   V_y = 7,
		   g = 9.81;
	double t;
};


class mainwidget : public QWidget
{
	Q_OBJECT

public:
	mainwidget(QWidget *parent = nullptr);
	~mainwidget();
private slots:
	void onGenerate ();

private:
	Ui::mainwidget *ui;
	QGraphicsScene *scene;
	QTimer *animationTimer;
	QTimer *generanorTimer;
};
#endif // MAINWIDGET_H
