#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <iomanip>
#include <string>
#include <locale.h>
#include <codecvt>

#include "Tag.h"
#include "MapReader.h"

#define ERROR_ATTR( x, y ) { AttributeError_in_terminal(x, y); \
							 system("pause"); \
							 return false; }

#define ERROR_FIND( x, y ) { FindError_in_terminal(x, y); \
							 system("pause"); \
							 return false; }

#define ERROR_OPEN( x, y ) { FileopenError_in_terminal(x, y); \
							 system("pause"); \
							 return false; }

#define ERROR_PARSE( x, y) { ParsingError_in_terminal(x, y); \
							 system("pause"); \
							 return false;}

MapReader::MapReader(void)
{
	all = new TagNS::Tag_ALL();
	xml = new TagNS::Tag_XML();
	osm = new TagNS::Tag_OSM();
	bounds = new TagNS::Tag_Bounds();
}

MapReader::MapReader(const wchar_t * filename)
{
	all = new TagNS::Tag_ALL();
	xml = new TagNS::Tag_XML();
	osm = new TagNS::Tag_OSM();
	bounds = new TagNS::Tag_Bounds();

	MapUpload(filename);
}

bool MapReader::MapUpload(const wchar_t * filename)
{

	std::locale::global(std::locale("kor")); //"UTF-8";
	std::wcout.imbue(std::locale("korean"));

	std::wifstream fp;
	fp.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));
	fp.open(filename);

	if (!fp.is_open())
	{
		ERROR_OPEN(filename, L"Please Check the file.");
	}

	std::wcout << "File opend. Wait a minute." << std::endl;
	// TODO: Calculate the processing time belong file size. 

	////////////////////////////// XML //////////////////////////////////////
	bool exit = false;
	std::wstring tag;
	long v_index = 0, v2_index = 0;

	while(!exit)
	{
		wchar_t temp[250] = { 0 };
		fp.getline(temp, 250);

		tag = temp;

		std::wcout << std::endl << tag.c_str() << std::endl << std::endl;

		if (fp.eof())
		{
			tag = L"\0";
			exit = true;
			continue;
		}

		// XML Tag Parsing
		v_index = tag.find(L"<?xml", v_index);
		if (v_index == -1)
		{
			v_index = 0;
			v_index = tag.find(L"<? xml", v_index);
			if (v_index == -1)
				continue;
			else
				break;
		}
		else
			break;
	}

	if (tag == L"\0")
		ERROR_FIND(L"XML", L"Please Check the file");

	if (!Parsing_XML(tag))
		ParsingError_in_terminal(L"XML", L"Please Check the file");

	Print_XML_in_terminal();

	////////////////////////////// OSM //////////////////////////////////////
	exit = false;
	tag.clear();
	v_index = 0, v2_index = 0;

	while (!exit)
	{
		wchar_t temp[250] = { 0 };
		fp.getline(temp, 250);

		tag = temp;

		std::wcout << std::endl << tag.c_str() << std::endl << std::endl;

		if (fp.eof())
		{
			tag = L"\0";
			exit = true;
			continue;
		}

		// OSM Tag Parsing
		v_index = tag.find(L"<osm", v_index);
		if (v_index == -1)
		{
			v_index = 0;
			v_index = tag.find(L"<osm", v_index);
			if (v_index == -1)
				continue;
			else
				break;
		}
		else
			break;
	}

	if (tag == L"\0")
		ERROR_FIND(L"OSM", L"Please Check the file");

	if (!Parsing_OSM(tag))
		ParsingError_in_terminal(L"OSM", L"Please Check the file");

	Print_OSM_in_terminal();

	////////////////////////////// Bounds //////////////////////////////////////

	exit = false;
	tag.clear();
	v_index = 0, v2_index = 0;

	while (!exit)
	{
		wchar_t temp[250] = { 0 };
		fp.getline(temp, 250);

		tag = temp;

		std::wcout << std::endl << tag.c_str() << std::endl << std::endl;

		if (fp.eof())
		{
			tag = L"\0";
			exit = true;
			continue;
		}

		// Bounds Tag Parsing
		v_index = tag.find(L"<bounds", v_index);
		if (v_index == -1)
		{
			v_index = 0;
			v_index = tag.find(L"< bounds", v_index);
			if (v_index == -1)
				continue;
			else
				break;
		}
		else
			break;
	}

	if (tag == L"\0")
		ERROR_FIND(L"Bounds", L"Please Check the file");

	if (!Parsing_Bounds(tag))
		ParsingError_in_terminal(L"Bounds", L"Please Check the file");

	Print_Bounds_in_terminal();

