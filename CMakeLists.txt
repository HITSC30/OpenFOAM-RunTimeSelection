set(projectNameOfSelfDict Demo06_07)

add_executable(
    ${projectNameOfSelfDict}
    01.cpp
    src/class_Base.cpp
    src/class_DerivedA.cpp
    src/class_DerivedB.cpp
)

target_include_directories(
    ${projectNameOfSelfDict}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
