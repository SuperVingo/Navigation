#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <iomanip>
#include <string>
#include <locale.h>

#include "Tag.h"
#include "MapReader.h"

#define ERROR_ATTR( x, y ) { AttributeError_in_terminal(x, y); \
							 return false; }

#define ERROR_FIND( x, y ) { FindError_in_terminal(x, y); \
							 return false; }

#define ERROR_OPEN( x, y ) { FileopenError_in_terminal(x, y); \
							 return false; }

#define ERROR_PARSE( x, y) { ParsingError_in_terminal(x, y); \
							 return false;}

MapReader::MapReader(void)
{
	all = new TagNS::Tag_ALL();
	xml = new TagNS::Tag_XML();
	osm = new TagNS::Tag_OSM();
	bounds = new TagNS::Tag_Bounds();
}

MapReader::MapReader(const char * filename)
{
	all = new TagNS::Tag_ALL();
	xml = new TagNS::Tag_XML();
	osm = new TagNS::Tag_OSM();
	bounds = new TagNS::Tag_Bounds();

	MapUpload(filename);
}

bool MapReader::MapUpload(const char * filename)
{
	_wsetlocale(LC_ALL, L"korean");

	std::ifstream fp;
	fp.open(filename);

	if (!fp.is_open())
	{
		ERROR_OPEN(filename, "Please Check the file.");
	}

	std::cout << "File opend. Wait a minute." << std::endl;
	// TODO: Calculate the processing time belong file size. 

	bool exit = false;
	std::string tag;
	long v_index = 0, v2_index = 0;

	while(!exit)
	{
		char temp[250] = { 0 };
		fp.getline(temp, 250);

		tag = temp;

		std::cout << std::endl << tag.c_str() << std::endl << std::endl;

		if (fp.eof())
		{
			tag = "\0";
			exit = true;
			continue;
		}

		// XML Tag Parsing
		v_index = tag.find("<?xml", v_index);
		if (v_index == -1)
		{
			v_index = 0;
			v_index = tag.find("<? xml", v_index);
			if (v_index == -1)
				continue;
			else
				break;
		}
		else
			break;
	}

	if (tag == "\0")
		ERROR_FIND("XML", "Please Check the file");

	if (!Parsing_XML(tag))
		ParsingError_in_terminal("XML", "Please Check the file");

	Print_XML_in_terminal();

	exit = false;
	tag.clear();
	v_index = 0, v2_index = 0;

	while (!exit)
	{
		char temp[250] = { 0 };
		fp.getline(temp, 250);

		tag = temp;

		std::cout << std::endl << tag.c_str() << std::endl << std::endl;

		if (fp.eof())
		{
			tag = "\0";
			exit = true;
			continue;
		}

		// OSM Tag Parsing
		v_index = tag.find("<osm", v_index);
		if (v_index == -1)
		{
			v_index = 0;
			v_index = tag.find("<osm", v_index);
			if (v_index == -1)
				continue;
			else
				break;
		}
		else
			break;
	}

	if (tag == "\0")
		ERROR_FIND("OSM", "Please Check the file");

	if (!Parsing_OSM(tag))
		ParsingError_in_terminal("OSM", "Please Check the file");

	Print_OSM_in_terminal();

	exit = false;
	tag.clear();
	v_index = 0, v2_index = 0;

	while (!exit)
	{
		char temp[250] = { 0 };
		fp.getline(temp, 250);

		tag = temp;

		std::cout << std::endl << tag.c_str() << std::endl << std::endl;

		if (fp.eof())
		{
			tag = "\0";
			exit = true;
			continue;
		}

		// Bounds Tag Parsing
		v_index = tag.find("<bounds", v_index);
		if (v_index == -1)
		{
			v_index = 0;
			v_index = tag.find("< bounds", v_index);
			if (v_index == -1)
				continue;
			else
				break;
		}
		else
			break;
	}

	if (tag == "\0")
		ERROR_FIND("Bounds", "Please Check the file");

	if (!Parsing_Bounds(tag))
		ParsingError_in_terminal("Bounds", "Please Check the file");

	Print_Bounds_in_terminal();

	exit = false;
	std::wstring node;
	v_index = 0, v2_index = 0;

	while (!exit)
	{
		wchar_t temp[250] = { 0 };

		fp.getline(temp, 250);

		node = temp;

		std::cout << std::endl << node.c_str() << std::endl << std::endl;

		v_index = node.find("/>", tag.size() - 3);
		if (v_index != -1)
			std::cout << "Finding Tag..." << std::endl;

		break;
	}

	/*if (tag == "\0")
		ERROR_FIND("Bounds", "Please Check the file");

	if (!Parsing_Bounds(tag))
		ParsingError_in_terminal("Bounds", "Please Check the file");

	Print_Bounds_in_terminal();*/

	return true;
}

