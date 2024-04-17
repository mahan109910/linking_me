#include "email_number.h"
#include "ui_email_number.h"
#include <QIntValidator>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QDebug>
#include "QSqlError"
#include <curl/curl.h>
//inchude database
#include "QSqlDatabase"
#include "QSqlDriver"
#include "QSqlQuery"
#include "QSqlQueryModel"

email_number::email_number(QWidget *parent) : QMainWindow(parent), ui(new Ui::email_number) {
    ui->setupUi(this);
    ui->lineEdit_email->setPlaceholderText("Enter your email");
}

email_number::~email_number() {
    delete ui;
}

void email_number::on_pushButton_ok_email_clicked() {
    QString email = ui->lineEdit_email->text();

    bool isValid = validateEmail(email);

    if (isValid) {
        sendVerificationCodeEmail(email);
    } else {
        QMessageBox::warning(this, "Error", "Invalid email format.");
    }
}

bool email_number::validateEmail(const QString& email) {
    // Your email validation logic
    // For example: Check format, domain, etc.
    // Return true if valid, false otherwise

    return true;
}

void email_number::sendVerificationCodeEmail(const QString& email) {
    // Replace these placeholders with your Gmail account details
    std::string gmailUsername = "mahan.test.h@gmail.com";
    std::string gmailPassword = "(#!3:-613_password";

    std::string from = gmailUsername + "@gmail.com";
    std::string to = email.toStdString();
    std::string subject = "Verification Code";
    std::string body = "Your verification code is: 123456"; // Replace with actual code

    CURL *curl;
    CURLcode res = CURLE_OK;

    curl = curl_easy_init();
    if (curl) {
        std::string url = "smtps://smtp.gmail.com:465";
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // Set username and password
        curl_easy_setopt(curl, CURLOPT_USERNAME, gmailUsername.c_str());
        curl_easy_setopt(curl, CURLOPT_PASSWORD, gmailPassword.c_str());

        // Set recipient
        struct curl_slist *recipients = NULL;
        recipients = curl_slist_append(recipients, to.c_str());
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

        // Set sender
        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, from.c_str());

        // Set email data (subject and body)
        std::string emailData = "Subject: " + subject + "\r\n\r\n" + body;
        curl_easy_setopt(curl, CURLOPT_READDATA, &emailData);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

        // Perform the email sending
        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            qDebug() << "curl_easy_perform() failed: " << curl_easy_strerror(res);
            QMessageBox::critical(this, "Error", "Failed to send verification code.");
        } else {
            qDebug() << "Email sent successfully!";
            QMessageBox::information(this, "Success", "Verification code sent to your email.");
        }

        curl_slist_free_all(recipients);
        curl_easy_cleanup(curl);
    } else {
        qDebug() << "Failed to initialize cURL.";
        QMessageBox::critical(this, "Error", "Failed to initialize cURL.");
    }
}
