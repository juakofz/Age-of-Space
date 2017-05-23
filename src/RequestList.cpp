#include "RequestList.h"



RequestList::RequestList()
{
}


RequestList::~RequestList()
{
	//Clear vector if there is any element remaining
	if (!v_requests.empty())
		v_requests.clear();
}


bool RequestList::check()
{
	if (v_requests.empty())
		return false;
	else
		return true;
}


int RequestList::count()
{
	if (v_requests.empty())
		return 0;
	else
		return v_requests.size();
}


void RequestList::clear()
{
	if (!v_requests.empty())
		v_requests.clear();
}


void RequestList::addRequest(Request req)
{
	v_requests.push_back(&req);
}


Request RequestList::popRequest()
{
	if (v_requests.empty())
	{
		Vector2 zero;
		Request aux = { 0, zero };
		return aux;
	}

	else
	{
		int last = v_requests.size();
		Request aux = * v_requests[last];
		v_requests.pop_back();
		return aux;
	}
}

