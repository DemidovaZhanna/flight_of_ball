#include "mainwidget.h"
#include "ui_mainwidget.h"

#define CIRCLE_SIZE 50
mainwidget::mainwidget(QWidget *parent):
	QWidget(parent),
	ui(new Ui::mainwidget)
{

	ui->setupUi(this);
	scene = new QGraphicsScene(0, 0, 1920, 960, this);
	ui->graphicsView->setScene(scene);
	scene->addRect(scene->sceneRect());

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


Flighting_ball::Flighting_ball(int yspread): QGraphicsEllipseItem()
{
	QColor color = QColor(rand()%255, rand()%255, rand()%255);
	setBrush(color);
	setRect(0, 0, CIRCLE_SIZE, CIRCLE_SIZE);
	setPos(0, yspread);
}

void Flighting_ball::advance(int phase)
{
	if (phase) {
			moveBy(V_x*t, -(V_y*t-g*t*t/2)); //V_x*t, -(V_y*t-g*t*t/2)
			t += 0.01;
	}
}

void mainwidget::onGenerate()
{
	scene->addItem(new Flighting_ball(scene->sceneRect().height()));
}




