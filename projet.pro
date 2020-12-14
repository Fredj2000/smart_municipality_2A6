QT       += core gui sql serialport

QT       += core gui sql multimediawidgets

QT       += core gui multimedia

QT       += core gui printsupport

QT       +=  network

QT       += core gui widgets texttospeech

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Bondescommandes.cpp \
    arduino.cpp \
    arduino_inter.cpp \
    connection.cpp \
    fournisseurs.cpp \
    main.cpp \
    mainwindow.cpp \
    produit.cpp \
    statistique_produit.cpp

HEADERS += \
    Bondescommandes.h \
    arduino.h \
    arduino_inter.h \
    connection.h \
    fournisseurs.h \
    mainwindow.h \
    produit.h \
    statistique_produit.h

FORMS += \
    arduino_inter.ui \
    mainwindow.ui \
    statistique_produit.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
