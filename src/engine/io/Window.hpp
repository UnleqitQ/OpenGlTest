#pragma once

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/freeglut.h>

#include "EventManager.hpp"

namespace engine::io {
	
	class Window {
	private:
		GLFWwindow* m_window;
		int m_width;
		int m_height;
		std::string m_title;
		EventManager m_event_manager;
	
	public:
		Window();
		Window(int width, int height, const std::string& title);
		
		Window(const Window&) = delete;
		Window(Window&&) = delete;
		Window& operator=(const Window&) = delete;
		Window& operator=(Window&&) = delete;
		~Window() = default;
		
		void create();
		void destroy();
		
		int width() const;
		int height() const;
		const std::string& title() const;
		
		void set_width(int width);
		void set_height(int height);
		void set_title(const std::string& title);
		
		const EventManager& event_manager() const;
		EventManager& event_manager();
		
		GLFWwindow* glfw_window() const;
	};
	
} // engine::io
