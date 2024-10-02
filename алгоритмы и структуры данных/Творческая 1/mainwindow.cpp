#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMap>
#include <QList>
#include <QMessageBox>
#include <QtGui>
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ввод названий
    team_l[0]=ui->lineEdit_1;  team_r[0]=ui->lineEdit_4;
    team_l[1]=ui->lineEdit_6;  team_r[1]=ui->lineEdit_5;
    team_l[2]=ui->lineEdit_10; team_r[2]=ui->lineEdit_9;
    team_l[3]=ui->lineEdit_15; team_r[3]=ui->lineEdit_21;
    team_l[4]=ui->lineEdit_18; team_r[4]=ui->lineEdit_14;
    team_l[5]=ui->lineEdit_19; team_r[5]=ui->lineEdit_24;
    team_l[6]=ui->lineEdit_27; team_r[6]=ui->lineEdit_25;
    team_l[7]=ui->lineEdit_31; team_r[7]=ui->lineEdit_30;
    //ввод счета
    score_l[0]=ui->lineEdit_2;  score_r[0]=ui->lineEdit_3;
    score_l[1]=ui->lineEdit_8;  score_r[1]=ui->lineEdit_7;
    score_l[2]=ui->lineEdit_12; score_r[2]=ui->lineEdit_11;
    score_l[3]=ui->lineEdit_23; score_r[3]=ui->lineEdit_20;
    score_l[4]=ui->lineEdit_17; score_r[4]=ui->lineEdit_16;
    score_l[5]=ui->lineEdit_13; score_r[5]=ui->lineEdit_22;
    score_l[6]=ui->lineEdit_26; score_r[6]=ui->lineEdit_28;
    score_l[7]=ui->lineEdit_32; score_r[7]=ui->lineEdit_29;
    //кнопки удаления
    btn_del[0]=ui->pushButton_1;
    btn_del[1]=ui->pushButton_2;
    btn_del[2]=ui->pushButton_3;
    btn_del[3]=ui->pushButton_4;
    btn_del[4]=ui->pushButton_5;
    btn_del[5]=ui->pushButton_6;
    btn_del[6]=ui->pushButton_7;
    btn_del[7]=ui->pushButton_8;
    //еще переменные
    NumOfAct=1;
    for (int i=0;i<8;i++)
    {
        Gdel->addButton(btn_del[i],i);
        btn_del[i]->setIcon(QIcon("C:/qtprojects/ArtProject1/icon1.png"));
        btn_del[i]->setStyleSheet("QPushButton { background-color: rgb(244,249,244); }\n");
    }
    for (int i=1;i<8;i++)
    {
        team_l[i]->hide();
        score_l[i]->hide();
        score_r[i]->hide();
        team_r[i]->hide();
        btn_del[i]->hide();
    }
    ui->menu_save->setIcon(QIcon("C:/qtprojects/ArtProject1/icon2.png"));
    ui->menu_load->setIcon(QIcon("C:/qtprojects/ArtProject1/icon3.png"));
    ui->result1->setStyleSheet("QPushButton { background-color: rgb(244,249,244); }\n");
    ui->btn1->setStyleSheet("QPushButton { background-color: rgb(244,249,244); }\n");
    ui->BtnPlus->setStyleSheet("QPushButton { background-color: rgb(244,249,244); }\n");
    //connection
    connect(ui->menu_save,&QAction::triggered,
            this,&MainWindow::MSave);
    connect(ui->menu_load,&QAction::triggered,
            this,&MainWindow::MLoad);
    for (int i=0;i<8;i++)
    {
        connect(btn_del[i],&QPushButton::clicked,
                this,&MainWindow::Idel);
    }
    connect(ui->BtnPlus,&QPushButton::clicked,
        this,&MainWindow::Iplus);
    connect(ui->btn1,&QPushButton::clicked,
        this,&MainWindow::Oanalis);
    connect(ui->result1,&QPushButton::clicked,
        this,&MainWindow::Orating);
}
void MainWindow::Iplus()
{
    if (NumOfAct<8)
    {
        team_l[NumOfAct]->show();
        score_l[NumOfAct]->show();
        score_r[NumOfAct]->show();
        team_r[NumOfAct]->show();
        btn_del[NumOfAct]->show();
        NumOfAct++;
    }
}
void MainWindow::Idel()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    int buttonID = Gdel->id(button);
    if (NumOfAct!=1)
    {
        for (int i=buttonID;i<7;i++)
        {
            team_l[i]->setText(team_l[i+1]->text());
            score_l[i]->setText(score_l[i+1]->text());
            score_r[i]->setText(score_r[i+1]->text());
            team_r[i]->setText(team_r[i+1]->text());
        }
        NumOfAct--;
        team_l[NumOfAct]->setText("");
        score_l[NumOfAct]->setText("");
        score_r[NumOfAct]->setText("");
        team_r[NumOfAct]->setText("");
        team_l[NumOfAct]->hide();
        score_l[NumOfAct]->hide();
        score_r[NumOfAct]->hide();
        team_r[NumOfAct]->hide();
        btn_del[NumOfAct]->hide();
    }
    else
    {
        team_l[0]->setText("");
        score_l[0]->setText("");
        score_r[0]->setText("");
        team_r[0]->setText("");
    }
}
bool comp(std::tuple<QString,int> a,std::tuple<QString,int> b)
{
    return std::get<1>(a)>std::get<1>(b);
}
void MainWindow::Orating()
{
    QMap <QString,int> MAP;
    QList <std::tuple<QString,int>> LIST;
    for (int i=0;i<8;i++)
    {
        QString a=team_l[i]->text();
        QString d=team_r[i]->text();
        int b;
        int c;
        if (a==d && a!="")
        {
            QMessageBox::critical(this, "Ошибка","Код ошибки: E007\n матч между одинаковыми командами");
            return;
        }
        try
        {
            b=score_l[i]->text().toInt();
            c=score_r[i]->text().toInt();
        }
        catch (...)
        {
            QMessageBox::critical(this, "Ошибка","Код ошибки: E001\n нецелочисленный счет");
            return;
        }
        if (a.isEmpty() && d.isEmpty()) continue;
        else if (!a.isEmpty() && !d.isEmpty())
        {

            if (MAP.find(a)==MAP.end()) MAP.insert(a,b);
            else MAP.insert(a,MAP[a]+b);
            if (MAP.find(d)==MAP.end()) MAP.insert(d,c);
            else MAP.insert(d,MAP[d]+c);
        }
        else
        {
            QMessageBox::critical(this, "Ошибка","Код ошибки: E002\n пустое имя команды");
            return;
        }
    }
    if (MAP.isEmpty())
    {
        QMessageBox::critical(this, "Ошибка","Код ошибки: E003\n пустая таблица");
        return;
    }
    for (auto it=MAP.begin();it!=MAP.end();it++)
    {
        std::tuple<QString,int> TUPLE(it.key(),it.value());
        LIST.push_back(TUPLE);
    }
    std::sort(LIST.begin(),LIST.end(),comp);
    QString text1="Рейтинг\n";
    QString text2="🏆\n";
    QString text3="⚽\n";
    int count=1;
    for (auto it=LIST.begin();it!=LIST.end();it++)
    {
        text1+=std::get<0>(*it)+"\n";
        text2+=QString::number(count)+"\n";
        text3+=QString::number(std::get<1>(*it))+"\n";
        count++;
    }
    ui->textBrowser_1->setText(text1);
    ui->textBrowser_2->setText(text2);
    ui->textBrowser_3->setText(text3);
}
void MainWindow::Oanalis()
{
    int count_win1=0;
    int count_win2=0;
    int count_win3=0;
    int count_iball=0;
    int count_oball=0;
    int count_games=0;
    QString name=ui->ent1->text();
    for (int i=0;i<8;i++)
    {
        QString a=team_l[i]->text();
        QString d=team_r[i]->text();
        int b;
        int c;
        if (a==d && a!="")
        {
            QMessageBox::critical(this, "Ошибка","Код ошибки: E007\n матч между одинаковыми командами");
            return;
        }
        try
        {
            b=score_l[i]->text().toInt();
            c=score_r[i]->text().toInt();
        }
        catch (...)
        {
            QMessageBox::critical(this, "Ошибка","Код ошибки: E001\n нецелочисленный счет");
            return;
        }
        if (a.isEmpty() && d.isEmpty()) continue;
        else if (!a.isEmpty() && !d.isEmpty())
        {
            if (a!=name && d!=name) continue;
            count_games++;
            if (d==name)
            {
                swap(a,d);
                int e=c;
                c=b; b=e;
            }
            if (b==c) count_win3++;
            if (b>c) count_win1++;
            if (b<c) count_win2++;
            count_iball+=c;
            count_oball+=b;
        }
        else
        {
            QMessageBox::critical(this, "Ошибка","Код ошибки: E002\n пустое имя команды");
            return;
        }
    }
    QString text1=name+"\n";
    QString text2="\n";
    QString text3="\n";
    if (count_games==0) text1+="не обнаружено";
    else
    {
        text1=name+"\nматчи\nпобеды\nпоражения\nничьи\nзабитые\nпропущенные";
        text2+=QString::number(count_games)+"\n";
        text2+=QString::number(count_win1)+"\n";
        text2+=QString::number(count_win2)+"\n";
        text2+=QString::number(count_win3)+"\n";
        text2+=QString::number(count_oball)+"\n";
        text2+=QString::number(count_iball)+"\n";
        text3+="--\n";
        text3+=QString::number(qCeil(100.0*count_win1/count_games))+"%\n";
        text3+=QString::number(qCeil(100.0*count_win2/count_games))+"%\n";
        text3+=QString::number(qCeil(100.0*count_win3/count_games))+"%\n";
        text3+="--\n";
        text3+="--\n";
    }
    ui->textBrowser_1->setText(text1);
    ui->textBrowser_2->setText(text2);
    ui->textBrowser_3->setText(text3);
}
void MainWindow::MSave()
{
    QString path = QFileDialog::getSaveFileName(this,
                                QString::fromUtf8("Сохранить файл"),
                                QDir::currentPath(),
                                "Tables (*.csv);;All files (*.*)");
    QFile file(path);
    if ( !file.open(QFile::WriteOnly | QFile::Text) )
    {
        QMessageBox::critical(this, "Ошибка","Код ошибки: E004\n не удалось отрыть файл");
        return;
    }
    else
    {
        QTextStream out(&file);
        for (int i=0;i<8;i++)
        {
            QString a=team_l[i]->text();
            QString b=score_l[i]->text();
            QString c=score_r[i]->text();
            QString d=team_r[i]->text();
            out<<a<<","<<b<<","<<c<<","<<d<<"\n";
        }
        file.close();
    }
    ui->textBrowser_1->setText("сохранено");
}
void MainWindow::MLoad()
{
    QString path = QFileDialog::getOpenFileName(this,
                                QString::fromUtf8("Открыть файл"),
                                QDir::currentPath(),
                                "Tables (*.csv);;All files (*.*)");
    QFile file(path);
    if ( !file.open(QFile::ReadOnly | QFile::Text) )
    {
        QMessageBox::critical(this, "Ошибка","Код ошибки: E004\n не удалось отрыть файл");
        return;
    }
    else
    {
        QTextStream in(&file);
        int count=0;
        while (!in.atEnd())
        {
            QStringList data = in.readLine().split(",");
            if (data.size()!=4)
            {
                QMessageBox::critical(this, "Ошибка","Код ошибки: E005\n некорректный формат данных");
                return;
            }
            team_l[count]->setText(data[0]);
            score_l[count]->setText(data[1]);
            score_r[count]->setText(data[2]);
            team_r[count]->setText(data[3]);
            team_l[count]->show();
            score_l[count]->show();
            score_r[count]->show();
            team_r[count]->show();
            btn_del[count]->show();
            count++;
            if (count>7 && !in.atEnd())
            {
                QMessageBox::critical(this, "Ошибка","Код ошибки: E006\n критический размер файла");
                return;
            }
        }
        file.close();
    }
    NumOfAct=8;
    ui->textBrowser_1->setText("загружено");
}
MainWindow::~MainWindow()
{
    delete ui;
}


