#pragma once
#include "Vector2.h"
#include "Global.h"
#include "GameObject.h"
#include <list>


struct Command
{
	int type;
	Vector2 center;
	Vector2 dest;
	GameObject * target;

	//General constructor
	Command(int type, Vector2 center, Vector2 dest, GameObject * target) :
		type(type), center(center), dest(dest), target(target)
	{}

	//Empty command
	Command() : type(NO_COMMAND), center(Vector2::zero()), dest(Vector2::zero()), target(NULL)
	{}

	//Move command
	Command(int type, Vector2 dest) :
		type(type), dest(dest), center(Vector2::zero()), target(NULL)
	{}

	//Follow / attack / guard command
	Command(int type, GameObject * target):
		type(NO_COMMAND), center(Vector2::zero()), dest(Vector2::zero()), target(target)
	{}
};



class CommandList
{
public:

	CommandList();
	~CommandList();

	bool check();
	int count();
	void clear();

	void addCommand(Command com);
	void popFirst();
	void replaceAll(Command com);

	Command firstCommand();		//Returns first command on the list
	Command nextCommand();		//Returns and then pops first command on the list 

private:

	std::list<Command> l_commands;
	bool new_command;
};

