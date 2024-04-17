#include "managers.h"
#include "ui_managers.h"
#include <QIntValidator>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QDebug>
// Include database headers
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QTableView> // Include QTableView header
#include <QVBoxLayout>  // Include QVBoxLayout header

managers::managers(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::managers)
{
    ui->setupUi(this);
    // Create and open SQLite database
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("d:\\database_linking.db");
    if (!database.open()) {
        qDebug() << "Error: Connection with database failed";
    } else {
        qDebug() << "Database connected successfully";
    }

    // Execute SQL query to fetch data from database_linking table
    QSqlQuery Information;
    Information.exec("SELECT * FROM database_linking");

    QSqlQueryModel *m = new QSqlQueryModel;
    m->setQuery(Information);

    ui->tableView->setModel(m);
}

managers::~managers()
{
    delete ui;
}
