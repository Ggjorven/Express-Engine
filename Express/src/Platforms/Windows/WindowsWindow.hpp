#pragma once

#include "Express/Core/Window.hpp"

#include <GLFW/glfw3.h>

#include "Renderer/GraphicsContext.hpp"

namespace Express
{

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProperties properties);
		virtual ~WindowsWindow();

		void SetEventCallBack(EventCallBackFunction func) override { m_data.CallBack = func; }

		void OnUpdate() override;

		uint32_t GetWidth() const override { return m_data.Width; }
		uint32_t GetHeight() const override { return m_data.Height; }

		void SetVSync(bool enabled) override;
		bool IsVSync() const override { return m_data.Vsync; }

		void* GetNativeWindow() const override { return (void*)m_window; }

	private:
		bool Init(WindowProperties properties);
		void Shutdown();

		static void ErrorCallBack(int errorCode, const char* description);
	private:
		static bool s_GLFWinitialized;
		static uint32_t s_Instances;

		GLFWwindow* m_window;
		Scope<GraphicsContext> m_context;
		WindowData m_data;
	};
}