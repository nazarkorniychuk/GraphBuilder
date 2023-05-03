#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPointF>
#include <QList>
#include <QVector2D>

class GraphicsScene;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QPoint* Graph[50][50]{};
    int NumberOfDots = 0;
    QPoint* parse(int i, QString* str);
    GraphicsScene* scene;
public slots:
    void open();
    void save();
    void exit();
    void BFS();
    void DFS();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
