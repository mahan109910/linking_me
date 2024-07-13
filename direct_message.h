#ifndef DIRECT_MESSAGE_H
#define DIRECT_MESSAGE_H

#include <string>
#include <QSqlDatabase>

class Direct_Message {
public:
    Direct_Message() = default;
    Direct_Message(const std::string &msg_id, const std::string &sender_id,
                   const std::string &receiver_id, const std::string &content,
                   const std::string &content_type, const std::string &timestamp)
        : message_id(msg_id), sender_id(sender_id), receiver_id(receiver_id),
        content(content), content_type(content_type), timestamp(timestamp) {}

    bool saveToDatabase(QSqlDatabase &db) const;
    bool loadFromDatabase(const std::string &msg_id, QSqlDatabase &db);

    std::string getMessageID() const { return message_id; }
    std::string getSenderID() const { return sender_id; }
    std::string getReceiverID() const { return receiver_id; }
    std::string getContent() const { return content; }
    std::string getContentType() const { return content_type; }
    std::string getTimestamp() const { return timestamp; }

private:
    std::string message_id;
    std::string sender_id;
    std::string receiver_id;
    std::string content;
    std::string content_type;
    std::string timestamp;
};

#endif // DIRECT_MESSAGE_H
