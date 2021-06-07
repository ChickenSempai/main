cmake_minimum_required(VERSION 3.0.0)

project(bigop-lib CXX)

set(Sources
	Cleanse.h
	CreationChamber.h
	Dimension.h
	Drone.h
  	EvolveChamber.h
	Existence.h
	Life.h
	StateViper.h
	Placeholder.cpp)
#set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
add_library(bigop-lib ${Sources})
#set_target_properties(bigop-lib PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(bigop-lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})