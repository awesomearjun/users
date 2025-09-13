cmake_minimum_required(VERSION 3.24)
project(users)

# settings
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -03")

# libs
include(FetchContent)
FetchContent_Declare(
	asio
	GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
    GIT_TAG asio-1-36-0
)
FetchContent_MakeAvailable(asio)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

FetchContent_Declare(
	crow
	GIT_REPOSITORY https://github.com/CrowCpp/Crow.git
    GIT_TAG v1.2.1.2
)
FetchContent_MakeAvailable(crow)

set(SRCS
	server/main.cpp
)

add_executable(${PROJECT_NAME} ${SRCS})
target_link_libraries(${PROJECT_NAME} PRIVATE Crow::Crow)

file(GLOB TEMPLATE_FILES "${CMAKE_SOURCE_DIR}/templates/*")
file(COPY ${TEMPLATE_FILES} DESTINATION ${CMAKE_BINARY_DIR}/templates)
