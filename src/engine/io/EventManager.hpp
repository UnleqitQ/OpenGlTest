#pragma once

#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace engine::io {
	
	class EventManager {
	private:
		GLFWwindow* m_window;
		
		std::vector<GLFWwindowsizefun> m_resizeCallbacks;
		std::vector<GLFWkeyfun> m_keyCallbacks;
		std::vector<GLFWcursorposfun> m_mouseMoveCallbacks;
		std::vector<GLFWmousebuttonfun> m_mouseButtonCallbacks;
	
	public:
		EventManager();
		EventManager(GLFWwindow* window);
		
		EventManager(const EventManager&) = default;
		EventManager(EventManager&&) = default;
		EventManager& operator=(const EventManager&) = default;
		EventManager& operator=(EventManager&&) = default;
		~EventManager() = default;
		
		const GLFWwindow* getWindow() const;
		
		void addResizeCallback(GLFWwindowsizefun callback);
		void addKeyCallback(GLFWkeyfun callback);
		void addMouseMoveCallback(GLFWcursorposfun callback);
		void addMouseButtonCallback(GLFWmousebuttonfun callback);
		
		void removeResizeCallback(GLFWwindowsizefun callback);
		void removeKeyCallback(GLFWkeyfun callback);
		void removeMouseMoveCallback(GLFWcursorposfun callback);
		void removeMouseButtonCallback(GLFWmousebuttonfun callback);
		
		void pollEvents() const;
		void waitEvents() const;
		void waitEventsTimeout(double timeout) const;
		
		static void setCallbacks(GLFWwindow* win);
	};
	
} // engine::io
