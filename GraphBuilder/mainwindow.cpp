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
    this->scene = new GraphicsScene();
    this->scene->parent = this;
    view->setScene(this->scene);
    view->setSceneRect(-300,-300, 300, 300);


    this->resize(600, 600);
    this->setCentralWidget(view);
    QMenuBar *menu = new QMenuBar(this);
    QMenu *file = new QMenu("&Files");
    file->addAction("Open", this, SLOT(open()));
    file->addAction("Save", this, SLOT(save()));
    file->addAction("Exіt", this, SLOT(exit()));

    menu->addMenu(file);
}

MainWindow::~MainWindow()
{

}

QPoint* MainWindow::parse(int i, QString *str)
{
    int j = i + 1;
    QString a = "";
    while(((str->at(j) <= '9') && (str->at(j) >= '0')) || (str->at(j) == '-')){

        a = a + str->at(j);
        j++;
    }
    *str = str->replace(i, j-i+1, "");
    int posX, posY;
    posX = a.toInt();
    a = "";
    j = i;
    while(((str->at(j) <= '9') && (str->at(j) >= '0')) || (str->at(j) == '-')){
        a = a + str->at(j);
        j++;
    }
    *str = str->replace(i, j-i+1, "1");
    posY = a.toInt();
    return new QPoint(posX, posY);
}

void MainWindow::open()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open");
    QFile file(filename);
    if(!file.exists()){
        qDebug() << "File <i>cannot</i> be found "<<filename;
    }else{
        qDebug() << filename<<" Opening...";
    }
    QString line = "";
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
            QTextStream stream(&file);
            while (!stream.atEnd()){
                line = line + stream.readLine();
            }
        }
    file.close();


    int a=0;
    int b=0;

    while(a < line.length()){
        if(line[a] == '('){
            this->Graph[b][b] = parse(a, &line);
            ++b;
        }
        a++;
    }
    this->NumberOfDots = b;
    a = 0;
    b = 0;
    int c = 0;
    while(a < line.length()){
        if(line[a] == '1'){
            this->Graph[b][c] = this->Graph[c][c];
            if(c == 49){
                c = 0;
                b++;
            }else if(b!=49){
                c++;
            }
        }else if(line[a] == '0'){
            this->Graph[b][c] = nullptr;
            if(c == 49){
                c = 0;
                b++;
            }else if(b!=49){
                c++;
            }
        }
        a++;
    }
    this->scene->UpdateScene();

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

void MainWindow::exit()
{
    QCoreApplication::exit();
}


