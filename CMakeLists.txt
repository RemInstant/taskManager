cmake_minimum_required(VERSION 3.18)

project(taskManager VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets LinguistTools)

SET(TS_FILES
        languages/taskManager_ru_RU.ts
        languages/taskManager_en_US.ts
)

#Qt5_create_translation(Translate ${CMAKE_SOURCE_DIR} ${TS_FILES})

set(PROJECT_SOURCES
        src/main.cpp
        src/mainModule/mainwindow.cpp
        src/mainModule/mainwindow.h
        src/mainModule/mainwindow.ui
        src/taskModule/taskmodel.h
        src/taskModule/taskmodel.cpp
        src/taskModule/taskdelegate.h
        src/taskModule/taskdelegate.cpp
        src/taskModule/taskeditor.h
        src/taskModule/taskeditor.cpp
        src/taskModule/taskeditor.ui
        languages/translation.qrc
        ${TS_FILES}
)

option(UPDATE_TRANSLATIONS "Update source translation translations/*.ts")
if(UPDATE_TRANSLATIONS)
    message("123")
    qt_create_translation(QM_FILES ${PROJECT_SOURCES})
else(UPDATE_TRANSLATIONS)
    message("456")
    qt_add_translation(QM_FILES ${TS_FILES})
endif(UPDATE_TRANSLATIONS)

add_custom_target(translations DEPENDS ${QM_FILES})

file(COPY ${QM_FILES} DESTINATION "D:/Programms/Qt/Projects/taskManager/languages")

source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${PROJECT_SOURCES})

add_executable(taskManager ${PROJECT_SOURCES} ${QM_FILES})

target_link_libraries(taskManager PRIVATE Qt5::Widgets)
