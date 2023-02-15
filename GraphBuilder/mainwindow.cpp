#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "graphicsscene.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QGraphicsView* view = new QGraphicsView;

    GraphicsScene* scene = new GraphicsScene();
    scene->parent = this;
    view->setScene(scene);
    view->setSceneRect(-300,-300, 300, 300);


    this->resize(600, 600);
    this->setCentralWidget(view);
}

MainWindow::~MainWindow()
{

}

