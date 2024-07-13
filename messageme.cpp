#include "messageme.h"
#include "ui_messageme.h"
#include "direct_message.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include <QUuid>
#include "QFileDialog"

static bool selectedLanguage;
static bool isDarkMode;

messageme::messageme(const QString &Account_ID, const QString &targetUser, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::messageme), // درست کردن تعریف اشاره‌گر به ui
    Account_ID(Account_ID),
    targetUser(targetUser)
{
    ui->setupUi(this); // تنظیم رابط کاربری
    ui->labelUsername->setText(targetUser);

    connect(ui->sendButton, &QPushButton::clicked, this, &messageme::sendMessage);
    connect(ui->imageButton, &QPushButton::clicked, this, &messageme::sendImage);
    connect(ui->audioButton, &QPushButton::clicked, this, &messageme::sendAudio);
    connect(ui->videoButton, &QPushButton::clicked, this, &messageme::sendVideo);

    loadMessages();
}

messageme::~messageme()
{
    delete ui;
}

void messageme::displayMessage(const QString &senderId, const QString &content, const QString &contentType)
{
    if (contentType == "text") {
        ui->listWidget->addItem(senderId + ": " + content);
    } else if (contentType == "image") {
        QListWidgetItem *item = new QListWidgetItem(senderId + ": [Image]");
        QLabel *imageLabel = new QLabel;
        QPixmap pixmap;
        pixmap.loadFromData(QByteArray::fromBase64(content.toUtf8()));
        imageLabel->setPixmap(pixmap);
        imageLabel->setScaledContents(true); // برای تنظیم اندازه تصویر بر اساس QLabel
        ui->listWidget->addItem(item);
        ui->listWidget->setItemWidget(item, imageLabel);
        ui->listWidget->setItemWidget(item, imageLabel);
    } else if (contentType == "audio") {
        ui->listWidget->addItem(senderId + ": [Audio]");
    } else if (contentType == "video") {
        ui->listWidget->addItem(senderId + ": [Video]");
    }
}


void messageme::sendMessage()
{
    QString messageContent = ui->textEdit->toPlainText();
    if (!messageContent.isEmpty()) {
        QString messageId = QUuid::createUuid().toString();
        QString timestamp = QDateTime::currentDateTime().toString(Qt::ISODate);

        Direct_Message message(messageId.toStdString(), Account_ID.toStdString(), targetUser.toStdString(),
                               messageContent.toStdString(), "text", timestamp.toStdString());
        QSqlDatabase db = QSqlDatabase::database(); // تعریف متغیر محلی QSqlDatabase
        if (message.saveToDatabase(db)) { // ارسال متغیر به تابع
            ui->listWidget->addItem(Account_ID + ": " + messageContent);
            ui->textEdit->clear();
        } else {
            qDebug() << "Error saving message to database";
        }
    }
}

void messageme::sendImage()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Select Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
    if (!filePath.isEmpty()) {
        sendFile(filePath, "image");
    }
}

void messageme::sendAudio()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Select Audio"), "", tr("Audio Files (*.mp3 *.wav *.ogg)"));
    if (!filePath.isEmpty()) {
        sendFile(filePath, "audio");
    }
}

void messageme::sendVideo()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Select Video"), "", tr("Video Files (*.mp4 *.avi *.mkv)"));
    if (!filePath.isEmpty()) {
        sendFile(filePath, "video");
    }
}

void messageme::sendFile(const QString &filePath, const QString &fileType)
{
    QString messageId = QUuid::createUuid().toString();
    QString timestamp = QDateTime::currentDateTime().toString(Qt::ISODate);

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Error opening file:" << file.errorString();
        return;
    }

    QByteArray fileData = file.readAll();
    file.close();

    QString encodedData = QString(fileData.toBase64());

    Direct_Message message(messageId.toStdString(), Account_ID.toStdString(), targetUser.toStdString(),
                           encodedData.toStdString(), fileType.toStdString(), timestamp.toStdString());

    QSqlDatabase db = QSqlDatabase::database();
    if (message.saveToDatabase(db)) {
        displayMessage(Account_ID, encodedData, fileType); // استفاده از displayMessage
    } else {
        qDebug() << "Error saving file message to database";
    }
}


void messageme::loadMessages()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    query.prepare("SELECT Sender_ID, Content, Content_Type FROM direct_messages WHERE (Sender_ID = ? AND Receiver_ID = ?) OR (Sender_ID = ? AND Receiver_ID = ?) ORDER BY Timestamp");
    query.addBindValue(Account_ID);
    query.addBindValue(targetUser);
    query.addBindValue(targetUser);
    query.addBindValue(Account_ID);

    if (query.exec()) {
        while (query.next()) {
            QString senderId = query.value(0).toString();
            QString content = query.value(1).toString();
            QString contentType = query.value(2).toString();
            displayMessage(senderId, content, contentType);
        }
    } else {
        qDebug() << "Error loading messages from database:" << query.lastError();
    }
}


void messageme::setDarkMode(bool dark)
{
    isDarkMode = dark;
    if (dark) {
        this->setStyleSheet("background-color: rgb(9, 0, 137); color: rgb(255, 255, 255);");
    } else {
        this->setStyleSheet("background-color: rgb(145, 206, 255); color: rgb(0, 0, 0);");
    }
}
