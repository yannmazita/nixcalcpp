# Creating target
add_library(calculator ${PROJECT_SOURCE_DIR}/lib/calc/calculator.cpp)
# Defining target properties
target_include_directories(calculator
    PUBLIC
        $<INSTALL_INTERFACE:include/calc>
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/calc>
)
target_compile_features(calculator PRIVATE cxx_std_20)
