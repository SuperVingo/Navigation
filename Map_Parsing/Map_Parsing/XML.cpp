#include <fstream>
#include "XML.h"

tag_XML::tag_XML()
{
	version = 0;
	encoding = "";
}

tag_XML::tag_XML(float f_version, string s_encoding)
{
	version = f_version;
	encoding = s_encoding;
}

tag_XML::tag_XML(float f_version, char * c_encoding)
{
	version = f_version;
	encoding = c_encoding;
}

void tag_XML::Print_Version(void)
{
	cout << "XML Version : " << version << endl;
}

void tag_XML::Print_Encoding(void)
{
	cout << "XML Encoding : " << encoding.c_str() << endl;
}

void tag_XML::Print_Attribute(void)
{
	cout << "================= XML Attribute =====================" << endl;
	cout << "XML Version : " << version << endl;
	cout << "XML Encoding : " << encoding.c_str() << endl;
}

void tag_XML::Set_Attribute(float f_version, string s_encoding)
{
	version = f_version;
	encoding = s_encoding;
}