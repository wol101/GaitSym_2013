# -------------------------------------------------
# Project created by QtCreator 2009-07-04T17:08:56
# -------------------------------------------------
VERSION = 3.1
AUTHOR = "Bill Sellers 2013"
macx {
    ICON = GaitSymQt.icns
    DEFINES += USE_OPENGL \
        USE_QT \
        dDOUBLE \
#        USE_OPENCL \
#        EXPERIMENTAL \
        USE_LIBTIFF USE_TIFF_LZW
    INCLUDEPATH += ../src \
        /usr/include/libxml2 \
        ${HOME}/Unix/include \
        /System/Library/Frameworks/OpenCL.framework/Versions/A/Headers/
    LIBS += -lxml2 \
        ${HOME}/Unix/lib/libode.a ${HOME}/Unix/lib/libtiff.a \
#        -framework OpenCL \
        -framework QTKit \
        -framework Cocoa
    HEADERS += QTKitHelper.h
    OBJECTIVE_SOURCES += QTKitHelper.mm

    #   Application signature (4 characters).
    SIGNATURE           =   "aSl+"
    #   Adds the Mac icons to the application bundle.
    ICON                =   GaitSymQt.icns
    #   Replaces yourcompany in the plist file
    COMPANY             =   AnimalSimulationLaboratory
    # nasty hack - this is the location of the Info.plist.template
    Info_plist_template =   ${HOME}/Qt5.0.2/5.0.2/clang_64/mkspecs/macx-clang/Info.plist.app

    Info_plist.target   =   Info.plist
    Info_plist.depends  =   $${Info_plist_template} $${TARGET}.app/Contents/Info.plist
    Info_plist.commands =   @$(DEL_FILE) $${TARGET}.app/Contents/Info.plist$$escape_expand(\n\t) \
                            @$(SED) -e \"s,@EXECUTABLE@,$$TARGET,g\" \
                            -e \"s,@TYPEINFO@,$$SIGNATURE,g\" \
                            -e \"s,@ICON@,$$basename(ICON),g\" \
                            -e \"s,yourcompany,$$COMPANY,g\" \
                            -e \"/CFBundleGetInfoString/ { n ; s/.*/<string>$${VERSION} $${AUTHOR}<\/string>/ ; }\" \
                            "$${Info_plist_template}" > $${TARGET}.app/Contents/Info.plist
    QMAKE_EXTRA_TARGETS +=  Info_plist
    PRE_TARGETDEPS      +=  $$Info_plist.target

    PkgInfo.target      =   PkgInfo
    PkgInfo.depends     =   $${TARGET}.app/Contents/PkgInfo
    PkgInfo.commands    =   @$(DEL_FILE) $$PkgInfo.depends$$escape_expand(\n\t) \
                            @echo "APPL$$SIGNATURE" > $$PkgInfo.depends
    QMAKE_EXTRA_TARGETS +=  PkgInfo
    PRE_TARGETDEPS      +=  $$PkgInfo.target

}
else:win32 {
    ICON = GaitSymQt.ico
    DEFINES += USE_OPENGL \
        USE_QT \
        dDOUBLE \
        MALLOC_H_NEEDED \
        BYTE_ORDER=LITTLE_ENDIAN \
        NEED_BCOPY \
        LIBXML_STATIC
    INCLUDEPATH += ../src \
        ../../Unix/include \
        ../../Unix/include/libxml2 \
        c:\QtSDK\mingw\include\GL
    LIBS += ../../Unix/lib/libxml2.a \
        ../../Unix/lib/libode.a \
        -lws2_32
}
else:unix {
#    ICON = GaitSymQt.icns
    DEFINES += USE_OPENGL \
        USE_QT \
        dDOUBLE \
        USE_LIBTIFF USE_TIFF_LZW \
        GL_GLEXT_PROTOTYPES
    INCLUDEPATH += ../src \
        /usr/include/libxml2 \
        ${HOME}/Unix/include \
        /usr/include/GL
    LIBS += -lxml2 -ltiff -lGLU \
        ${HOME}/Unix/lib/libode.a
}
QMAKE_CXXFLAGS_RELEASE += -O3 \
    -ffast-math
