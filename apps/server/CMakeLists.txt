add_executable(lws-server main.c ss-server.c)

target_link_libraries(lws-server 
${PROJECT_SOURCE_DIR}/libwebsockets/build/lib/libwebsockets.a
# Linking mbedtls libs twice is not a mistake.  
# https://forums.mbed.com/t/static-build-failing/7514
${PROJECT_SOURCE_DIR}/mbedtls/build/library/libmbedcrypto.a
${PROJECT_SOURCE_DIR}/mbedtls/build/library/libmbedtls.a
${PROJECT_SOURCE_DIR}/mbedtls/build/library/libmbedx509.a
${PROJECT_SOURCE_DIR}/mbedtls/build/library/libmbedcrypto.a
${PROJECT_SOURCE_DIR}/mbedtls/build/library/libmbedtls.a
${PROJECT_SOURCE_DIR}/mbedtls/build/library/libmbedx509.a
)

target_include_directories(lws-server PUBLIC
                          "${PROJECT_SOURCE_DIR}/libwebsockets/build"
                          "${PROJECT_SOURCE_DIR}/libwebsockets/include"
                          "${PROJECT_SOURCE_DIR}/mbedtls/include"
                          "${PROJECT_SOURCE_DIR}/mbedtls/build/include"
                          ) 