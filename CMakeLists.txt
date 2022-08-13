cmake_minimum_required(VERSION 3.6)

project(raytrace LANGUAGES CXX)

if(WIN32)
#Disables Boost's auto-linking, which often causes problems for me on Windows.
add_definitions( -DBOOST_ALL_NO_LIB )
endif(WIN32)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

if(APPLE)
	set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -std=c++14 -stdlib=libc++")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++")
endif(APPLE)

find_package(glue REQUIRED)
find_package(EIGEN REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(OpenCV REQUIRED)
find_package(SDL REQUIRED)
find_package(SDL_ttf REQUIRED)
find_package(Boost REQUIRED)
find_package(Boost COMPONENTS Filesystem System REQUIRED)
find_package(Assimp REQUIRED)
find_package(FLANN REQUIRED)


include_directories(include)
include_directories(${glue_INCLUDE_DIRS})
include_directories(${EIGEN_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${SDL_INCLUDE_DIRS})
include_directories(${SDL_ttf_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${ASSIMP_INCLUDE_DIRS})
include_directories(${FLANN_INCLUDE_DIRS})

add_library(ray
	include/raytrace/CameraModel.hpp
	src/CameraModel.cpp

	include/raytrace/CameraModelPinhole.hpp
	src/CameraModelPinhole.cpp

	include/Raytrace/CollisionInfo.hpp

	include/Raytrace/CollisionMask.hpp

	include/raytrace/Geometry.hpp
	src/Geometry.cpp

	include/raytrace/Object.hpp
	src/Object.cpp

	include/raytrace/Photon.hpp

	include/raytrace/PhotonMap.hpp
	src/PhotonMap.cpp

	include/raytrace/PhotonShaders.hpp
	src/PhotonShaders.cpp

	include/raytrace/Plane.hpp
	src/Plane.cpp

	include/raytrace/PointLight.hpp
	src/PointLight.cpp

	include/raytrace/Polynomial.hpp
	src/Polynomial.cpp

	include/raytrace/RandGen.hpp
	src/RandGen.cpp

	include/raytrace/Ray.hpp

	include/raytrace/Scene.hpp
	src/Scene.cpp

	include/raytrace/Shaders.hpp
	src/Shaders.cpp

	include/raytrace/Sphere.hpp
	src/Sphere.cpp
)

add_executable(DirectIlluminationDemo
	demo/DirectIlluminationDemo.cpp
)

target_link_libraries(DirectIlluminationDemo
	ray
	${SDL_ttf_LIBRARIES}
	${GLEW_LIBRARIES}
	${OPENGL_LIBRARIES}
	${OPENCV_LIBRARIES}
	${Boost_LIBRARIES}
	optimized ${glue_LIBRARIES_RELEASE}
	debug ${glue_LIBRARIES_DEBUG}
	${SDL_MAIN_LIBRARY}
	${SDL_LIBRARIES}
	optimized ${FLANN_LIBRARY_RELEASE}
	debug ${FLANN_LIBRARY_DEBUG}
)

add_executable(CausticMappingDemo
	demo/CausticMappingDemo.cpp
)

target_link_libraries(CausticMappingDemo
	ray
	${SDL_ttf_LIBRARIES}
	${GLEW_LIBRARIES}
	${OPENGL_LIBRARIES}
	${OPENCV_LIBRARIES}
	${Boost_LIBRARIES}
	optimized ${glue_LIBRARIES_RELEASE}
	debug ${glue_LIBRARIES_DEBUG}
	${SDL_MAIN_LIBRARY}
	${SDL_LIBRARIES}
	optimized ${FLANN_LIBRARY_RELEASE}
	debug ${FLANN_LIBRARY_DEBUG}
)
