#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <iomanip>
#include "MapReader.h"

bool MapReader::MapUpload(const char * filename)
{
	return false;
}

void MapReader::Print_XML_in_terminal()
{
	std::cout.setf(std::ios::fixed);
	std::cout << "-------------------- XML Tag -----------------------" << std::endl;
	std::cout << "	Version : " << std::cout.precision(2) << xml->version << std::endl;
	std::cout << "	Encoding : " << xml->encoding.c_str() << std::endl;
	std::cout << "----------------------------------------------------" << std::endl;
}

void MapReader::Print_OSM_in_terminal()
{
}

void MapReader::Print_Bounds_in_terminal()
{
}

void MapReader::Print_Node_Index_in_terminal(int index)
{
}

void MapReader::Print_Node_ID_in_terminal(int id)
{
}

void MapReader::Print_Way_Index_in_terminal(int index)
{
}

void MapReader::Print_Way_ID_in_terminal(int id)
{
}

void MapReader::Print_Relation_Index_in_terminal(int index)
{
}

void MapReader::Print_Relation_ID_in_terminal(int id)
{
}

bool MapReader::Get_Node_Index(TagNS::Tag_Node * Node, int index)
{
	return false;
}

bool MapReader::Get_Node_ID(TagNS::Tag_Node * Node, int id)
{
	return false;
}

bool MapReader::Get_Way_Index(TagNS::Tag_Way * way, int index)
{
	return false;
}

bool MapReader::Get_Way_ID(TagNS::Tag_Way * way, int id)
{
	return false;
}

bool MapReader::Get_Relation_Index(TagNS::Tag_Relation * relation, int index)
{
	return false;
}

bool MapReader::Get_Relation_ID(TagNS::Tag_Relation * relation, int id)
{
	return false;
}

bool MapReader::Parshing_XML(std::string tag_line)
{
	std::string s_encoding;
	double d_version;

	if (!GetAttribute(tag_line, "version", &d_version))
		return false;

	if (!GetAttribute(tag_line, "encoding", &s_encoding))
		return false;

	xml->version = d_version;
	xml->encoding = s_encoding;

	return true;
}

bool MapReader::Parshing_OSM(std::string tag_line)
{
	double d_version;
	std::string s_generator;
	std::string s_copyright;
	std::string s_attribution;
	std::string s_license;

	if (!GetAttribute(tag_line, "version", &d_version))
		return false;

	if (!GetAttribute(tag_line, "generator", &s_generator))
		return false;

	if (!GetAttribute(tag_line, "copyright", &s_copyright))
		return false;

	if (!GetAttribute(tag_line, "attribution", &s_attribution))
		return false;

	if (!GetAttribute(tag_line, "license", &s_license))
		return false;

	osm->version = d_version;
	osm->generator = s_generator;
	osm->copyright = s_copyright;
	osm->attribution = s_attribution;
	osm->license = s_license;

	return true;
}

bool MapReader::Parshing_Bounds(std::string tag_line)
{
	double d_minlat;
	double d_minlon;
	double d_maxlat;
	double d_maxlon;

	if (!GetAttribute(tag_line, "version", &d_minlat))
		return false;

	if (!GetAttribute(tag_line, "minlon", &d_minlon))
		return false;

	if (!GetAttribute(tag_line, "maxlat", &d_maxlat))
		return false;

	if (!GetAttribute(tag_line, "maxlon", &d_maxlon))
		return false;
		
	bounds->minlat = d_minlat;
	bounds->minlon = d_minlon;
	bounds->maxlat = d_maxlat;
	bounds->maxlon = d_maxlon;

	return true;
}

bool MapReader::Parshing_Node(std::string tag_line)
{	
	long l_id;
	bool b_visible;
	int i_version;
	long l_changeset;
	std::string s_timestamp;
	std::string s_user;
	long l_uid;
	double d_lat;
	double d_lon;
	std::vector<TagNS::Tag_Tag> v_tag;

	GetAttribute(tag_line, "id", &l_id);
	GetAttribute(tag_line, "visible", &b_visible);
	GetAttribute(tag_line, "version", &i_version);
	GetAttribute(tag_line, "changeset", &l_changeset);
	GetAttribute(tag_line, "timestamp", &s_timestamp);
	GetAttribute(tag_line, "user", &s_user);
	GetAttribute(tag_line, "uid", &l_uid);
	GetAttribute(tag_line, "lat", &d_lat);
	GetAttribute(tag_line, "lon", &d_lon);

	bool exit = false;

	while (!exit)
	{
		int v_index = 0, v2_index = 0;
		v_index = tag_line.find("<tag", v2_index + 1);
		v2_index = tag_line.find("/>", v_index + 1);

		if (v_index == -1)
		{
			exit = true;
			continue;
		}

		std::string temp = tag_line.substr(v_index, v2_index);
		std::string k, v;
		
		GetAttribute(temp, "k", &k);
		GetAttribute(temp, "v", &v);

		v_tag.push_back(TagNS::Tag_Tag(k, v));
	}

	nodes.push_back(TagNS::Tag_Node(l_id, b_visible, i_version, l_changeset, s_timestamp, s_user, l_uid, d_lat, d_lon, v_tag));

	return true;
}

