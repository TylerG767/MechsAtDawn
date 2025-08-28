cmake_minimum_required(VERSION 3.10)
project(MechsAtDawn)

set(CMAKE_CXX_STANDARD 17)

# Set source and include directories
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

# Add raylib (assumes raylib is installed system-wide or via vcpkg)
find_package(raylib 4.0 REQUIRED)

include_directories(${INCLUDE_DIR})

add_executable(MechsAtDawn 
    ${SRC_DIR}/main.cpp 
    ${SRC_DIR}/game.cpp 
    ${SRC_DIR}/Player.cpp 
    ${SRC_DIR}/Bullet.cpp 
    ${SRC_DIR}/Enemy.cpp 
    ${SRC_DIR}/XPOrb.cpp
    ${SRC_DIR}/LevelUpUI.cpp
    ${SRC_DIR}/ScalingSystem.cpp
    ${SRC_DIR}/PlayerSystem.cpp
    ${SRC_DIR}/EnemySystem.cpp
    ${SRC_DIR}/XPSystem.cpp
    ${SRC_DIR}/CollisionSystem.cpp
)

target_link_libraries(MechsAtDawn raylib)

# Copy assets to build directory after build
add_custom_command(TARGET MechsAtDawn POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:MechsAtDawn>/assets)
