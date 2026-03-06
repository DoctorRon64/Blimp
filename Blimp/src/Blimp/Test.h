#pragma once

#include <GLAD/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "Log.h"

namespace Blimp {
    class Test {
    public:
        void Init() {
            window = nullptr;

            BLIMP_CORE_ASSERT(glfwInit(), "Cannot initialize glfw!");

            // Create a window and OpenGL context.
            window = glfwCreateWindow(1280, 480, "HELLO WORLD", nullptr, nullptr);
            if (!window) {
                glfwTerminate();
                BLIMP_CORE_ASSERT(window, "Cannot initialize window!");
                return;
            }

            glfwMakeContextCurrent(window);

            int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
            BLIMP_CORE_ASSERT(status, "Cannot initialize Glad!");

            const char* version = reinterpret_cast<const char*>(glGetString(GL_VERSION));
            BLIMP_INFO("OpenGL Version: {}", version ? version : "<null>");
        }

        void Run() {
            while (!glfwWindowShouldClose(window)) {
                glClear(GL_COLOR_BUFFER_BIT);

                //triangle
                glBegin(GL_TRIANGLES);
                glVertex2f(-0.5f, -0.5f);
                glVertex2f(0.0f, 0.5f);
                glVertex2f(0.5f, -0.5f);
                glEnd();

                glfwSwapBuffers(window);
                glfwPollEvents();
            }

            Terminate();
        }

        private:
        void Terminate() {
            glfwDestroyWindow(window);
            glfwTerminate();
        }

        private:
        GLFWwindow* window;
    };
}
