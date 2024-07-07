QT += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17


SOURCES += \
    account.cpp \
    comment.cpp \
    company.cpp \
    content.cpp \
    direct_message.cpp \
    home.cpp \
    information.cpp \
    job1.cpp \
    jobui.cpp \
    main.cpp \
    managers.cpp \
    message.cpp \
    network.cpp \
    ok.cpp \
    person.cpp \
    post.cpp \
    signin.cpp \
    time1.cpp \
    welcome.cpp \
    login.cpp \
    like.cpp

HEADERS += \
    account.h \
    comment.h \
    company.h \
    content.h \
    direct_message.h \
    home.h \
    information.h \
    job1.h \
    jobui.h \
    managers.h \
    message.h \
    network.h \
    ok.h \
    person.h \
    post.h \
    signin.h \
    time1.h \
    welcome.h \
    login.h \
    like.cpp

FORMS += \
    home.ui \
    information.ui \
    jobui.ui \
    managers.ui \
    message.ui \
    network.ui \
    ok.ui \
    signin.ui \
    welcome.ui \
    login.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc
