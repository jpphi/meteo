cmake_minimum_required(VERSION 3.5)

project(meteo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(meteo main.cpp)

install(TARGETS meteo
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

find_package(CURL REQUIRED)

if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${CURL_LIBRARIES})

endif()
