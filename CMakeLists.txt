cmake_minimum_required (VERSION 3.0 FATAL_ERROR)

project(kcd)

set(QT_MIN_VERSION     "5.6.0")
set(KF5_MIN_VERSION    "5.29.0")
set(PLASMA_MIN_VERSION "5.4.0")

find_package(ECM ${KF5_MIN_VERSION} REQUIRED NO_MODULE)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(QT_MIN_VERSION "5.3.0")
set(KF5_MIN_VERSION "5.2.0")
find_package(ECM 1.0.0 REQUIRED NO_MODULE)

set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# set up kf5

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(ECMInstallIcons)
include(ECMSetupVersion)
include(FeatureSummary)

find_package(
    Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS
        Core
        Concurrent
        Widgets
        DBus
        PrintSupport
        Quick
)

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

add_definitions(-DQT_NO_URL_CAST_FROM_STRING)
add_definitions(-DQT_USE_QSTRINGBUILDER)
add_definitions(-DQT_NO_CAST_FROM_ASCII)
add_definitions(-DQT_NO_CAST_TO_ASCII)
add_definitions(-DQT_NO_NARROWING_CONVERSIONS_IN_CONNECT)

add_executable(${PROJECT_NAME} "kcd.cpp" "kcdxml.cpp" "metadata.cpp" "parsekdesrc.cpp" kcdconfig.cpp)


target_link_libraries(
   kcd
        KF5::CoreAddons
        KF5::I18n
        KF5::ConfigCore
)

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)


