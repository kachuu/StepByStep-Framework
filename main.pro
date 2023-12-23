TEMPLATE = app
TARGET = example
QT += core

SOURCES += \
            main.cpp \
            mainObject.cpp \

HEADERS += \
            mainObject.h \
            ./framework/stepInterface.hpp \
            ./steps/stepTimer.hpp \
            ./steps/stepCount.hpp \
            ./steps/stepTask.hpp \
            ./steps/stepHandle2.hpp \
            ./steps/stepHandle1.hpp \
