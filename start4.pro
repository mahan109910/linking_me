QT += core gui sql
QT += network
INCLUDEPATH += C:\curl-8.7.1\include
LIBS += C:\curl-8.7.1

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    completion_information.cpp \
    email_number.cpp \
    main.cpp \
    managers.cpp \
    welcome.cpp\
    singin.cpp\
    login.cpp\

HEADERS += \
    completion_information.h \
    email_number.h \
    managers.h \
    welcome.h\
    singin.h\
    login.h\


FORMS += \
    completion_information.ui \
    email_number.ui \
    managers.ui \
    welcome.ui\
    singin.ui\
    login.ui\


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc
