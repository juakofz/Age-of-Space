#include "Game.h"
#include <typeinfo>

int Game::ataques=0;
bool Game::atacar=false;

Game::Game()
{
	manager = ObjectManager::getInstance();
}

Game::~Game()
{
}

int Game::event(SDL_Event* e)
{
	int f_quit = false; //quit event flag

	int mx, my;
	SDL_GetMouseState(&mx, &my); //get absolute mouse position
	
	//Top bar area
	if (my <= top_bar.down())
	{
		//cout << "bar  " << "\r";

		top_bar.Set(); //Render pointer
		mouse.setPos(mx, my);//Absolute
		mouse.setR_pos(mx, my);//Relative to viewport
		mouse.update(e, TOP_BAR, false);
	}

	//Game area
	if (my > top_bar.down() && my < map_area.up())
	{
		//cout << "game " << "\r";

		game_area.Set(); //Render pointer
		
		f_quit = gameEvents(e); //Game selection events

		//Lock mouse while selecting
		if (mouse.isActive())
		{
			//Upper limit
			if (my <= top_bar.down())
			{
				//Absolute
				mouse.setPos(mx, top_bar.down());
				//Relative
				mouse.setR_pos(mx, 0);
			}

			//Lower limit
			else if (my >= game_area.down())
			{
				//Absolute
				mouse.setPos(mx, top_bar.getHeight() + game_area.getHeight());
				//Relative
				mouse.setR_pos(mx, game_area.getHeight());
			}

			else
			{
				//Absolute
				mouse.setPos(mx, my);
				//Relative
				mouse.setR_pos(mx, game_area.relatxy(mx, my).y);
			}

		}
		//Not selecting
		else
		{
			//Absolute
			mouse.setPos(mx, my);
			//Relative
			mouse.setR_pos(mx, game_area.relatxy(mx, my).y);
		}

		//Map
		mouse.setMpos(cam.getPos().x + mouse.getR_pos().x, cam.getPos().y + mouse.getR_pos().y);

		//Update mouse
		mouse.update(e, GAME, true);
	}

	//Lower part of the screen
	if (my >= game_area.down())
	{
		//Orders area
		if (mx <= orders_area.right())
		{
			//cout << "order" << "\r";

			orders_area.Set();
			//Absolute
			mouse.setPos(mx, my);
			//Relative
			mouse.setR_pos(orders_area.relatxy(mx, my).x, orders_area.relatxy(mx, my).y);
			mouse.update(e, ORDERS, false);
		}

		//Info area
		if (mx >= info_area.left() && mx < info_area.right())
		{
			//cout << "info " << "\r";

			info_area.Set();
			//Absolute
			mouse.setPos(mx, my);
			//Relative
			mouse.setR_pos(info_area.relatxy(mx, my).x, info_area.relatxy(mx, my).y);
			mouse.update(e, INFO, false);
		}
		
		//Map area
		if (mx >= map_area.left())
		{
			//cout << "map  " << "\r";

			map_area.Set();
			eventMinimapa(e);
			//Absolute
			mouse.setPos(mx, my);
			//Relative
			mouse.setR_pos(map_area.relatxy(mx, my).x, map_area.relatxy(mx, my).y);
			mouse.update(e, MAP, false);
		}
	}
	return f_quit;
}

void Game::cargarTexturas()
{
	g_tex[0].load("img/Nave.png");
	g_tex[1].load("img/asteroide.png");
	g_tex[2].load("img/edificio.png");
	g_tex[3].load("img/markerW.png");
	g_tex[4].load("img/markerW.png");
	g_tex[5].load("img/Cursor1.png");
	g_tex[6].load("img/new_background.png");
	g_tex[7].load("img/grid.png");
	g_tex[8].load("img/Nave.png");
	g_tex[9].load("img/disparo.png");
	g_tex[10].load("img/disparo.png");

	g_tex[5].setColor(0, 255, 0); // Cursor Verde
	g_tex[0].setColor(30, 210, 240); //Nave cian
	g_tex[3].setColor(255, 100, 0); //Marcador naranja
	g_tex[4].setColor(0, 255, 0); //Marcador verde
	g_tex[8].setColor(210, 50, 50); //Nave roja
	g_tex[9].setColor(0, 255, 255); //Cyan laser
	g_tex[10].setColor(255, 0, 0); //Red laser
	g_tex[7].setAlpha(40);

	texOpciones[0].load("img/edificio.png");
	texOpciones[1].load("img/markerW.png");
	texOpciones[2].load("img/Nave1.png");
	texOpciones[3].load("img/atras.png");
	texOpciones[4].load("img/cerrar.png");
}

