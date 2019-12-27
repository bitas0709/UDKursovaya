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
    QApplication::quit(); //но это не работает
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

void MainWindow::on_addDiseaseHistoryForm_triggered()
{
    formWidget = new QWidget();
    QFormLayout form(formWidget);
    diseaseHistoryNum = new QLineEdit(formWidget);
    diseaseNum = new QLineEdit(formWidget);
    patientNum = new QLineEdit(formWidget);
    medicNum = new QLineEdit(formWidget);
    dataOfIllness = new QLineEdit(formWidget);
    dataOfRecovery = new QLineEdit(formWidget);
    QPushButton *confirmButton = new QPushButton(formWidget);
    connect(confirmButton, SIGNAL(clicked()), SLOT(addDiseaseHistoryFormConfirmButtonClicked()));
    QPushButton *cancelButton = new QPushButton(formWidget);
    confirmButton->setText("Добавить");
    cancelButton->setText("Отмена");
    form.addRow(new QLabel("Номер записи:"), diseaseHistoryNum);
    form.addRow(new QLabel("Номер типа болезни"), diseaseNum);
    form.addRow(new QLabel("Номер пациента"), patientNum);
    form.addRow(new QLabel("Номер медика:"), medicNum);
    form.addRow(new QLabel("Дата заболевания"), dataOfIllness);
    form.addRow(new QLabel("Дата выздоровления"), dataOfRecovery);
    form.addRow(confirmButton, cancelButton);
    formWidget->show();
}

void MainWindow::on_writePatientOnOperationForm_triggered()
{
    formWidget = new QWidget();
    QFormLayout form(formWidget);
    operationNum = new QLineEdit(formWidget);
    operationTypeNum = new QLineEdit(formWidget);
    diseaseHistoryNum = new QLineEdit(formWidget);
    operationDate = new QLineEdit(formWidget);
    QPushButton *confirmButton = new QPushButton(formWidget);
    QPushButton *cancelButton = new QPushButton(formWidget);
    confirmButton->setText("Добавить");
    cancelButton->setText("Отмена");
    form.addRow(new QLabel("Номер записи:"), operationNum);
    form.addRow(new QLabel("Номер типа операции:"), operationTypeNum);
    form.addRow(new QLabel("Номер записи в истории болезней:"), diseaseHistoryNum);
    form.addRow(new QLabel("Дата проведения операции:"), operationDate);
    form.addRow(confirmButton, cancelButton);
    formWidget->show();
}

void MainWindow::on_watchPatientDiseaseHistoryForm_triggered()
{
    QDialog *enterPatientNumDialog = new QDialog();
    QFormLayout dialogForm(enterPatientNumDialog);
    QLineEdit *patientNum = new QLineEdit(enterPatientNumDialog);
    QPushButton *confirmButton = new QPushButton(enterPatientNumDialog);
    confirmButton->setText("Подтвердить:");
    dialogForm.addRow(new QLabel("Номер пациента:"), patientNum);
    dialogForm.addRow(confirmButton);
    enterPatientNumDialog->show();
}

void MainWindow::on_addPatientForm_triggered()
{
    formWidget = new QWidget();
    QFormLayout form(formWidget);
    patientNum = new QLineEdit(formWidget);
    lastName = new QLineEdit(formWidget);
    firstName = new QLineEdit(formWidget);
    fatherName = new QLineEdit(formWidget);
    sex = new QLineEdit(formWidget);
    birthDate = new QLineEdit(formWidget);
    address = new QLineEdit(formWidget);
    medPolisNum = new QLineEdit(formWidget);
    passportNum = new QLineEdit(formWidget);
    mobileNum = new QLineEdit(formWidget);
    QPushButton *confirmButton = new QPushButton(formWidget);
    connect(confirmButton, SIGNAL(clicked()), SLOT(addPatientFormConfirmButtonClicked()));
    QPushButton *cancelButton = new QPushButton(formWidget);
    confirmButton->setText("Добавить");
    cancelButton->setText("Отмена");
    form.addRow(new QLabel("Номер пациента:"), patientNum);
    form.addRow(new QLabel("Фамилия:"), lastName);
    form.addRow(new QLabel("Имя:"), firstName);
    form.addRow(new QLabel("Отчество:"), fatherName);
    form.addRow(new QLabel("Пол:"), sex);
    form.addRow(new QLabel("Дата рождения:"), birthDate);
    form.addRow(new QLabel("Адрес:"), address);
    form.addRow(new QLabel("Номер мед. полиса:"), medPolisNum);
    form.addRow(new QLabel("Серия и номер паспорта:"), passportNum);
    form.addRow(new QLabel("Номер телефона:"), mobileNum);
    form.addRow(confirmButton, cancelButton);
    formWidget->show();
}

