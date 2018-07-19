#pragma once

#include <iostream>

using namespace std;

typedef class tag_XML
{
public:
	tag_XML();
	tag_XML(float f_version, string s_encoding);
	tag_XML(float f_version, char* c_encoding);

	void Set_Attribute(float f_version, string s_encoding);
	void Print_Version(void);
	void Print_Encoding(void);
	void Print_Attribute(void);

private:
	float version;
	string encoding;
} XML;