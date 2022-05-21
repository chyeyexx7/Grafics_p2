QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DataSettings/Serializable.cpp \
    Factories/Builder.cpp \
    Modelling/Animation.cpp \
    Modelling/Lights/Light.cpp \
    Modelling/Materials/ColorMapStatic.cpp \
    Modelling/Materials/Material.cpp \
    Modelling/Objects/Cara.cpp \
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
    DataSettings/Serializable.h \
    Factories/Builder.h \
    IncludeWin32/GL/glut.h \
    Modelling/Animation.h \
    Modelling/Lights/Light.h \
    Modelling/Materials/ColorMap.h \
    Modelling/Materials/ColorMapStatic.h \
    Modelling/Materials/Material.h \
    Modelling/Objects/Cara.h \
    Modelling/Objects/Mesh.h \
    Modelling/Objects/Pane.h \
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
    resources/README.fst \
    resources/fshader1.glsl \
    resources/gouraud_fshader.glsl \
    resources/gouraud_vshader.glsl \
    resources/models/common-cockle.mtl \
    resources/models/cruiser.mtl \
    resources/models/f16.mtl \
    resources/models/sphere0.mtl \
    resources/models/sphere1.mtl \
    resources/phong_fshader.glsl \
    resources/phong_vshader.glsl \
    resources/textures/2k_earth_clouds.jpg \
    resources/textures/2k_earth_daymap.jpg \
    resources/textures/2k_earth_nightmap.jpg \
    resources/textures/2k_earth_normal_map.tif \
    resources/textures/2k_earth_specular_map.tif \
    resources/textures/2k_jupiter.jpg \
    resources/textures/2k_mars.jpg \
    resources/textures/2k_mercury.jpg \
    resources/textures/2k_moon.jpg \
    resources/textures/2k_saturn.jpg \
    resources/textures/2k_stars+milky_way.jpg \
    resources/textures/2k_sun.jpg \
    resources/textures/2k_uranus.jpg \
    resources/textures/2k_venus_atmosphere.jpg \
    resources/textures/2k_venus_surface.jpg \
    resources/textures/bricks.png \
    resources/textures/earth1.png \
    resources/textures/earth3.png \
    resources/textures/ennis.png \
    resources/textures/grace-new.png \
    resources/textures/metal_crosshatch_pattern_6190173.JPG \
    resources/vshader1.glsl
