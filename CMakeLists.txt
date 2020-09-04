PROJECT(datamosh)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET (CMAKE_CXX_FLAGS "-O1")

FILE(GLOB datamosh_SRC "src/main.cpp")

ADD_EXECUTABLE(datamosh ${datamosh_SRC})