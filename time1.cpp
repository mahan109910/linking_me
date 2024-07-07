#include "time1.h"
#include "iostream"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>


Time1 Time1::fromString(const std::string &str) {
    std::istringstream ss(str);
    std::string d, m, y, h, min, s;
    char dash, colon, space;
    ss >> d >> dash >> m >> dash >> y >> space >> h >> colon >> min >> colon >> s;
    return Time1(d, m, y, h, min, s);
}

bool Time1::saveToDatabase(const std::string& context_id, QSqlDatabase& db) {
    QSqlQuery query(db);
    query.prepare("INSERT INTO times (context_id, day, month, year, hour, minute, second) VALUES (?, ?, ?, ?, ?, ?, ?)");
    query.addBindValue(QString::fromStdString(context_id));
    query.addBindValue(QString::fromStdString(day));
    query.addBindValue(QString::fromStdString(month));
    query.addBindValue(QString::fromStdString(year));
    query.addBindValue(QString::fromStdString(hour));
    query.addBindValue(QString::fromStdString(minute));
    query.addBindValue(QString::fromStdString(second));
    if (!query.exec()) {
        qDebug() << "Error inserting into times table:" << query.lastError();
        return false;
    }
    return true;
}

bool Time1::loadFromDatabase(const std::string& context_id, QSqlDatabase& db) {
    QSqlQuery query(db);
    query.prepare("SELECT day, month, year, hour, minute, second FROM times WHERE context_id = ?");
    query.addBindValue(QString::fromStdString(context_id));
    if (!query.exec() || !query.next()) {
        qDebug() << "Error loading from times table:" << query.lastError();
        return false;
    }
    day = query.value(0).toString().toStdString();
    month = query.value(1).toString().toStdString();
    year = query.value(2).toString().toStdString();
    hour = query.value(3).toString().toStdString();
    minute = query.value(4).toString().toStdString();
    second = query.value(5).toString().toStdString();
    return true;
}
