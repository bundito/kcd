cmake_minimum_required (VERSION 3.0 FATAL_ERROR)

project(kcd)
set(KCD_VERSION 0.4b)

set(QT_MIN_VERSION     "5.6.0")
set(KF5_MIN_VERSION    "5.29.0")
set(PLASMA_MIN_VERSION "5.4.0")

find_package(ECM ${KF5_MIN_VERSION} REQUIRED NO_MODULE)

# Generated header file for kcp.cpp
configure_file(Config.h.in Config.h)

# Settings variables / QT & KF5 minimum versions
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(QT_MIN_VERSION "5.3.0")
set(KF5_MIN_VERSION "5.2.0")
find_package(ECM 1.0.0 REQUIRED NO_MODULE)

set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# CMake includes
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(ECMInstallIcons)
include(ECMSetupVersion)
include(FeatureSummary)

# QT packages
find_package(
    Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS
        Core
        Concurrent
        Widgets
        DBus
        PrintSupport
        Quick
        XmlPatterns
        Xml
        Sql
)

# KF5 packages
find_package(
    KF5 ${KF5_MIN_VERSION} REQUIRED
        CoreAddons
        WidgetsAddons
        DBusAddons
        Notifications
        Config
        I18n
        KIO
        XmlGui
        WindowSystem
        DocTools
        Declarative
        NewStuff
)

# Source files to be included
set ( KCD_SOURCES
        kcd.cpp
        kcdxml.cpp
        metadata.cpp
        parsekdesrc.cpp
        kcdconfig.cpp
        kcddatabase.cpp
)

# Executable creation = ('kcd' + all .cpp files from list above)
# NOTE: must be listed before target_link_libraries
add_executable(${PROJECT_NAME} ${KCD_SOURCES})

# Link libraries (Qt5::Sql needed for <QSqlQuery>
target_link_libraries(
   kcd
        KF5::CoreAddons
        KF5::I18n
        KF5::ConfigCore
        Qt5::Sql
)

# Misc CMake options ('NO_CAST*ASCII` for KDE translation)
add_definitions(-DQT_NO_URL_CAST_FROM_STRING)
add_definitions(-DQT_USE_QSTRINGBUILDER)
add_definitions(-DQT_NO_CAST_FROM_ASCII)
add_definitions(-DQT_NO_CAST_TO_ASCII)
add_definitions(-DQT_NO_NARROWING_CONVERSIONS_IN_CONNECT)


# More misc CMake directives
feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
