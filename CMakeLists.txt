cmake_minimum_required(VERSION 3.2)

project(ip_filter)

add_executable(ip_filter ip_filter.cpp FilterLibrary.hpp)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)
add_executable(tests tests.cpp  FilterLibrary.hpp)

set_target_properties(ip_filter tests PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)
target_include_directories(ip_filter
    PRIVATE "${CMAKE_BINARY_DIR}"
)

install(TARGETS ip_filter tests RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

include(CPack)