////////////////////////////// Node //////////////////////////////////////

	fp.clear();
	fp.seekg(0, std::ios_base::beg);
	exit = false;
	tag.clear();
	std::wstring w_temp;
	w_temp.clear();
	v_index = 0, v2_index = 0;
	bool exit_node = false;

	while (!exit_node)
	{
		bool node = false;
		bool not_node = false;
		wchar_t temp[250] = { 0 };
		tag.clear();
		exit = false;

		fp.getline(temp, 250);

		tag += temp;

		if (fp.eof())
		{
			tag = L"\0";
			exit_node = true;
			continue;
		}

		while (!exit)
		{
			if (node == false)
			{
				//Find Node
				v_index = tag.find(L"<node", 0);
				v2_index = tag.find(L"/>", 0);
				if (v_index == -1)
				{
					not_node = true;
					exit = true;
					continue;
				}
				//Find Tag
				else if(v_index != -1 && v2_index == -1)
				{
					node = true;
					std::wcout << "Finding Tag..." << std::endl;
				}
				//No Tag, go back.
				else if(v_index != -1 && v2_index != -1)
				{ 
					std::wcout << "No Tag..." << std::endl;
					break;
				}
			}
			else
			{
				//find tag
				memset(temp, 0, sizeof(temp));

				fp.getline(temp, 250);

				w_temp = temp;

				v_index = w_temp.find(L"<tag", 0);
				if (v_index == -1)
				{
					v_index = w_temp.find(L"</node>", 0);
					if (v_index != -1) // Node End. go back.
					{
						tag += w_temp;
						break;
					}
					
				}
				else
				{
					//Find Tag, And Add
					std::wcout.clear();
					std::wcout << "Tag Finded..." << w_temp << std::endl;
					tag += w_temp;
					continue;
				}
			}
		}

		if (!not_node)
		{
			std::wcout << tag << std::endl << std::endl;

			if (!Parsing_Node(tag))
				ParsingError_in_terminal(L"Node", L"Please Check the file");
		}
	}

