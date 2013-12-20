include_directories(
    "${PROJECT_SOURCE_DIR}/src"
)

add_executable(test_hsv2rgb
    "${PROJECT_SOURCE_DIR}/src/hsv2rgb.c"
    "test_hsv2rgb.c"
)

# hi8
add_test(NAME hi8
    COMMAND test_hsv2rgb hi8)

# p8
add_test(NAME p8
    COMMAND test_hsv2rgb p8)