OBJECTS_DIR = obj
QT += opengl
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = GaitSymQt
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    glwidget.cpp \
    ../src/Util.cpp \
    ../src/UGMMuscle.cpp \
    ../src/UDP.cpp \
    ../src/TwoPointStrap.cpp \
    ../src/TIFFWrite.cpp \
    ../src/ThreePointStrap.cpp \
    ../src/TCP.cpp \
    ../src/StrokeFont.cpp \
    ../src/Strap.cpp \
    ../src/StepDriver.cpp \
    ../src/SphereGeom.cpp \
    ../src/Simulation.cpp \
    ../src/PlaneGeom.cpp \
    ../src/ObjectiveMain.cpp \
    ../src/NPointStrap.cpp \
    ../src/NamedObject.cpp \
    ../src/Muscle.cpp \
    ../src/MAMuscleExtended.cpp \
    ../src/MAMuscleComplete.cpp \
    ../src/MAMuscle.cpp \
    ../src/Joint.cpp \
    ../src/IrrlichtRoutines.cpp \
    ../src/HingeJoint.cpp \
    ../src/GLUtils.cpp \
    ../src/GLUIRoutines.cpp \
    ../src/Geom.cpp \
    ../src/FloatingHingeJoint.cpp \
    ../src/FixedJoint.cpp \
    ../src/fec.cpp \
    ../src/FacetedSphere.cpp \
    ../src/FacetedPolyline.cpp \
    ../src/FacetedObject.cpp \
    ../src/FacetedConicSegment.cpp \
    ../src/Face.cpp \
    ../src/ErrorHandler.cpp \
    ../src/Environment.cpp \
    ../src/DataTarget.cpp \
    ../src/DataFile.cpp \
    ../src/DampedSpringMuscle.cpp \
    ../src/CylinderWrapStrap.cpp \
    ../src/CyclicDriver.cpp \
    ../src/Contact.cpp \
    ../src/CappedCylinderGeom.cpp \
    ../src/Body.cpp \
    ../src/BallJoint.cpp \
    dialogpreferences.cpp \
    viewcontrolwidget.cpp \
    ../src/DataTargetScalar.cpp \
    ../src/DataTargetQuaternion.cpp \
    dialogoutputselect.cpp \
    ../src/DataTargetVector.cpp \
    ../src/Driver.cpp \
    trackball.cpp \
    ../src/TrimeshGeom.cpp \
    ../src/RayGeom.cpp \
    ../src/Reporter.cpp \
    ../src/TorqueReporter.cpp \
    ../src/OpenCLRoutines.cpp \
    ../src/ExpressionParser.cpp \
    ../src/XMLConverter.cpp \
    ../src/ExpressionVec.cpp \
    ../src/ExpressionVar.cpp \
    ../src/ExpressionRef.cpp \
    ../src/ExpressionMat.cpp \
    ../src/ExpressionFunTransform3D.cpp \
    ../src/ExpressionFolder.cpp \
    ../src/PositionReporter.cpp \
    ../src/Marker.cpp \
    ../src/UniversalJoint.cpp \
    ../src/AMotorJoint.cpp \
    dialoginterface.cpp \
    ../src/FacetedCappedCylinder.cpp \
    ../src/PIDMuscleLength.cpp \
    ../src/Drivable.cpp \
    ../src/Controller.cpp \
    ../src/SwingClearanceAbortReporter.cpp \
    ../src/TwoCylinderWrapStrap.cpp \
    ../src/SliderJoint.cpp \
    ../src/BoxGeom.cpp \
    ../src/FacetedBox.cpp \
    ../src/BoxCarDriver.cpp \
    ../src/StackedBoxCarDriver.cpp \
    aboutdialog.cpp \
    doublespinbox.cpp \
    spinbox.cpp \
    lineedit.cpp
