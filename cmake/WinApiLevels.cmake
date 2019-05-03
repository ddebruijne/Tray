add_library(tray_full_winapi INTERFACE)
target_link_libraries(tray_full_winapi
    INTERFACE tray_base
)
add_library(tray::tray_full_winapi ALIAS tray_full_winapi)

add_library(tray INTERFACE)
target_link_libraries(tray
    INTERFACE tray_full_winapi
)
target_compile_definitions(tray
    INTERFACE WIN32_LEAN_AND_MEAN NOMINMAX
)
install(TARGETS tray_full_winapi EXPORT trayConfig)
