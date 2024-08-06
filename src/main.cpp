#include <iostream>
#include <cmath>
#include <chrono>
#include <thread>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/freeglut.h>

#include "engine/math/Vec2.hpp"
#include "engine/math/Mat3.hpp"
#include "engine/Camera.hpp"
#include "engine/render/Shader.hpp"
#include "engine/object/Mesh.hpp"
#include "engine/object/Object.hpp"
#include "engine/io/Window.hpp"
#include "engine/render/RenderHelper.hpp"
#include "engine/object/Material.hpp"
#include "engine/graphics/TextureMixingMode.hpp"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"

// https://docs.gl/

const int GAME_FPS = 60;

engine::io::Window window(800, 600, "Engine");
engine::Camera camera;

engine::Shader shader_col_3d;
engine::Shader shader_tex_3d;
engine::Shader shader_tex_mix_3d;
engine::Shader shader_tex_refract_3d;

engine::graphics::Texture texture1;
engine::graphics::Texture texture2;
engine::graphics::Texture texture3;

engine::render::Material texture;
engine::render::Material offsetMap;
engine::render::Material heightMap;

//engine::render::Mesh _square_mesh;
engine::render::Mesh square_ring_mesh;
engine::render::Mesh square_mesh;
std::vector<engine::object::Object> objects;

void add_cube(engine::math::Vec3 position, float alpha = 1) {
	engine::render::Mesh& mesh = square_mesh;
	{
		engine::object::Object obj(mesh);
		obj.position() = engine::math::Vec3(0, 0, 1) + position;
		obj.rotation() = engine::math::Vec3(0, 0, 0);
		obj.scale() = engine::math::Vec3(1);
		obj.albedo() = engine::math::Vec4(1, 0, 0, alpha);
		objects.push_back(obj);
	}
	{
		engine::object::Object obj(mesh);
		obj.position() = engine::math::Vec3(0, 0, -1) + position;
		obj.rotation() = engine::math::Vec3(0, M_PI, 0);
		obj.scale() = engine::math::Vec3(1, 1, 1);
		obj.albedo() = engine::math::Vec4(1, 0, 0, alpha);
		objects.push_back(obj);
	}
	{
		engine::object::Object obj(mesh);
		obj.position() = engine::math::Vec3(-1, 0, 0) + position;
		obj.rotation() = engine::math::Vec3(0, -M_PI / 2, 0);
		obj.scale() = engine::math::Vec3(1, 1, 1);
		obj.albedo() = engine::math::Vec4(0, 1, 0, alpha);
		objects.push_back(obj);
	}
	{
		engine::object::Object obj(mesh);
		obj.position() = engine::math::Vec3(1, 0, 0) + position;
		obj.rotation() = engine::math::Vec3(0, M_PI / 2, 0);
		obj.scale() = engine::math::Vec3(1, 1, 1);
		obj.albedo() = engine::math::Vec4(0, 1, 0, alpha);
		objects.push_back(obj);
	}
	{
		engine::object::Object obj(mesh);
		obj.position() = engine::math::Vec3(0, 1, 0) + position;
		obj.rotation() = engine::math::Vec3(-M_PI / 2, 0, 0);
		obj.scale() = engine::math::Vec3(1, 1, 1);
		obj.albedo() = engine::math::Vec4(0, 0, 1, alpha);
		objects.push_back(obj);
	}
	{
		engine::object::Object obj(mesh);
		obj.position() = engine::math::Vec3(0, -1, 0) + position;
		obj.rotation() = engine::math::Vec3(M_PI / 2, 0, 0);
		obj.scale() = engine::math::Vec3(1, 1, 1);
		obj.albedo() = engine::math::Vec4(0, 0, 1, alpha);
		objects.push_back(obj);
	}
}

void on_mouse_move(GLFWwindow* window, double x, double y) {
}

void on_resize(GLFWwindow* window, int width, int height) {
	camera.aspect_ratio((float) width / height);
}

void on_key(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		switch (key) {
			case GLFW_KEY_ESCAPE:
				glfwSetWindowShouldClose(window, GLFW_TRUE);
				break;
			default:
				break;
		}
	}
}

