#include "EventManager.hpp"
#include "Window.hpp"

namespace engine::io {
	EventManager::EventManager()
		: m_window(nullptr), m_resizeCallbacks(), m_keyCallbacks(), m_mouseMoveCallbacks(), m_mouseButtonCallbacks() {
	}
	EventManager::EventManager(GLFWwindow* window)
		: m_window(window), m_resizeCallbacks(), m_keyCallbacks(), m_mouseMoveCallbacks(), m_mouseButtonCallbacks() {
		setCallbacks(window);
	}
	const GLFWwindow* EventManager::getWindow() const {
		return m_window;
	}
	void EventManager::addResizeCallback(GLFWwindowsizefun callback) {
		m_resizeCallbacks.push_back(callback);
	}
	void EventManager::addKeyCallback(GLFWkeyfun callback) {
		m_keyCallbacks.push_back(callback);
	}
	void EventManager::addMouseMoveCallback(GLFWcursorposfun callback) {
		m_mouseMoveCallbacks.push_back(callback);
	}
	void EventManager::addMouseButtonCallback(GLFWmousebuttonfun callback) {
		m_mouseButtonCallbacks.push_back(callback);
	}
	void EventManager::removeResizeCallback(GLFWwindowsizefun callback) {
		erase_if(m_resizeCallbacks, [callback](GLFWwindowsizefun& cb) {
			return cb == callback;
		});
	}
	void EventManager::removeKeyCallback(GLFWkeyfun callback) {
		erase_if(m_keyCallbacks, [callback](GLFWkeyfun& cb) {
			return cb == callback;
		});
	}
	void EventManager::removeMouseMoveCallback(GLFWcursorposfun callback) {
		erase_if(m_mouseMoveCallbacks, [callback](GLFWcursorposfun& cb) {
			return cb == callback;
		});
	}
	void EventManager::removeMouseButtonCallback(GLFWmousebuttonfun callback) {
		erase_if(m_mouseButtonCallbacks, [callback](GLFWmousebuttonfun& cb) {
			return cb == callback;
		});
	}
	void EventManager::pollEvents() const {
		glfwPollEvents();
	}
	void EventManager::waitEvents() const {
		glfwWaitEvents();
	}
	void EventManager::waitEventsTimeout(double timeout) const {
		glfwWaitEventsTimeout(timeout);
	}
	void EventManager::setCallbacks(GLFWwindow* window) {
		glfwSetWindowSizeCallback(window, [](GLFWwindow* win, int width, int height) {
			Window* w = static_cast<Window*>(glfwGetWindowUserPointer(win));
			EventManager* em = &w->event_manager();
			for (auto& cb : em->m_resizeCallbacks) {
				cb(win, width, height);
			}
		});
		glfwSetKeyCallback(window, [](GLFWwindow* win, int key, int scancode, int action, int mods) {
			Window* w = static_cast<Window*>(glfwGetWindowUserPointer(win));
			EventManager* em = &w->event_manager();
			for (auto& cb : em->m_keyCallbacks) {
				cb(win, key, scancode, action, mods);
			}
		});
		glfwSetCursorPosCallback(window, [](GLFWwindow* win, double x, double y) {
			Window* w = static_cast<Window*>(glfwGetWindowUserPointer(win));
			EventManager* em = &w->event_manager();
			for (auto& cb : em->m_mouseMoveCallbacks) {
				cb(win, x, y);
			}
		});
		glfwSetMouseButtonCallback(window, [](GLFWwindow* win, int button, int action, int mods) {
			Window* w = static_cast<Window*>(glfwGetWindowUserPointer(win));
			EventManager* em = &w->event_manager();
			for (auto& cb : em->m_mouseButtonCallbacks) {
				cb(win, button, action, mods);
			}
		});
	}
	
} // engine::io