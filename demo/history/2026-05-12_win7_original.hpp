#ifndef CMEI_TOOLS_H_
#define CMEI_TOOLS_H_
#include <cstdio>
namespace ctool
{
	template <typename TYPE>
	void Swap(TYPE &a, TYPE &b)
	{
	    TYPE tmp(a);
	    a = b;
	    b = tmp;
	}
	void cls() {printf("\033[2J\033[H");}
	
}
#endif