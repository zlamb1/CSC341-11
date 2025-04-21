set(DEFAULT_UI_LIB "Qt")

if(DEFINED ENV{UI_LIB})
    set(UI_LIB $ENV{UI_LIB})
else()
    set(UI_LIB ${DEFAULT_UI_LIB})
endif()

if(UI_LIB STREQUAL "Qt")
    file(GLOB_RECURSE SOURCE_FILES data/*.cpp service/*.cpp ui/*.cpp)
    qt_add_executable(${CMAKE_PROJECT_NAME} main.cpp ${SOURCE_FILES})

    target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE . ./ui/qt)
    target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Qt6::Core Qt6::Widgets)
    set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
        WIN32_EXECUTABLE ON
        MACOSX_BUNDLE ON
    )
else()
    message(FATAL_ERROR "Unknown UI_LIB (${UI_LIB}) Specified.")
endif()

