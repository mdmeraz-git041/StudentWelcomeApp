cmake_minimum_required(VERSION 3.20)

project(StudentWelcomeApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Crow CONFIG REQUIRED)

add_executable(StudentWelcomeApp main.cpp)

target_link_libraries(
    StudentWelcomeApp
    PRIVATE Crow::Crow
)