include("C:/Users/kalle/OneDrive/Workspace/Programmieren/skui2/build/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/skui2-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE C:/Users/kalle/OneDrive/Workspace/Programmieren/skui2/build/skui2.exe
    GENERATE_QT_CONF
)
