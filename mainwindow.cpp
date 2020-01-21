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
    query.prepare("SELECT * FROM Пациенты");
    query.exec();
    QSqlTableModel *model = new QSqlTableModel(this, db);
    model->setTable("Пациенты");
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
    QTableView *view = new QTableView;
    view->setModel(model);
    qDebug() << view->size();
    view->show();
}

void MainWindow::on_medicTable_triggered()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM Врачи");
    query.exec();
    QSqlTableModel *model = new QSqlTableModel(this, db);
    model->setTable("Врачи");
    model->select();
    model->setHeaderData(0, Qt::Horizontal, tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("Фамилия"));
    model->setHeaderData(2, Qt::Horizontal, tr("Имя"));
    model->setHeaderData(3, Qt::Horizontal, tr("Отчество"));
    model->setHeaderData(4, Qt::Horizontal, tr("Дата найма"));
    model->setHeaderData(5, Qt::Horizontal, tr("ID профессии"));
    model->setHeaderData(6, Qt::Horizontal, tr("Номер телефона"));
    QTableView *view = new QTableView;
    view->setModel(model);
    qDebug() << view->size();
    view->show();
}

void MainWindow::on_diseaseHistoryTable_triggered()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM ИсторияБолезни");
    query.exec();
    QSqlTableModel *model = new QSqlTableModel(this, db);
    model->setTable("ИсторияБолезни");
    model->select();
    model->setHeaderData(0, Qt::Horizontal, tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("ID посещения"));
    model->setHeaderData(2, Qt::Horizontal, tr("ID заболевания"));
    model->setHeaderData(4, Qt::Horizontal, tr("Дата заболевания"));
    model->setHeaderData(5, Qt::Horizontal, tr("Дата выздоровления"));
    QTableView *view = new QTableView;
    view->setModel(model);
    qDebug() << view->size();
    view->show();
}

void MainWindow::on_OperationTable_triggered()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM Операции");
    query.exec();
    QSqlTableModel *model = new QSqlTableModel(this, db);
    model->setTable("Операции");
    model->select();
    model->setHeaderData(0, Qt::Horizontal, tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("ID операции"));
    model->setHeaderData(2, Qt::Horizontal, tr("ID номера истории болезни"));
    model->setHeaderData(3, Qt::Horizontal, tr("Дата проведения операции"));
    model->setHeaderData(4, Qt::Horizontal, tr("Время начала операции"));
    QTableView *view = new QTableView;
    view->setModel(model);
    qDebug() << view->size();
    view->show();
}

void MainWindow::on_diseaseTypeTable_triggered()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM ТипЗаболевания");
    query.exec();
    QSqlTableModel *model = new QSqlTableModel(this, db);
    model->setTable("ТипЗаболевания");
    model->select();
    model->setHeaderData(0, Qt::Horizontal, tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("Название заболевания"));
    QTableView *view = new QTableView;
    view->setModel(model);
    qDebug() << view->size();
    view->show();
}

void MainWindow::on_medicProfessionTable_triggered()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM ПрофессииВрача");
    query.exec();
    QSqlTableModel *model = new QSqlTableModel(this, db);
    model->setTable("ПрофессииВрача");
    model->select();
    model->setHeaderData(0, Qt::Horizontal, tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("Название профессии"));
    QTableView *view = new QTableView;
    view->setModel(model);
    qDebug() << view->size();
    view->show();
}

void MainWindow::on_operationTypeTable_triggered()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM ТипОперации");
    query.exec();
    QSqlTableModel *model = new QSqlTableModel(this, db);
    model->setTable("ТипОперации");
    model->select();
    model->setHeaderData(0, Qt::Horizontal, tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("Название операции"));
    QTableView *view = new QTableView;
    view->setModel(model);
    qDebug() << view->size();
    view->show();
}

