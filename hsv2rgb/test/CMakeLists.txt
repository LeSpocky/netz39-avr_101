include_directories(
    "${PROJECT_SOURCE_DIR}/src"
)

add_executable(test_hsv2rgb
    "${PROJECT_SOURCE_DIR}/src/hsv2rgb.c"
    "test_hsv2rgb.c"
)

# f
add_test(NAME f
    COMMAND test_hsv2rgb f)

# hi8
add_test(NAME hi8
    COMMAND test_hsv2rgb hi8)

# p8
add_test(NAME p8
    COMMAND test_hsv2rgb p8)

# q8
add_test(NAME q8
    COMMAND test_hsv2rgb q8)

# t8
add_test(NAME t8
    COMMAND test_hsv2rgb t8)

# rgb
add_test(NAME rgb
    COMMAND test_hsv2rgb rgb)
