QT += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17


SOURCES += \
    account.cpp \
    comment.cpp \
    company.cpp \
    content.cpp \
    direct_message.cpp \
    full_information.cpp \
    home.cpp \
    information.cpp \
    job1.cpp \
    job_company.cpp \
    job_person.cpp \
    main.cpp \
    managers.cpp \
    message.cpp \
    network_company.cpp \
    network_person.cpp \
    ok.cpp \
    person.cpp \
    post.cpp \
    signin.cpp \
    time1.cpp \
    welcome.cpp \
    login.cpp \
    like.cpp \

HEADERS += \
    account.h \
    comment.h \
    company.h \
    content.h \
    direct_message.h \
    full_information.h \
    home.h \
    information.h \
    job1.h \
    job_company.h \
    job_person.h \
    managers.h \
    message.h \
    network_company.h \
    network_person.h \
    ok.h \
    person.h \
    post.h \
    signin.h \
    time1.h \
    welcome.h \
    login.h \
    like.h \

FORMS += \
    full_information.ui \
    home.ui \
    information.ui \
    job_company.ui \
    job_person.ui \
    managers.ui \
    message.ui \
    network_company.ui \
    network_person.ui \
    ok.ui \
    signin.ui \
    welcome.ui \
    login.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc
