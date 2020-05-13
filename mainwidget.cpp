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

//	ball = new Flighting_ball (scene->sceneRect().height());
//	scene->addItem(ball);

//	connect(ball, &Flighting_ball::signalCheckItem, this, &mainwidget::slotRebound);

	victim = new Victim (scene->sceneRect().width());
	scene->addItem(victim);

//	connect(ball, &Flighting_ball::signalCheckItem, this, &mainwidget::slotDeleteVictim);


	animationTimer = new QTimer(this);
	connect(animationTimer, SIGNAL(timeout()), scene, SLOT(advance()));
	animationTimer->start(1000/50);

	generanorTimer = new QTimer(this);
	connect(generanorTimer, SIGNAL(timeout()), this, SLOT(onGenerate()));
	generanorTimer->start(1000);
}


mainwidget::~mainwidget()
{
	delete ui;
}


void mainwidget::slotRebound(QGraphicsItem *item)
{
	if (victim == item)
		void advance(int phase);
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
		scene->removeItem(victim); //пока что объект удаляется со сцены, впоследствии сделать так, чтобы ломался пополам
		delete (victim);
	}
}


Victim::Victim(int pos): QGraphicsRectItem()
{
	QColor color = QColor(qrand());
	setBrush(color);
	int width_of_victim = 100;
	int height_of_victim = 50;
	setRect(0, 0, width_of_victim, height_of_victim);
	setPos(1075, 960 - height_of_victim);
}