void MainWindow::on_VisitTable_triggered()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM Посещение");
    query.exec();
    QSqlTableModel *model = new QSqlTableModel(this, db);
    model->setTable("Посещение");
    model->select();
    model->setHeaderData(0, Qt::Horizontal, tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("ID Пациента"));
    model->setHeaderData(2, Qt::Horizontal, tr("ID Врача"));
    model->setHeaderData(3, Qt::Horizontal, tr("Дата посещения"));
    model->setHeaderData(4, Qt::Horizontal, tr("Время посещения"));
    model->setHeaderData(5, Qt::Horizontal, tr("Жалоба"));
    model->setHeaderData(6, Qt::Horizontal, tr("Результат обследования"));
    model->setHeaderData(7, Qt::Horizontal, tr("Цена"));
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
    visitNum = new QLineEdit(formWidget);
    diseaseNum = new QLineEdit(formWidget);
    dataOfIllness = new QLineEdit(formWidget);
    dataOfRecovery = new QLineEdit(formWidget);
    int maxNum = 1;
    QSqlQuery query;
    query.prepare("SELECT MAX(НомерЗаписи) FROM ИсторияБолезни");
    query.exec();
    while(query.next()) {
        maxNum = query.value(0).toInt();
        maxNum += 1;
    }
    diseaseHistoryNum->setText(QString::number(maxNum));
    QPushButton *confirmButton = new QPushButton(formWidget);
    connect(confirmButton, SIGNAL(clicked()), SLOT(addDiseaseHistoryFormConfirmButtonClicked()));
    QPushButton *cancelButton = new QPushButton(formWidget);
    confirmButton->setText("Добавить");
    cancelButton->setText("Отмена");
    form.addRow(new QLabel("Номер записи:"), diseaseHistoryNum);
    form.addRow(new QLabel("Номер посещения:"), visitNum);
    form.addRow(new QLabel("Номер типа болезни:"), diseaseNum);
    form.addRow(new QLabel("Дата заболевания:"), dataOfIllness);
    form.addRow(new QLabel("Дата выздоровления:"), dataOfRecovery);
    form.addRow(confirmButton, cancelButton);
    formWidget->show();
}

