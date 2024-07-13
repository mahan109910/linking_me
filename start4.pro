QT += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17


SOURCES += \
    account.cpp \
    comment.cpp \
    company.cpp \
    content.cpp \
    direct_message.cpp \
    full_company.cpp \
    full_information.cpp \
    home.cpp \
    job.cpp \
    job_company.cpp \
    job_person.cpp \
    main.cpp \
    message.cpp \
    messageme.cpp \
    network_company.cpp \
    network_person.cpp \
    person.cpp \
    post.cpp \
    serch.cpp \
    signin.cpp \
    snowanimation.cpp \
    time1.cpp \
    viwe_profile.cpp \
    welcome.cpp \
    login.cpp \
    like.cpp \

HEADERS += \
    account.h \
    comment.h \
    company.h \
    content.h \
    direct_message.h \
    full_company.h \
    full_information.h \
    home.h \
    job.h \
    job_company.h \
    job_person.h \
    message.h \
    messageme.h \
    network_company.h \
    network_person.h \
    person.h \
    post.h \
    serch.h \
    signin.h \
    snowanimation.h \
    time1.h \
    viwe_profile.h \
    welcome.h \
    login.h \
    like.h \

FORMS += \
    full_company.ui \
    full_information.ui \
    home.ui \
    job_company.ui \
    job_person.ui \
    message.ui \
    messageme.ui \
    network_company.ui \
    network_person.ui \
    serch.ui \
    signin.ui \
    viwe_profile.ui \
    welcome.ui \
    login.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc
