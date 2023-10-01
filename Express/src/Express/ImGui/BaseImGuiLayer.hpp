#pragma once

#include "Express/Core/Core.hpp"

#include "Express/Core/Layer.hpp"

namespace Express
{

	class BaseImGuiLayer : public Layer
	{
	public:
		BaseImGuiLayer();
		virtual ~BaseImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void Begin();
		void End();
	};

}