void MainWindow::addDiseaseHistoryFormConfirmButtonClicked() {
    if (!diseaseHistoryNum->text().isEmpty() &&
            !visitNum->text().isEmpty() &&
            !diseaseNum->text().isEmpty() &&
            !dataOfIllness->text().isEmpty() &&
            !dataOfRecovery->text().isEmpty()) {
        QSqlQuery query;
        query.prepare("INSERT INTO ИсторияБолезни (НомерЗаписи, НомерПосещения, НомерЗаболевания, ДатаЗаболевания, ДатаВыздоровления) "
                      "VALUES ( :diseaseHistoryNum, :visitNum, :diseaseNum, :dataOfIllness, :dataOfRecovery )");
        query.bindValue(":diseaseHistoryNum", diseaseHistoryNum->text().toInt());
        query.bindValue(":visitNum", visitNum->text().toInt());
        query.bindValue(":diseaseNum", diseaseNum->text().toInt());
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

void MainWindow::on_writePatientOnOperationForm_triggered()
{
    formWidget = new QWidget();
    QFormLayout form(formWidget);
    operationNum = new QLineEdit(formWidget);
    operationTypeNum = new QLineEdit(formWidget);
    diseaseHistoryNum = new QLineEdit(formWidget);
    operationDate = new QLineEdit(formWidget);
    operationStartTime = new QLineEdit(formWidget);
    int maxNum = 1;
    QSqlQuery query;
    query.prepare("SELECT MAX(НомерОперации) FROM Операции");
    query.exec();
    while(query.next()) {
        maxNum = query.value(0).toInt();
        maxNum += 1;
    }
    operationNum->setText(QString::number(maxNum));
    QPushButton *confirmButton = new QPushButton(formWidget);
    connect(confirmButton, SIGNAL(clicked()), SLOT(writePatientOnOperationFormConfirmButtonClicked()));
    QPushButton *cancelButton = new QPushButton(formWidget);
    confirmButton->setText("Добавить");
    cancelButton->setText("Отмена");
    form.addRow(new QLabel("Номер записи:"), operationNum);
    form.addRow(new QLabel("Номер типа операции:"), operationTypeNum);
    form.addRow(new QLabel("Номер записи в истории болезней:"), diseaseHistoryNum);
    form.addRow(new QLabel("Дата проведения операции:"), operationDate);
    form.addRow(new QLabel("Время начала операции:"), operationStartTime);
    form.addRow(confirmButton, cancelButton);
    formWidget->show();
}

void MainWindow::writePatientOnOperationFormConfirmButtonClicked() {
    if (!operationNum->text().isEmpty() &&
            !operationTypeNum->text().isEmpty() &&
            !diseaseHistoryNum->text().isEmpty() &&
            !operationDate->text().isEmpty() &&
            !operationStartTime->text().isEmpty()) {
        QSqlQuery query;
        query.prepare("INSERT INTO Операции (НомерОперации, НомерТипаОперации, НомерИсторииБолезни, ДатаПроведенияОперации, ВремяНачалаОперации) "
                      "VALUES (:operationNum, :operationTypeNum, :diseaseHistoryNum, :operationDate, :operationStartTime)");
        query.bindValue(":operationNum", operationNum->text().toInt());
        query.bindValue(":operationTypeNum", operationTypeNum->text().toInt());
        query.bindValue(":diseaseHistoryNum", diseaseHistoryNum->text().toInt());
        query.bindValue(":operationDate", QDate::fromString(operationDate->text(), "dd.MM.yyyy"));
        query.bindValue(":operationStartTime", QTime::fromString(operationStartTime->text(), "hh.mm.ss"));
        if (query.exec()) {
            formWidget->close();
        } else {
            qDebug() << "hmhmhmhmhm" << query.lastError();
        }
    } else {
        qDebug() << "Заполнены не все поля!";
    }
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
    int maxNum = 1;
    QSqlQuery query;
    query.prepare("SELECT MAX(НомерПациента) FROM Пациенты");
    query.exec();
    while(query.next()) {
        maxNum = query.value(0).toInt();
        maxNum += 1;
    }
    patientNum->setText(QString::number(maxNum));
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
        query.prepare("INSERT INTO Пациенты (НомерПациента, Фамилия, Имя, Отчество, Пол, ДатаРождения, Адрес, НомерМедПолиса, НомерПаспорта, НомерТелефона) "
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

void MainWindow::on_addPatientToVisit_triggered()
{
    int maxNum = 1;
    formWidget = new QWidget();
    QFormLayout form(formWidget);
    visitNum = new QLineEdit(formWidget);
    patientFIO = new QComboBox(formWidget);
    medicFIO = new QComboBox(formWidget);
    //patientNum = new QLineEdit(formWidget);
    //medicNum = new QLineEdit(formWidget);
    visitDate = new QLineEdit(formWidget);
    visitTime = new QLineEdit(formWidget);
    visitReport = new QLineEdit(formWidget);
    visitResult = new QLineEdit(formWidget);
    visitPrice = new QLineEdit(formWidget);
    QSqlQuery query;
    query.prepare("SELECT MAX(НомерПосещения) FROM Посещение");
    query.exec();
    while(query.next()) {
        maxNum = query.value(0).toInt();
        maxNum += 1;
    }
    query.prepare("SELECT CONCAT(Фамилия, ' ', Имя, ' ', Отчество) FROM Пациенты");
    query.exec();
    while(query.next()) {
        patientFIO->addItem(query.value(0).toString());
        //qDebug() << query.value(0).toString();
    }
    query.prepare("SELECT CONCAT(Фамилия, ' ', Имя, ' ', Отчество) FROM Врачи");
    query.exec();
    while(query.next()) {
        medicFIO->addItem(query.value(0).toString());
    }
    QPushButton *confirmButton = new QPushButton(formWidget);
    connect(confirmButton, SIGNAL(clicked()), SLOT(addPatientToVisitConfirmButtonClicked()));
    QPushButton *cancelButton = new QPushButton(formWidget);
    confirmButton->setText("Добавить");
    cancelButton->setText("Отмена");
    form.addRow(new QLabel("Номер посещения:"), visitNum);
    visitNum->setText(QString::number(maxNum));
    //form.addRow(new QLabel("Номер пациента:"), patientNum);
    form.addRow(new QLabel("ФИО Пациента"), patientFIO);
    form.addRow(new QLabel("ФИО Врача"), medicFIO);
    //form.addRow(new QLabel("Номер врача:"), medicNum);
    form.addRow(new QLabel("Дата посещения:"), visitDate);
    form.addRow(new QLabel("Время посещения:"), visitTime);
    form.addRow(new QLabel("Жалоба:"), visitReport);
    form.addRow(new QLabel("Результат обследования:"), visitResult);
    form.addRow(new QLabel("Цена:"), visitPrice);
    form.addRow(confirmButton, cancelButton);
    formWidget->show();
}

void MainWindow::addPatientToVisitConfirmButtonClicked() {
    if (!visitNum->text().isEmpty() &&
            //!patientNum->text().isEmpty() &&
            //!medicNum->text().isEmpty() &&
            !visitDate->text().isEmpty() &&
            !visitTime->text().isEmpty() &&
            !visitReport->text().isEmpty() &&
            !visitResult->text().isEmpty() &&
            !visitPrice->text().isEmpty()) {
        QSqlQuery query;
        query.prepare("INSERT INTO Посещение (НомерПосещения, НомерПациента, НомерВрача, ДатаПосещения, ВремяПосещения, Жалоба, РезультатОбследования, Цена) "
                      "VALUES ( :visitNum, :patientNum, :medicNum, :visitDate, :visitTime, :visitReport, :visitResult, :visitPrice )");
        query.bindValue(":visitNum", visitNum->text().toInt());
        //query.bindValue(":patientNum", patientNum->text().toInt());
        //query.bindValue(":medicNum", medicNum->text().toInt());
        query.bindValue(":patientNum", patientFIO->currentIndex() + 1);
        query.bindValue(":medicNum", medicFIO->currentIndex() + 1);
        qDebug() << patientFIO->currentIndex() + 1;
        qDebug() << medicFIO->currentIndex() + 1;
        query.bindValue(":visitDate", QDate::fromString(visitDate->text(), "dd.MM.yyyy"));
        query.bindValue(":visitTime", QTime::fromString(visitTime->text(), "hh.mm.ss"));
        query.bindValue(":visitReport", visitReport->text());
        query.bindValue(":visitResult", visitResult->text());
        query.bindValue(":visitPrice", visitPrice->text().toInt());
        if (query.exec()) {
            formWidget->close();
        } else {
            qDebug() << "Insert error" << query.lastError();
        }
    } else {
        qDebug() << "Заполнены не все поля!";
    }
}

void MainWindow::on_MedicCard_triggered()
{
    QSqlQuery query;

    query.prepare("CREATE TABLE `Hospital`.`TempTable` ( `НомерВрача` INT NOT NULL , `Фамилия` VARCHAR(30) NOT NULL , `Имя` VARCHAR(30) NOT NULL , `Отчество` VARCHAR(30) NOT NULL , "
                  "`ДатаНайма` DATE NOT NULL , `Профессия` VARCHAR(30) NOT NULL , `НомерТелефона` VARCHAR(15) NOT NULL , "
                  "PRIMARY KEY (`НомерВрача`)) ENGINE = InnoDB CHARSET=utf8mb4 COLLATE utf8mb4_unicode_ci;");
    if (query.exec()) {
        qDebug() << "Table Created";
        query.prepare("INSERT INTO TempTable ( НомерВрача, Фамилия, Имя, Отчество, ДатаНайма, Профессия, НомерТелефона ) "
                      "SELECT a.НомерВрача, a.Фамилия, a.Имя, a.Отчество, a.ДатаНайма, b.Профессия, a.НомерТелефона "
                      "FROM Врачи a join ПрофессииВрача b "
                      "WHERE a.НомерПрофессии = b.НомерПрофессии");
        if (query.exec()) {
            qDebug() << "Values Inserted";
            query.prepare("SELECT * FROM TempTable");
            if (query.exec()) {
                QSqlTableModel *model = new QSqlTableModel(this, db);
                model->setTable("TempTable");
                model->select();
                model->setHeaderData(0, Qt::Horizontal, tr("ID"));
                model->setHeaderData(1, Qt::Horizontal, tr("Фамилия"));
                model->setHeaderData(2, Qt::Horizontal, tr("Имя"));
                model->setHeaderData(3, Qt::Horizontal, tr("Отчество"));
                model->setHeaderData(4, Qt::Horizontal, tr("Дата найма"));
                model->setHeaderData(5, Qt::Horizontal, tr("Профессия"));
                model->setHeaderData(6, Qt::Horizontal, tr("Номер телефона"));
                QTableView *view = new QTableView;
                view->setModel(model);
                view->show();
                query.prepare("DROP TABLE TempTable");
                if (query.exec()) {
                    qDebug() << "All Right";
                } else {
                    qDebug() << "Wery bad";
                }
            } else {
                qDebug() << "Error while selecting from TempTable";
            }
        } else {
            qDebug() << "Values Not Inserted";
        }
    } else {
        qDebug() << "Table Not Created";
    }
}

void MainWindow::on_watchPatientDiseaseHistory_triggered()
{
    QDialog *enterPatientNumDialog = new QDialog();
        QFormLayout dialogForm(enterPatientNumDialog);
        patientNum = new QLineEdit(enterPatientNumDialog);
        QPushButton *confirmButton = new QPushButton(enterPatientNumDialog);
        connect(confirmButton, SIGNAL(clicked()), SLOT(watchPatientDiseaseHistoryConfirmButtonClicked()));
        confirmButton->setText("Подтвердить:");
        dialogForm.addRow(new QLabel("Номер пациента:"), patientNum);
        dialogForm.addRow(confirmButton);
        enterPatientNumDialog->show();
}

void MainWindow::watchPatientDiseaseHistoryConfirmButtonClicked() {
    QSqlQuery query;

    query.prepare("CREATE TABLE `Hospital`.`TempTable` ( `НомерПациента` INT NOT NULL , `ФИОПациента` VARCHAR(255) NOT NULL , `НомерЗаписи` INT NOT NULL , "
                  "`НомерПосещения` INT NOT NULL , `Заболевание` VARCHAR(50) NOT NULL , `ДатаЗаболевания` DATE NOT NULL , "
                  "`ДатаВыздоровления` DATE NOT NULL , PRIMARY KEY (`НомерПациента`)) ENGINE = InnoDB CHARSET=utf8mb4 COLLATE utf8mb4_unicode_ci;");
    if (query.exec()) {
        qDebug() << "Table Created";
        query.prepare("INSERT INTO TempTable ( НомерПациента, ФИОПациента, НомерЗаписи, НомерПосещения, Заболевание, ДатаЗаболевания, ДатаВыздоровления ) "
                      "SELECT c.НомерПациента, concat(b.Фамилия, ' ', b.Имя, ' ', b.Отчество), a.НомерЗаписи, a.НомерПосещения, d.Заболевание, a.ДатаЗаболевания, a.ДатаВыздоровления "
                      "FROM ИсторияБолезни a join Посещение c on a.НомерПосещения = c.НомерПосещения "
                      "JOIN ТипЗаболевания d on a.НомерЗаболевания = d.НомерЗаболевания "
                      "JOIN Пациенты b on b.НомерПациента = c.НомерПациента");
        if (query.exec()) {
            qDebug() << "Values Inserted";
            query.prepare("delete from TempTable where НомерПациента <> :patientNum");
            query.bindValue(":patientNum", patientNum->text().toInt());
            query.exec();
            query.prepare("select * from TempTable");
            QSqlTableModel *model = new QSqlTableModel(this, db);
            model->setTable("TempTable");
            model->select();
            model->setHeaderData(0, Qt::Horizontal, tr("Номер пациента"));
            model->setHeaderData(1, Qt::Horizontal, tr("ФИО Пациента"));
            model->setHeaderData(2, Qt::Horizontal, tr("Номер записи"));
            model->setHeaderData(3, Qt::Horizontal, tr("Номер посещения"));
            model->setHeaderData(4, Qt::Horizontal, tr("Дата найма"));
            model->setHeaderData(5, Qt::Horizontal, tr("Заболевание"));
            model->setHeaderData(6, Qt::Horizontal, tr("Дата заболевания"));
            model->setHeaderData(7, Qt::Horizontal, tr("Дата выздоровления"));
            QTableView *view = new QTableView;
            view->setModel(model);
            view->show();
            query.prepare("DROP TABLE TempTable");
            query.exec();
        } else {
            qDebug() << "Values not inserted";
            query.prepare("DROP TABLE TempTable");
            query.exec();
        }
    } else {
        qDebug() << "Table not created";
    }
}

void MainWindow::on_watchOperationInThisMonth_triggered()
{
    QSqlQuery query;

    query.prepare("CREATE TABLE `Hospital`.`TempTable` ( `НомерОперации` INT NOT NULL , `НомерТипаОперации` INT NOT NULL , `НомерИсторииБолезни` INT NOT NULL , "
                  "`ДатаПроведеннойОперации` DATE NOT NULL , `ВремяНачалаОперации` TIME NOT NULL , "
                  "PRIMARY KEY (`НомерОперации`)) ENGINE = InnoDB CHARSET=utf8mb4 COLLATE utf8mb4_unicode_ci;");
    if (query.exec()) {
        qDebug() << "Table created";
        query.prepare("INSERT INTO TempTable ( НомерОперации, НомерТипаОперации, НомерИсторииБолезни, ДатаПроведеннойОперации, ВремяНачалаОперации ) "
                      "SELECT * FROM Операции");
        if (query.exec()) {
            qDebug() << "Values inserted";
            query.prepare("DELETE FROM TempTable WHERE MONTH(ДатаПроведеннойОперации) <> MONTH(:currentDate)");
            QDate dt = QDate::currentDate();
            query.bindValue(":currentDate", dt.toString("dd.MM.yyyy"));
            query.exec();
            query.prepare("select * from TempTable");
            query.exec();
            QSqlTableModel *model = new QSqlTableModel(this, db);
            model->setTable("TempTable");
            model->select();
            model->setHeaderData(0, Qt::Horizontal, tr("Номер операции"));
            model->setHeaderData(1, Qt::Horizontal, tr("Номер типа операции"));
            model->setHeaderData(2, Qt::Horizontal, tr("Номер истории болезни"));
            model->setHeaderData(3, Qt::Horizontal, tr("Дата проведённой операции"));
            model->setHeaderData(3, Qt::Horizontal, tr("Время начала операции"));
            QTableView *view = new QTableView;
            view->setModel(model);
            view->show();
            query.prepare("DROP TABLE TempTable");
            query.exec();
        } else {
            qDebug() << "Values not inserted";
            query.prepare("DROP TABLE TempTable");
            query.exec();
        }
    } else {
        qDebug() << "Table not created";
    }
}

void MainWindow::on_medicGraphic_triggered()
{

    QDialog *enterMedicFIODialog = new QDialog();
    medicFIO = new QComboBox(enterMedicFIODialog);
    QPushButton *confirmButton = new QPushButton(enterMedicFIODialog);
    connect(confirmButton, SIGNAL(clicked()), SLOT(watchMedicWorkloadConfirmButtonClicked()));
    confirmButton->setText("Подтвердить");
    QFormLayout dialogForm(enterMedicFIODialog);
    dialogForm.addRow(new QLabel("Выбор врача:"), medicFIO);
    dialogForm.addRow(confirmButton);

    QSqlQuery query;

    query.prepare("SELECT CONCAT(Фамилия, ' ', Имя, ' ', Отчество) FROM Врачи");
    query.exec();
    while(query.next()) {
        medicFIO->addItem(query.value(0).toString());
    }

    enterMedicFIODialog->show();
}

void MainWindow::watchMedicWorkloadConfirmButtonClicked() {
    QSqlQuery query;

    /*query.prepare("CREATE TABLE `Hospital`.`TempTable` ( `НомерОперации` INT NOT NULL , `НомерТипаОперации` INT NOT NULL , `НомерИсторииБолезни` INT NOT NULL , "
                  "`ДатаПроведеннойОперации` DATE NOT NULL , `ВремяНачалаОперации` TIME NOT NULL , "
                  "PRIMARY KEY (`НомерОперации`)) ENGINE = InnoDB CHARSET=utf8mb4 COLLATE utf8mb4_unicode_ci;");*/

    if (query.exec()) {
        qDebug() << "Table created";
        query.prepare("");
    } else {
        qDebug() << "Table not created";
    }


    QSqlTableModel *model = new QSqlTableModel(this, db);
    model->setTable("TempTable");
    model->select();
    QTableView *view = new QTableView;
    view->setModel(model);
    view->show();

}
