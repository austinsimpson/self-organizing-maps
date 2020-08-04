CONFIG += c++17
QT += core gui widgets

SOURCES += main.cpp \
    FunctionModel.cpp \
    GraphLayer.cpp \
    GraphWidget.cpp \
    PointSetModel.cpp \
    SOMCategoriesGraphLayer.cpp \
    SelfOrganizingMapWindow.cpp

FORMS += \
    SelfOrganizingMapWindow.ui

HEADERS += \
    FunctionModel.h \
    GraphLayer.h \
    GraphWidget.h \
    IPointSetModel.h \
    PointSetModel.h \
    Range.h \
    SOMCategoriesGraphLayer.h \
    SelfOrganizingMap.h \
    SelfOrganizingMapCategory.h \
    SelfOrganizingMapUnit.h \
    SelfOrganizingMapWindow.h \
    VectorND.h

RESOURCES += \
    Resources.qrc