void MainWindow::addPatientFormConfirmButtonClicked() {
    if (!patientNum->text().isEmpty() &&
            !lastName->text().isEmpty() &&
            !firstName->text().isEmpty() &&
            !fatherName->text().isEmpty() &&
            !sex->text().isEmpty() &&
            !birthDate->text().isEmpty() &&
            !address->text().isEmpty() &&
            !medPolisNum->text().isEmpty() &&
            !passportNum->text().isEmpty()) {
        QSqlQuery query;
        query.prepare("INSERT INTO Patient (PatientNum, LastName, FirstName, FatherName, Sex, BirthDate, Address, MedPolisNum, PassportNum, MobileNum) "
                      "VALUES (:patientNum, :lastName, :firstName, :fatherName, :sex, :birthDate, :address, :medPolisNum, :passportNum, :mobileNum)");
        query.bindValue(":patientNum", patientNum->text().toInt());
        query.bindValue(":lastName", lastName->text());
        query.bindValue(":firstName", firstName->text());
        query.bindValue(":fatherName", fatherName->text());
        query.bindValue(":sex", sex->text());
        query.bindValue(":birthDate", QDate::fromString(birthDate->text(), "dd.MM.yyyy"));
        query.bindValue(":address", address->text());
        query.bindValue(":medPolisNum", medPolisNum->text());
        query.bindValue(":passportNum", passportNum->text());
        query.bindValue(":mobileNum", mobileNum->text());
        if (query.exec()) {
            formWidget->close();
        } else {
            qDebug() << "hmhmhmhmhm" << query.lastError();
        }
    } else {
        qDebug() << "Заполнены не все поля!";
    }
}

void MainWindow::addDiseaseHistoryFormConfirmButtonClicked() {
//    diseaseHistoryNum = new QLineEdit(formWidget);
//    diseaseNum = new QLineEdit(formWidget);
//    patientNum = new QLineEdit(formWidget);
//    medicNum = new QLineEdit(formWidget);
//    dataOfIllness = new QLineEdit(formWidget);
//    dataOfRecovery = new QLineEdit(formWidget);
    if (!diseaseHistoryNum->text().isEmpty() &&
            !diseaseNum->text().isEmpty() &&
            !patientNum->text().isEmpty() &&
            !medicNum->text().isEmpty() &&
            !dataOfIllness->text().isEmpty() &&
            !dataOfRecovery->text().isEmpty()) {
        QSqlQuery query;
        query.prepare("INSERT INTO DiseaseHistory (DiseaseHistoryNum, DiseaseNum, PatientNum, MedicNum, DateOfIllness, DateOfRecovery) "
                      "VALUES ( :diseaseHistoryNum, :diseaseNum, :patientNum, :medicNum, :dataOfIllness, :dataOfRecovery )");
        query.bindValue(":diseaseHistoryNum", diseaseHistoryNum->text().toInt());
        query.bindValue(":diseaseNum", diseaseNum->text().toInt());
        query.bindValue(":patientNum", patientNum->text().toInt());
        query.bindValue(":medicNum", medicNum->text().toInt());
        query.bindValue(":dataOfIllness", QDate::fromString(dataOfIllness->text(), "dd.MM.yyyy"));
        query.bindValue(":dataOfRecovery", QDate::fromString(dataOfRecovery->text(), "dd.MM.yyyy"));
        if (query.exec()) {
            formWidget->close();
        } else {
            qDebug() << "Insert error" << query.lastError();
        }
    } else {
        qDebug() << "Заполнены не все поля!";
    }
}

void MainWindow::writePatientOnOperationFormConfirmButtonClicked() {

}

void MainWindow::watchPatientDiseaseHistoryFormConfirmButtonClicked() {

}
