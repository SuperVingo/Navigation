#pragma once

#include <string.h>
#include <stdlib.h>
#include <iostream>
#include "MapReader.h"


bool GetAttribute(std::string tag, const char name[], int * value);
bool GetAttribute(std::string tag, const char name[], long * value);
bool GetAttribute(std::string tag, const char name[], double * value);
bool GetAttribute(std::string tag, const char name[], bool * value);
bool GetAttribute(std::string tag, const char name[], char value[]);
bool GetAttribute(std::string tag, const char name[], std::string * value);
bool GetTag(std::string tag, TagNS::Tag_Tag * value);
bool GetND(std::string tag, TagNS::Tag_nd * value);
bool GetMember(std::string tag, TagNS::Tag_Member * value);

inline void FindError(const char * name, const char * Additional = ' ')
{
	std::cout << "Can't find" << name << "." << Additional << std::endl;
}