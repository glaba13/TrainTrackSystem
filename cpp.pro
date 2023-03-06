TEMPLATE    = app
TARGET      = test-cpp
CONFIG      += qt warn_on thread c++14
QT          += widgets core gui qml quick quickcontrols2

include(../../src/quickqanava.pri)

SOURCES	+=  \
    TrainTrackSolver.cpp \
    astart.cpp \
    graphgui.cpp \
    parser.cpp \
    trackgraph.cpp \
    train.cpp

HEADERS += \
    TrackGUI.h \
    TrainTrackSolver.h \
    astart.h \
    buttonCust.h \
    graphgui.h \
    parser.h \
    trackgraph.h \
    train.h

OTHER_FILES +=  cpp_sample.qml  \
                CustomNode.qml  \
                CustomEdge.qml  \
                CustomGroup.qml

RESOURCES   +=  cpp_sample.qrc

