#pragma once
#include <vector>
#include "Camera.h"

template <typename T>

class T_Vector
{
public:
	T_Vector();
	~T_Vector();

	bool check();		//Check if empty
	bool in(int i);		//Check if within vector
	int size();		//Return size
	void clear();		//Clear whole vector
	void clean();		//Clean NULL pointers

	void add(T * element);	//Add element
	void erase(int i);		//Remove element
	T * get(int i);			//Get * to element
	T pop();				//Pop last element
	
	T_Vector<T> operator += (T_Vector<T> v);

protected:

	std::vector<T *> v_elements;
};


//Definitions

template <typename T>
T_Vector<T>::T_Vector()
{
}


template <typename T>
T_Vector<T>::~T_Vector()
{
	//Clear vector if there is any element remaining
	if (!v_elements.empty())
		v_elements.clear();
}


template <typename T>
bool T_Vector<T>::check()
{
	return !v_elements.empty();
}


template <typename T>
bool T_Vector<T>::in(int i)
{
	if (!v_elements.empty() && i >= v_elements.size())
		return false;
	else
		return true;
}


template <typename T>
int T_Vector<T>::size()
{
	if (v_elements.empty())
		return 0;
	else
		return v_elements.size();
}


template <typename T>
void T_Vector<T>::clear()
{
	if (!v_elements.empty())
		v_elements.clear();
}


template <typename T>
void T_Vector<T>::add(T * element)
{
	v_elements.push_back(element);
	//if (g_f_debug) cout << "Added element, now " << v_elements.size() << endl;
}


template <typename T>
void T_Vector<T>::erase(int i)
{
	if (in(i))
	{
		delete (v_elements[i]);
		v_elements.erase(v_elements.begin() + i); //Remove and destroy object
	}
	clean();
		
}


template <typename T>
T * T_Vector<T>::get(int i)
{
	if (in(i))
	{
		T * aux = v_elements[i];
		return aux;
	}
	else
		return NULL;
}


template <typename T>
T T_Vector<T>::pop()
{
	if (v_elements.empty())
	{
		T aux;
		//if (g_f_debug) cout << "No elements to pop" << endl;
		return aux;
	}

	else
	{
		int last = v_elements.size() - 1;
		T aux = v_elements[last];
		v_elements.pop_back();
		//if (g_f_debug) cout << "Popped element, now " << v_elements.size() << endl;
		return aux;
	}
}


template <typename T>
void T_Vector<T>::clean()
{
	if (v_elements.empty())
	{
		for (int i = 0; i < v_elements.size(); i++)
		{
			if (v_elements[i] == NULL)
				v_elements.erase(v_elements.begin() + i);
		}
	}
}

//Operators

template <typename T>
T_Vector<T> T_Vector<T>::operator += (T_Vector<T> v)
{
	for (int i = 0; i < v.size(); i++)
	{
		add(v.get(i));
	}

	return *this;
}
