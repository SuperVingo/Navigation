#include "MapReader.h"

#define ERROR_ATTR( x, y ) { AttributeError_in_terminal(x, y); \
							 return false; }

#define ERROR_FIND( x, y ) { FindError_in_terminal(x, y); \
							 return false; }

bool GetAttribute(std::wstring tag, const wchar_t name[], int * value)
{
	int v_index, v2_index, ivalue;
	std::wstring c_name = name;

	c_name += L"=\"";

	v_index = tag.find(c_name) + c_name.size();
	v2_index = tag.find(L"\"", v_index);

	if (v_index == -1 || v2_index == -1)
	{
		ERROR_FIND(name, L" ");
		value = nullptr;
		return false;
	}
	else
	{
		std::wstring temp = tag.substr(v_index, v2_index - v_index);

		ivalue = _wtoi(temp.c_str());

		*value = ivalue;
	}
	
	return true;
}


bool GetAttribute(std::wstring tag, const wchar_t name[], unsigned long long * value)
{
	int v_index, v2_index;
	unsigned long long lvalue;
	std::wstring c_name = name;

	c_name += L"=\"";

	v_index = tag.find(c_name) + c_name.size();
	v2_index = tag.find('"', v_index);

	if (v_index == -1 || v2_index == -1)
	{
		ERROR_FIND(name, L" ");
		return false;
	}
	else
	{
		std::wstring temp = tag.substr(v_index, v2_index - v_index);

		lvalue = _wtoi64(temp.c_str());

		*value = lvalue;
	}

	return true;
}

bool GetAttribute(std::wstring tag, const wchar_t name[], double * value)
{
	int v_index, v2_index;
	double dvalue;
	std::wstring c_name = name;

	c_name += L"=\"";

	v_index = tag.find(c_name) + c_name.size();
	v2_index = tag.find('"', v_index + 1);

	if (v_index == -1 || v2_index == -1)
	{
		ERROR_FIND(name, L" ");
		return false;
	}
	else
	{
		std::wstring temp = tag.substr(v_index, v2_index - v_index);

		dvalue = _wtof(temp.c_str());

		*value = dvalue;
	}

	return true;

}

bool GetAttribute(std::wstring tag, const wchar_t name[], bool * value)
{
	int v_index, v2_index;
	std::wstring c_name = name;

	c_name += L"=\"";

	v_index = tag.find(c_name) + c_name.size();
	v2_index = tag.find('"', v_index);

	if (v_index == -1 || v2_index == -1)
	{
		ERROR_FIND(name, L" ");
		return false;
	}
	else
	{
		std::wstring temp = tag.substr(v_index, v2_index - v_index);

		if (temp == L"true")
			*value = true;
		else
			*value = false;
	}

	return true;

}

bool GetAttribute(std::wstring tag, const wchar_t name[], char value[])
{
	int v_index, v2_index;
	std::wstring cvalue;
	std::wstring c_name = name;

	c_name += L"=\"";

	v_index = tag.find(c_name) + c_name.size();
	v2_index = tag.find('"', v_index);

	if (v_index == -1 || v2_index == -1)
	{
		ERROR_FIND(name, L" ");
		return false;
	}
	else
	{
		std::wstring temp = tag.substr(v_index, v2_index - v_index);

		cvalue = temp;

		value = (char*)cvalue.c_str();
	}

	return true;
}

bool GetAttribute(std::wstring tag, const wchar_t name[], std::wstring * value)
{
	int v_index, v2_index;
	std::wstring svalue;
	std::wstring c_name = name;

	c_name += L"=\"";

	v_index = tag.find(c_name) + c_name.size();
	v2_index = tag.find('"', v_index);

	if (v_index == -1 || v2_index == -1)
	{
		ERROR_FIND(name, L" ");
		return false;
	}
	else
	{
		std::wstring temp = tag.substr(v_index, v2_index - v_index);

		svalue = temp;

		*value = svalue;
	}
	return true;
}

bool GetND(std::wstring tag, TagNS::Tag_nd * value)
{
	unsigned long long ref;
	
	if (!GetAttribute(tag, L"ref", &ref))
		ERROR_ATTR(L"Tag - k", L" ");

	*value = TagNS::Tag_nd(ref);

	return true;
}

bool GetTag(std::wstring tag, TagNS::Tag_Tag * value)
{
	std::wstring s_k;
	std::wstring s_v;

	if (!GetAttribute(tag, L"k", &s_k))
		ERROR_ATTR(L"Tag - k", L" ");

	if (!GetAttribute(tag, L"v", &s_v))
		ERROR_ATTR(L"Tag - v", L" ");

	*value = TagNS::Tag_Tag(s_k, s_v);

	return true;
}

bool GetMember(std::wstring tag, TagNS::Tag_Member * value)
{
	std::wstring s_type;
	unsigned long long ref;
	std::wstring s_role;

	if (!GetAttribute(tag, L"type", &s_type))
		ERROR_ATTR(L"type", L" ");

	if (!GetAttribute(tag, L"ref", &ref))
		ERROR_ATTR(L"ref", L" ");

	if (!GetAttribute(tag, L"role", &s_role))
		ERROR_ATTR(L"role", L" ");


	*value = TagNS::Tag_Member(s_type, ref, s_role);

	return true;
}