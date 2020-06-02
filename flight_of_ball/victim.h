#ifndef VICTIM_H
#define VICTIM_H

#include <QWidget>
#include <QGraphicsItem>


class Victim: public QGraphicsRectItem {
public:
	Victim(int pos);

	double get_position_on_y() {return position_on_y;}
	double get_position_on_x() {return position_on_x;}
	double get_width_of_victim() {return width_of_victim;}
private:
	double width_of_victim;
	double height_of_victim;
	double position_on_x;
	double position_on_y;
};

#endif // VICTIM_H
