#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDriver>
#include <QSettings>
#include <QSize>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QDateTime dateTime;

private:
    Ui::MainWindow *ui;
    //bool createConnection();

private slots:

    //void readData();
    //void sendQuery();

};

#endif // MAINWINDOW_H
