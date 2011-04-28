#ifndef BUTTON_H
#define BUTTON_H

#include "Component.h"

namespace SenGUI
{
	class Button : public Component
	{
	public:
		Button();

		bool IsClicked(int mouseX, int mouseY);

	private:
		void UpdateImage();

	};
}

#endif