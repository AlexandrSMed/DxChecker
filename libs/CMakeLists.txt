# DirectX
list(APPEND LIB_TARGETS d3d11.lib dxgi.lib)
target_link_libraries(${PROJ_NAME} PRIVATE ${LIB_TARGETS})