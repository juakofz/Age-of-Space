#pragma once
#include "Vector2.h"
#include <vector>

struct Request
{
	int type;
	Vector2 center;
};

class RequestList
{
public:
	RequestList();
	~RequestList();

	bool check();
	int count();
	void clear();

	void addRequest(Request req);
	Request popRequest();

private:
	std::vector<Request *> v_requests;
};

