#ifndef CONTENT_H
#define CONTENT_H

#include <string>
#include <vector>
#include "time1.h"
#include <QSqlDatabase>


class Content {
public:
    std::string sender_ID;
    Time1 time_sent;
    std::string Content_Text;
    std::vector<std::string> Content_picture;
    std::vector<std::string> Content_video;

    Content(const std::string &sender, const Time1 &time, const std::string &text,
            const std::vector<std::string> &picture, const std::vector<std::string> &video)
        : sender_ID(sender), time_sent(time), Content_Text(text),
        Content_picture(picture), Content_video(video) {}

    virtual bool saveToDatabase(const std::string &content_id, QSqlDatabase& db);
    virtual bool loadFromDatabase(const std::string &content_id, QSqlDatabase& db);
};

#endif // CONTENT_H
