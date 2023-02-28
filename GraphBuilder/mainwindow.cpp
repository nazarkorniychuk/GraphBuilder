#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "graphicsscene.h"
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QString>
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
    /*QMenuBar *menu = new QMenuBar(this);
    QMenu *file = new QMenu("&File");
    file->addAction("Open", this, SLOT(open()));
    file->addAction("Save", this, SLOT(save()));
    menu->addMenu(file);*/
}

MainWindow::~MainWindow()
{

}

void MainWindow::open()
{
    qDebug() << "123";
}

void MainWindow::save()
{
    QString filename= QFileDialog::getSaveFileName(this, "Save");
    if (filename.isEmpty())
            return;

    QFile file(filename);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;

    QTextStream out(&file);

    for(int i = 0; i < 50; ++i){
        for(int j = 0; j < 50; ++j){
            if(this->Graph[i][j] != nullptr){
                if(i == j){
                    out << "(" << QString::number(this->Graph[i][j]->x()) << "," << QString::number(this->Graph[i][j]->y()) << ")" << " ";
                }else{
                    out << "1 ";
                }
            }else{
                out << "0 ";
            }
        }
        out << "\n";
    }

    file.close();
}