void Game::InitViewPorts()
{
	//Screen areas directions
	areas[TOP_BAR] = &top_bar;
	areas[GAME] = &game_area;
	areas[ORDERS] = &orders_area;
	areas[INFO] = &info_area;
	areas[MAP] = &map_area;
	areas[WINDOW] = &window_area;

	//Init areas
	areas[TOP_BAR]->initViewPort(0.0f, 0.0f, 1.0f, 0.1f, "img/barra.png"); //Top bar
	areas[GAME]->initViewPort(0.0f, 0.1f, 1.0f, 0.75f); //Game area
	areas[ORDERS]->initViewPort(0.0f, 0.75f, 0.25f, 1.0f, "img/space2.png"); //Orders area
	areas[INFO]->initViewPort(0.25f, 0.75f, 0.75f, 1.0f, "img/space2.png"); //Info area
	areas[MAP]->initViewPort(0.75f, 0.75f, 1.0f, 1.0f, "img/space2.png"); //Map area
	areas[WINDOW]->initViewPort(0.0f, 0.0f, 1.0f, 1.0f);

	//Actualizar tamaño de cámara
	cam.update(game_area.getViewport());
}

void Game::UpdateViewPorts()
{
	for (int i = 0; i < AREA_NUMBER; i++) areas[i]->update(); //Update viewports
	cam.update(game_area.getViewport()); //Update camera frame size
}

void Game::RenderViewPorts()
{
	for (int i = 0; i < AREA_NUMBER; i++) areas[i]->render(); //general render
	//specific rendering
	renderJuego();
	renderMinimapa();
	window_area.Set();
	mouse.render();
}

void Game::RenderTotal()
{
	areas[WINDOW]->render();
	//mouse.render(gRenderer);
}

void Game::initjuego()
{
	//Cursor texture
	mouse.setCursor(&g_tex[5]);

	//Disparos
	//Explosion::setTexture(tex + 10);
	//GameObject::setTextures(&tex[9]);

	//Map
	map.setSize(2000, 2000);
	map.setBg(&g_tex[6]);
	map.setGrid(&g_tex[7]);

	//Camera
	cam.setCen(map.getSize().x / 2, map.getSize().y / 2);

	//Lists
	v_ships = * new ShipVector;
	v_projectiles = * new ProjectileVector;
	v_explosions = *new ExplosionVector;

	//manager = *new ObjectManager(&v_ships, &v_projectiles, &v_explosions);

	////inicializacion asteroide
	//ast.SetTex(tex+1);
	//ast.setMarker(&(tex[4]));
	//ast.SetCen(1500,1500);	
	//ast.setSize(500);

	//edificio.SetTex(tex+2);
	//edificio.setMarker(tex+4);
	//edificio.SetCen(1500, 1500);
	//edificio.setSize(100);
	
	////inicializacion naves
	//for(int i=0;i<20;i++)
	//{
	//	Ship* aux = new Ship;
	//	aux->setPlayer(1);
	//	aux->SetTex(tex);
	//	aux->setSize(60);
	//	aux->setMarker(&(tex[3]));
	//	aux->SetCen(150*i, 1500);
	//	aux->stop();

	//	naves.agregar(aux);
	//}

	//Test objects; testing movement
	Vector2 aux_cen(1000, 980);

	initBarra(1);
}

void Game::reinitjuego()
{
	/*ataques = 1;

	ast.SetCen(1500,1500);	
	edificio.SetCen(1500, 1500);
	edificio.setVida(10);



	proyectiles.eliminarContenido();
	naves.eliminarContenido();

	for(int i=0;i<20;i++)
	{
		Ship* aux = new Ship;
		aux->SetTex(tex);
		aux->setSize(60);
		aux->setMarker(&(tex[3]));
		aux->SetCen(150*i, 1500);
		aux->stop();

		naves.agregar(aux);
	}

	initBarra(1);
	*/
}

void Game::nuevafase(int i)
{
	player1.cambiarRecursos(0, 50);
	ataques=i;
	initBarra(i);
	//naves.eliminarJugador(2);
}

