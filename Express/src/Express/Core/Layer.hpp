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
		
		virtual void OnAttach() {}
		virtual void OnDetach() {}

		virtual void OnUpdate() {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& e) {}

		inline const std::string& GetName() { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};

}