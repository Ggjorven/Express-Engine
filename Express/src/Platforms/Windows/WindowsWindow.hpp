#pragma once

#include "Express/Core/Window.hpp"

#include <GLFW/glfw3.h>

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

		static void ErrorCallBack(int errorCode, const char* description);
	private:
		static bool s_GLFWinitialized;

		GLFWwindow* m_window;
		WindowData m_data;
	};
}