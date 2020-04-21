TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        DSString.cpp \
        main.cpp \
        match.cpp \
        player.cpp \
        team.cpp

HEADERS += \
    DSString.h \
    match.h \
    player.h \
    team.h

DISTFILES += \
    match \
    team1 \
    team2
