#pragma once

#include <string.h>
#include <stdlib.h>
#include <iostream>
#include "MapReader.h"


bool GetAttribute(std::string tag, std::string name, int * value);
bool GetAttribute(std::string tag, std::string name, long * value);
bool GetAttribute(std::string tag, std::string name, double * value);
bool GetAttribute(std::string tag, std::string name, bool * value);
bool GetAttribute(std::string tag, std::string name, char value[]);
bool GetAttribute(std::string tag, std::string name, std::string * value);
bool GetTag(std::string tag, TagNS::Tag_Tag * value);
bool GetND(std::string tag, TagNS::Tag_nd * value);