////////////////////////////// Way //////////////////////////////////////

	fp.clear();
	fp.seekg(0, std::ios_base::beg);
	exit = false;
	tag.clear();
	w_temp.clear();
	v_index = 0, v2_index = 0;
	bool exit_way = false;

	while (!exit_way)
	{
		bool way = false;
		bool not_way = false;
		wchar_t temp[250] = { 0 };
		tag.clear();
		exit = false;

		fp.getline(temp, 250);

		tag += temp;

		if (fp.eof())
		{
			tag = L"\0";
			exit_way = true;
			continue;
		}

		while (!exit)
		{
			//Find Way
			if (way == false)
			{
				v_index = tag.find(L"<way", 0);
				v2_index = tag.find(L"/>", 0);
				if (v_index == -1)
				{
					not_way = true;
					exit = true;
					continue;
				}
				//Find nd Tag
				else if (v_index != -1 && v2_index == -1)
				{
					way = true;
					std::wcout << "Finding nd Tag..." << std::endl;
				}
				//No nd Tag, go back.
				else if (v_index != -1 && v2_index != -1)
				{
					std::wcout << "No nd Tag..." << std::endl;
					break;
				}
			}
			else
			{
				//find tag
				memset(temp, 0, sizeof(temp));

				fp.getline(temp, 250);

				w_temp = temp;

				v_index = w_temp.find(L"<nd", 0);
				if (v_index == -1)
				{
					v_index = w_temp.find(L"</way>", 0); // Way End. go back.
					if (v_index != -1)
					{
						tag += w_temp;
						break;
					}

				}
				else
				{
					//Find Tag, And Add
					std::wcout.clear();
					std::wcout << "nd Tag Finded..." << w_temp << std::endl;
					tag += w_temp;
					continue;
				}
			}
		}

		if (!not_way)
		{
			std::wcout << tag << std::endl << std::endl;

			if (!Parsing_Way(tag))
				ParsingError_in_terminal(L"Way", L"Please Check the file");
		}
	}

	////////////////////////////// Find Relation //////////////////////////////////////

	fp.clear();
	fp.seekg(0, std::ios_base::beg);
	exit = false;
	tag.clear();
	w_temp.clear();
	v_index = 0, v2_index = 0;
	bool exit_relation = false;

	while (!exit_relation)
	{
		bool relation = false;
		bool not_relation = false;
		wchar_t temp[250] = { 0 };
		tag.clear();
		exit = false;

		fp.getline(temp, 250);

		tag += temp;

		if (fp.eof())
		{
			tag = L"\0";
			exit_relation = true;
			continue;
		}

		while (!exit)
		{
			//Find relation
			if (relation == false)
			{
				v_index = tag.find(L"<relation", 0);
				v2_index = tag.find(L"/>", 0);
				if (v_index == -1)
				{
					not_relation = true;
					exit = true;
					continue;
				}
				//Find Subproperty Tag
				else if (v_index != -1 && v2_index == -1)
				{
					relation = true;
					std::wcout << "Finding Subproperty Tag..." << std::endl;
				}
				//No Subproperty Tag, go back.
				else if (v_index != -1 && v2_index != -1)
				{
					std::wcout << "No Subproperty Tag..." << std::endl;
					break;
				}
			}
			else
			{
				//find tag
				memset(temp, 0, sizeof(temp));

				fp.getline(temp, 250);

				w_temp = temp;

				v_index = w_temp.find(L"<member", 0);
				if (v_index == -1)
				{
					v_index = w_temp.find(L"<tag", 0);
					if (v_index == -1)
					{
						v_index = w_temp.find(L"</relation>", 0); // Relation End. go back.
						if (v_index != -1)
						{
							tag += w_temp;
							break;
						}
					}
					else
					{
						std::wcout.clear();
						std::wcout << "Subproperty Tag Finded..." << w_temp << std::endl;
						tag += w_temp;
						continue;
					}
				}
				else
				{
					//Find Tag, And Add
					std::wcout.clear();
					std::wcout << "Subproperty Tag Finded..." << w_temp << std::endl;
					tag += w_temp;
					continue;
				}
			}
		}

		if (!not_relation)
		{
			std::wcout << tag << std::endl << std::endl;

			if (!Parsing_Relation(tag))
				ParsingError_in_terminal(L"Relation", L"Please Check the file");
		}
	}

	////////////////////////////// Print Nodes and Ways //////////////////////////////////////

	for (unsigned int i = 0; i < nodes.size(); i++)
		Print_Node_in_terminal(nodes[i]);

	for (unsigned int i = 0; i < ways.size(); i++)
		Print_Way_in_terminal(ways[i]);

	for (unsigned int i = 0; i < relations.size(); i++)
		Print_Relation_in_terminal(relations[i]);

	return true;
}

////////////////////////////////////////////////////////////////////////////////////

#pragma region "Print Method"

void MapReader::Print_XML_in_terminal()
{
	std::wcout.setf(std::ios::fixed);
	std::wcout.precision(1);
	std::wcout << "-------------------- XML Tag -----------------------" << std::endl;
	std::wcout << "	Version : " << xml->GetVersion() << std::endl;
	std::wcout << "	Encoding : " << xml->encoding.c_str() << std::endl;
	std::wcout << "----------------------------------------------------" << std::endl;
}

