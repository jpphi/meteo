cmake_minimum_required(VERSION 3.5)

project(meteo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(meteo ginfos.cpp)

install(TARGETS meteo
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

find_package(CURL REQUIRED)

if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${CURL_LIBRARIES})
endif()

find_package(JSON REQUIRED)

if (JSON_FOUND)
    include_directories(${QJSON_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${QJSON_LIBRARIES})
endif()