////////////////////////////////////////////////////////////////////////////////////

#pragma region "Print Method"

void MapReader::Print_XML_in_terminal()
{
	std::cout.setf(std::ios::fixed);
	std::cout.precision(1);
	std::cout << "-------------------- XML Tag -----------------------" << std::endl;
	std::cout << "	Version : " << xml->GetVersion() << std::endl;
	std::cout << "	Encoding : " << xml->encoding.c_str() << std::endl;
	std::cout << "----------------------------------------------------" << std::endl;
}

void MapReader::Print_OSM_in_terminal()
{

	std::cout.setf(std::ios::fixed);
	std::cout.precision(1);
	std::cout << "-------------------- OSM Tag -----------------------" << std::endl;
	std::cout << "	Version : " << osm->version << std::endl;
	std::cout << "	Generator : " << osm->generator.c_str() << std::endl;
	std::cout << "	Copyright : " << osm->copyright.c_str() << std::endl;
	std::cout << "	Attribution : " << osm->attribution.c_str() << std::endl;
	std::cout << "	License : " << osm->license.c_str() << std::endl;
	std::cout << "----------------------------------------------------" << std::endl;
}

void MapReader::Print_Bounds_in_terminal()
{
	std::cout.setf(std::ios::fixed);
	std::cout.precision(7);
	std::cout << "-------------------- Bounds Tag -----------------------" << std::endl;
	std::cout << "	Min Latitude : " << bounds->minlat << std::endl;
	std::cout << "	Min Longitude : " << bounds->minlon << std::endl;
	std::cout << "	Max Latitude : " << bounds->maxlat << std::endl;
	std::cout << "	Max Longitude : " << bounds->maxlon << std::endl;
	std::cout << "----------------------------------------------------" << std::endl;
}

void MapReader::Print_Node_in_terminal(TagNS::Tag_Node node)
{
	std::cout.setf(std::ios::fixed);
	std::cout.precision(7);
	std::cout << "-------------------- Node Tag -----------------------" << std::endl;
	std::cout << "	ID : " << node.id << std::endl;
	std::cout << "	Visible : " << node.visible << std::endl;
	std::cout << "	Version : " << node.version << std::endl;
	std::cout << "	Changeset : " << node.changeset << std::endl;
	std::cout << "	Timestamp : " << node.timestamp.c_str() << std::endl;
	std::cout << "	User : " << node.user.c_str() << std::endl;
	std::cout << "	UID : " << node.uid << std::endl;
	std::cout << "	Latitude : " << node.lat << std::endl;
	std::cout << "	Longitude : " << node.lon << std::endl;

	for (unsigned int i = 0; i < node.tag.size(); i++)
	{
		std::cout << std::endl << i << " Tag" << std::endl;
		Print_Tag(node.tag[i]);
		std::cout << std::endl;
	}

	std::cout << "----------------------------------------------------" << std::endl;
}

void MapReader::Print_Node_Index_in_terminal(int index)
{
	Print_Node_in_terminal(nodes[index - 1]);
}

void MapReader::Print_Node_ID_in_terminal(int id)
{
	for(unsigned int i = 0; i < nodes.size(); i++)
		if (nodes[i].id == id)
		{
			Print_Node_in_terminal(nodes[i]);
			break;
		}
}

