set(tasks_engine_SRCS
    tasksengine.cpp
    taskservice.cpp
    taskjob.cpp
    virtualdesktopssource.cpp
     taskwindowservice.cpp
   taskwindowjob.cpp
)

add_library(plasma_engine_tasks MODULE ${tasks_engine_SRCS})
target_link_libraries(plasma_engine_tasks
                      KF5::CoreAddons
                      KF5::Service
                      KF5::WindowSystem
                      KF5::Plasma
                      Qt5::DBus
                      legacytaskmanager)
kcoreaddons_desktop_to_json(plasma_engine_tasks plasma-dataengine-tasks.desktop)

install(TARGETS plasma_engine_tasks DESTINATION ${KDE_INSTALL_PLUGINDIR}/plasma/dataengine)
install(FILES plasma-dataengine-tasks.desktop DESTINATION ${KDE_INSTALL_KSERVICES5DIR})
install(FILES tasks.operations DESTINATION ${PLASMA_DATA_INSTALL_DIR}/services)
install(FILES windowtasks.operations DESTINATION ${PLASMA_DATA_INSTALL_DIR}/services)
