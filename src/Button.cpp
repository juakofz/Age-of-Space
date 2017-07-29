#include "Button.h"


Button::Button(Vector2 dim, Vector2 pos)
{
	m_pos = pos;
	m_dim = dim;

	f_clicked = false;
	f_enabled = true;

	setOverlay(&g_tex[11], &g_tex[12]);
	setBackground(&g_tex[13]);
}


Button::~Button()
{
}


void Button::setBackground(Texture * t_normal)
{
	m_tex_background = t_normal;
}


void Button::setOverlay(Texture * t_clicked, Texture * t_clicked_overlay)
{
	m_tex_overlay = t_clicked;
	m_tex_overlay_clicked = t_clicked_overlay;
}


void Button::setPos(int x, int y)
{
	m_pos.x = x;
	m_pos.y = y;
}


bool Button::event(SDL_Event* e, SDL_Point xyrel)
{
	if (clickOn(e, xyrel) && f_enabled)
	{
		//Left click
		if (e->button.button == SDL_BUTTON_LEFT)
		{
			f_clicked = true;
			f_enabled = false;
			//cout << "Button clicked!" << endl;
			return true;
		}	
	}

	f_clicked = false;
	return false;
}


void Button::render()
{
	//Overlay rendering
	if (f_clicked)
	{
		//Clicked button overlay
		m_tex_overlay_clicked->render(g_Renderer, &m_dim, (int)m_pos.x, (int)m_pos.y);
	}
	else
	{
		//Regular button overlay
		m_tex_overlay->render(g_Renderer, &m_dim, (int)m_pos.x, (int)m_pos.y);
	}

	//Grey out disabled buttons
	if (f_enabled)
		m_tex_background->setColor(255, 0, 0);
	else
		m_tex_background->setColor(50, 50, 50);

	//Render background
	m_tex_background->render(g_Renderer, &m_dim, (int)m_pos.x, (int)m_pos.y);
}


bool Button::clickOn(SDL_Event* e, SDL_Point xyrel)
{
	int mx = xyrel.x, my = xyrel.y;

	if (e->type == SDL_MOUSEBUTTONDOWN)
	{
		if (mx >= m_pos.x && mx <= (m_pos.x + m_dim.x))
		{
			if (my >= m_pos.y && my <= (m_pos.y + m_dim.y))
			{
				return true;
			}
		}
	}

	return false;
}