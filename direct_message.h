#ifndef DIRECT_MESSAGE_H
#define DIRECT_MESSAGE_H

#include <string>
#include <QSqlDatabase>

class Direct_Message {
public:
    Direct_Message(const std::string &msg_id, const std::string &sndr_id, const std::string &rcvr_id,
                   const std::string &cntnt, const std::string &cntnt_type, const std::string &time)
        : message_id(msg_id), sender_id(sndr_id), receiver_id(rcvr_id), content(QByteArray::fromStdString(cntnt)),
        content_type(cntnt_type), timestamp(time) {}

    bool saveToDatabase(QSqlDatabase &db) const;
    bool loadFromDatabase(const std::string &msg_id, QSqlDatabase &db);

    std::string getMessageID() const { return message_id; }
    std::string getSenderID() const { return sender_id; }
    std::string getReceiverID() const { return receiver_id; }
    QByteArray getContent() const { return content; }
    std::string getContentType() const { return content_type; }
    std::string getTimestamp() const { return timestamp; }

private:
    std::string message_id;
    std::string sender_id;
    std::string receiver_id;
    QByteArray content;
    std::string content_type;
    std::string timestamp;
};

#endif // DIRECT_MESSAGE_H
