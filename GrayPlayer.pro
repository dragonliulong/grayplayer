QT += core gui
UI_DIR = ./UI
QT += quickwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AdditionWidget.cpp \
    Button.cpp \
    CoderWidget.cpp \
    D3D11VAFilterWidget.cpp \
    D3D11VAWidget.cpp \
    DXVA2Widget.cpp \
    DXVAHDFilterWidget.cpp \
    DecodeWidget.cpp \
    GrayPlayer.cpp \
    GrayPlayerBorder.cpp \
    GrayPlayerDecodeSetting.cpp \
    GrayPlayerEvent.cpp \
    GrayPlayerInit.cpp \
    MultimediaAHelper.cpp \
    MultimediaAReleaser.cpp \
    MultimediaAddSetting.cpp \
    MultimediaDecodeSetting.cpp \
    MultimediaEvent.cpp \
    MultimediaExit.cpp \
    MultimediaFilter.cpp \
    MultimediaHW.cpp \
    MultimediaInterrupt.cpp \
    MultimediaMain.cpp \
    MultimediaResource.cpp \
    MultimediaTime.cpp \
    MultimediaType.cpp \
    MultimediaVD3D11.cpp \
    MultimediaVD3D9.cpp \
    MultimediaVDP.cpp \
    PlayList.cpp \
    SWWidget.cpp \
    SettingWidget.cpp \
    Slider.cpp \
    SystemWidget.cpp \
    main.cpp \

HEADERS += \
    AboutWidget.h \
    AdditionWidget.h \
    BeginWidget.h \
    Button.h \
    CoderWidget.h \
    D3D11VAFilterWidget.h \
    D3D11VAWidget.h \
    DXVA2Widget.h \
    DXVAHDFilterWidget.h \
    DecodeWidget.h \
    ExplainWidget.h \
    FramelessWidget.h \
    GrayPlayer.h \
    LineEdit.h \
    Logo.h \
    MainFrame.h \
    MultimediaAHelper.h \
    MultimediaAReleaser.h \
    MultimediaAddSetting.h \
    MultimediaDXVAHD.h \
    MultimediaDecodeSetting.h \
    MultimediaEvent.h \
    MultimediaExit.h \
    MultimediaFilter.h \
    MultimediaHW.h \
    MultimediaInterrupt.h \
    MultimediaMain.h \
    MultimediaResource.h \
    MultimediaTime.h \
    MultimediaType.h \
    MultimediaVD3D11.h \
    MultimediaVD3D9.h \
    MultimediaVDP.h \
    PlayList.h \
    SWWidget.h \
    SettingLabel.h \
    SettingWidget.h \
    Slider.h \
    StandardItem.h \
    StopButton.h \
    SystemWidget.h \
    TimeLabel.h \
    VideoArea.h \
    Volume.h

FORMS += \
    AdditionWidget.ui \
    CoderWidget.ui \
    D3D11VAFilterWidget.ui \
    D3D11VAWidget.ui \
    DXVA2Widget.ui \
    DXVAHDFilterWidget.ui \
    DecodeWidget.ui \
    GrayPlayer.ui \
    PlayList.ui \
    SWWidget.ui \
    SettingWidget.ui \
    SystemWidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc \
    qml.qrc

win32
{
    LIBS += -luser32
    LIBS += -ldwmapi
    LIBS += -lgdi32
    LIBS += -lole32
}

QT += multimedia

#----------------------ffmpeg--------------------#

INCLUDEPATH+=E:/ffmpeg/dev/include
LIBS+=E:/ffmpeg/dev/lib/avcodec.lib\
      E:/ffmpeg/dev/lib/avdevice.lib\
      E:/ffmpeg/dev/lib/avfilter.lib\
      E:/ffmpeg/dev/lib/avformat.lib\
      E:/ffmpeg/dev/lib/avutil.lib\
      E:/ffmpeg/dev/lib/swresample.lib\
      E:/ffmpeg/dev/lib/swscale.lib\
      E:/ffmpeg/dev/lib/postproc.lib

#------------------------------------------------#

#----------------------SDL2----------------------#

INCLUDEPATH+=E:/sdl2/include
LIBS+=E:/sdl2/lib/x64/SDL2.lib

#------------------------------------------------#

#-----------------------D3D----------------------#

LIBS += $${PWD}/d3d9.lib
LIBS += $${PWD}/d3d11.lib
LIBS += $${PWD}/dxva2.lib
LIBS += $${PWD}/dxgi.lib

#-----------------------------------------------#

#---------------------CUDA----------------------#

win32{
INCLUDEPATH += $$(CUDA_PATH)\include

contains(QT_ARCH,i386){
    QMAKE_LIBDIR += $$(CUDA_PATH)\lib\Win32
    LIBS += $$(CUDA_PATH)\lib\Win32\cuda.lib
    LIBS += $$(CUDA_PATH)\lib\Win32\cudart.lib
}else{
    QMAKE_LIBDIR += $$(CUDA_PATH)\lib\x64
    LIBS += $$(CUDA_PATH)\lib\x64\cuda.lib
    LIBS += $$(CUDA_PATH)\lib\x64\cudart.lib
}
}

#-----------------------------------------------#
