#include <fstream>
#include <stdlib.h>
#include <iomanip>
#include "MapReader.h"

bool MapReader::MapUpload(const char * filename)
{
	return false;
}

void MapReader::Print_XML()
{
}

void MapReader::Print_OSM()
{
}

void MapReader::Print_Bounds()
{
}

void MapReader::Print_Node_Index(int index)
{
}

void MapReader::Print_Node_ID(int id)
{
}

void MapReader::Print_Way_Index(int index)
{
}

void MapReader::Print_Way_ID(int id)
{
}

void MapReader::Print_Relation_Index(int index)
{
}

void MapReader::Print_Relation_ID(int id)
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

	if (!GetAttribute(tag_line, std::string("version"), &d_version))
		return false;

	if (!GetAttribute(tag_line, std::string("encoding"), &s_encoding))
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

	if (!GetAttribute(tag_line, std::string("version"), &d_version))
		return false;

	if (!GetAttribute(tag_line, std::string("generator"), &s_generator))
		return false;

	if (!GetAttribute(tag_line, std::string("copyright"), &s_copyright))
		return false;

	if (!GetAttribute(tag_line, std::string("attribution"), &s_attribution))
		return false;

	if (!GetAttribute(tag_line, std::string("license"), &s_license))
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

	if (!GetAttribute(tag_line, std::string("version"), &d_minlat))
		return false;

	if (!GetAttribute(tag_line, std::string("minlon"), &d_minlon))
		return false;

	if (!GetAttribute(tag_line, std::string("maxlat"), &d_maxlat))
		return false;

	if (!GetAttribute(tag_line, std::string("maxlon"), &d_maxlon))
		return false;
		
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

	GetAttribute(tag_line, std::string("id"), &l_id);
	GetAttribute(tag_line, std::string("visible"), &b_visible);
	GetAttribute(tag_line, std::string("version"), &i_version);
	GetAttribute(tag_line, std::string("changeset"), &l_changeset);
	GetAttribute(tag_line, std::string("timestamp"), &s_timestamp);
	GetAttribute(tag_line, std::string("uid"), &l_uid);
	GetAttribute(tag_line, std::string("lat"), &d_lat);
	GetAttribute(tag_line, std::string("lon"), &d_lon);

	bool exit = false;

	while (!exit)
	{

	}

	return true;
}

bool MapReader::Parshing_Way(std::string tag_line)
{
	return false;
}

bool MapReader::Parshing_Relation(std::string tag_line)
{
	return false;
}
