使用相对路径的时候，你要让cmake能够搜索到找到你动态库，就像直接使用gcc/g++来链接的时候一样，要使用-L来指定第三方库所在路径。
cmake可以使用  LINK_DIRECTORIES 命令来指定第三方库所在路径，比如，你的动态库在
/home/myproject/libs
这个路径下，则通过命令：
LINK_DIRECTORIES(/home/myproject/libs)
把该路径添加到第三方库搜索路径中，这样就可以使用相对路径了，使用TARGET_LINK_LIBRARIES的时候，只需要给出动态链接库的名字就行了，比如：
TARGET_LINK_LIBRARIES(MyApp -lcurl )

```
cmake_minimum_required (VERSION 2.8) 

PROJECT(WebcamFaceRec)

# Requires OpenCV v2.4.1 or later
FIND_PACKAGE( OpenCV REQUIRED )
IF (${OpenCV_VERSION} VERSION_LESS 2.4.1)
    MESSAGE(FATAL_ERROR "OpenCV version is not compatible : ${OpenCV_VERSION}. FaceRec requires atleast OpenCV v2.4.1")
ENDIF()

SET(SRC
    main.cpp
    detectObject.cpp
    preprocessFace.cpp
    recognition.cpp
    ImageUtils_0.7.cpp
)

#ADD_EXECUTABLE( ${PROJECT_NAME} ${SRC} )
LINK_DIRECTORIES(/usr/lib/arm-linux-gnueabihf)
ADD_EXECUTABLE( ${PROJECT_NAME} ${SRC} )
target_link_libraries(${PROJECT_NAME} -lmysqlclient)
TARGET_LINK_LIBRARIES( ${PROJECT_NAME}  ${OpenCV_LIBS} ${LD_LIBRARY_PATH})
```
