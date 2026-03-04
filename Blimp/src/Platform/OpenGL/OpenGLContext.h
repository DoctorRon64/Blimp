#pragma once

#include "Blimp/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Blimp {
	class OpenGLContext : public GraphicsContext {
	public:
		OpenGLContext(GLFWwindow* window);
		virtual void Init() override;
		virtual void SwapBuffers() override;
		virtual void SetVSync(bool enabled) override;
		virtual bool IsVSync() const override;

	private:
		GLFWwindow* m_WindowHandle;
		bool m_VSync = false;
	};
}