void MapReader::Print_Way_in_terminal(TagNS::Tag_Way way)
{
	std::cout.setf(std::ios::fixed);
	std::cout << "-------------------- Node Tag -----------------------" << std::endl;
	std::cout << "	ID : " << way.id << std::endl;
	std::cout << "	Visible : " << way.visible << std::endl;
	std::cout << "	Version : " << way.version << std::endl;
	std::cout << "	Changeset : " << way.changeset << std::endl;
	std::cout << "	Timestamp : " << way.timestamp.c_str() << std::endl;
	std::cout << "	User : " << way.user.c_str() << std::endl;
	std::cout << "	UID : " << way.uid << std::endl;

	for (unsigned int i = 0; i < way.nd.size(); i++)
	{
		std::cout << std::endl << i << " nd" << std::endl;
		Print_nd(way.nd[i]);
		std::cout << std::endl;
	}

	for (unsigned int i = 0; i < way.tag.size(); i++)
	{
		std::cout << std::endl << i << " Tag" << std::endl;
		Print_Tag(way.tag[i]);
		std::cout << std::endl;
	}

	std::cout << "----------------------------------------------------" << std::endl;
}

void MapReader::Print_Way_Index_in_terminal(int index)
{
	Print_Way_in_terminal(ways[index - 1]);
}

void MapReader::Print_Way_ID_in_terminal(int id)
{
	for (unsigned int i = 0; i < ways.size(); i++)
		if (ways[i].id == id)
		{
			Print_Way_in_terminal(ways[i]);
			break;
		}
}

void MapReader::Print_Relation_in_terminal(TagNS::Tag_Relation rel)
{
	std::cout.setf(std::ios::fixed);
	std::cout << "-------------------- Node Tag -----------------------" << std::endl;
	std::cout << "	ID : " << rel.id << std::endl;
	std::cout << "	Visible : " << rel.visible << std::endl;
	std::cout << "	Version : " << rel.version << std::endl;
	std::cout << "	Changeset : " << rel.changeset << std::endl;
	std::cout << "	Timestamp : " << rel.timestamp.c_str() << std::endl;
	std::cout << "	User : " << rel.user.c_str() << std::endl;
	std::cout << "	UID : " << rel.uid << std::endl;

	for (unsigned int i = 0; i < rel.member.size(); i++)
	{
		std::cout << std::endl << i << " nd" << std::endl;
		Print_Member(rel.member[i]);
		std::cout << std::endl;
	}

	for (unsigned int i = 0; i < rel.tag.size(); i++)
	{
		std::cout << std::endl << i << " Tag" << std::endl;
		Print_Tag(rel.tag[i]);
	}

	std::cout << "----------------------------------------------------" << std::endl;
}

void MapReader::Print_Relation_Index_in_terminal(int index)
{
	Print_Relation_in_terminal(relations[index - 1]);
}

void MapReader::Print_Relation_ID_in_terminal(int id)
{
	for (unsigned int i = 0; i < relations.size(); i++)
		if (ways[i].id == id)
		{
			Print_Relation_in_terminal(relations[i]);
			break;
		}
}

void MapReader::Print_Tag(TagNS::Tag_Tag tag)
{
	std::cout << "k : " << tag.k.c_str() << std::endl;
	std::cout << "v : " << tag.v.c_str() << std::endl;
}

void MapReader::Print_nd(TagNS::Tag_nd nd)
{
	std::cout << "ref : " << nd.ref << std::endl;
}

void MapReader::Print_Member(TagNS::Tag_Member member)
{
	std::cout << "type : " << member.type.c_str() << std::endl;
	std::cout << "ref : " << member.ref << std::endl;
	std::cout << "role : " << member.role.c_str() << std::endl;
}

#pragma endregion

///////////////////////////////////////////////////////////////////////

#pragma region "Get Some Method"

bool MapReader::Get_Node_Index(TagNS::Tag_Node * Node, unsigned int index)
{
	if (nodes.size() <= index)
	{
		Node = nullptr;
		return false;
	}
	else
	{
		*Node = nodes[index - 1];
		return true;
	}
}

bool MapReader::Get_Node_ID(TagNS::Tag_Node * Node, int id)
{
	for(unsigned int i = 0; i < nodes.size(); i++)
		if (nodes[i].id == id)
		{
			*Node = nodes[i];
			return true;
		}

	Node = nullptr;
	return false;
}

