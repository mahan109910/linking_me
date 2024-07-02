QT += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17


SOURCES += \
    information.cpp \
    main.cpp \
    managers.cpp \
    my_network.cpp \
    ok.cpp \
    signin.cpp \
    welcome.cpp \
    login.cpp

HEADERS += \
    information.h \
    managers.h \
    my_network.h \
    ok.h \
    signin.h \
    welcome.h \
    login.h

FORMS += \
    information.ui \
    managers.ui \
    my_network.ui \
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
