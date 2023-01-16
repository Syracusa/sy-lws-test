add_executable(simple-server server.c)

target_link_libraries(simple-server ${LWS_DEPS})

target_include_directories(lws-server PUBLIC
                          "${PROJECT_SOURCE_DIR}/libwebsockets/build"
                          "${PROJECT_SOURCE_DIR}/libwebsockets/include"
                          "${PROJECT_SOURCE_DIR}/mbedtls/include"
                          "${PROJECT_SOURCE_DIR}/mbedtls/build/include"
                          ) 