#pragma once

#include "Express/Core/Core.hpp"

#include "Express/Events/Event.hpp"

namespace Express
{

	class Layer
	{
	public:
		Layer(const std::string& LayerName = "Default Layer");
		virtual ~Layer() = default;
		
		virtual void OnAttach() = 0;
		virtual void OnDetach() = 0;

		virtual void OnUpdate() = 0;
		virtual void OnImGuiRender() = 0;
		virtual void OnEvent(Event& e) = 0;

		inline const std::string& GetName() { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};

}