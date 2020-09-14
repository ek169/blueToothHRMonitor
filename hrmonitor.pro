TARGET = hrmonitor

QT += core bluetooth widgets charts
requires(qtConfig(listwidget))
TEMPLATE = app

SOURCES = \
    ChipFinder.cpp \
    Client.cpp \
    DeviceSearcher.cpp \
    PeakDetection.cpp \
    Plotter.cpp \
    main.cpp

HEADERS = \
    ChipFinder.h \
    Client.h \
    DeviceSearcher.h \
    PeakDetection.h \
    Plotter.h

FORMS = \
    ChipFinder.ui \
    DeviceSearcher.ui

target.path = /hrmonitor
INSTALLS += target
