#pragma once

#include "Balun/Core/Layer.h"

#include "Balun/Events/ApplicationEvent.h"
#include "Balun/Events/KeyEvent.h"
#include "Balun/Events/MouseEvent.h"

namespace Balun {

	class BALUN_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}