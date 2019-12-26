#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if (sett.value("/Settings/loggedIn", 0).toInt() == 0) {
        QFormLayout form(&loginPage);
        loginEdit = new QLineEdit(&loginPage);
        passwordEdit = new QLineEdit(&loginPage);
        QPushButton *confirmButton = new QPushButton(&loginPage);
        QPushButton *cancelButton = new QPushButton(&loginPage);
        connect(confirmButton, SIGNAL(clicked()), SLOT(loginButtonClicked()));
        connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelButtonClicked()));
        confirmButton->setText("Подключиться");
        cancelButton->setText("Выход");
        passwordEdit->setEchoMode(QLineEdit::Password);

        loginPage.setWindowTitle("LoginPage");
        form.addRow(new QLabel("Login:"), loginEdit);
        form.addRow(new QLabel("Password:"), passwordEdit);
        form.addRow(confirmButton, cancelButton);

        loginPage.exec();
    }
}

void MainWindow::loginButtonClicked() {
    if (createConnection()) {
        loginPage.close();
    }
}

void MainWindow::cancelButtonClicked() {
    QApplication::quit();
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::createConnection() {
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName("Hospital");
    db.setHostName("192.168.88.110");
    db.setUserName(loginEdit->text());
    db.setPassword(passwordEdit->text());
    if (!db.open()) {
        qDebug() << "Cannot open database:" << db.lastError();
        return false;
    } else {
        qDebug() << "Oooh yeeah";
    }
    return true;
}

void MainWindow::on_patientTable_triggered()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM Patient");
    query.exec();
    QSqlTableModel *model = new QSqlTableModel(this, db);
    model->setTable("Patient");
    model->select();
    model->setHeaderData(0, Qt::Horizontal, tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("Фамилия"));
    model->setHeaderData(2, Qt::Horizontal, tr("Имя"));
    model->setHeaderData(3, Qt::Horizontal, tr("Отчество"));
    model->setHeaderData(4, Qt::Horizontal, tr("Пол"));
    model->setHeaderData(5, Qt::Horizontal, tr("Дата рождения"));
    model->setHeaderData(6, Qt::Horizontal, tr("Адрес"));
    model->setHeaderData(7, Qt::Horizontal, tr("Номер мед. полиса"));
    model->setHeaderData(8, Qt::Horizontal, tr("Серия и номер паспорта"));
    model->setHeaderData(9, Qt::Horizontal, tr("Номер телефона"));
    //sendQuery(query, QString("Table"), model);
    QTableView *view = new QTableView;
    view->setModel(model);
    qDebug() << view->size();
    view->show();
}

void MainWindow::on_medicTable_triggered()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM Medic");
    query.exec();
    QSqlTableModel *model = new QSqlTableModel(this, db);
    model->setTable("Medic");
    model->select();
    model->setHeaderData(0, Qt::Horizontal, tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("Фамилия"));
    model->setHeaderData(2, Qt::Horizontal, tr("Имя"));
    model->setHeaderData(3, Qt::Horizontal, tr("Отчество"));
    model->setHeaderData(4, Qt::Horizontal, tr("Дата найма"));
    model->setHeaderData(5, Qt::Horizontal, tr("ID профессии"));
    model->setHeaderData(6, Qt::Horizontal, tr("Номер телефона"));
    //sendQuery(query, QString("Table"), model);
    QTableView *view = new QTableView;
    view->setModel(model);
    qDebug() << view->size();
    view->show();
}

void MainWindow::on_diseaseHistoryTable_triggered()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM DiseaseHistory");
    query.exec();
    QSqlTableModel *model = new QSqlTableModel(this, db);
    model->setTable("DiseaseHistory");
    model->select();
    model->setHeaderData(0, Qt::Horizontal, tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("ID болезни"));
    model->setHeaderData(2, Qt::Horizontal, tr("ID пациента"));
    model->setHeaderData(3, Qt::Horizontal, tr("ID врача"));
    model->setHeaderData(4, Qt::Horizontal, tr("Дата заболевания"));
    model->setHeaderData(5, Qt::Horizontal, tr("Дата выздоровления"));
    //sendQuery(query, QString("Table"), model);
    QTableView *view = new QTableView;
    view->setModel(model);
    qDebug() << view->size();
    view->show();
}

void MainWindow::on_OperationTable_triggered()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM Operation");
    query.exec();
    QSqlTableModel *model = new QSqlTableModel(this, db);
    model->setTable("Operation");
    model->select();
    model->setHeaderData(0, Qt::Horizontal, tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("ID операции"));
    model->setHeaderData(2, Qt::Horizontal, tr("ID номера истории болезни"));
    model->setHeaderData(3, Qt::Horizontal, tr("Дата операции"));
    //sendQuery(query, QString("Table"), model);
    QTableView *view = new QTableView;
    view->setModel(model);
    qDebug() << view->size();
    view->show();
}

void MainWindow::on_diseaseTypeTable_triggered()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM DiseaseType");
    query.exec();
    QSqlTableModel *model = new QSqlTableModel(this, db);
    model->setTable("DiseaseType");
    model->select();
    model->setHeaderData(0, Qt::Horizontal, tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("Название заболевания"));
    //sendQuery(query, QString("Table"), model);
    QTableView *view = new QTableView;
    view->setModel(model);
    qDebug() << view->size();
    view->show();
}

void MainWindow::on_medicProfessionTable_triggered()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM MedicProfession");
    query.exec();
    QSqlTableModel *model = new QSqlTableModel(this, db);
    model->setTable("MedicProfession");
    model->select();
    model->setHeaderData(0, Qt::Horizontal, tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("Название профессии"));
    //sendQuery(query, QString("Table"), model);
    QTableView *view = new QTableView;
    view->setModel(model);
    qDebug() << view->size();
    view->show();
}

void MainWindow::on_operationTypeTable_triggered()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM OperationType");
    query.exec();
    QSqlTableModel *model = new QSqlTableModel(this, db);
    model->setTable("OperationType");
    model->select();
    model->setHeaderData(0, Qt::Horizontal, tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("Название операции"));
    //sendQuery(query, QString("Table"), model);
    QTableView *view = new QTableView;
    view->setModel(model);
    qDebug() << view->size();
    view->show();
}
