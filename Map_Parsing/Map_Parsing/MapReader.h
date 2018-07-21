#pragma once

#include <iostream>
#include <vector>
#include "Tag.h"
#include "map_parsing.h"

class MapReader
{
public:
	MapReader(void) { };
	MapReader(const char * filename) { MapUpload(filename); }

	bool MapUpload(const char * filename);

public:
	void Print_XML();

	void Print_OSM();

	void Print_Bounds();

	void Print_Node_Index(int index);
	void Print_Node_ID(int id);

	void Print_Way_Index(int index);
	void Print_Way_ID(int id);

	void Print_Relation_Index(int index);
	void Print_Relation_ID(int id);

public:
	TagNS::Tag_XML* Get_XML() { return xml; }

	TagNS::Tag_OSM* Get_OSM() { return osm; }

	TagNS::Tag_Bounds* Get_Bounds() { return bounds; }

	std::vector<TagNS::Tag_Node> Get_Nodes() { return nodes; }
	bool Get_Node_Index(TagNS::Tag_Node * Node, int index);
	bool Get_Node_ID(TagNS::Tag_Node * Node, int id);

	std::vector<TagNS::Tag_Way> Get_Ways() { return ways; }
	bool Get_Way_Index(TagNS::Tag_Way * way, int index);
	bool Get_Way_ID(TagNS::Tag_Way * way, int id);

	std::vector<TagNS::Tag_Relation> Get_Relations() { return relation; }
	bool Get_Relation_Index(TagNS::Tag_Relation * relation, int index);
	bool Get_Relation_ID(TagNS::Tag_Relation * relation, int id);

private:
	bool Parshing_XML(std::string tag_line);

	bool Parshing_OSM(std::string tag_line);

	bool Parshing_Bounds(std::string tag_line);

	bool Parshing_Node(std::string tag_line);

	bool Parshing_Way(std::string tag_line);

	bool Parshing_Relation(std::string tag_line);

public:
	TagNS::C_Tag_All * all;
	TagNS::Tag_XML * xml;
	TagNS::Tag_OSM * osm;
	TagNS::Tag_Bounds * bounds;
	std::vector<TagNS::Tag_Node> nodes;
	std::vector<TagNS::Tag_Way> ways;
	std::vector<TagNS::Tag_Relation> relations;
};
