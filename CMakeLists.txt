cmake_minimum_required(VERSION 2.8.12)

project(kcd)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(QT_MIN_VERSION "5.3.0")
set(KF5_MIN_VERSION "5.2.0")
find_package(ECM 1.0.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(KCD_VERSION 0.1b)
set(VERSION_CODENAME "abide")

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings)
include(FeatureSummary)

# Find Qt modules
find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS
        Core
        Widgets
        )

# Find KDE modules
find_package(
    KF5 ${KF5_MIN_VERSION} REQUIRED
        CoreAddons     
        I18n            
        )

add_definitions(-DQT_NO_URL_CAST_FROM_STRING)
add_definitions(-DQT_USE_QSTRINGBUILDER)
add_definitions(-DQT_NO_NARROWING_CONVERSIONS_IN_CONNECT)
add_definitions(-DQT_NO_CAST_FROM_ASCII)
add_definitions(-DQT_NO_CAST_TO_ASCII)



add_executable(${PROJECT_NAME} kcd.cpp parsekdesrc.cpp metadata.cpp)


target_link_libraries(
   kcd
        KF5::CoreAddons
        KF5::I18n
)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
