#pragma once
#include "csgo.h"
#include <vector>

enum control_types
{
	check_box = 1,
	slider,
	key_bind,
	drop_down,
	color_picker,
};

class c_control
{
public:
	std::string name, caption;
	std::vector<c_control*> Children;
	Vector position, size = Vector(0, 15);
	bool visible = false;
	bool in_tab;
	c_control() {}
	c_control(std::string name, std::string caption, Vector pos, Vector size)
	{
		this->name = name;
		this->caption = caption;
		this->position = pos;
		this->size = size;
	}
	void add_child_control(c_control * Child)
	{
		//Children.push_back(Child);
		Children.emplace_back(Child);
	}
	std::string FileIdentifier;
	int FileControlType;

	virtual void Draw() = 0;
	Color White = Color(255, 255, 255, 255);
	Color Black = Color(0, 0, 0, 255);
	Color Yellow = Color(255, 255, 0, 255);
	Color DarkGrey = Color(35, 35, 35, 255);
	Color MidGrey = Color(44, 44, 44, 255);
	Color LightGrey = Color(106, 106, 106, 255);
	Color LightRed = Color(186, 0, 40, 255);
	Color pWhite = Color(0, 102, 51, 255);
	Color OutlineGrey = Color(86, 86, 86, 255);
};