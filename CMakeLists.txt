cmake_minimum_required(VERSION 3.19)
project(BinaryTreeEditor LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets WebEngineWidgets)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

qt_add_executable(BinaryTreeEditor
    WIN32 MACOSX_BUNDLE
    src/main.cpp
    src/gui/mainwindow.cpp
    src/gui/mainwindow.h
    src/gui/mainwindow.ui
    res/resources.qrc
    src/models/binarytree.h
    src/models/binarytree.cpp
    src/gui/customgraphicsview.h
    src/gui/customgraphicsview.cpp
    src/gui/treeview.h src/gui/treeview.cpp
    src/gui/treenodeitem.h src/gui/treenodeitem.cpp
    src/gui/treescene.h src/gui/treescene.cpp
    src/utils/jsonserializer.h src/utils/jsonserializer.cpp
    src/utils/utils.h
    src/gui/paintwidget.h src/gui/paintwidget.cpp src/gui/paintwidget.ui
    src/gui/paintview.h src/gui/paintview.cpp

)


target_link_libraries(BinaryTreeEditor PRIVATE Qt6::Widgets)
target_include_directories(${PROJECT_NAME}
    PRIVATE
        src/gui
        src/utils
        src/models
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt6::WebEngineWidgets
)

include(GNUInstallDirs)

install(TARGETS BinaryTreeEditor
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET BinaryTreeEditor
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