void MapReader::Print_OSM_in_terminal()
{

	std::wcout.setf(std::ios::fixed);
	std::wcout.precision(1);
	std::wcout << "-------------------- OSM Tag -----------------------" << std::endl;
	std::wcout << "	Version : " << osm->version << std::endl;
	std::wcout << "	Generator : " << osm->generator.c_str() << std::endl;
	std::wcout << "	Copyright : " << osm->copyright.c_str() << std::endl;
	std::wcout << "	Attribution : " << osm->attribution.c_str() << std::endl;
	std::wcout << "	License : " << osm->license.c_str() << std::endl;
	std::wcout << "----------------------------------------------------" << std::endl;
}

void MapReader::Print_Bounds_in_terminal()
{
	std::wcout.setf(std::ios::fixed);
	std::wcout.precision(7);
	std::wcout << "-------------------- Bounds Tag -----------------------" << std::endl;
	std::wcout << "	Min Latitude : " << bounds->minlat << std::endl;
	std::wcout << "	Min Longitude : " << bounds->minlon << std::endl;
	std::wcout << "	Max Latitude : " << bounds->maxlat << std::endl;
	std::wcout << "	Max Longitude : " << bounds->maxlon << std::endl;
	std::wcout << "----------------------------------------------------" << std::endl;
}

void MapReader::Print_Node_in_terminal(TagNS::Tag_Node node)
{
	std::wcout.setf(std::ios::fixed);
	std::wcout.precision(7);
	std::wcout << "-------------------- Node Tag ----------------------" << std::endl;
	std::wcout << "	ID : " << node.id << std::endl;
	std::wcout << "	Visible : " << node.visible << std::endl;
	std::wcout << "	Version : " << node.version << std::endl;
	std::wcout << "	Changeset : " << node.changeset << std::endl;
	std::wcout << "	Timestamp : " << node.timestamp.c_str() << std::endl;
	std::wcout << "	User : " << node.user.c_str() << std::endl;
	std::wcout << "	UID : " << node.uid << std::endl;
	std::wcout << "	Latitude : " << node.lat << std::endl;
	std::wcout << "	Longitude : " << node.lon << std::endl;

	for (unsigned int i = 0; i < node.tag.size(); i++)
	{
		std::wcout << std::endl << "\t" << i << " Tag" << std::endl;
		Print_Tag(node.tag[i]);
		std::wcout << std::endl;
	}

	std::wcout << "----------------------------------------------------" << std::endl;
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

	std::wcout << "-------------------- Way Tag -----------------------" << std::endl;
	std::wcout << "	ID : " << way.id << std::endl;
	std::wcout << "	Visible : " << way.visible << std::endl;
	std::wcout << "	Version : " << way.version << std::endl;
	std::wcout << "	Changeset : " << way.changeset << std::endl;
	std::wcout << "	Timestamp : " << way.timestamp.c_str() << std::endl;
	std::wcout << "	User : " << way.user.c_str() << std::endl;
	std::wcout << "	UID : " << way.uid << std::endl;

	for (unsigned int i = 0; i < way.nd.size(); i++)
	{
		std::wcout << std::endl << "\t" << i << " nd" << std::endl;
		Print_nd(way.nd[i]);
		std::wcout << std::endl;
	}

	for (unsigned int i = 0; i < way.tag.size(); i++)
	{
		std::wcout << std::endl << "\t" << i << " Tag" << std::endl;
		Print_Tag(way.tag[i]);
		std::wcout << std::endl;
	}

	std::wcout << "----------------------------------------------------" << std::endl;
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
	std::wcout.setf(std::ios::fixed);
	std::wcout << "-------------------- Relation Tag -----------------------" << std::endl;
	std::wcout << "	ID : " << rel.id << std::endl;
	std::wcout << "	Visible : " << rel.visible << std::endl;
	std::wcout << "	Version : " << rel.version << std::endl;
	std::wcout << "	Changeset : " << rel.changeset << std::endl;
	std::wcout << "	Timestamp : " << rel.timestamp.c_str() << std::endl;
	std::wcout << "	User : " << rel.user.c_str() << std::endl;
	std::wcout << "	UID : " << rel.uid << std::endl;

	for (unsigned int i = 0; i < rel.member.size(); i++)
	{
		std::wcout << std::endl << "\t" << i << " nd" << std::endl;
		Print_Member(rel.member[i]);
		std::wcout << std::endl;
	}

	for (unsigned int i = 0; i < rel.tag.size(); i++)
	{
		std::wcout << std::endl << "\t" << i << " Tag" << std::endl;
		Print_Tag(rel.tag[i]);
	}

	std::wcout << "----------------------------------------------------" << std::endl;
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
	std::wcout << "\t" << "k : " << tag.k.c_str() << std::endl;
	std::wcout << "\t" << "v : " << tag.v.c_str() << std::endl;
}

