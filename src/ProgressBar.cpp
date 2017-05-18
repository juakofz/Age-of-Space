#include "ProgressBar.h"



ProgressBar::ProgressBar()
{
	m_width = 20;
	m_height = 3;

	setCen(0, 0);

	m_frontColor.r = 0; //Green
	m_frontColor.g = 255;
	m_frontColor.b = 0;

	m_backColor.r = 255; //Red
	m_backColor.g = 0;
	m_backColor.b = 0;

	m_progress = 0.5;
}

ProgressBar::ProgressBar(int type, Vector2 cen, float prog)
{
	//Default type
	m_width = 20;
	m_height = 3;

	setCen(cen);

	m_frontColor.r = 0; //Green
	m_frontColor.g = 255;
	m_frontColor.b = 0;

	m_backColor.r = 255; //Red
	m_backColor.g = 0;
	m_backColor.b = 0;

	m_progress = prog;
}


ProgressBar::~ProgressBar()
{
}

void ProgressBar::setDim(float w, float h)
{
	m_width = w;
	m_height = h;
}

void ProgressBar::setDim(Vector2 dim)
{
	m_width = dim.x;
	m_height = dim.y;
}

void ProgressBar::setCen(float w, float h)
{
	m_center.x = w;
	m_center.y = h;

	m_position.x = m_center.x - m_width / 2;
	m_position.y = m_center.y - m_height / 2;
}

void ProgressBar::setCen(Vector2 cen)
{
	m_center.x = cen.x;
	m_center.y = cen.y;

	m_position.x = m_center.x - m_width / 2;
	m_position.y = m_center.y - m_height / 2;
}

void ProgressBar::setPos(float x, float y)
{
	m_position.x = x;
	m_position.y = y;

	m_center.x = m_position.x + m_width / 2;
	m_center.y = m_position.y + m_height / 2;
}

void ProgressBar::setPos(Vector2 pos)
{
	m_position = pos;

	m_center.x = m_position.x + m_width / 2;
	m_center.y = m_position.y + m_height / 2;
}

//Bar progress, 0 to 1;
void ProgressBar::setProgress(float prog)
{
	if (prog < 0) prog = 0;
	if (prog > 1) prog = 1;
	m_progress = prog;
}

void ProgressBar::render(Camera cam)
{
	//If inside camera frame
	if (cam.isVisible(m_center, m_width / 2))
	{
		SDL_Point aux_cen;
		aux_cen.x = m_center.x - cam.getPos().x;
		aux_cen.y = m_center.y - cam.getPos().y;
		
		//Update rects dimensions
		if (m_progress == 0) //Only draw back rect
		{
			r_back.x = m_position.x - cam.getPos().x;
			r_back.y = m_position.y - cam.getPos().y;
			r_back.h = m_height;
			r_back.w = m_width;
			
			SDL_SetRenderDrawColor(g_Renderer, m_backColor.r, m_backColor.g, m_backColor.b, SDL_ALPHA_OPAQUE);
			SDL_RenderFillRect(g_Renderer, &r_back);
		}	
		else if (m_progress == 1) //Only draw front rect
		{
			r_front.x = m_position.x - cam.getPos().x;
			r_front.y = m_position.y - cam.getPos().y;
			r_front.h = m_height;
			r_front.w = m_width;

			SDL_SetRenderDrawColor(g_Renderer, m_frontColor.r, m_frontColor.g, m_frontColor.b, SDL_ALPHA_OPAQUE);
			SDL_RenderFillRect(g_Renderer, &r_front);

		}
		else
		{
			r_front.x = m_position.x - cam.getPos().x;
			r_front.y = m_position.y - cam.getPos().y;
			r_front.h = m_height;
			r_front.w = m_width * m_progress;

			r_back.x = m_position.x + m_width * m_progress - cam.getPos().x;
			r_back.y = m_position.y - cam.getPos().y;
			r_back.h = m_height;
			r_back.w = m_width * (1 - m_progress);

			SDL_SetRenderDrawColor(g_Renderer, m_backColor.r, m_backColor.g, m_backColor.b, SDL_ALPHA_OPAQUE);
			SDL_RenderFillRect(g_Renderer, &r_back);
			SDL_SetRenderDrawColor(g_Renderer, m_frontColor.r, m_frontColor.g, m_frontColor.b, SDL_ALPHA_OPAQUE);
			SDL_RenderFillRect(g_Renderer, &r_front);
		}


		//render
	}
}