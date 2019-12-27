#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QWidget>
#include <QDate>
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

    QWidget *formWidget;
    QDialog loginPage;
    QLineEdit *loginEdit;
    QLineEdit *passwordEdit;

    QLineEdit *patientNum;
    QLineEdit *lastName;
    QLineEdit *firstName;
    QLineEdit *fatherName;
    QLineEdit *sex;
    QLineEdit *birthDate;
    QLineEdit *address;
    QLineEdit *medPolisNum;
    QLineEdit *passportNum;
    QLineEdit *mobileNum;

    QLineEdit *diseaseHistoryNum;
    QLineEdit *diseaseNum;
    QLineEdit *medicNum;
    QLineEdit *dataOfIllness;
    QLineEdit *dataOfRecovery;

    QLineEdit *operationNum;
    QLineEdit *operationTypeNum;
    QLineEdit *operationDate;

private:
    Ui::MainWindow *ui;
    bool createConnection();

private slots:

    void cancelButtonClicked();
    void loginButtonClicked();

    void addDiseaseHistoryFormConfirmButtonClicked();
    void writePatientOnOperationFormConfirmButtonClicked();
    void watchPatientDiseaseHistoryFormConfirmButtonClicked();
    void addPatientFormConfirmButtonClicked();

    void on_patientTable_triggered();
    void on_medicTable_triggered();
    void on_diseaseHistoryTable_triggered();
    void on_OperationTable_triggered();
    void on_diseaseTypeTable_triggered();
    void on_medicProfessionTable_triggered();
    void on_operationTypeTable_triggered();
    void on_addDiseaseHistoryForm_triggered();
    void on_writePatientOnOperationForm_triggered();
    void on_watchPatientDiseaseHistoryForm_triggered();
    void on_addPatientForm_triggered();
};

#endif // MAINWINDOW_H
