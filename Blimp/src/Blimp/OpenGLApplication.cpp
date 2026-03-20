#include "pch.h"
#include "Blimp/OpenGLApplication.h"

#include "Blimp/Log.h"

namespace {
	constexpr int kWindowWidth = 1280;
	constexpr int kWindowHeight = 720;
	constexpr const char* kWindowTitle = "OpenGL Application";
}

namespace Blimp {
	OpenGLApplication::~OpenGLApplication() {
		Shutdown();
	}

	void OpenGLApplication::Run() {
		if (!Init()) {
			return;
		}

		glClearColor(0.08f, 0.10f, 0.14f, 1.0f);

		while (!glfwWindowShouldClose(m_Window)) {
			if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
				glfwSetWindowShouldClose(m_Window, GLFW_TRUE);
			}
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			CreateTriangle();
			
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

			glfwSwapBuffers(m_Window);
			glfwPollEvents();
		}
	}

	bool OpenGLApplication::Init() {
		if (m_Window != nullptr) {
			return true;
		}

		if (glfwInit() == GLFW_FALSE) {
			BLIMP_CORE_ERROR("Could not initialize GLFW for the OpenGL learning app.");
			return false;
		}
		m_GlfwInitialized = true;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_Window = glfwCreateWindow(kWindowWidth, kWindowHeight, kWindowTitle, nullptr, nullptr);
		if (m_Window == nullptr) {
			BLIMP_CORE_ERROR("Could not create the OpenGL learning window.");
			Shutdown();
			return false;
		}

		glfwMakeContextCurrent(m_Window);
		glfwSwapInterval(1);
		glfwSetFramebufferSizeCallback(m_Window, FramebufferSizeCallback);

		const int gladStatus = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
		if (gladStatus == 0) {
			BLIMP_CORE_ERROR("Could not initialize GLAD for the OpenGL learning app.");
			Shutdown();
			return false;
		}

		int framebufferWidth = 0;
		int framebufferHeight = 0;
		glfwGetFramebufferSize(m_Window, &framebufferWidth, &framebufferHeight);
		glViewport(0, 0, framebufferWidth, framebufferHeight);

		const char* renderer = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
		const char* version = reinterpret_cast<const char*>(glGetString(GL_VERSION));
		BLIMP_INFO("OpenGL renderer: {}", renderer != nullptr ? renderer : "<unknown>");
		BLIMP_INFO("OpenGL version: {}", version != nullptr ? version : "<unknown>");

		CreateTriangle();
		return true;
	}

	void OpenGLApplication::Shutdown() {
		DestroyTriangle();

		if (m_Window != nullptr) {
			glfwDestroyWindow(m_Window);
			m_Window = nullptr;
		}

		if (m_GlfwInitialized) {
			glfwTerminate();
			m_GlfwInitialized = false;
		}
	}

	void OpenGLApplication::CreateTriangle() {
		static constexpr float vertices[] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		static constexpr unsigned int indices[] = { 0, 1, 2 };

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		glGenBuffers(1, &m_VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		glGenBuffers(1, &m_IndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	}

	void OpenGLApplication::DestroyTriangle() {
		if (m_IndexBuffer != 0) {
			glDeleteBuffers(1, &m_IndexBuffer);
			m_IndexBuffer = 0;
		}

		if (m_VertexBuffer != 0) {
			glDeleteBuffers(1, &m_VertexBuffer);
			m_VertexBuffer = 0;
		}

		if (m_VertexArray != 0) {
			glDeleteVertexArrays(1, &m_VertexArray);
			m_VertexArray = 0;
		}
	}

	void OpenGLApplication::FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
		(void)window;
		glViewport(0, 0, width, height);
	}
}
