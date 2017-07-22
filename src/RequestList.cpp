#include "RequestList.h"

RequestList * RequestList::s_instance = 0;

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
	v_requests.push_back(req);
	//v_requests.emplace_back(& req);
	//if (g_f_debug) cout << "Added req, now " << v_requests.size() << endl;
}


Request RequestList::popRequest()
{
	if (v_requests.empty())
	{
		Request aux = { NONE, 0, Vector2::zero() };
		//if (g_f_debug) cout << "No reqs to pop" << endl;
		return aux;
		
	}

	else
	{
		int last = v_requests.size() - 1;
		Request aux = v_requests[last];
		v_requests.pop_back();
		//if (g_f_debug) cout << "Popped req, now " << v_requests.size() << endl;
		return aux;
	}
}