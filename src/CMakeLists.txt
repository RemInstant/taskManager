
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets)

set(MAIN_MODULE_H
        mainModule/mainwindow.h
)
set(MAIN_MODULE_CPP
        mainModule/main.cpp
        mainModule/mainwindow.cpp
)
set(MAIN_MODULE_UI
        mainModule/mainwindow.ui
)

set(TASK_MODULE_H
        taskModule/header/taskmodel.h
        taskModule/header/taskdelegate.h
        taskModule/header/taskeditor.h
)
set(TASK_MODULE_CPP
        taskModule/implementation/taskmodel.cpp
        taskModule/implementation/taskdelegate.cpp
        taskModule/implementation/taskeditor.cpp
)
set(TASK_MODULE_UI
        taskModule/taskeditor.ui
)


message(${CMAKE_CURRENT_SOURCE_DIR})

set(PROJECT_SOURCES
        main.cpp
)



source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${PROJECT_SOURCES})



add_executable(taskManager ${PROJECT_SOURCES})

add_subdirectory(mainModule)

target_link_libraries(taskManager PRIVATE Qt5::Widgets)

set_target_properties(taskManager PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)


#[[
find_package(
        Qt5
        REQUIRED
        Core
        Gui
        Widgets
        LinguistTools)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)



add_executable(taskManager)

add_subdirectory(mainModule)
add_subdirectory(taskModule)

target_sources(taskManager
    PRIVATE main.cpp)


target_include_directories(
  taskManager
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/mainModule>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/taskModule>)

set(_src_root_path ${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB_RECURSE _source_list LIST_DIRECTORIES false
    "${_src_root_path}/*.cpp"
    "${_src_root_path}/*.h")

#  will be organized according to the actual directory structure, .h.cpp is put together
source_group(TREE ${_src_root_path} FILES ${_source_list})

find_package (Git)
if (GIT_FOUND)
    message("git found: ${GIT_EXECUTABLE} in version     ${GIT_VERSION_STRING}")
    #execute_process(COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD OUTPUT_VARIABLE FLAMESHOT_GIT_HASH)
    #string(REGEX REPLACE "\r*\n$" "" FLAMESHOT_GIT_HASH "${FLAMESHOT_GIT_HASH}")
    #target_compile_definitions(flameshot PRIVATE FLAMESHOT_GIT_HASH="${FLAMESHOT_GIT_HASH}")
    #message("FLAMESHOT_GIT_HASH: ${FLAMESHOT_GIT_HASH}")
else()
    #target_compile_definitions(flameshot PRIVATE FLAMESHOT_GIT_HASH="-")
    message("git command is not found")
endif ()

#target_compile_definitions(taskManager PRIVATE APP_PREFIX="${CMAKE_INSTALL_PREFIX}")
#target_compile_definitions(taskManager PRIVATE APP_VERSION="v${PROJECT_VERSION}")
]]
