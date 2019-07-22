cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)

project(luftwaffle)
add_subdirectory(win)

add_executable(luftwaffle
	build/asset

	src/main.cpp
	src/luftwaffle.hpp
	src/objectdb.hpp
	src/worldobject.cpp
	src/worldobject.hpp

	src/entity/entity.cpp
	src/entity/entity.hpp

	src/component/component.hpp
	src/component/component.cpp

	src/system/system.hpp
	src/system/player.cpp
	src/system/toaster.cpp
	src/system/wander.cpp
	src/system/lasergun.cpp

	src/world.cpp
	src/world.hpp

	src/asset.cpp
	src/asset.hpp

	src/render/renderer.cpp
	src/render/renderer.hpp
	src/render/quad.cpp
)

# all the binary assets under /assets
file(GLOB_RECURSE assetfiles LIST_DIRECTORIES false ${CMAKE_CURRENT_LIST_DIR}/asset/*)

# my shaders also get packaged up in the asset roll
file(GLOB shaders ${CMAKE_CURRENT_LIST_DIR}/src/render/*.vert ${CMAKE_CURRENT_LIST_DIR}/src/render/*.frag)

list(APPEND assetfiles ${shaders})

# all the textures (and descriptor files), for the texture atlases
file(GLOB textures ${CMAKE_CURRENT_LIST_DIR}/asset/texture/*)

# make the main atlas
add_custom_command(
	OUTPUT
		${CMAKE_CURRENT_LIST_DIR}/asset/common.atlas
	COMMAND
		cd ${CMAKE_CURRENT_LIST_DIR}/asset/texture && atlas ${CMAKE_CURRENT_LIST_DIR}/asset/common.atlas ${CMAKE_CURRENT_LIST_DIR}/asset/texture/common.adesc
	DEPENDS
		${textures}
)

# make the grand asset roll
add_custom_command(
	OUTPUT
		${CMAKE_CURRENT_LIST_DIR}/build/asset
	COMMAND
		cd ${CMAKE_CURRENT_LIST_DIR} && roll ${CMAKE_CURRENT_LIST_DIR}/build/asset
	DEPENDS
		${assetfiles} ${CMAKE_CURRENT_LIST_DIR}/asset/common.atlas
)

target_link_libraries(luftwaffle PRIVATE win)
target_include_directories(luftwaffle PRIVATE win/include)
