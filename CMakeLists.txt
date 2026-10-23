cmake_minimum_required(VERSION 3.20)
project(LibSorter VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Quick QuickControls2)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# --- LibCore как подпроект ---
if(EXISTS "${CMAKE_SOURCE_DIR}/../libcore/CMakeLists.txt")
    add_subdirectory("${CMAKE_SOURCE_DIR}/../libcore" "${CMAKE_BINARY_DIR}/libcore_build")
    set(LIBCORE_TARGET libcore_lib)
else()
    find_library(LIBCORE_LIB liblibcore_lib.a PATHS /usr/lib /usr/local/lib)
    if(NOT LIBCORE_LIB)
        message(FATAL_ERROR "LibCore not found. Clone it to ../LibCore or install libcore")
    endif()
    set(LIBCORE_TARGET ${LIBCORE_LIB})
endif()

# --- Источники ---
set(LIBSORTER_SOURCES
    main.cpp
    src/bridge/LibCoreBridge.cpp
)

add_executable(libsorter ${LIBSORTER_SOURCES})

target_include_directories(libsorter PRIVATE
    "${CMAKE_SOURCE_DIR}/src"
)

target_link_libraries(libsorter PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Quick
    Qt6::QuickControls2
    ${LIBCORE_TARGET}
)

# --- QML ---
qt_add_qml_module(libsorter
    URI LibSorter
    VERSION 1.0
    QML_FILES
        qml/Main.qml
        qml/Canvas.qml
        qml/Widget.qml
        qml/BookListWidget.qml
)

# --- Install ---
install(TARGETS libsorter RUNTIME DESTINATION bin)
