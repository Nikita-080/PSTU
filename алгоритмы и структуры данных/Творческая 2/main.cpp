#include "mainwindow.h"
#include "top.h"
#include "edge.h"
#include <QApplication>
#include <QLineEdit>
#include <QTableView>
QString status="none";
int mem_x;
int mem_y;
int mem_num;
int len_del1;
int len_del2;
QTableView* display;
QVector <TOP> graph1;
QVector <EDGE> graph2;
QVector <QVector<int>> matrix;
//QVector <int> row_history;
//QVector <int> column_history;
int drawing_index=-1;
QVector <QVector<QVector <int>>> data_history;
QString statusBook[]={"top","edge1.1","edge2.1","move","del","none"};
QString text_for_arrows;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(1700,700);
    w.show();
    return a.exec();
}