bool MapReader::Get_Way_Index(TagNS::Tag_Way * way, unsigned int index)
{
	if (ways.size() <= index)
	{
		way = nullptr;
		return false;
	}
	else
	{
		*way = ways[index - 1];
		return true;
	}
}

bool MapReader::Get_Way_ID(TagNS::Tag_Way * way, int id)
{
	for (unsigned int i = 0; i < ways.size(); i++)
		if (ways[i].id == id)
		{
			*way = ways[i];
			return true;
		}

	way = nullptr;
	return false;
}

bool MapReader::Get_Relation_Index(TagNS::Tag_Relation * relation, unsigned int index)
{
	if (relations.size() <= index)
	{
		relation = nullptr;
		return false;
	}
	else
	{
		*relation = relations[index - 1];
		return true;
	}
}

bool MapReader::Get_Relation_ID(TagNS::Tag_Relation * relation, int id)
{
	for (unsigned int i = 0; i < relations.size(); i++)
		if (relations[i].id == id)
		{
			*relation = relations[i];
			return true;
		}

	relation = nullptr;
	return false;
}

#pragma endregion

//////////////////////////////////////////////////////////////////////////////////////

#pragma region "Parsing Method"

bool MapReader::Parsing_XML(std::string tag_line)
{
	std::string s_encoding;
	double d_version;

	if (!GetAttribute(tag_line, "version", &d_version))
		ERROR_ATTR("XML - version", " ");

	if (!GetAttribute(tag_line, "encoding", &s_encoding))
		ERROR_ATTR("XML - encoding", " ");

	xml->version = d_version;
	xml->encoding = s_encoding;

	return true;
}

bool MapReader::Parsing_OSM(std::string tag_line)
{
	double d_version;
	std::string s_generator;
	std::string s_copyright;
	std::string s_attribution;
	std::string s_license;

	if (!GetAttribute(tag_line, "version", &d_version))
		ERROR_ATTR("OSM - version", " ");

	if (!GetAttribute(tag_line, "generator", &s_generator))
		ERROR_ATTR("OSM - generator", " ");

	if (!GetAttribute(tag_line, "copyright", &s_copyright))
		ERROR_ATTR("OSM - copyright", " ");

	if (!GetAttribute(tag_line, "attribution", &s_attribution))
		ERROR_ATTR("OSM - attribution", " ");

	if (!GetAttribute(tag_line, "license", &s_license))
		ERROR_ATTR("OSM - license", " ");

	osm->version = d_version;
	osm->generator = s_generator;
	osm->copyright = s_copyright;
	osm->attribution = s_attribution;
	osm->license = s_license;

	return true;
}

bool MapReader::Parsing_Bounds(std::string tag_line)
{
	double d_minlat;
	double d_minlon;
	double d_maxlat;
	double d_maxlon;

	if (!GetAttribute(tag_line, "minlat", &d_minlat))
		ERROR_ATTR("Bounds - minlat", " ");

	if (!GetAttribute(tag_line, "minlon", &d_minlon))
		ERROR_ATTR("Bounds - minlon", " ");

	if (!GetAttribute(tag_line, "maxlat", &d_maxlat))
		ERROR_ATTR("Bounds - maxlat", " ");

	if (!GetAttribute(tag_line, "maxlon", &d_maxlon))
		ERROR_ATTR("Bounds - maxlon", " ");
		
	bounds->minlat = d_minlat;
	bounds->minlon = d_minlon;
	bounds->maxlat = d_maxlat;
	bounds->maxlon = d_maxlon;

	return true;
}

