PROJECT(datamosh)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
# QT5 flags
#SET (CMAKE_CXX_FLAGS "-DQT_WIDGETS_LIB -I/usr/include/qt/QtWidgets -I/usr/include/qt -I/usr/include/qt/QtCore -DQT_GUI_LIB -I/usr/include/qt/QtGui -DQT_CORE_LIB -lQt5Widgets -lQt5Gui -lQt5Core -fPIC -lcurl -lpthread -std=c++17 -lcrypto -ldl")

FILE(GLOB datamosh_SRC "src/main.cpp" "src/mainwindow.cpp")

ADD_EXECUTABLE(datamosh ${datamosh_SRC})