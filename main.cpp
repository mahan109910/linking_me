#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <iostream>
#include "welcome.h"
#include "account.h"
#include "direct_message.h"
#include "job1.h"
#include "post.h"
#include "time1.h"

using namespace std;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Initialize and open your database
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("D:\\sobooty\\Qt\\start-me\\sqlite\\me-test-1.db");

    if (!db.open()) {
        qDebug() << "Error: could not open database.";
        return 1;
    }

    welcome w;
    w.show();

    // Example of using Account class
    /*Account user("user_id", "user_phone", "user_email" , "password");
    if (user.saveToDatabase(db)) {
        qDebug() << "Account saved to database.";
    } else {
        qDebug() << "Failed to save account to database.";
    }

    // Example of using Direct_Message class
    Direct_Message message("sender_id", "recipient_id", "message_text", Time1(), "message_id");
    if (message.saveToDatabase(db)) {
        qDebug() << "Message saved to database.";
    } else {
        qDebug() << "Failed to save message to database.";
    }

    // Example of using Job1 class
    Job1 job("job_id", "job_title", "company_name", "job_description", Time1());
    if (job.saveToDatabase(db)) {
        qDebug() << "Job saved to database.";
    } else {
        qDebug() << "Failed to save job to database.";
    }

    // Example of using Post class
    Post post("post_sender", Time1(), "post_text", {"picture1.jpg", "picture2.jpg"}, {"video1.mp4", "video2.mp4"}, "post_id");
    if (post.saveToDatabase(db)) {
        qDebug() << "Post saved to database.";
    } else {
        qDebug() << "Failed to save post to database.";
    }

    // Close the database connection
    db.close();*/

    return a.exec();
}
