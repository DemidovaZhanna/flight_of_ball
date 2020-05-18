#include "Square.h"
#include "ui_mainwidget.h"

#define CIRCLE_SIZE 50

Flighting_ball::Flighting_ball(int yspread)
{
	x0 = 50;
	y0 = 100;
	QColor color = QColor(rand()%255, rand()%255, rand()%255);
	setBrush(color);
	setRect(0, 0, CIRCLE_SIZE, CIRCLE_SIZE);
	setPos(x0, yspread - y0);
	t = 0;
	i = 1;

	//	QGraphicsRectItem rect;
	//	x0 = 50;
	//	y0 = 100;
	//	rect.setRect(0, 0, CIRCLE_SIZE, CIRCLE_SIZE);
	//	setPos(x0, yspread - y0);
	//	t = 0;
	//	i = 1;
}


Flighting_ball::~Flighting_ball() {}

//void Flighting_ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
//{
//	QColor color = QColor(rand()%255, rand()%255, rand()%255);
//	painter->setBrush(color);

////	Q_UNUSED(option)
////	Q_UNUSED(widget)
//}


//void Flighting_ball::slotGameTimer()
//{
//	QList<QGraphicsItem *> foundItems = scene()->items(QPolygonF()
//													   <<mapToScene(25, -25)
//													   <<mapToScene(-25, -25)
//													   <<mapToScene(25, 25)
//													   <<mapToScene(-25, 25));

//	foreach (QGraphicsItem *item, foundItems) {
//		if (item == this)
//			continue;
//		emit signalCheckItem(item);
//	}
//}

//QRectF Flighting_ball::boundingRect() const
//{
//	return QPolygonF::boundingRect();
//}


void Flighting_ball::advance(int phase)
{
	if (phase) {
		std::pair<double, double> coord = create_ser_without_resistance(V_x, V_y, g, t, x0, y0);
		x1 = coord.first;        //случай без сопротивления воздуха
		y1 = coord.second;

		if (y1 > 0) {
			V_y = - V_y;
			y1 = - y1;
			x0 = x1;
			y0 = 0;
			t = 0;
		}

		this->setPos(x1, 960 - CIRCLE_SIZE + y1);
		t += 0.1;
	}
}


////void Flighting_ball::advance(int phase)
////{
////	if (phase) {
////		std::pair<double, double> coord = create_arbitrary_angle (m, k, V_x, V_y, m, g, 0, 0, 0, x0, y0, t);
////		x1 = coord.first;        //с сопротивлением воздуха (точное решение)
////		y1 = coord.second;
////		this->setPos(x1, 960 - CIRCLE_SIZE + y1);
////		t += 0.1;
////	}
////}


////void Flighting_ball::advance(int phase)
////{
////	if (phase) {
////		std::pair<double, double> coord = create_numer_approx (N, k, m, g, V_x, V_y, i);
////		x1 = coord.first;        //с учетом сопротивления(численное приближение)
////		y1 = - coord.second;
////		this->setPos(x1, 960 - CIRCLE_SIZE + y1);
////		i ++;
////	}
////}


////void Flighting_ball::advance(int phase)
////{
////	if (phase) {
////		std::pair<double, double> coord = create_relativism(V_y1, V_x1, m, k, g, N, i);
////		x1 = coord.first;
////		y1 = - coord.second;
////		this->setPos(x1, 960 - CIRCLE_SIZE + y1);
////		i ++;
////	}
////}


////void Flighting_ball::advance(int phase)
////{
////	if (phase) {
////		std::pair<double, double> coord = create_arbitrary_angle (m, k, V_x, V_y, m_p2, g, V_xt, V_yt, t_detach, x0, y0, t);
////		x1 = coord.first;        //случай резкого изменения массы под произвольным углом
////		y1 = coord.second;
////		this->setPos(x1, 960 - CIRCLE_SIZE + y1);
////		t += 0.01;
////	}
////}
