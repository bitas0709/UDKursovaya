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
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName("Hospital");
    db.setHostName("192.168.88.110");
    db.setUserName(loginEdit->text());
    db.setPassword(passwordEdit->text());
    //db.setUserName(loginStr);
    //db.setPassword(passwordStr);
    if (!db.open()) {
        qDebug() << "Cannot open database:" << db.lastError();
        return false;
    } else {
        qDebug() << "Oooh yeeah";
    }
    return true;
}

void MainWindow::readData() {

}

void MainWindow::sendQuery() {

}
