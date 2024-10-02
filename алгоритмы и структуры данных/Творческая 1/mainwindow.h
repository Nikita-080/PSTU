#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QButtonGroup>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    int NumOfAct;
    QLineEdit*    team_l[8];
    QLineEdit*    score_l[8];
    QLineEdit*    team_r[8];
    QLineEdit*    score_r[8];
    QPushButton*  btn_del[8];
    QButtonGroup* Gdel =new QButtonGroup;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void Iplus();  //input plus
    void Idel();   //input delete
    void MSave();  //menu save
    void MLoad();  //menu download
    void Orating();//output rating
    void Oanalis();//output team analis
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