bool MapReader::Parshing_Way(std::string tag_line)
{
	long l_id;
	bool b_visible;
	int i_version;
	long l_changeset;
	std::string s_timestamp;
	std::string s_user;
	long l_uid;
	std::vector<TagNS::Tag_nd> v_nd;
	std::vector<TagNS::Tag_Tag> v_tag;

	GetAttribute(tag_line, "id", &l_id);
	GetAttribute(tag_line, "visible", &b_visible);
	GetAttribute(tag_line, "version", &i_version);
	GetAttribute(tag_line, "changeset", &l_changeset);
	GetAttribute(tag_line, "timestamp", &s_timestamp);
	GetAttribute(tag_line, "user", &s_user);
	GetAttribute(tag_line, "uid", &l_uid);

	bool exit = false;

	while (!exit)
	{
		int v_index = 0, v2_index = 0;
		v_index = tag_line.find("<nd", v2_index + 1);
		v2_index = tag_line.find("/>", v_index + 1);

		if (v_index == -1)
		{
			exit = true;
			continue;
		}

		std::string tag = tag_line.substr(v_index, v2_index);
		TagNS::Tag_Tag temp
		v_nd.push_back(GetND(tag));
	}

	exit = false;

	while (!exit)
	{
		int v_index = 0, v2_index = 0;
		v_index = tag_line.find("<tag", v2_index + 1);
		v2_index = tag_line.find("/>", v_index + 1);

		if (v_index == -1)
		{
			exit = true;
			continue;
		}

		std::string tag = tag_line.substr(v_index, v2_index);
		TagNS::Tag_Tag temp;

		if (!GetTag(tag, &temp))
		{
			std::cout
		}

		v_tag.push_back(temp);
	}

	ways.push_back(TagNS::Tag_Way(l_id, b_visible, i_version, l_changeset, s_timestamp, s_user, l_uid, v_nd, v_tag));

	return true;
}

bool MapReader::Parshing_Relation(std::string tag_line)
{
	long l_id;
	bool b_visible;
	int i_version;
	long l_changeset;
	std::string s_timestamp;
	std::string s_user;
	long l_uid;
	std::vector<TagNS::Tag_Member> v_member;
	std::vector<TagNS::Tag_Tag> v_tag;

	GetAttribute(tag_line, "id", &l_id);
	GetAttribute(tag_line, "visible", &b_visible);
	GetAttribute(tag_line, "version", &i_version);
	GetAttribute(tag_line, "changeset", &l_changeset);
	GetAttribute(tag_line, "timestamp", &s_timestamp);
	GetAttribute(tag_line, "user", &s_user);
	GetAttribute(tag_line, "uid", &l_uid);

	bool exit = false;

	while (!exit)
	{
		int v_index = 0, v2_index = 0;
		v_index = tag_line.find("<member", v2_index + 1);
		v2_index = tag_line.find("/>", v_index + 1);

		if (v_index == -1)
		{
			exit = true;
			continue;
		}

		std::string temp = tag_line.substr(v_index, v2_index);

		v_member.push_back(GetMember(temp));
	}

	exit = false;

	while (!exit)
	{
		int v_index = 0, v2_index = 0;
		v_index = tag_line.find("<tag", v2_index + 1);
		v2_index = tag_line.find("/>", v_index + 1);

		if (v_index == -1)
		{
			exit = true;
			continue;
		}

		std::string temp = tag_line.substr(v_index, v2_index);

		v_tag.push_back(GetTag(temp));
	}

	relations.push_back(TagNS::Tag_Relation(l_id, b_visible, i_version, l_changeset, s_timestamp, s_user, l_uid, v_member, v_tag));

	return true;
}
