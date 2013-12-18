include_directories(
    "${PROJECT_SOURCE_DIR}/src"
)

# list_create
add_executable(test_hsv2rgb
    "${PROJECT_SOURCE_DIR}/src/hsv2rgb.c"
    "test_hsv2rgb.c"
)
add_test(hsv2rgb ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_hsv2rgb)
