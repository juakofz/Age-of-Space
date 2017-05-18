#pragma once
#include "Vector2.h"
#include "Global.h"

class ProgressBar
{
public:
	ProgressBar();
	ProgressBar(int type, Vector2 cen, float prog);
	~ProgressBar();

	void setDim(float w, float h);
	void setDim(Vector2 dim);

	void setCen(float x, float y);
	void setCen(Vector2 cen);

	void setPos(float x, float y);
	void setPos(Vector2 pos);

	void setProgress(float prog);

	void render(Camera cam);
	void render();

private:
	float m_width;
	float m_height;

	Vector2 m_center;
	Vector2 m_position;

	float m_progress;

	SDL_Color m_frontColor;
	SDL_Color m_backColor;

	SDL_Rect r_front;
	SDL_Rect r_back;
};

