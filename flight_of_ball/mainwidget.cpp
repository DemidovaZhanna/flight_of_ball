#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "settlement.h"

#define CIRCLE_SIZE 50 //как сделать радиус 0.1 м????

mainwidget::mainwidget(QWidget *parent):
	QWidget(parent),
	ui(new Ui::mainwidget)
{
	ui->setupUi(this);

	scene = new QGraphicsScene (0, 0, 1920, 960, this);
	ui->graphicsView->setScene(scene);
	scene->addRect(scene->sceneRect());

	ball = new Flighting_ball (scene->sceneRect().height());
	scene->addItem(ball);

	timer = new QTimer();
	connect(timer, &QTimer::timeout, ball, &Flighting_ball::slotGameTimer);
	timer->start(1000 / 100);

	connect(ball, &Flighting_ball::signalCheckItem, this, &mainwidget::slotRebound);

	victim = new Victim (scene->sceneRect().width());
	scene->addItem(victim);

	connect(ball, &Flighting_ball::signalCheckItem, this, &mainwidget::slotDeleteVictim);

	animationTimer = new QTimer(this);
	connect(animationTimer, SIGNAL(timeout()), scene, SLOT(advance()));
	animationTimer->start(1000/50);

//	generanorTimer = new QTimer(this);
//	connect(generanorTimer, SIGNAL(timeout()), this, SLOT(onGenerate()));
//	generanorTimer->start(1000);
}


mainwidget::~mainwidget()
{
	delete ui;
}


void mainwidget::slotRebound(QGraphicsItem *item)
{
//	if (victim == item) {
//		double x1 = ball->get_x();
//		double y1 = - ball->get_y();
//		double V_x = ball->get_V_x();
//		double V_y = - ball->get_V_yy();
//		double x0 = x1;
//		double y0 = ball->get_yspread() - victim->get_position_on_y();
//		double g = 9.81;
//		double t = 0;

//		create_ser_without_resistance(V_x, V_y, g, t, x0, y0);
//		ball->setPos(x1, 960 - CIRCLE_SIZE + y1);

//	}

//	if (y1 > victim->position_on_y || x1 > victim->position_on_x) {
//		V_y = - V_y;
//		y1 = - y1;
//		double x0 = x1;
//		double y0 = 0;

//		//ball->advance(1);
//		double g = 9.81;

//		for (double t = 0; t < 2000; t += 0.1) {
//			create_ser_without_resistance(V_x, V_y, g, t, x0, y0);
//			ball->setPos(x1, 960 - CIRCLE_SIZE + y1);
//		}
//	}
//	double V_x = ball->get_V_x();
//	double t = 0;


//	std::vector<double> coord = create_ser_without_resistance(V_x, V_y, g, t, x0, y0);
//	double x1 = coord[0];        //случай без сопротивления воздуха
//	double y1 = coord[1];
//	double V_yy = coord[2]; //надо установить, чтобы скорость V_yy была в момент удара об объект!!!!!!




}


void mainwidget::onGenerate()
{
	scene->addItem(new Flighting_ball(scene->sceneRect().height()));
}


void mainwidget::slotDeleteVictim(QGraphicsItem *item)
{
//получив сигнал от шарика, удаляем найденный статический объект
//позднее можно создать список статический объектов, и удалять, исключая объект из списка
	if (victim == item) {
//		scene->removeItem(victim); //пока что объект удаляется со сцены, впоследствии сделать так, чтобы ломался пополам
//		delete (victim);
		victim->setBrush(QColor(rand() % 255));
	}
}


Victim::Victim(int pos): QGraphicsRectItem()
{
	QColor color = QColor(qrand());
	setBrush(color);

	width_of_victim = 100;
	height_of_victim = 50;
	position_on_x = 1060;
	//position_on_x = 550;
	position_on_y = 960 - height_of_victim;

	setRect(0, 0, width_of_victim, height_of_victim);
	setPos(position_on_x, position_on_y);
}


