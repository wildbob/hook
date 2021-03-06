#pragma once
#include "basecontrol.h"

class c_window : public c_control
{
public:
	int categoryXoffset, dragYoffset;

	bool BlockInput = false;
	c_control* BlockingElement = nullptr;

	bool bDragging;
	bool IsMainWindow = false;
	bool bMouse1pressed,
		bMouse2pressed,
		bMouse1released,
		bMouse2released;
	bool moved_in_that_frame = false;
	bool ToggleButton(int code);
	bool GetKeyPress(unsigned int key);
	void ClickHandler();
	bool Clicked(Vector position, Vector bounds);
	bool InBounds(Vector position, Vector bounds);
	c_window(std::string name, Vector pos, Vector size, bool IsMainWindow);
	POINT Cur;

	void DrawMouseCursor();
	virtual void Draw() override;
};