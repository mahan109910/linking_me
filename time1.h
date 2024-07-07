#ifndef TIME1_H
#define TIME1_H

#include "sstream"
#include <string>
#include <QSqlDatabase>

class Time1 {
public:
    std::string day;
    std::string month;
    std::string year;
    std::string hour;
    std::string minute;
    std::string second;

    Time1() = default;
    Time1(const std::string &d, const std::string &m, const std::string &y, const std::string &h, const std::string &min, const std::string &s)
        : day(d), month(m), year(y), hour(h), minute(min), second(s) {}

    std::string toString() const {
        return day + "-" + month + "-" + year + " " + hour + ":" + minute + ":" + second;
    }

    static Time1 fromString(const std::string &str);

    bool saveToDatabase(const std::string& context_id, QSqlDatabase& db);
    bool loadFromDatabase(const std::string& context_id, QSqlDatabase& db);
};

#endif // TIME1_H
