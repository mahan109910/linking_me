#ifndef DIRECT_MESSAGE_H
#define DIRECT_MESSAGE_H

#include <string>
#include <vector>
#include "time1.h" // Assuming Time class is declared here

class QSqlDatabase;
class QSqlQuery;

class Direct_Message {
public:
    Direct_Message(const std::string &message_id, const std::string &sender_id, const std::string &to_who,
                   const Time1 &time_sent, const std::string &content_text);

    bool saveToDatabase(QSqlDatabase &db) const;
    bool loadFromDatabase(const std::string &message_id, QSqlDatabase &db);

private:
    std::string Message_ID;
    std::string Sender_ID;
    std::string To_who;
    Time1 time_sent; // Assuming Time class is defined and has necessary methods
    std::string Content_Text;
    std::vector<std::string> Content_picture;
    std::vector<std::string> Content_video;
};

#endif // DIRECT_MESSAGE_H
