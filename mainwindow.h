#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QWidget>
#include <QTableView>
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
    QSqlDatabase db;

    QDialog loginPage;
    QWidget tableWidget;
    QLineEdit *loginEdit;
    QLineEdit *passwordEdit;

private:
    Ui::MainWindow *ui;
    bool createConnection();

private slots:

    void cancelButtonClicked();
    void loginButtonClicked();

    void on_patientTable_triggered();
    void on_medicTable_triggered();
    void on_diseaseHistoryTable_triggered();
    void on_OperationTable_triggered();
    void on_diseaseTypeTable_triggered();
    void on_medicProfessionTable_triggered();
    void on_operationTypeTable_triggered();
};

#endif // MAINWINDOW_H
