#pragma once

#include <iostream>
#include <vector>
#include "Tag.h"
#include "map_parsing.h"

class MapReader
{
public:
	MapReader(void);
	MapReader(const wchar_t * filename);

	bool MapUpload(const wchar_t * filename);

public:
	// In Terminal Output
	void Print_XML_in_terminal();

	void Print_OSM_in_terminal();

	void Print_Bounds_in_terminal();

	void Print_Node_in_terminal(TagNS::Tag_Node node);
	void Print_Node_Index_in_terminal(int index);
	void Print_Node_ID_in_terminal(int id);

	void Print_Way_in_terminal(TagNS::Tag_Way way);
	void Print_Way_Index_in_terminal(int index);
	void Print_Way_ID_in_terminal(int id);

	void Print_Relation_in_terminal(TagNS::Tag_Relation rel);
	void Print_Relation_Index_in_terminal(int index);
	void Print_Relation_ID_in_terminal(int id);

	void Print_Tag(TagNS::Tag_Tag tag);
	void Print_nd(TagNS::Tag_nd nd);
	void Print_Member(TagNS::Tag_Member member);

public:
	//Return Tag
	TagNS::Tag_XML* Get_XML() { return xml; }

	TagNS::Tag_OSM* Get_OSM() { return osm; }

	TagNS::Tag_Bounds* Get_Bounds() { return bounds; }

	std::vector<TagNS::Tag_Node> Get_Nodes() { return nodes; }
	bool Get_Node_Index(TagNS::Tag_Node * Node, unsigned int index);
	bool Get_Node_ID(TagNS::Tag_Node * Node, int id);

	std::vector<TagNS::Tag_Way> Get_Ways() { return ways; }
	bool Get_Way_Index(TagNS::Tag_Way * way, unsigned int index);
	bool Get_Way_ID(TagNS::Tag_Way * way, int id);

	std::vector<TagNS::Tag_Relation> Get_Relations() { return relations; }
	bool Get_Relation_Index(TagNS::Tag_Relation * relation, unsigned int index);
	bool Get_Relation_ID(TagNS::Tag_Relation * relation, int id);

private:
	//Parsing Function
	bool Parsing_XML(std::wstring tag_line);

	bool Parsing_OSM(std::wstring tag_line);

	bool Parsing_Bounds(std::wstring tag_line);

	bool Parsing_Node(std::wstring tag_line);

	bool Parsing_Way(std::wstring tag_line);

	bool Parsing_Relation(std::wstring tag_line);

public:
	TagNS::Tag_ALL * all;
	TagNS::Tag_XML * xml;
	TagNS::Tag_OSM * osm;
	TagNS::Tag_Bounds * bounds;
	std::vector<TagNS::Tag_Node> nodes;
	std::vector<TagNS::Tag_Way> ways;
	std::vector<TagNS::Tag_Relation> relations;
};
