#ifndef DIRECT_MESSAGE_H
#define DIRECT_MESSAGE_H

#include <string>
#include <QSqlDatabase>

class Direct_Message {
public:
    std::string message_id;
    std::string sender_id;
    std::string receiver_id;
    std::string content;
    std::string timestamp;

    Direct_Message() = default;
    Direct_Message(const std::string &msg_id, const std::string &sender, const std::string &receiver,
                   const std::string &content, const std::string &timestamp)
        : message_id(msg_id), sender_id(sender), receiver_id(receiver), content(content), timestamp(timestamp) {}

    bool saveToDatabase(QSqlDatabase& db) const;
    bool loadFromDatabase(const std::string &msg_id, QSqlDatabase& db);
};

#endif // DIRECT_MESSAGE_H
