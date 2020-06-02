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
}


Flighting_ball::~Flighting_ball() {}


void Flighting_ball::slotGameTimer()
{
	QList<QGraphicsItem *> foundItems = scene()->items(QPolygonF()
													   <<mapToScene(25, -25)
													   <<mapToScene(-25, -25)
													   <<mapToScene(25, 25)
													   <<mapToScene(-25, 25));

	foreach (QGraphicsItem *item, foundItems) {
		if (item == this)
			continue;
		emit signalCheckItem(item);
	}
}


void Flighting_ball::advance(int phase)
{
	if (phase) {
		std::vector<double> coord = create_ser_without_resistance(V_x, V_y, g, t, x0, y0);
		x1 = coord[0];        //случай без сопротивления воздуха
		y1 = coord[1];
		V_yy = coord[2]; //надо установить, чтобы скорость V_yy была в момент удара об объект!!!!!!

		victim = new Victim(i);

		if (yspread + y1 > victim->get_position_on_y()) {
			V_y = - V_yy;
			y1 = - y1;
			x0 = x1;
			y0 = yspread - victim->get_position_on_y();
			t = 0;
		}
//		if (y1 > 0) {
//			V_y = - V_yy;
//			y1 = - y1;
//			x0 = x1;
//			y0 = 0;
//			t = 0;
//		}

//		if (x1 > victim->get_position_on_x() && ((yspread + y1) > victim->get_position_on_y())) {
//			V_x = - V_x;
//			x0 = x1;
//			y0 = yspread - victim->get_position_on_y();
//			t = 0;
//		}

		this->setPos(x1, 960 - CIRCLE_SIZE + y1);
		t += 0.1;
	}

}


//void Flighting_ball::advance(int phase)
//{
//	if (phase) {
//		std::vector<double> coord = create_arbitrary_angle (m, k, V_x, V_y, m, g, 0, 0, 0, x0, y0, t);
//		x1 = coord[0];        //с сопротивлением воздуха (точное решение)
//		y1 = coord[1];
//		V_yy = coord[2];

//		victim = new Victim(i);

//		if (yspread + y1 > victim->get_position_on_y()) {
//			V_y = - V_yy;
//			y1 = - y1;
//			x0 = x1;
//			y0 = yspread - victim->get_position_on_y();
//			t = 0;
//		}

////		if (y1 > 0) {
////			V_y = - V_yy;
////			y1 = - y1;
////			x0 = x1;
////			y0 = 0;
////			t = 0;
////		}


//		this->setPos(x1, 960 - CIRCLE_SIZE + y1);
//		t += 0.1;
//	}
//}


//void Flighting_ball::advance(int phase)
//{
//	if (phase) {
//		std::vector<double> coord = create_relativism(V_y, V_x, m, k, g, N, i, x0, y0);
//		x1 = coord[0];
//		y1 = - coord[1];
//		V_yy = coord[2];

//		victim = new Victim(i);

//		if (yspread + y1 > victim->get_position_on_y()) {
//			V_y = - V_yy;
//			y1 = - y1;
//			x0 = x1;
//			y0 = yspread - victim->get_position_on_y();
//			t = 0;
//		}

////		if (y1 > 0) {
////			V_y = - V_yy;
////			y1 = - y1;
////			x0 = x1;
////			y0 = 0;
////			t = 0;
////		}

//		this->setPos(x1, 960 - CIRCLE_SIZE + y1);
//		i ++;
//	}
//}


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