void render_all() {
	engine::Shader& shader = shader_tex_mix_3d;
	std::vector<engine::object::Renderable*> renderables;
	for (auto& obj : objects) {
		renderables.push_back(&obj);
	}
	
	engine::render::RenderHelper::sortObjects(renderables, camera);
	
	shader.use();
	shader.set_mat4("projection", camera.projection_matrix());
	shader.set_mat4("view", camera.view_matrix());
	for (auto& obj : renderables) {
		shader.set_mat4("model", obj->get_model());
		shader.set_vec4("albedo", obj->get_albedo());
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture.id());
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, offsetMap.id());
		shader.set_int("textures", {0, 1});
		shader.set_int("mixModes",
			std::vector<int>({static_cast<int>(engine::graphics::TextureMixingMode::Multiply)}));
		shader.set_int("texCount", 2);
		
		obj->get_mesh().draw();
	}
	shader.release();
}

int main(int argc, char** argv) {
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return -1;
	}
	
	glutInit(&argc, argv);
	
	// Print GLFW, GLEW, and GLUT versions
	{
		std::cout << "Starting engine" << std::endl;
		const char* glfw_version = glfwGetVersionString();
		const unsigned char* glew_version = glewGetString(GLEW_VERSION);
		const int glut_version = glutGet(GLUT_VERSION);
		
		if (glfw_version == NULL)
			std::cout << "Failed to get GLFW version" << std::endl;
		else
			std::cout << "Using GLFW version " << glfw_version << std::endl;
		if (glew_version == NULL)
			std::cout << "Failed to get GLEW version" << std::endl;
		else
			std::cout << "Using GLEW version " << glew_version << std::endl;
		std::cout << "Using GLUT version " << glut_version << std::endl;
	}
	
	window.create();
	
	// Initialize GLEW
	{
		GLenum status = glewInit();
		if (status != GLEW_OK) {
			std::cerr << "Failed to initialize GLEW" << std::endl;
			std::cerr << glewGetErrorString(status) << std::endl;
			return -1;
		}
	}
	
	// Print OpenGL and GLSL versions
	{
		const unsigned char* gl_version = glGetString(GL_VERSION);
		const unsigned char* glsl_version = glGetString(GL_SHADING_LANGUAGE_VERSION);
		
		if (gl_version == NULL)
			std::cout << "Failed to get OpenGL version" << std::endl;
		else
			std::cout << "Using OpenGL version " << gl_version << std::endl;
		if (glsl_version == NULL)
			std::cout << "Failed to get GLSL version" << std::endl;
		else
			std::cout << "Using GLSL version " << glsl_version << std::endl;
		
		std::cout << std::endl;
	}
	
	glfwSetInputMode(window.glfw_window(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	
	camera = engine::Camera(90, (float) window.width() / window.height(), 0.1f, 1000.0f);
	camera.set_position(engine::math::Vec3(0, 0, 0));
	camera.set_rotation(engine::math::Vec3(0, 0, 0));
	
	window.event_manager().addMouseMoveCallback(on_mouse_move);
	window.event_manager().addResizeCallback(on_resize);
	window.event_manager().addKeyCallback(on_key);
	
	glfwSwapInterval(1);
	
	// Render settings
	{
		// Enable depth testing
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glClearDepth(1.0);
		
		// Enable blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glAlphaFunc(GL_GREATER, 0.1);
		
		// Enable face culling
		//glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);
		
		// Enable multisampling
		glEnable(GL_MULTISAMPLE);
		
	}
	
	shader_col_3d = engine::Shader("../res/shaders/color-3d.vert", "../res/shaders/color.frag");
	shader_tex_3d = engine::Shader("../res/shaders/tex-3d.vert", "../res/shaders/tex.frag");
	shader_tex_mix_3d = engine::Shader("../res/shaders/tex-3d.vert", "../res/shaders/tex_mix.frag");
	shader_tex_refract_3d = engine::Shader("../res/shaders/tex-3d.vert", "../res/shaders/tex_refract.frag");
	
	// Load the textures
	{
		texture1 = engine::graphics::Texture("../res/assets/Untitled.jpg").load();
		texture2 = engine::graphics::Texture("../res/assets/13391-normal.jpg").load();
		texture3 = engine::graphics::Texture("../res/assets/height.png").load();
		
		texture = engine::render::Material(texture1);
		offsetMap = engine::render::Material(texture2);
		heightMap = engine::render::Material(texture3);
	}
	
	// Create the square ring mesh
	{
		float inner_radius = 0.2;
		// Define the vertices for a square mesh with a black circle in the middle
		std::vector<engine::render::Vertex> vertices = {
			// Outer square vertices
			{engine::math::Vec3(-1, -1, 0),                       engine::math::Vec2(0, 0)},
			{engine::math::Vec3(1, -1, 0),                        engine::math::Vec2(1, 0)},
			{engine::math::Vec3(1, 1, 0),                         engine::math::Vec2(1, 1)},
			{engine::math::Vec3(-1, 1, 0),                        engine::math::Vec2(0, 1)},
			
			// Inner circle vertices (black)
			{engine::math::Vec3(-inner_radius, -inner_radius, 0), engine::math::Vec2(0.5 - inner_radius / 2,
				0.5 - inner_radius / 2)},
			{engine::math::Vec3(inner_radius, -inner_radius, 0),  engine::math::Vec2(0.5 + inner_radius / 2,
				0.5 - inner_radius / 2)},
			{engine::math::Vec3(inner_radius, inner_radius, 0),   engine::math::Vec2(0.5 + inner_radius / 2,
				0.5 + inner_radius / 2)},
			{engine::math::Vec3(-inner_radius, inner_radius, 0),  engine::math::Vec2(0.5 - inner_radius / 2,
				0.5 + inner_radius / 2)}
		};
		
		// Define the indices for the mesh
		std::vector<unsigned int> indices = {
			// Outer square
			0, 1, 4, 1, 5, 4,
			1, 2, 5, 2, 6, 5,
			2, 3, 6, 3, 7, 6,
			3, 0, 7, 0, 4, 7
		};
		
		// Create the Mesh object
		square_ring_mesh = engine::render::Mesh(vertices, indices);
	}
	
	// Create the square mesh
	{
		// Define the vertices for a square mesh
		std::vector<engine::render::Vertex> vertices = {
			{engine::math::Vec3(-1, -1, 0), engine::math::Vec2(0, 0)},
			{engine::math::Vec3(1, -1, 0),  engine::math::Vec2(1, 0)},
			{engine::math::Vec3(1, 1, 0),   engine::math::Vec2(1, 1)},
			{engine::math::Vec3(-1, 1, 0),  engine::math::Vec2(0, 1)}
		};
		
		// Define the indices for the mesh
		std::vector<unsigned int> indices = {0, 1, 3, 1, 2, 3};
		
		// Create the Mesh object
		square_mesh = engine::render::Mesh(vertices, indices);
		//square_mesh = engine::render::Mesh::fromHeightmap(texture3, 0.1, 40, 40);
	}
	
	/*int sl = 1;
	int dl = 4;
	for (int i = -sl; i <= sl; i++) {
		for (int j = -sl; j <= sl; j++) {
			for (int k = -sl; k <= sl; k++) {
				if (i == 0 && j == 0 && k == 0) continue;
				add_cube(engine::math::Vec3(i * dl, j * dl, k * dl));
			}
		}
	}*/
	add_cube(engine::math::Vec3(4, 0, 0), 0.5);
	add_cube(engine::math::Vec3(-4, 0, 0));
	
	{
		engine::object::Object obj(square_mesh);
		obj.position() = engine::math::Vec3(0, 0, -10);
		obj.rotation() = engine::math::Vec3(0, 0, 0);
		obj.scale() = engine::math::Vec3(5);
		obj.albedo() = engine::math::Vec4(1, 1, 1, 1);
		objects.push_back(obj);
	}
	
	std::chrono::milliseconds last_time = std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch()
	);
	camera.reset_mouse_pos();
	
	while (!glfwWindowShouldClose(window.glfw_window())) {
		std::chrono::milliseconds start_time = std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch()
		);
		
		std::chrono::milliseconds delta_time = start_time - last_time;
		last_time = start_time;
		
		camera.update(delta_time);
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		
		render_all();
		
		glfwSwapBuffers(window.glfw_window());
		window.event_manager().pollEvents();
		
		std::chrono::milliseconds end_time = std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch()
		);
		std::chrono::milliseconds elapsed_time = end_time - start_time;
		std::chrono::milliseconds sleep_time = std::chrono::milliseconds(1000 / GAME_FPS) - elapsed_time;
		if (sleep_time > std::chrono::milliseconds(0)) {
			std::this_thread::sleep_for(sleep_time);
		}
	}
	
	engine::Shader::destroyAll();
	engine::render::Mesh::destroyAll();
	engine::render::Material::destroyAll();
	engine::graphics::Texture::destroyAll();
	glfwTerminate();
	return 0;
}

#pragma clang diagnostic pop
