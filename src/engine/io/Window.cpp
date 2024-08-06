#include "Window.hpp"
#include <iostream>

namespace engine::io {
	Window::Window()
		: m_window(nullptr), m_width(0), m_height(0), m_title("Untitled"), m_event_manager() {
	}
	Window::Window(int width, int height, const std::string& title)
		: m_window(nullptr), m_width(width), m_height(height), m_title(title), m_event_manager() {
	}
	void Window::create() {
		// We assume everything is already initialized
		m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
		if (!m_window) {
			std::cerr << "Failed to create window" << std::endl;
			return;
		}
		glfwMakeContextCurrent(m_window);
		
		// Set window user pointer
		glfwSetWindowUserPointer(m_window, this);
		
		// Create event manager
		m_event_manager = EventManager(m_window);
		
		// Set GLFW callbacks
		m_event_manager.addResizeCallback([](GLFWwindow* window, int width, int height) {
			Window* w = static_cast<Window*>(glfwGetWindowUserPointer(window));
			w->m_width = width;
			w->m_height = height;
			glViewport(0, 0, width, height);
		});
	}
	void Window::destroy() {
		glfwDestroyWindow(m_window);
		m_window = nullptr;
	}
	int Window::width() const {
		return m_width;
	}
	int Window::height() const {
		return m_height;
	}
	const std::string& Window::title() const {
		return m_title;
	}
	void Window::set_width(int width) {
		m_width = width;
		glfwSetWindowSize(m_window, m_width, m_height);
		glViewport(0, 0, m_width, m_height);
	}
	void Window::set_height(int height) {
		m_height = height;
		glfwSetWindowSize(m_window, m_width, m_height);
		glViewport(0, 0, m_width, m_height);
	}
	void Window::set_title(const std::string& title) {
		m_title = title;
		glfwSetWindowTitle(m_window, m_title.c_str());
	}
	const EventManager& Window::event_manager() const {
		return m_event_manager;
	}
	EventManager& Window::event_manager() {
		return m_event_manager;
	}
	GLFWwindow* Window::glfw_window() const {
		return m_window;
	}
} // engine::io