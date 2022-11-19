# DirectX
list(APPEND LIB_TARGETS d3d11 dxgi dxguid) #dxguid is only required for portable UUIDS (like IID_IDXGIFactory1)

target_link_libraries(${PROJ_NAME} PRIVATE ${LIB_TARGETS})