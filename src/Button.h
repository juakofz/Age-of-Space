#pragma once
#include "Global.h"
#include "Texture.h"

class Button
{

public:

	Button(Vector2 dim, Vector2 pos);
	~Button();

	void setBackground(Texture *t_bg);
	void setOverlay(Texture *t_overlay, Texture *t_clicked_overlay);

	void setPos(int x, int y);

	bool event(SDL_Event* e, SDL_Point xyrel);
	void render();

	bool clickOn(SDL_Event* e, SDL_Point xyrel);

private:

	Texture * m_tex_background;
	Texture * m_tex_overlay;
	Texture * m_tex_overlay_clicked;

	Vector2 m_pos;
	Vector2 m_dim;

	bool f_clicked;
	bool f_enabled;
	
};