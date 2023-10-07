#pragma once

#include <Express/Express.hpp>

#include <glm/glm.hpp>
#include <imgui.h>

#include <thread>

class CustomImGuiLayer : public Express::Layer
{
public:
	CustomImGuiLayer() 
		: m_WindowFlags(0)
	{}
	virtual ~CustomImGuiLayer() {}

	void OnAttach() override
	{
		/*
		m_WindowFlags = ImGuiWindowFlags_MenuBar;
		EX_TRACE("Window flags: {0}", m_WindowFlags);

		std::this_thread::sleep_for(static_cast<std::chrono::milliseconds>(3000));

		m_WindowFlags = m_WindowFlags | ImGuiWindowFlags_NoDecoration;
		EX_TRACE("Window flags: {0}", m_WindowFlags);
		*/
	}

	void OnUpdate(Express::TimeStep& ts) override
	{

	}

	void OnRender() override
	{

	}

	void OnImGuiRender() override
	{
		//ImGui::ShowStyleEditor();
		// 
		//Initialize style
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));


		//ImGui::PushStyleColor(ImGuiCol_MenuBarBg, ImVec4(0.6f, 0.1f, 0.1f, 1.0f));

		ImGui::PushStyleColor(ImGuiCol_Tab, ImVec4(0.3f, 0.1f, 0.1f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_TabActive, ImVec4(0.7f, 0.1f, 0.1f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.48f, 0.16f, 0.16f, 0.54f));
		ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0.98f, 0.26f, 0.26f, 0.40f));
		ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(0.98f, 0.26f, 0.26f, 0.67f));
		ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.48f, 0.16f, 0.16f, 1.00f));
		ImGui::PushStyleColor(ImGuiCol_CheckMark, ImVec4(0.98f, 0.26f, 0.26f, 1.00f));
		ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(0.88f, 0.24f, 0.24f, 1.00f));
		ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(0.98f, 0.26f, 0.26f, 1.00f));
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.98f, 0.26f, 0.26f, 0.40f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.98f, 0.26f, 0.26f, 1.00f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.98f, 0.06f, 0.06f, 1.00f));
		ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.98f, 0.26f, 0.26f, 0.31f));
		ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0.98f, 0.26f, 0.26f, 0.80f));
		ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(0.98f, 0.26f, 0.26f, 1.00f));
		ImGui::PushStyleColor(ImGuiCol_Separator, ImVec4(0.50f, 0.43f, 0.43f, 0.50f));
		ImGui::PushStyleColor(ImGuiCol_SeparatorHovered, ImVec4(0.75f, 0.10f, 0.10f, 0.78f));
		ImGui::PushStyleColor(ImGuiCol_SeparatorActive, ImVec4(0.75f, 0.10f, 0.10f, 1.00f));
		ImGui::PushStyleColor(ImGuiCol_ResizeGrip, ImVec4(0.98f, 0.26f, 0.26f, 0.20f));
		ImGui::PushStyleColor(ImGuiCol_ResizeGripHovered, ImVec4(0.98f, 0.26f, 0.26f, 0.67f));
		ImGui::PushStyleColor(ImGuiCol_ResizeGripActive, ImVec4(0.98f, 0.26f, 0.26f, 0.95f));
		ImGui::PushStyleColor(ImGuiCol_TabHovered, ImVec4(0.98f, 0.26f, 0.26f, 0.80f));
		ImGui::PushStyleColor(ImGuiCol_TabUnfocusedActive, ImVec4(0.42f, 0.14f, 0.14f, 1.00f));
		ImGui::PushStyleColor(ImGuiCol_DockingPreview, ImVec4(0.98f, 0.26f, 0.26f, 0.70f));
		ImGui::PushStyleColor(ImGuiCol_TextSelectedBg, ImVec4(0.98f, 0.26f, 0.26f, 0.35f));
		ImGui::PushStyleColor(ImGuiCol_NavHighlight, ImVec4(0.98f, 0.26f, 0.26f, 1.00f));

		//Create window
		ImGui::Begin("Custom", nullptr, ImGuiWindowFlags_MenuBar);

		//ImGui::ShowStyleEditor();

		///*
		if (ImGui::BeginMenu("One"))
		{
			if (ImGui::MenuItem("Two"))
			{
				EX_INFO("Two pressed...");
			}

			ImGui::EndMenu();
		}
		//*/

		///*
		//* //Top Menu bar in the GLFW window
		//* 
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("Test"))
			{
				if (ImGui::MenuItem("Test2"))
				{
					EX_WARN("Test2 pressed...");
				}

				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}
		//*/
		
		///*
		if (ImGui::BeginChild("abc"))
		{
			if (ImGui::BeginPopup("abc"));
				//ImGui::OpenPopup("abc");
		}
		ImGui::EndChild();
		//*/
		
		///*
		ImGui::BeginTabBar("TabBar");
		if (ImGui::BeginTabItem("Tab"))
		{
			ImGui::Text("Tab text");

			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Tab1"))
		{
			ImGui::Text("Tab text 1");

			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
		//*/

		///*
		if (ImGui::BeginCombo("Combo", "Press"))
		{
			ImGui::Text("Item1");
			ImGui::SliderFloat("Item2", &m_Float, 0.0f, 1.0f);

			ImGui::EndCombo();
		}
		//*/

		///*
		//* //Top Menu bar in the ImGui window
		//* 
		ImGui::BeginMenuBar();
		if (ImGui::BeginMenu("Item 1"))
		{
			if (ImGui::MenuItem("Clickable"))
			{
				EX_WARN("Clicked");
			}

			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
		//*/

		//End of  Window
		ImGui::End();


		//Delete style
		ImGui::PopStyleVar(1);
		ImGui::PopStyleColor(26);
	}

	void OnEvent(Express::Event& e) override
	{

	}

private:
	ImGuiWindowFlags m_WindowFlags;
	float m_Float = 0;
};