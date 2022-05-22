QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DataSettings/InfoMapping.cpp \
    DataSettings/Serializable.cpp \
    DataSettings/propertyinfo.cpp \
    Factories/Builder.cpp \
    Modelling/Animation.cpp \
    Modelling/Lights/Light.cpp \
    Modelling/Materials/ColorMapStatic.cpp \
    Modelling/Materials/Material.cpp \
    Modelling/Objects/Cara.cpp \
    Modelling/Objects/Cub.cpp \
    Modelling/Objects/Mesh.cpp \
    Modelling/Objects/Plane.cpp \
    Modelling/Scene.cpp \
    Modelling/TG/TG.cpp \
    Modelling/TG/TranslateTG.cpp \
    Rendering/Camera.cpp \
    Rendering/GLWidget.cpp \
    library/Common.cpp \
    Main.cpp \
    Rendering/MainWindow.cpp

HEADERS += \
    DataSettings/InfoMapping.h \
    DataSettings/PropertyInfo.h \
    DataSettings/Serializable.h \
    Factories/Builder.h \
    IncludeWin32/GL/glut.h \
    Modelling/Animation.h \
    Modelling/Lights/Light.h \
    Modelling/Materials/ColorMap.h \
    Modelling/Materials/ColorMapStatic.h \
    Modelling/Materials/Material.h \
    Modelling/Objects/Cara.h \
    Modelling/Objects/Cub.h \
    Modelling/Objects/Mesh.h \
    Modelling/Objects/Plane.h \
    Modelling/Scene.h \
    Modelling/TG/TG.h \
    Modelling/TG/TranslateTG.h \
    Rendering/Camera.h \
    Rendering/GLWidget.h \
    Rendering/MainWindow.h \
    library/Common.h \
    library/mat.h \
    library/vec.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES += \
    LICENSE \
    README.md \
    libWin32/glut.dll \
    libWin32/glut.lib \
    libWin32/glut32.dll \
    libWin32/glut32.lib \

