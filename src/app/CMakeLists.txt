qt_add_executable(CSC341_11
    main.cpp mainwidget.cpp
)

target_link_libraries(CSC341_11 PRIVATE Qt6::Widgets)

set_target_properties(CSC341_11 PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)