void Game::renderJuego()
{

	//Controller
	//control.setList(&naves);
	//control.setList(&edificios);
	//control.setList(&edificio);

	//for (int i = (naves.getSize() - 1); i >= 0; i--)
	//{
	//	if (control.agressive(i))
	//	{
	//		//cout<<"prueba3"<<endl;
	//		Vector2 sh = naves.shoot(i);
	//		Proyectil * p = new Proyectil(naves.getPlayer(i));
	//		switch(p->getPlayer())
	//		{
	//			case 1: //jugador
	//				p->SetTex(tex + 9);
	//				break;

	//			case 2: //maquina
	//				p->SetTex(tex + 10);
	//				break;

	//			default:
	//				break;
	//		}
	//		p->setSize(25);
	//		p->SetCen(naves.getPointyEnd(i).x, naves.getPointyEnd(i).y);
	//		p->moveTo(sh.x, sh.y);
	//		proyectiles.agregar(p);
	//	}
	//}


	//viewport de juego
	game_area.Set();
	
	//Mapa
	map.renderBg(cam);
	map.renderGrid(cam);

	//Test objects
	//...

	//Object manager
	manager->projectileImpacts();
	manager->moveProjectiles();
	manager->renderProjectiles(cam);
	manager->updateExplosions();
	manager->moveShips();
	manager->renderShips(cam);

	//if (cam.isVisible(ast.GetCen(), 20))
	//	{
	//		ast.render(cam);
	//	}
	//asteroides.render(cam);
	//edificio.render(cam);
	//naves.render(cam);
	//objetos_prueba.render(cam);
	//proyectiles.render(cam);

	//if(edificio.getSel()) 
	//{
	//		renderMenu();
	//		//int type=ast.getType();
	//}
	//
	////if(asteroides.getSel()) renderMenu();
	game_area.Set();
}

void Game::setNombre(std::string nombre)
{
	player1.setName(nombre);
	top_bar.SetName(player1.getName());
}

int Game::gameEvents(SDL_Event* e)
{
	//Object manager events
	manager->shipEvents(e, mouse.getMrect(), mouse.getMpos());

	//Test objects events; testing movement
	//..

	//Keyboard events
	if (e->type == SDL_KEYDOWN) 
	{
		//ESC: Exit game
		if (e->key.keysym.sym == SDLK_ESCAPE)
		{
			return 1;
		}

		//d: Toggle debug mode
		if (e->key.keysym.sym == SDLK_d)
		{
			g_f_debug = !g_f_debug;
			cout << "Debug: " << g_f_debug << endl;
		}

		//Debug creation key
		if (e->key.keysym.sym == SDLK_z)
		{
			//cout << "Debug projectile created! " << endl;
			Vector2 debug_origin(1000, 1000), debug_dest(mouse.getMpos());
			manager->createProjectile(1, 0, debug_origin, debug_dest);
		}

		//Debug creation key 2
		if (e->key.keysym.sym == SDLK_x)
		{
			//cout << "Debug explosion created! " << endl;
			Vector2 debug_origin, debug_dest(mouse.getMpos());
			manager->createExplosion(1000, 1000, 10);
		}

		//Debug creation key 3
		if (e->key.keysym.sym == SDLK_c)
		{
			//cout << "Debug ship created! " << endl;
<<<<<<< HEAD
			manager->createShip(0, 1, mouse.getMpos());
=======
			manager.createShip(0, 1, mouse.getMpos());
>>>>>>> origin/rework
		}
	}

	return 0;
	
}

void Game::mainEvent()
{
	mouse.scroll(cam, map); //Camera scroll via mouse
	cam.scroll(); //Camera scroll via keyboard

	if (g_keyboardState != NULL)//Add keyboard shortcuts here
	{	
		//...
	}
}

void Game::initMenu()
{
	//menu.setBotones(texOpciones);
	//menu.setBotonQuad(40, 40);
}

void Game::renderMenu()
{
	//Abrimos el menu
	areas[ORDERS]->Open();

}

void Game::eventMenu(SDL_Event* e)
{
	////eventos del menu
	//switch (menu.event(e, menu.relatxy()))
	//{
	//	case 2:
	//		{
	//			static int i=0;

	//			if(jugador.cambiarRecursos(-5, -1)) break;
	//			Ship* aux = new Ship(tex, 60, tex+3, Vector2(1500 + 15*i++, 1500), 1, true);				
	//			act_barra=true;
	//			naves.agregar(aux);

	//			break;			
	//		}

	//	case 3:
	//		do{
	//			naves.eliminarNave(naves.getSel()-1);
	//		} while(naves.getSel());
	//		break;
	//	
	//	case 4:
	//		//cout<<"cerrar"<<endl;
	//		break;
	//}
}

void Game::initBarra(int fase)
{
	top_bar.SetName(player1.getName());

	std::stringstream recursos[2];
	player1.getRecursos(recursos);
	top_bar.setRecursos(recursos);

	top_bar.SetFase(fase);
	top_bar.setVida(10);
}

