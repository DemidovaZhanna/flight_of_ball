#ifndef SQUARE_H
#define SQUARE_H

#include <QWidget>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPolygonF>
#include <QGraphicsRectItem>
#include <QPainter>
#include <QGraphicsEllipseItem>

#include "settlement.h"
#include "victim.h"


class Flighting_ball : public QObject, public QGraphicsEllipseItem
{
	Q_OBJECT
public:
	Flighting_ball(int yspread);
	~Flighting_ball();

	double get_x() {return x1;}
	double get_y() {return y1;}
	double get_V_x () {return V_x;}
	double get_V_y () {return V_y;}
	double get_yspread() {return yspread;}
	double get_V_yy() {return V_yy;}

public:
	virtual void advance(int phase);

private:
	double V_yy;
	double yspread = 960;
	double V_x = 70,
		   V_y = 70,
		   g = 9.81;
	double t,
		   x1, y1,
		   x0, y0,

		   P = 1.29,    // (кг/м^3)
		   S = 0.0314,  // S = M_PI*r^2
		   C = 0.47,    // безразмерный коэффициент сопротивления формы
		   k = C*S*P/2,
		   m = 1;       // (кг)
	const int N = 20000;
	double dt = 0.1;
	int i;
	double V_x1 = 2000,
		   V_y1 = 2000,
		   m_p2 = 0.6,
		   V_xt = 40,
		   V_yt = 40,
		   t_detach = 5;
	Victim *victim;

signals:
	void signalCheckItem (QGraphicsItem *item); //сигнал передается в ядро игры и требуется принять решение о том, что делать с объектом

public slots:
	void slotGameTimer (); //отвечает за обработку перемещения треугольника
	//void slotRebound(QGraphicsItem *item);
//protected:
//	QRectF boundingRect() const;
//	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // SQUARE_H

