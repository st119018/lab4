cmake_minimum_required(VERSION 3.2) # specifies the minimum version of CMake the project needs
									# Version 3.2 provides a reasonably complete feature set for modern CMake techniques
project(lab4 C CXX)			# ensures compiler are able to compile and link successfully

add_executable(graph lab4.cpp DrawGraph.cpp Number.cpp Picture.cpp VerticesLayout.cpp) # Adds an executable target to be built from the source files listed in the command invocation
																					   # Target corresponds to the logical target name and must be globally unique within a project