void Game::renderBarra()
{
	//viewport de menu
//	barra.Set();
	if(act_barra)
	{
		std::stringstream recursos[2];
		player1.getRecursos(recursos);
		top_bar.setRecursos(recursos);
	//	cout<<"actualizar"<<endl;
		act_barra=false;
	}
	//if(act_vida)
	//{
	//	top_bar.setVida(edificio.getVida());
	//	act_vida = false;
	//}
}

void Game::eventBarra(SDL_Event* e)
{
	//eventos de la barra
	top_bar.event(e, top_bar.relatxy());

}

void Game::initMinimapa()
{
	//Lista de cositas?
}

void Game::renderMinimapa()
{
	map_area.render();
	int margen = 10;
	int h = map_area.getHeight();
	int w = map_area.getWidth();

	//Map border
	SDL_Rect mapRect = {margen, margen, w - 2 * margen, h - 2 * margen };
	SDL_SetRenderDrawColor(g_Renderer, 0, 128, 255, 255);
	SDL_RenderDrawRect(g_Renderer, &mapRect);

	//Manager minimap render


	//if (naves.getSize()) {
	//	for (int i = (naves.getSize() - 1); i >= 0; i--)
	//	{
	//		Vector2 p = naves.getCen(i);
	//		Vector2 rp;
	//		rp.x = (p.x / map.getSize().x) * (w - 2 * margen) + margen;
	//		rp.y = (p.y / map.getSize().y) * (h - 2 * margen) + margen;

	//		SDL_Rect fillRect = {rp.x, rp.y, 2, 2};
	//		switch (naves.getPlayer(i))
	//		{
	//		case 1:
	//			SDL_SetRenderDrawColor(g_Renderer, 0, 255, 255, 0);
	//			break;
	//		case 2:
	//			SDL_SetRenderDrawColor(g_Renderer, 255, 0, 0, 0);
	//			break;
	//		default:
	//			SDL_SetRenderDrawColor(g_Renderer, 0, 0, 0, 0);
	//		}
	//		SDL_RenderFillRect(g_Renderer, &fillRect);
	//	}
	//}

	//Camera rect
	Vector2 c, rc, s, rs;
	
	c = cam.getPos();
	rc.x = (c.x / map.getSize().x) * (w - 2 * margen) + margen;
	rc.y = (c.y / map.getSize().y) * (h - 2 * margen) + margen;
	
	s = cam.getSize();

	rs.x = (s.x / map.getSize().x) * (w - 2 * margen);
	rs.y = (s.y / map.getSize().y) * (h - 2 * margen);

	SDL_Rect camRect = {rc.x, rc.y, rs.x, rs.y};
	SDL_SetRenderDrawColor( g_Renderer, 255, 255, 255, 150);        
	SDL_RenderDrawRect( g_Renderer, &camRect );

	//Renderizar minicositas

}

void Game::eventMinimapa(SDL_Event* e)
{
	int map_margin = 10;

	//Inside margin (x)
	if ((mouse.getR_pos().x > map_margin) || (mouse.getR_pos().x < map_area.getWidth() + map_margin))
	{
		//Inside margin (y)
		if ((mouse.getR_pos().y > map_margin) || (mouse.getR_pos().y < map_area.getHeight() + map_margin))
		{
			SDL_Point p;
			p.x = ((mouse.getR_pos().x - map_margin) * map.getSize().x) / (map_area.getWidth() - 2 * map_margin);
			p.y = ((mouse.getR_pos().y - map_margin) * map.getSize().y) / (map_area.getHeight() - 2 * map_margin);
			
			//Half fix
			if (p.x < 0) p.x = 0;
			if (p.x > map.getSize().x) p.x = map.getSize().x;
			if (p.y < 0) p.y = 0;
			if (p.y > map.getSize().y) p.y = map.getSize().y;


			//Move camera
			if (e->button.button == SDL_BUTTON_LEFT)
			{
				cam.setCen(p.x, p.y);
			}

			//Movimiento de naves
			if (e->button.button == SDL_BUTTON_RIGHT)
			{
				//naves.event(e, mouse.getMrect(), p);
			}
		}
	}
}

void Game::ataqueEnemigo()
{
	//Vector2 centro;
	//
	//centro.x=  map.getSize().x / 2;
	//centro.y = map.getSize().y / 2;
	//int radio = ( ((centro.x<centro.y)?centro.x:centro.y) - 100 * ataques );
	//float angulo = (2 * M_PI )/( ataques * 4);


	//for(int j = 0; j < ataques*4; j++)
	//{
	//	Ship* aux = new Ship(tex+8, 60, tex+3, Vector2(centro.x + radio * cos(angulo * j ), centro.y - radio * sin(angulo * j)), 2, false);
	//	naves.agregar(aux);
	//}
	//
	//ataques++;
}