void MapReader::Print_nd(TagNS::Tag_nd nd)
{
	std::wcout << "\t" << "ref : " << nd.ref << std::endl;
}

void MapReader::Print_Member(TagNS::Tag_Member member)
{
	std::wcout << "\t" << "type : " << member.type.c_str() << std::endl;
	std::wcout << "\t" << "ref : " << member.ref << std::endl;
	std::wcout << "\t" << "role : " << member.role.c_str() << std::endl;
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

bool MapReader::Parsing_XML(std::wstring tag_line)
{
	std::wstring s_encoding;
	double d_version;

	if (!GetAttribute(tag_line, L"version", &d_version))
		ERROR_ATTR(L"XML - version", L" ");

	if (!GetAttribute(tag_line, L"encoding", &s_encoding))
		ERROR_ATTR(L"XML - encoding", L" ");

	xml->version = d_version;
	xml->encoding = s_encoding;

	return true;
}

bool MapReader::Parsing_OSM(std::wstring tag_line)
{
	double d_version;
	std::wstring s_generator;
	std::wstring s_copyright;
	std::wstring s_attribution;
	std::wstring s_license;

	if (!GetAttribute(tag_line, L"version", &d_version))
		ERROR_ATTR(L"OSM - version", L" ");

	if (!GetAttribute(tag_line, L"generator", &s_generator))
		ERROR_ATTR(L"OSM - generator", L" ");

	if (!GetAttribute(tag_line, L"copyright", &s_copyright))
		ERROR_ATTR(L"OSM - copyright", L" ");

	if (!GetAttribute(tag_line, L"attribution", &s_attribution))
		ERROR_ATTR(L"OSM - attribution", L" ");

	if (!GetAttribute(tag_line, L"license", &s_license))
		ERROR_ATTR(L"OSM - license", L" ");

	osm->version = d_version;
	osm->generator = s_generator;
	osm->copyright = s_copyright;
	osm->attribution = s_attribution;
	osm->license = s_license;

	return true;
}

bool MapReader::Parsing_Bounds(std::wstring tag_line)
{
	double d_minlat;
	double d_minlon;
	double d_maxlat;
	double d_maxlon;

	if (!GetAttribute(tag_line, L"minlat", &d_minlat))
		ERROR_ATTR(L"Bounds - minlat", L" ");

	if (!GetAttribute(tag_line, L"minlon", &d_minlon))
		ERROR_ATTR(L"Bounds - minlon", L" ");

	if (!GetAttribute(tag_line, L"maxlat", &d_maxlat))
		ERROR_ATTR(L"Bounds - maxlat", L" ");

	if (!GetAttribute(tag_line, L"maxlon", &d_maxlon))
		ERROR_ATTR(L"Bounds - maxlon", L" ");
		
	bounds->minlat = d_minlat;
	bounds->minlon = d_minlon;
	bounds->maxlat = d_maxlat;
	bounds->maxlon = d_maxlon;

	return true;
}

bool MapReader::Parsing_Node(std::wstring tag_line)
{
	unsigned long long l_id;
	bool b_visible;
	int i_version;
	unsigned long long l_changeset;
	std::wstring s_timestamp;
	std::wstring s_user;
	unsigned long long l_uid;
	double d_lat;
	double d_lon;
	std::vector<TagNS::Tag_Tag> v_tag;

	if (!GetAttribute(tag_line, L"id", &l_id))
		ERROR_ATTR(L"Node - id", L" ");

	if (!GetAttribute(tag_line, L"visible", &b_visible))
		ERROR_ATTR(L"Node - visible", L" ")

	if (!GetAttribute(tag_line, L"version", &i_version))
		ERROR_ATTR(L"Node - version", L" ");

	if (!GetAttribute(tag_line, L"changeset", &l_changeset))
		ERROR_ATTR(L"Node - changeset", L" ");

	if (!GetAttribute(tag_line, L"timestamp", &s_timestamp))
		ERROR_ATTR(L"Node - timestamp", L" ");

	if (!GetAttribute(tag_line, L"user", &s_user))
		ERROR_ATTR(L"Node - user", L" ");

	if (!GetAttribute(tag_line, L"uid", &l_uid))
		ERROR_ATTR(L"Node - uid", L" ");

	if (!GetAttribute(tag_line, L"lat", &d_lat))
		ERROR_ATTR(L"Node - lat", L" ");

	if (!GetAttribute(tag_line, L"lon", &d_lon))
		ERROR_ATTR(L"Node - lon", L" ");

	bool exit = false;
	int v_index = 0, v2_index = 0;

	while (!exit)
	{
		
		v_index = tag_line.find(L"<tag", v2_index + 1);
		v2_index = tag_line.find(L"/>", v_index + 1);

		if (v_index == -1 || v2_index == -1)
		{
			//ERROR_FIND(L"Node - Tag", L" ");
			exit = true;
			continue;
		}

		std::wstring temp = tag_line.substr(v_index, v2_index);
		std::wstring k, v;
		
		if (!GetAttribute(temp, L"k", &k))
			ERROR_ATTR(L"Node - Tag - k", L" ");
		if (!GetAttribute(temp, L"v", &v))
			ERROR_ATTR(L"Node - Tag - v", L" ");

		v_tag.push_back(TagNS::Tag_Tag(k, v));
	}

	nodes.push_back(TagNS::Tag_Node(l_id, b_visible, i_version, l_changeset, s_timestamp, s_user, l_uid, d_lat, d_lon, v_tag));

	return true;
}

bool MapReader::Parsing_Way(std::wstring tag_line)
{
	unsigned long long l_id;
	bool b_visible;
	int i_version;
	unsigned long long l_changeset;
	std::wstring s_timestamp;
	std::wstring s_user;
	unsigned long long l_uid;
	std::vector<TagNS::Tag_nd> v_nd;
	std::vector<TagNS::Tag_Tag> v_tag;

	if (!GetAttribute(tag_line, L"id", &l_id))
		ERROR_ATTR(L"Way - id", L" ");

	if (!GetAttribute(tag_line, L"visible", &b_visible))
		ERROR_ATTR(L"Way - visible", L" ");

	if (!GetAttribute(tag_line, L"version", &i_version))
		ERROR_ATTR(L"Way - version", L" ");

	if (!GetAttribute(tag_line, L"changeset", &l_changeset))
		ERROR_ATTR(L"Way - changeset", L" ");

	if (!GetAttribute(tag_line, L"timestamp", &s_timestamp))
		ERROR_ATTR(L"Way - timestamp", L" ");

	if (!GetAttribute(tag_line, L"user", &s_user))
		ERROR_ATTR(L"Way - user", L" ");

	if (!GetAttribute(tag_line, L"uid", &l_uid))
		ERROR_ATTR(L"Way - uid", L" ");

	bool exit = false;
	int v_index = 0, v2_index = 0;

	while (!exit)
	{
		v_index = tag_line.find(L"<nd", v2_index + 1);
		v2_index = tag_line.find(L"/>", v_index + 1);

		if (v_index == -1)
		{
			exit = true;
			continue;
		}

		std::wstring tag = tag_line.substr(v_index, v2_index);
		TagNS::Tag_nd temp;
		if (!GetND(tag, &temp))
			ERROR_ATTR(L"Way - nd", L" ");

		v_nd.push_back(temp);
	}

	exit = false;
	v_index = 0, v2_index = 0;

	while (!exit)
	{
		v_index = tag_line.find(L"<tag", v2_index + 1);
		v2_index = tag_line.find(L"/>", v_index + 1);

		if (v_index == -1)
		{
			exit = true;
			continue;
		}

		std::wstring tag = tag_line.substr(v_index, v2_index);
		TagNS::Tag_Tag temp;

		if (!GetTag(tag, &temp))
			ERROR_ATTR(L"Way - Tag", L" ");

		v_tag.push_back(temp);
	}

	ways.push_back(TagNS::Tag_Way(l_id, b_visible, i_version, l_changeset, s_timestamp, s_user, l_uid, v_nd, v_tag));

	return true;
}

bool MapReader::Parsing_Relation(std::wstring tag_line)
{
	unsigned long long l_id;
	bool b_visible;
	int i_version;
	unsigned long long l_changeset;
	std::wstring s_timestamp;
	std::wstring s_user;
	unsigned long long l_uid;
	std::vector<TagNS::Tag_Member> v_member;
	std::vector<TagNS::Tag_Tag> v_tag;

	if (!GetAttribute(tag_line, L"id", &l_id))
		ERROR_ATTR(L"Relation - id", L" ");

	if (!GetAttribute(tag_line, L"visible", &b_visible))
		ERROR_ATTR(L"Relation - visible", L" ");

	if (!GetAttribute(tag_line, L"version", &i_version))
		ERROR_ATTR(L"Relation - version", L" ");

	if (!GetAttribute(tag_line, L"changeset", &l_changeset))
		ERROR_ATTR(L"Relation - changeset", L" ");

	if (!GetAttribute(tag_line, L"timestamp", &s_timestamp))
		ERROR_ATTR(L"Relation - timestamp", L" ");

	if (!GetAttribute(tag_line, L"user", &s_user))
		ERROR_ATTR(L"Relation - user", L" ");

	if (!GetAttribute(tag_line, L"uid", &l_uid))
		ERROR_ATTR(L"Relation - uid", L" ");

	bool exit = false;
	int v_index = 0, v2_index = 0;

	while (!exit)
	{
		v_index = tag_line.find(L"<member", v2_index + 1);
		v2_index = tag_line.find(L"/>", v_index + 1);

		if (v_index == -1)
		{
			exit = true;
			continue;
		}

		std::wstring tag = tag_line.substr(v_index, v2_index);
		TagNS::Tag_Member temp;

		if (!GetMember(tag, &temp))
			ERROR_ATTR(L"Relation - Member", L" ");

		v_member.push_back(temp);
	}

	exit = false;
	v_index = 0, v2_index = 0;
	while (!exit)
	{
		v_index = tag_line.find(L"<tag", v2_index + 1);
		v2_index = tag_line.find(L"/>", v_index + 1);

		if (v_index == -1)
		{
			exit = true;
			continue;
		}

		std::wstring tag = tag_line.substr(v_index, v2_index);
		TagNS::Tag_Tag temp;

		if (!GetTag(tag, &temp))
			ERROR_ATTR(L"Relation - Tag", L" ");

		v_tag.push_back(temp);
	}

	relations.push_back(TagNS::Tag_Relation(l_id, b_visible, i_version, l_changeset, s_timestamp, s_user, l_uid, v_member, v_tag));

	return true;
}

#pragma endregion