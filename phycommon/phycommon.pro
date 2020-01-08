QT += widgets

TEMPLATE = lib
CONFIG += staticlib

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += \
    ../../phycoub/borderconditions/ \
    ../../phycoub/borderevents/ \
    ../../phycoub/borderfieldconditions/ \
    ../../phycoub/common/ \
    ../../phycoub/calculationmodels/ \
    ../../phycoub/fieldfunctions/ \
    ../../phycoub/interworkingfunctions/ \
    ../../phycoub/otherobjects/ \
    ../../phycoub/lifetimecontrollers/ \
    ../../phycoub/particlesources/ \
    ../../phycoub/phyobjects/particlefigurematrix/ \
    ../../phycoub/phycoubs/ \
    ../../phycoub/phymeasurement/ \
    ../../phycoub/phyobjects/ \
    ../../phycoub/specialmodellingfunctions/ \
    ../../phycoub/src/ \
    ../../phycoub/shapes/ \
    ../../phycoub/types/

SOURCES += \
    GLRotationController.cpp \
    PhyCoubController.cpp

HEADERS += \
    GLRotationController.h \
    GLRotationIface.h \
    GetCoubSizeAdapterIface.h \
    GetParticlesForGLAdapterIface.h \
    PhyCoubController.h \
    PhyCoubControllerSubscriberIface.h \
    ScalarControllerAdapterIface.h

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    .clang-format