HEADERS += mainwindow.h \
    glwidget.h \
    ../src/Util.h \
    ../src/UGMMuscle.h \
    ../src/UDP.h \
    ../src/TwoPointStrap.h \
    ../src/TIFFWrite.h \
    ../src/ThreePointStrap.h \
    ../src/TCP.h \
    ../src/StrokeFont.h \
    ../src/Strap.h \
    ../src/StepDriver.h \
    ../src/SphereGeom.h \
    ../src/SocketMessages.h \
    ../src/Simulation.h \
    ../src/SimpleStrap.h \
    ../src/PlaneGeom.h \
    ../src/PGDMath.h \
    ../src/NPointStrap.h \
    ../src/NamedObject.h \
    ../src/Muscle.h \
    ../src/MPIStuff.h \
    ../src/MAMuscleExtended.h \
    ../src/MAMuscleComplete.h \
    ../src/MAMuscle.h \
    ../src/Joint.h \
    ../src/IrrlichtRoutines.h \
    ../src/HingeJoint.h \
    ../src/GLUtils.h \
    ../src/GLUIRoutines.h \
    ../src/Geom.h \
    ../src/FloatingHingeJoint.h \
    ../src/FixedJoint.h \
    ../src/fec.h \
    ../src/FacetedSphere.h \
    ../src/FacetedPolyline.h \
    ../src/FacetedObject.h \
    ../src/FacetedConicSegment.h \
    ../src/Face.h \
    ../src/ErrorHandler.h \
    ../src/Environment.h \
    ../src/Driver.h \
    ../src/DebugControl.h \
    ../src/DataTarget.h \
    ../src/DataFile.h \
    ../src/DampedSpringMuscle.h \
    ../src/CylinderWrapStrap.h \
    ../src/CyclicDriver.h \
    ../src/Contact.h \
    ../src/CappedCylinderGeom.h \
    ../src/Body.h \
    ../src/BallJoint.h \
    ../src/ObjectiveMain.h \
    dialogpreferences.h \
    viewcontrolwidget.h \
    ../src/DataTargetScalar.h \
    ../src/DataTargetQuaternion.h \
    dialogoutputselect.h \
    ../src/DataTargetVector.h \
    trackball.h \
    ../src/TrimeshGeom.h \
    ../src/RayGeom.h \
    ../src/Reporter.h \
    ../src/TorqueReporter.h \
    ../src/OpenCLRoutines.h \
    ../src/ExpressionParser.h \
    ../src/XMLConverter.h \
    ../src/ExpressionVec.h \
    ../src/ExpressionVar.h \
    ../src/ExpressionRef.h \
    ../src/ExpressionMat.h \
    ../src/ExpressionFunTransform3D.h \
    ../src/ExpressionFolder.h \
    ../src/PositionReporter.h \
    ../src/Marker.h \
    ../src/UniversalJoint.h \
    ../src/AMotorJoint.h \
    dialoginterface.h \
    ../src/FacetedCappedCylinder.h \
    ../src/PIDMuscleLength.h \
    ../src/Drivable.h \
    ../src/Controller.h \
    ../src/SwingClearanceAbortReporter.h \
    ../src/TwoCylinderWrapStrap.h \
    ../src/SliderJoint.h \
    ../src/BoxGeom.h \
    ../src/FacetedBox.h \
    ../src/BoxCarDriver.h \
    ../src/StackedBoxCarDriver.h \
    aboutdialog.h \
    doublespinbox.h \
    spinbox.h \
    lineedit.h
FORMS += mainwindow.ui \
    dialogpreferences.ui \
    dialogoutputselect.ui \
    dialoginterface.ui \
    aboutdialog.ui
RESOURCES += resources.qrc




