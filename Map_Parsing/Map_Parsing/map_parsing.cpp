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
		std::cout << "Can't find " << name << "Check the file." << std::endl;
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
		std::cout << "Can't find " << name << "Check the file." << std::endl;
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
		std::cout << "Can't find " << name << "Check the file." << std::endl;
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
		std::cout << "Can't find " << name << "Check the file." << std::endl;
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
		std::cout << "Can't find " << name << "Check the file." << std::endl;
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
		std::cout << "Can't find " << name << "Check the file." << std::endl;
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

TagNS::Tag_nd GetND(std::string tag)
{
	long ref;
	
	GetAttribute(tag, "ref", &ref);

	return TagNS::Tag_nd(ref);
}

TagNS::Tag_Tag GetTag(std::string tag)
{
	std::string s_k;
	std::string s_v;

	GetAttribute(tag, "k", &s_k);
	GetAttribute(tag, "v", &s_v);

	return TagNS::Tag_Tag(s_k, s_v);
}

TagNS::Tag_Member GetMember(std::string tag)
{
	std::string s_type;
	long ref;
	std::string s_role;

	GetAttribute(tag, "type", &s_type);
	GetAttribute(tag, "ref", &ref);
	GetAttribute(tag, "role", &s_role);

	return TagNS::Tag_Member(s_type, ref, s_role);
}