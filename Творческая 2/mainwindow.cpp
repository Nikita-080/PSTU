#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myglwidget.h"
#include <QPainter>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>
#include <top.h>
#include <edge.h>
#include <QTableView>
#include <QKeyEvent>
#include <QFileDialog>
#include <QTextStream>
MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //widgets
    ent1=new QLineEdit;
    ent2=new QLineEdit;
    grid=new QGridLayout();
    openGLW=new myGLWidget(this);
    btn_calc=new QPushButton;
    btn_del=new QPushButton;
    btn_del->setEnabled(false);
    extern QTableView* display;
    display=new QTableView;
    btn_R=new QPushButton;
    btn_L=new QPushButton;
    btn_R->setEnabled(false);
    btn_L->setEnabled(false);
    for (int i=0;i<6;i++)
    {
        QPushButton* btn=new QPushButton;
        btn->setFixedSize(200,50);
        grid->addWidget(btn,i,1,1,2);
        connect(btn,&QPushButton::clicked,this,&MainWindow::Fswitch);
        G->addButton(btn,i);
    }
    //icons
    ui->menu_save->setIcon(QIcon("C:/qtprojects/ArtProject2/icon2.png"));
    ui->menu_load->setIcon(QIcon("C:/qtprojects/ArtProject2/icon3.png"));
    //texts
    G->button(0)->setText("◯");
    G->button(1)->setText("-->");
    G->button(2)->setText("<->");
    G->button(3)->setText("<<◯>>");
    G->button(4)->setText("✖");
    G->button(5)->setText("Отмена");
    btn_calc->setText("Рассчитать");
    btn_del->setText("Удалить");
    btn_R->setText("▶");
    btn_L->setText("◀");
    ent1->setText("1");
    ent2->setText("1");
    //sizes
    openGLW->setFixedSize(700,700);
    display->setFixedSize(700,550);
    G->button(1)->setFixedSize(100,50);
    G->button(2)->setFixedSize(100,50);
    btn_calc->setFixedSize(100,50);
    btn_del->setFixedSize(100,50);
    ent1->setFixedSize(100,50);
    ent2->setFixedSize(100,50);
    btn_R->setFixedSize(50,50);
    btn_L->setFixedSize(50,50);
    //locations
    grid->addWidget(openGLW,0,0,8,1);
    grid->addWidget(ent1,1,1);
    grid->addWidget(ent2,2,1);
    grid->addWidget(G->button(1),1,2);
    grid->addWidget(G->button(2),2,2);
    grid->addWidget(btn_calc,7,1);
    grid->addWidget(btn_del,7,2);
    grid->addWidget(btn_R,7,4,1,1,Qt::AlignLeft);
    grid->addWidget(btn_L,7,3,1,1,Qt::AlignRight);
    grid->addWidget(display,0,3,8,2,Qt::AlignTop);
    connect(btn_calc,&QPushButton::clicked,this,&MainWindow::F);
    connect(btn_del,&QPushButton::clicked,this,&MainWindow::Fdel);
    connect(btn_R,&QPushButton::clicked,this,&MainWindow::FR);
    connect(btn_L,&QPushButton::clicked,this,&MainWindow::FL);
    connect(ui->menu_save,&QAction::triggered,this,&MainWindow::MSave);
    connect(ui->menu_load,&QAction::triggered,this,&MainWindow::MLoad);
    ui->centralwidget->setLayout(grid);
}
void MainWindow::MSave()
{
    extern QVector<TOP> graph1;
    extern QVector<EDGE> graph2;
    extern QVector <QVector<int>> matrix;
    QString path = QFileDialog::getSaveFileName(this,
                                QString::fromUtf8("Сохранить файл"),
                                QDir::currentPath(),
                                "Tables (*.csv);;All files (*.*)");
    QFile file(path);
    if ( !file.open(QFile::WriteOnly | QFile::Text) )
    {
        QMessageBox::critical(this, "Ошибка","не удалось отрыть файл");
        return;
    }
    else
    {
        QTextStream out(&file);
        for (int i=0;i<graph1.size();i++)
        {
            out<<1<<","<<graph1[i].x<<","<<graph1[i].y<<"\n";
        }
        for (int i=0;i<graph2.size();i++)
        {
            out<<2<<","<<graph2[i].x1<<","<<graph2[i].x2<<","<<graph2[i].y1<<","
            <<graph2[i].y2<<","<<graph2[i].ind_in<<","<<graph2[i].ind_out<<","
            <<graph2[i].mass<<","<<graph2[i].type<<"\n";
        }
        for (int i=0;i<matrix.size();i++)
        {
            out<<3;
            for (int j=0;j<matrix.size();j++) out<<","<<matrix[i][j];
            out<<"\n";
        }
        file.close();
    }
}
void MainWindow::MLoad()
{
    extern QVector<TOP> graph1;
    extern QVector<EDGE> graph2;
    extern QVector <QVector<int>> matrix;
    graph1.clear();
    graph2.clear();
    matrix.clear();
    QString path = QFileDialog::getOpenFileName(this,
                                QString::fromUtf8("Открыть файл"),
                                QDir::currentPath(),
                                "Tables (*.csv);;All files (*.*)");
    QFile file(path);
    if ( !file.open(QFile::ReadOnly | QFile::Text) )
    {
        QMessageBox::critical(this, "Ошибка","не удалось отрыть файл");
        return;
    }
    else
    {
        QTextStream in(&file);
        while (!in.atEnd())
        {
            QStringList data = in.readLine().split(",");
            if (data[0]=="1")
            {
                TOP a;
                a.x=data[1].toInt();
                a.y=data[2].toInt();
                graph1.push_back(a);
            }
            if (data[0]=="2")
            {
                EDGE a;
                a.x1=data[1].toInt();
                a.x2=data[2].toInt();
                a.y1=data[3].toInt();
                a.y2=data[4].toInt();
                a.ind_in=data[5].toInt();
                a.ind_out=data[6].toInt();
                a.mass=data[7].toInt();
                a.type=data[8].toInt();
                graph2.push_back(a);
            }
            if (data[0]=="3")
            {
                QVector <int> matrix_line;
                for (int i=1;i<data.size();i++) matrix_line.push_back(data[i].toInt());
                matrix.push_back(matrix_line);
            }
        }
        file.close();
    }
}
void MainWindow::FR()
{
    extern QVector <QVector<QVector <int>>> data_history;
    extern int drawing_index;
    if (drawing_index!=data_history.size()-1) drawing_index++;
    openGLW->repaint();
}
void MainWindow::FL()
{
    extern QVector <QVector<QVector <int>>> data_history;
    extern int drawing_index;
    if (drawing_index!=0) drawing_index--;
    openGLW->repaint();
}
void MainWindow::Fdel()
{
    //cleaning
    extern QVector <QVector<QVector<int>>> data_history;
    extern int drawing_index;
    extern QVector<TOP> graph1;
    extern QVector<EDGE> graph2;
    extern int len_del1;
    extern int len_del2;
    graph1.erase(graph1.end()-len_del1,graph1.end());
    graph2.erase(graph2.end()-len_del2,graph2.end());
    data_history.clear();
    drawing_index=-1;
    //enabled
    btn_calc->setEnabled(true);
    btn_del->setEnabled(false);
    for (int i=0;i<6;i++) G->button(i)->setEnabled(true);
    ent1->setEnabled(true);
    ent2->setEnabled(true);
    btn_R->setEnabled(false);
    btn_L->setEnabled(false);
    ui->menu_save->setEnabled(true);
    ui->menu_load->setEnabled(true);
    openGLW->repaint();
    update();
}
void MainWindow::Fswitch()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    int buttonID = G->id(button);
    for (int i=0;i<6;i++)
    {
        G->button(i)->setStyleSheet("QPushButton { background-color: rgb(240,240,240); }\n");
    }
    if (buttonID!=5) G->button(buttonID)->setStyleSheet("QPushButton { background-color: rgb(200,200,200); }\n");
    extern QString status;
    extern QString text_for_arrows;
    extern QString statusBook[7];
    if (buttonID==1) text_for_arrows=ent1->text();
    if (buttonID==2) text_for_arrows=ent2->text();
    status=statusBook[buttonID];
}
void MainWindow::F()
{
    //calculation
    extern QVector <QVector<QVector <int>>> data_history;
    extern QVector <QVector<int>> matrix;
    QVector <int> result_arr_1;
    QVector <int> result_arr_2;
    int len=matrix.size();
    int sum=0;
    bool flag=true;
    int M=1000;
    QVector <QVector<int>> data=matrix;
    for (int i=0;i<len;i++) for (int k=0;k<len;k++) if (i==k || data[i][k]==0) data[i][k]=M;
    data_history.push_back(data);
    while (flag)
    {
        QVector <int> row(len);
        row.fill(M);
        QVector <int> column(len);
        column.fill(M);
        for (int i=0;i<len;i++) for (int k=0;k<len;k++) row[i]=qMin(row[i],data[i][k]);
        for (int i=0;i<len;i++) for (int k=0;k<len;k++) if (row[i]!=M && data[i][k]!=M) data[i][k]-=row[i];
        data_history.push_back(data);
        for (int i=0;i<len;i++) for (int k=0;k<len;k++) column[k]=qMin(column[k],data[i][k]);
        for (int i=0;i<len;i++) for (int k=0;k<len;k++) if (column[k]!=M && data[i][k]!=M) data[i][k]-=column[k];
        data_history.push_back(data);
        int max_mark_x;
        int max_mark_y;
        int max_mark=-1;
        for (int i=0;i<len;i++) for (int k=0;k<len;k++) if (data[i][k]==0)
        {
            int min1=M;
            int min2=M;
            for (int j=0;j<len;j++) if (j!=k) min1=qMin(min1,data[i][j]);
            for (int j=0;j<len;j++) if (j!=i) min2=qMin(min2,data[j][k]);
            if (min1+min2>max_mark)
            {
                max_mark=min1+min2;
                max_mark_x=i;
                max_mark_y=k;
            }
        }
        sum+=matrix[max_mark_x][max_mark_y];
        data[max_mark_y][max_mark_x]=M;
        for (int i=0;i<len;i++)
        {
            data[max_mark_x][i]=M;
            data[i][max_mark_y]=M;
        }
        data_history.push_back(data);
        result_arr_1.push_back(max_mark_x);
        result_arr_2.push_back(max_mark_y);
        flag=false;
        for (int i=0;i<len;i++) for (int k=0;k<len;k++) if (data[i][k]!=M) flag=true;
    }
    QVector <int> result;
    result.push_back(result_arr_1[0]);
    result.push_back(result_arr_2[0]);
    int x=result_arr_2[0];
    result_arr_1.erase(result_arr_1.begin());
    result_arr_2.erase(result_arr_2.begin());
    while (result_arr_1.size()!=0)
    {
        for (int i=0;i<result_arr_1.size();i++) if (result_arr_1[i]==x)
        {
            result.push_back(result_arr_2[i]);
            x=result_arr_2[i];
            result_arr_1.erase(result_arr_1.begin()+i);
            result_arr_2.erase(result_arr_2.begin()+i);
            break;
        }
    }
    if (result[0]!=result[result.size()-1])
    {
        QMessageBox::warning(this, "Внимание","невозможно вычислить");
        return;
    }
    //animation
    extern QVector<TOP> graph1;
    extern QVector<EDGE> graph2;
    extern int len_del1; //кол-во добавленных узлов
    extern int len_del2; //кол-во добавленных ребер
    len_del1=result.size();
    len_del2=result.size()-1;
    int len_g2=graph2.size(); //кол-во ребер
    for (int i=0;i<result.size();i++)
    {
        TOP a;
        a.x=graph1[result[i]].x;
        a.y=graph1[result[i]].y;
        a.id=result[i];
        a.Vmark=true;
        graph1.push_back(a);
    }
    for (int i=0;i<result.size()-1;i++)
    {
        EDGE a;
        a.ind_in=i;   //другая система индексов
        a.ind_out=i+1;//нежели у основного графа
        a.mass=matrix[result[i]][result[i+1]];
        a.type=(matrix[result[i]][result[i+1]]==matrix[result[i+1]][result[i]])?2:1;
        a.x1=graph1[result[i]].x;
        a.x2=graph1[result[i+1]].x;
        a.y1=graph1[result[i]].y;
        a.y2=graph1[result[i+1]].y;
        graph2.push_back(a);
    }
    for (int i=0;i<100;i++)
    {
        for (int j=len;j<graph1.size();j++)//move tops
        {
            int ind=j-len;
            graph1[j].x+=(60+ind*180-graph1[j].x)/(100-i);
            graph1[j].y+=(60-graph1[j].y)/(100-i);
        }
        for (int j=len_g2;j<graph2.size();j++)//move edges
        {
            int ind1=graph2[j].ind_in;
            int ind2=graph2[j].ind_out;
            graph2[j].x1+=(60+ind1*180-graph2[j].x1)/(100-i);
            graph2[j].y1+=(60-graph2[j].y1)/(100-i);
            graph2[j].x2+=(60+ind2*180-graph2[j].x2)/(100-i);
            graph2[j].y2+=(60-graph2[j].y2)/(100-i);
        }
        Sleep(20);
        openGLW->repaint();
    }
    //settings
    extern int drawing_index;
    drawing_index=0;
    btn_del->setEnabled(true);
    for (int i=0;i<6;i++) G->button(i)->setEnabled(false);
    btn_calc->setEnabled(false);
    ent1->setEnabled(false);
    ent2->setEnabled(false);
    btn_R->setEnabled(true);
    btn_L->setEnabled(true);
    ui->menu_save->setEnabled(false);
    ui->menu_load->setEnabled(false);
    openGLW->repaint();
}
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    extern QVector<TOP> graph1;
    extern QVector<EDGE> graph2;
    int dx=0;
    int dy=0;
    if (event->key()==Qt::Key_A) dx=10;
    else if (event->key()==Qt::Key_D) dx=-10;
    else if (event->key()==Qt::Key_W) dy=10;
    else if (event->key()==Qt::Key_S) dy=-10;
    for (int i=0;i<graph1.size();i++)
    {
        graph1[i].x+=dx;
        graph1[i].y+=dy;
    }
    for (int i=0;i<graph2.size();i++)
    {
        graph2[i].x1+=dx;
        graph2[i].y1+=dy;
        graph2[i].x2+=dx;
        graph2[i].y2+=dy;
    }
    openGLW->repaint();
}
MainWindow::~MainWindow()
{
    delete ui;
}