bool MapReader::Parsing_Node(std::string tag_line)
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

	if (!GetAttribute(tag_line, "id", &l_id))
		ERROR_ATTR("Node - id", " ");

	if (!GetAttribute(tag_line, "visible", &b_visible))
		ERROR_ATTR("Node - visible", " ")

	if (!GetAttribute(tag_line, "version", &i_version))
		ERROR_ATTR("Node - version", " ");

	if (!GetAttribute(tag_line, "changeset", &l_changeset))
		ERROR_ATTR("Node - changeset", " ");

	if (!GetAttribute(tag_line, "timestamp", &s_timestamp))
		ERROR_ATTR("Node - timestamp", " ");

	if (!GetAttribute(tag_line, "user", &s_user))
		ERROR_ATTR("Node - user", " ");

	if (!GetAttribute(tag_line, "uid", &l_uid))
		ERROR_ATTR("Node - uid", " ");

	if (!GetAttribute(tag_line, "lat", &d_lat))
		ERROR_ATTR("Node - lat", " ");

	if (!GetAttribute(tag_line, "lon", &d_lon))
		ERROR_ATTR("Node - lon", " ");

	bool exit = false;

	while (!exit)
	{
		int v_index = 0, v2_index = 0;
		v_index = tag_line.find("<tag", v2_index + 1);
		v2_index = tag_line.find("/>", v_index + 1);

		if (v_index == -1 || v2_index == -1)
		{
			ERROR_FIND("Node - Tag", " ");
			exit = true;
			continue;
		}

		std::string temp = tag_line.substr(v_index, v2_index);
		std::string k, v;
		
		if (!GetAttribute(temp, "k", &k))
			ERROR_ATTR("Node - Tag - k", " ");
		if (!GetAttribute(temp, "v", &v))
			ERROR_ATTR("Node - Tag - v", " ");

		v_tag.push_back(TagNS::Tag_Tag(k, v));
	}

	nodes.push_back(TagNS::Tag_Node(l_id, b_visible, i_version, l_changeset, s_timestamp, s_user, l_uid, d_lat, d_lon, v_tag));

	return true;
}

bool MapReader::Parsing_Way(std::string tag_line)
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

	if (!GetAttribute(tag_line, "id", &l_id))
		ERROR_ATTR("Way - id", " ");

	if (!GetAttribute(tag_line, "visible", &b_visible))
		ERROR_ATTR("Way - visible", " ");

	if (!GetAttribute(tag_line, "version", &i_version))
		ERROR_ATTR("Way - version", " ");

	if (!GetAttribute(tag_line, "changeset", &l_changeset))
		ERROR_ATTR("Way - changeset", " ");

	if (!GetAttribute(tag_line, "timestamp", &s_timestamp))
		ERROR_ATTR("Way - timestamp", " ");

	if (!GetAttribute(tag_line, "user", &s_user))
		ERROR_ATTR("Way - user", " ");

	if (!GetAttribute(tag_line, "uid", &l_uid))
		ERROR_ATTR("Way - uid", " ");

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
		TagNS::Tag_nd temp;
		if (!GetND(tag, &temp))
			ERROR_ATTR("Way - nd", " ");

		v_nd.push_back(temp);
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
			ERROR_ATTR("Way - Tag", " ");

		v_tag.push_back(temp);
	}

	ways.push_back(TagNS::Tag_Way(l_id, b_visible, i_version, l_changeset, s_timestamp, s_user, l_uid, v_nd, v_tag));

	return true;
}

bool MapReader::Parsing_Relation(std::string tag_line)
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

	if (!GetAttribute(tag_line, "id", &l_id))
		ERROR_ATTR("Relation - id", " ");

	if (!GetAttribute(tag_line, "visible", &b_visible))
		ERROR_ATTR("Relation - visible", " ");

	if (!GetAttribute(tag_line, "version", &i_version))
		ERROR_ATTR("Relation - version", " ");

	if (!GetAttribute(tag_line, "changeset", &l_changeset))
		ERROR_ATTR("Relation - changeset", " ");

	if (!GetAttribute(tag_line, "timestamp", &s_timestamp))
		ERROR_ATTR("Relation - timestamp", " ");

	if (!GetAttribute(tag_line, "user", &s_user))
		ERROR_ATTR("Relation - user", " ");

	if (!GetAttribute(tag_line, "uid", &l_uid))
		ERROR_ATTR("Relation - uid", " ");

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

		std::string tag = tag_line.substr(v_index, v2_index);
		TagNS::Tag_Member temp;

		if (!GetMember(tag, &temp))
			ERROR_ATTR("Relation - Member", " ");

		v_member.push_back(temp);
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
			ERROR_ATTR("Relation - Tag", " ");

		v_tag.push_back(temp);
	}

	relations.push_back(TagNS::Tag_Relation(l_id, b_visible, i_version, l_changeset, s_timestamp, s_user, l_uid, v_member, v_tag));

	return true;
}

#pragma endregion