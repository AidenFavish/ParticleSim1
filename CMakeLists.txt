cmake_minimum_required(VERSION 3.10)

# Set the project name
project(MySFMLApp)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the paths for SFML
set(SFML_INCLUDE_DIR "/opt/homebrew/Cellar/sfml/2.6.1/include")
set(SFML_LIBRARY_DIR "/opt/homebrew/Cellar/sfml/2.6.1/lib")

# Include SFML directories
include_directories(${SFML_INCLUDE_DIR})

# Link SFML libraries
link_directories(${SFML_LIBRARY_DIR})

# Add the executable with multiple source files
add_executable(MySFMLApp main.cpp Simulator.cpp Simulator.h Particle.cpp Particle.h)

# Link SFML libraries
target_link_libraries(MySFMLApp sfml-graphics sfml-window sfml-system sfml-network sfml-audio)

# Copy assets folder to the build directory
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

