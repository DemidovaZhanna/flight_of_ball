#include "my_chart.h"


MyChart::MyChart(int a, int b, int c)
{
	axisX = new QValueAxis;
	axisY = new QValueAxis;

	axisX->setRange(a, b);
	axisY->setRange(a, c);

	axisX->setLabelFormat("%.2f");
	axisY->setLabelFormat("%g");
}

void MyChart::addSeries(QAbstractSeries *a)
{
	this->QChart::addSeries(a);
	setAxisX(axisX, a);
	setAxisY(axisY, a);
}
