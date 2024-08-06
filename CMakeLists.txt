cmake_minimum_required(VERSION 3.28)
project(OpenGlTest)

find_package(OpenGL REQUIRED)

set(GLFW_DIR ${CMAKE_SOURCE_DIR}/libraries/GLFW)
set(FREEGLUT_DIR ${CMAKE_SOURCE_DIR}/libraries/freeglut)
set(GLEW_DIR ${CMAKE_SOURCE_DIR}/libraries/glew)

set(CMAKE_CXX_STANDARD 26)

include_directories(${GLFW_DIR}/include)
include_directories(${FREEGLUT_DIR}/include)
include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${GLEW_DIR}/include)

add_executable(OpenGlTest
	src/main.cpp

	src/engine/Camera.cpp
	src/engine/Camera.hpp
	src/engine/render/Shader.cpp
	src/engine/render/Shader.hpp

	src/engine/math/AxisAngle.cpp
	src/engine/math/AxisAngle.hpp
	src/engine/math/Mat2.cpp
	src/engine/math/Mat2.hpp
	src/engine/math/Mat3.cpp
	src/engine/math/Mat3.hpp
	src/engine/math/Mat4.cpp
	src/engine/math/Mat4.hpp
	src/engine/math/Quaternion.cpp
	src/engine/math/Quaternion.hpp
	src/engine/math/Vec2.cpp
	src/engine/math/Vec2.hpp
	src/engine/math/Vec3.cpp
	src/engine/math/Vec3.hpp
	src/engine/math/Vec4.cpp
	src/engine/math/Vec4.hpp
	src/engine/object/Mesh.cpp
	src/engine/object/Mesh.hpp
	src/engine/object/Object.cpp
	src/engine/object/Object.hpp
	src/engine/io/Window.cpp
	src/engine/io/Window.hpp
	src/engine/io/EventManager.cpp
	src/engine/io/EventManager.hpp
	src/engine/object/Renderable.hpp
	src/engine/render/RenderHelper.cpp
	src/engine/render/RenderHelper.hpp
	src/vendor/stb/stb_image.h
	src/vendor/stb/stb_image.cpp
	src/engine/object/Material.cpp
	src/engine/object/Material.hpp
	src/engine/graphics/Texture.cpp
	src/engine/graphics/Texture.hpp
	src/engine/graphics/TextureMixingMode.hpp
)

target_link_libraries(OpenGlTest ${GLFW_DIR}/lib-mingw-w64/libglfw3.a)
target_link_libraries(OpenGlTest ${GLEW_DIR}/lib/Release/x64/glew32.lib)
target_link_libraries(OpenGlTest ${FREEGLUT_DIR}/lib/x64/libfreeglut.a)
target_link_libraries(OpenGlTest ${OPENGL_LIBRARIES})


# Copy the DLLs to the build directory
add_custom_command(TARGET OpenGlTest POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${FREEGLUT_DIR}/bin/x64
	$<TARGET_FILE_DIR:OpenGlTest>
)
# copy the glew32.dll to the build directory
add_custom_command(TARGET OpenGlTest POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
	${CMAKE_SOURCE_DIR}/libraries/glew/bin/Release/x64/glew32.dll
	$<TARGET_FILE_DIR:OpenGlTest>
)
