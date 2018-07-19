#include "MapReader.h"

bool GetAttribute(std::string tag, std::string name, int * value)
{
	int v_index, v2_index, ivalue;

	name += "=\"";

	v_index = tag.find(name);
	v2_index = tag.find("\"", v_index);

	if (v_index == -1 || v2_index == -1)
	{
		std::cout << "Can't find " << name.c_str() << "Check the file." << std::endl;
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


bool GetAttribute(std::string tag, std::string name, long * value)
{
	int v_index, v2_index;
	long lvalue;

	name += "=\"";

	v_index = tag.find(name);
	v2_index = tag.find('"', v_index);

	if (v_index == -1 || v2_index == -1)
	{
		std::cout << "Can't find " << name.c_str() << "Check the file." << std::endl;
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

bool GetAttribute(std::string tag, std::string name, double * value)
{
	int v_index, v2_index;
	double dvalue;

	name += "=\"";

	v_index = tag.find(name);
	v2_index = tag.find('"', v_index);

	if (v_index == -1 || v2_index == -1)
	{
		std::cout << "Can't find " << name.c_str() << "Check the file." << std::endl;
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

bool GetAttribute(std::string tag, std::string name, bool * value)
{
	int v_index, v2_index;

	name += "=\"";

	v_index = tag.find(name);
	v2_index = tag.find('"', v_index);

	if (v_index == -1 || v2_index == -1)
	{
		std::cout << "Can't find " << name.c_str() << "Check the file." << std::endl;
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

bool GetAttribute(std::string tag, std::string name, char value[])
{
	int v_index, v2_index;
	std::string cvalue;

	name += "=\"";

	v_index = tag.find(name);
	v2_index = tag.find('"', v_index);

	if (v_index == -1 || v2_index == -1)
	{
		std::cout << "Can't find " << name.c_str() << "Check the file." << std::endl;
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

bool GetAttribute(std::string tag, std::string name, std::string * value)
{
	int v_index, v2_index;
	std::string svalue;

	name += "=\"";

	v_index = tag.find(name);
	v2_index = tag.find('"', v_index);

	if (v_index == -1 || v2_index == -1)
	{
		std::cout << "Can't find " << name.c_str() << "Check the file." << std::endl;
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

bool GetTag(std::string tag, TagNS::Tag_Tag * value)
{
	TagNS::Tag_Tag result;
	std::string s_k;
	std::string s_v;
	
	GetAttribute(tag, std::string("k"), &s_k);
	GetAttribute(tag, std::string("v"), &s_v);

	return true;
}

bool GetND(std::string tag, TagNS::Tag_nd * value)
{
	long ref;
	
	GetAttribute(tag, std::string("ref"), &ref);

	*value = TagNS::Tag_nd();

	return true;
}