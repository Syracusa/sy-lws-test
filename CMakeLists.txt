cmake_minimum_required(VERSION 3.16)

project(lws-test)

set(CMAKE_BUILD_TYPE Debug)

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address -lcap)

set(LWS_DEPS
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



add_subdirectory(ref)