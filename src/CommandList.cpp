#include "CommandList.h"




CommandList::CommandList()
{
	new_command = false;
}


CommandList::~CommandList()
{
	//Clear vector if there is any element remaining
	if (!l_commands.empty())
		l_commands.clear();
}


bool CommandList::check()
{
	return new_command;
}


int CommandList::count()
{
	if (l_commands.empty())
		return 0;
	else
		return l_commands.size();
}


void CommandList::clear()
{
	if (!l_commands.empty())
		l_commands.clear();
	new_command = false;
}


void CommandList::addCommand(Command com)
{
	if(l_commands.empty())
		new_command = true;
	l_commands.push_back(com);
}


void CommandList::popFirst()
{
	//If no command to pop
	if (l_commands.empty())
	{
		new_command = false;
		return;
	}

	else
	{
		l_commands.pop_front();
		if (l_commands.empty())
			new_command = false;
		else
			new_command = true;
	}
}


void CommandList::replace(Command com)
{
	clear();
	addCommand(com);
	new_command = true;
}


Command CommandList::firstCommand()
{
	Command aux = {};
	new_command = false;
	if (l_commands.empty()) return aux;
	aux = l_commands.front();
	return aux;
}


Command CommandList::nextCommand()
{
	Command aux = {};
	new_command = false;
	if (l_commands.empty()) return aux;
	aux = l_commands.front();
	l_commands.pop_front();
	return aux;
}