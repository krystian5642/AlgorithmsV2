cmake_minimum_required(VERSION 3.16)

project(Algorithms VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Charts Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Charts Widgets)

set(PROJECT_SOURCES
        main.cpp
        algorithmvisializationwindow.cpp
        algorithmvisializationwindow.h
        algorithmvisializationwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Algorithms
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}

        # Core classes
        Core/algorithm.h Core/algorithm.cpp
        Core/algorithmbenchmarkwindow.cpp Core/algorithmbenchmarkwindow.h Core/algorithmbenchmarkwindow.ui
        Core/datastructurewidget.h Core/datastructurewidget.cpp
        Core/algorithmwidgetlibrary.h Core/algorithmwidgetlibrary.cpp
        Core/propertylayoutfactory.h Core/propertylayoutfactory.cpp

        # Graph classes
        Graphs/graph.h Graphs/graph.cpp
        Graphs/graphalgorithms.h Graphs/graphalgorithms.cpp
        Graphs/graphalgorithms.cpp Graphs/graphalgorithms.h
        Graphs/graphwidget.cpp Graphs/graphwidget.h Graphs/graphwidget.ui
        Graphs/addgraphedgedialog.h Graphs/addgraphedgedialog.cpp Graphs/addgraphedgedialog.ui
        Graphs/edgelist.h Graphs/edgelist.cpp
        Graphs/graphbenchmark.h Graphs/graphbenchmark.cpp

        # app root
        rootappwidget.h rootappwidget.cpp rootappwidget.ui

        # Resources
        icons.qrc
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Algorithms APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Algorithms SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Algorithms
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Algorithms PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(Algorithms PRIVATE Qt${QT_VERSION_MAJOR}::Charts)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Algorithms)
endif()
set_target_properties(Algorithms PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Algorithms
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Algorithms)
endif()
