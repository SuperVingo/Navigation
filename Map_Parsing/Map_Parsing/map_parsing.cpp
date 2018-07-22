#include "MapReader.h"

bool GetAttribute(std::string tag, const char name[], int * value)
{
	int v_index, v2_index, ivalue;
	char * c_name = (char*)name;

	strcat_s(c_name, sizeof(name), "=\"");

	v_index = tag.find(c_name);
	v2_index = tag.find("\"", v_index);

	if (v_index == -1 || v2_index == -1)
	{
		FindError(name);
		value = nullptr;
		return false;
	}
	else
	{
		std::string temp = tag.substr(v_index, v2_index - v_index);

		ivalue = atoi(temp.c_str());

		*value = ivalue;
	}
	
	return true;
}


bool GetAttribute(std::string tag, const char name[], long * value)
{
	int v_index, v2_index;
	long lvalue;
	char * c_name = (char*)name;

	strcat_s(c_name, sizeof(name), "=\"");

	v_index = tag.find(c_name);
	v2_index = tag.find('"', v_index);

	if (v_index == -1 || v2_index == -1)
	{
		FindError(name);
		return false;
	}
	else
	{
		std::string temp = tag.substr(v_index, v2_index - v_index);

		lvalue = atoi(temp.c_str());

		*value = lvalue;
	}

	return true;
}

bool GetAttribute(std::string tag, const char name[], double * value)
{
	int v_index, v2_index;
	double dvalue;
	char * c_name = (char*)name;

	strcat_s(c_name, sizeof(name), "=\"");

	v_index = tag.find(c_name);
	v2_index = tag.find('"', v_index);

	if (v_index == -1 || v2_index == -1)
	{
		FindError(name);
		return false;
	}
	else
	{
		std::string temp = tag.substr(v_index, v2_index - v_index);

		dvalue = atof(temp.c_str());

		*value = dvalue;
	}

	return true;

}

bool GetAttribute(std::string tag, const char name[], bool * value)
{
	int v_index, v2_index;
	char * c_name = (char*)name;

	strcat_s(c_name, sizeof(name), "=\"");

	v_index = tag.find(c_name);
	v2_index = tag.find('"', v_index);

	if (v_index == -1 || v2_index == -1)
	{
		FindError(name);
		return false;
	}
	else
	{
		std::string temp = tag.substr(v_index, v2_index - v_index);

		if (temp == "true")
			*value = true;
		else
			*value = false;
	}

	return true;

}

bool GetAttribute(std::string tag, const char name[], char value[])
{
	int v_index, v2_index;
	std::string cvalue;
	char * c_name = (char*)name;

	strcat_s(c_name, sizeof(name), "=\"");

	v_index = tag.find(c_name);
	v2_index = tag.find('"', v_index);

	if (v_index == -1 || v2_index == -1)
	{
		FindError(name);
		return false;
	}
	else
	{
		std::string temp = tag.substr(v_index, v2_index - v_index);

		cvalue = temp;

		value = (char*)cvalue.c_str();
	}

	return true;
}

bool GetAttribute(std::string tag, const char name[], std::string * value)
{
	int v_index, v2_index;
	std::string svalue;
	char * c_name = (char*)name;

	strcat_s(c_name, sizeof(name), "=\"");

	v_index = tag.find(c_name);
	v2_index = tag.find('"', v_index);

	if (v_index == -1 || v2_index == -1)
	{
		FindError(name);
		return false;
	}
	else
	{
		std::string temp = tag.substr(v_index, v2_index - v_index);

		svalue = temp;

		*value = svalue;
	}
	return true;
}

bool GetND(std::string tag, TagNS::Tag_nd * value)
{
	long ref;
	
	if (!GetAttribute(tag, "ref", &ref))
		return false;

	*value = TagNS::Tag_nd(ref);

	return true;
}

bool GetTag(std::string tag, TagNS::Tag_Tag * value)
{
	std::string s_k;
	std::string s_v;

	if (!GetAttribute(tag, "k", &s_k))
		return false;
	if (!GetAttribute(tag, "v", &s_v))
		return false;

	*value = TagNS::Tag_Tag(s_k, s_v);

	return true;
}

bool GetMember(std::string tag, TagNS::Tag_Member * value)
{
	std::string s_type;
	long ref;
	std::string s_role;

	if (!GetAttribute(tag, "type", &s_type))
		return false;
	if (!GetAttribute(tag, "ref", &ref))
		return false;
	if (!GetAttribute(tag, "role", &s_role))
		return false;

	*value = TagNS::Tag_Member(s_type, ref, s_role);

	return true;
}