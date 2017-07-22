#pragma once
#include "Vector2.h"
#include "Global.h"
#include <vector>

struct Request
{
	int type;
	int player;
	Vector2 center;
	Vector2 dest;
};

class RequestList
{
public:

	//Singleton
	static RequestList * s_instance;

	static RequestList * getInstance()
	{
		if (!s_instance)
			s_instance = new RequestList;
		return s_instance;
	};

	~RequestList();

	bool check();
	int count();
	void clear();

	void addRequest(Request req);
	Request popRequest();

private:
	RequestList();
	std::vector<Request> v_requests;
};

