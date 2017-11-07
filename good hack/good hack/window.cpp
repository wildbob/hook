#pragma once
#include "window.h"
#include "menu.h"
#include "drawings.h"


#pragma region keyshit
bool keys[256];
bool oldKeys[256];

#pragma endregion
#pragma region input
bool c_window::ToggleButton(int code)
{
	static int buttonPressedTick = 0;
	if (GetAsyncKeyState(code) && (GetTickCount64() - buttonPressedTick) > 150)
	{
		buttonPressedTick = GetTickCount64();
		return true;
	}
	return false;
}
bool c_window::GetKeyPress(unsigned int key)
{
	if (keys[key] == true && oldKeys[key] == false)
		return true;
	else
		return false;
}

void c_window::ClickHandler()
{
	if ((GetAsyncKeyState(VK_LBUTTON)))
	{
		bMouse1pressed = true;
	}
	else if (!(GetAsyncKeyState(VK_LBUTTON)))
	{
		if (bMouse1pressed)
			bMouse1released = true;
		else
		{
			bMouse1released = false;
		}
		bMouse1pressed = false;
	}

	if ((GetAsyncKeyState(VK_RBUTTON)))
	{
		bMouse2pressed = true;
	}
	else if (!(GetAsyncKeyState(VK_RBUTTON)))
	{
		if (bMouse2pressed)
			bMouse2released = true;
		else
		{
			bMouse2released = false;
		}
		bMouse2pressed = false;
	}
}
bool c_window::Clicked(Vector position, Vector bounds)
{

	return (Cur.x > position.x && Cur.y > position.y &&
		Cur.x < position.x + bounds.x && Cur.y < position.y + bounds.y &&
		bMouse1released);//ToggleButton(VK_LBUTTON));
}

bool c_window::InBounds(Vector position, Vector bounds)
{

	return (Cur.x > position.x && Cur.y > position.y &&
		Cur.x < position.x + bounds.x && Cur.y < position.y + bounds.y);
}
#pragma endregion
c_window::c_window(std::string name, Vector pos, Vector size, bool IsMainWindow)
{
	this->name = name;
	this->position = pos;
	this->size = size;
	this->visible = false;
	this->bDragging = false;
	this->IsMainWindow = IsMainWindow;
	categoryXoffset = 100;// this->size.x / 5.3333333f;
	dragYoffset = 25;// this->size.y / 10;
					 //init move
	this->moved_in_that_frame = true;
}



void c_window::Draw()
{
	static bool risetotop = false;
	static bool risetobottom = false;
	if (ToggleButton(VK_INSERT))
	{
		this->visible = !this->visible;
		char buf[32];
		sprintf_s(buf, "cl_mouseenable %i", !this->visible);
		g_csgo.m_engine->execute_client_cmd(buf);
		if (this->visible)
		{
			//g_pInputSystem->EnableInput(false);
			risetobottom = false;
			risetotop = true;
		}
		else
		{
			//g_pInputSystem->ResetInputState();
			//g_pInputSystem->EnableInput(true);
			risetobottom = true;
			risetotop = false;
		}

	}
	if (g_menu->alpha >= 255)
		risetotop = false;
	else if (g_menu->alpha <= 0)
		risetobottom = false;

	if (risetobottom)
		g_menu->alpha -= 3;

	if (risetotop)
		g_menu->alpha += 3;

	if (!this->visible && g_menu->alpha == 0)
		return;


	//Surface->LockCursor();

	ClickHandler();
	HWND Window = FindWindow(NULL, "Counter-Strike: Global Offensive");
	GetCursorPos(&Cur);
	ScreenToClient(Window, &Cur);


	std::copy(keys, keys + 255, oldKeys);
	for (int x = 0; x < 255; x++)
	{
		//oldKeys[x] = oldKeys[x] & keys[x];
		keys[x] = (GetAsyncKeyState(x));
	}

	static int iXDif = 0;
	static int iYDif = 0;


	/*Menu dragging*/
	/*Adjusted for themes, just delete the addition with categoryXoFsset*/
	if ((InBounds(Vector(this->position.x, this->position.y), Vector(this->size.x, dragYoffset)) && bMouse1pressed))
		this->bDragging = true;
	if (this->bDragging)
	{
		if (bMouse1pressed)
		{
			if (iXDif == -1 || iYDif == -1)
			{
				iXDif = Cur.x - this->position.x;
				iYDif = Cur.y - this->position.y;
			}
			this->position.x += Cur.x - (iXDif + this->position.x);
			this->position.y += Cur.y - (iYDif + this->position.y);

			this->moved_in_that_frame = true;
		}
		else
			this->bDragging = false;
	}
	else
	{
		iXDif = -1;
		iYDif = -1;
	}




	int alpha = g_menu->alpha;


	int x = position.x, y = position.y, w = size.x, h = size.y;



	//base
	g_drawings.draw_rect(x, y, w, h, Color(20, 20, 20, 255));

	//outline
	g_drawings.draw_outlined_rect(x, y, w, h, Color(0, 0, 0, 255));

	
	for (int i = 0; i < Children.size(); i++)
		Children[i]->Draw();

	this->DrawMouseCursor();
}

void c_window::DrawMouseCursor()
{
	int x = g_menu->main_window->Cur.x;
	int y = g_menu->main_window->Cur.y;
	Color col = Color(3, 6, 26, 255);
	g_drawings.draw_rect(x + 1, y, 1, 17, col);
	for (int i = 0; i < 11; i++)
		g_drawings.draw_rect(x + 2 + i, y + 1 + i, 1, 1, col);
	g_drawings.draw_rect(x + 8, y + 12, 5, 1, col);
	g_drawings.draw_rect(x + 8, y + 13, 1, 1, col);
	g_drawings.draw_rect(x + 9, y + 14, 1, 2, col);
	g_drawings.draw_rect(x + 10, y + 16, 1, 2, col);
	g_drawings.draw_rect(x + 8, y + 18, 2, 1, col);
	g_drawings.draw_rect(x + 7, y + 16, 1, 2, col);
	g_drawings.draw_rect(x + 6, y + 14, 1, 2, col);
	g_drawings.draw_rect(x + 5, y + 13, 1, 1, col);
	g_drawings.draw_rect(x + 4, y + 14, 1, 1, col);
	g_drawings.draw_rect(x + 3, y + 15, 1, 1, col);
	g_drawings.draw_rect(x + 2, y + 16, 1, 1, col);
	for (int i = 0; i < 4; i++)
		g_drawings.draw_rect(x + 2 + i, y + 2 + i, 1, 14 - (i * 2), Color(255 - (i * 4), 255 - (i * 4), 255 - (i * 4), 255));
	g_drawings.draw_rect(x + 6, y + 6, 1, 8, Color(235, 235, 235, 255));
	g_drawings.draw_rect(x + 7, y + 7, 1, 9, Color(231, 231, 231, 255));
	for (int i = 0; i < 4; i++)
		g_drawings.draw_rect(x + 8 + i, y + 8 + i, 1, 4 - i, Color(227 - (i * 4), 227 - (i * 4), 227 - (i * 4), 255));
	g_drawings.draw_rect(x + 8, y + 14, 1, 4, Color(207, 207, 207, 255));
	g_drawings.draw_rect(x + 9, y + 16, 1, 2, Color(203, 203, 203, 255));
}