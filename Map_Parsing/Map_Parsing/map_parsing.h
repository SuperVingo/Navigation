#pragma once

#include <string.h>
#include <stdlib.h>
#include <iostream>
#include "MapReader.h"

bool GetAttribute(std::wstring tag, const wchar_t name[], int * value);
bool GetAttribute(std::wstring tag, const wchar_t name[], unsigned long long * value);
bool GetAttribute(std::wstring tag, const wchar_t name[], double * value);
bool GetAttribute(std::wstring tag, const wchar_t name[], bool * value);
bool GetAttribute(std::wstring tag, const wchar_t name[], char value[]);
bool GetAttribute(std::wstring tag, const wchar_t name[], std::wstring * value);
bool GetTag(std::wstring tag, TagNS::Tag_Tag * value);
bool GetND(std::wstring tag, TagNS::Tag_nd * value);
bool GetMember(std::wstring tag, TagNS::Tag_Member * value);

inline void FindError_in_terminal(const wchar_t * name, const wchar_t * Additional = L" ")
{
	std::wcout << "Can't find \"" << name << "\". " << Additional << std::endl;
}

inline void AttributeError_in_terminal(const wchar_t * Attribute, const wchar_t * Additional = L" ")
{
	std::wcout << "Can't get Attribution \"" << Attribute << "\". " << Additional << std::endl;
}

inline void FileopenError_in_terminal(const wchar_t * filename, const wchar_t * Additional = L" ")
{
	std::wcout << "Can't open the file \"" << filename << "\". " << Additional << std::endl;
}

inline void ParsingError_in_terminal(const wchar_t * Tag, const wchar_t * Additional = L" ")
{
	std::wcout << "Can't parsing \"" << Tag << "\". " << Additional << std::endl;
}