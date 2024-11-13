cmake_minimum_required(VERSION 3.16)

project(my_qt_project LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/qt/lib/cmake")

find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(SQLite3 REQUIRED)

include_directories("/opt/homebrew/include")

set(SOURCES
    Shop.cpp
    Sale.cpp
    Product.cpp
    Person.cpp
    Seller.cpp
    Manager.cpp
    AdminSeller.cpp
    main.cpp
    Mainwindow.cpp
    ReportWindow.cpp
)

qt6_wrap_cpp(MOC_SOURCES
    ../Headers/Mainwindow.hpp
    ../Headers/ReportWindow.hpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${MOC_SOURCES})

target_link_libraries(${PROJECT_NAME} Qt6::Widgets SQLite::SQLite3 /opt/homebrew/lib/libxlsxwriter.dylib)