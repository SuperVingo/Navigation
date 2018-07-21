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
TagNS::Tag_Tag GetTag(std::string tag);
TagNS::Tag_nd GetND(std::string tag);
TagNS::Tag_Member GetMember(std::string tag);