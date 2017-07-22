#pragma once
#include "Vector2.h"
#include "Global.h"
#include <list>


enum COMMAND_TYPES
{
	NO_COMMAND,
	MOVE_TO,
	FOLLOW,
	DIE
};

struct Command
{
	int type;
	Vector2 center;
	Vector2 dest;

	//General constructor
	Command(int type, Vector2 center, Vector2 dest) :
		type(type), center(center), dest(dest)
	{}

	//Empty command
	Command() : type(NO_COMMAND), center(Vector2::zero()), dest(Vector2::zero())
	{}

	//Move command
	Command(int type, Vector2 dest) :
		type(type), dest(dest), center(Vector2::zero())
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
	void replace(Command com);

	Command firstCommand();		//Returns first command on the list
	Command nextCommand();		//Returns and then pops first command on the list 

private:

	std::list<Command> l_commands;
	bool new_command;
};

