#pragma once

#include "Express/Core/Core.hpp"

#include "Express/Core/TimeStep.hpp"
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

		virtual void OnUpdate(TimeStep& ts) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& e) {}

		inline const std::string& GetName() { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};

}