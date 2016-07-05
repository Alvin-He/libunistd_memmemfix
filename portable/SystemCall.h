// SystemCall_h
// Copyright 2016 Robin.Rowe@CinePaint.org
// License open source MIT

#ifndef SystemCall_h
#define SystemCall_h

#include <stdio.h>
#include <stdlib.h>

#ifdef __clang__
#include <stdnoreturn.h>
#define no_return noreturn
#elif __GNUC__
#define no_return  __attribute__((__noreturn__))
#elif _MSC_VER
#define no_return
#endif

inline
no_return 
void StubExit(int errorlevel,const char* file,const char* function,int line)
{	printf("ERROR: %s exit(%i)\n%s:%i",function,errorlevel,file,line);
	exit(errorlevel);
}

#define SystemExit(x) StubExit(x,__FILE__, __FUNCTION__, __LINE__)

inline
int SystemCall(const char* cmd)
{	
#ifdef _WIN32
	static int i;
	printf("[%i] system(%s)\n",++i,cmd);
	return 1;
#else
	return system(cmd);
#endif
}

namespace portable
{

template <typename T>
bool memcopy(T& dest,const char* start,unsigned size)
{	const_pointer p=nullptr;
	size*=sizeof(char);
	if(sizeof(*p)*dest.size() < size)
	{	return false;
	}
	memcpy(dest.data(),start,size);
	return true;
}

template <typename T>
bool std_cpy(const char* start,const char* end,T& dest)
{	const unsigned size = (end-start)*sizeof(char);
	const_pointer p=nullptr;
	if(sizeof(*p)*dest.size() < size)
	{	return false;
	}
	memcpy(dest.data(),start,size);
	return true;
}

} //portable

#endif

