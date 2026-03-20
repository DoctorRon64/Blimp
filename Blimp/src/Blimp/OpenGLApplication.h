#pragma once

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

namespace Blimp {
	class OpenGLApplication {
	public:
		OpenGLApplication() = default;
		~OpenGLApplication();

		void Run();

	private:
		bool Init();
		void Shutdown();
		void CreateTriangle();
		void DestroyTriangle();

		static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

	private:
		GLFWwindow* m_Window = nullptr;
		bool m_GlfwInitialized = false;

		unsigned int m_VertexArray = 0;
		unsigned int m_VertexBuffer = 0;
		unsigned int m_IndexBuffer = 0;
	};
}
