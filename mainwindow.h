#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
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

    QSettings sett;
    QDateTime dateTime;

    QDialog loginPage;
    QLineEdit *loginEdit;
    QLineEdit *passwordEdit;

private:
    Ui::MainWindow *ui;
    bool createConnection();

private slots:

    void cancelButtonClicked();
    void loginButtonClicked();
    void readData();
    void sendQuery();

};

#endif // MAINWINDOW_H
