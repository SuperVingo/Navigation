#pragma once

#include <iostream>
#include <vector>

namespace TagNS
{
	class Tag_ALL;
	class Tag_XML;
	class Tag_OSM;
	class Tag_Bounds;
	class Tag_Node;
	class Tag_Way;
	class Tag_Relation;
	class Tag_nd;
	class Tag_Tag;
	class Tag_Member;

	class Tag_XML
	{
	public:
		Tag_XML() {}

		Tag_XML(double d_version, std::wstring s_encoding) : version(d_version), encoding(s_encoding) {}

		Tag_XML(const Tag_XML & other) : version(other.version), encoding(other.encoding) {}

		void SetVersion(double d_version) { version = d_version; }
		void SetEncoding(std::wstring s_encoding) { encoding = s_encoding; }

		double GetVersion(void) { return version; }
		std::wstring GetEncoding(void) { return encoding; }

	public:
		double version;
		std::wstring encoding;
	};
	
	class Tag_OSM
	{
	public:
		Tag_OSM() {}

		Tag_OSM(double d_version, std::wstring s_generator, std::wstring s_copyright, std::wstring s_attribution, std::wstring s_license)
			: version(d_version), generator(s_generator), copyright(s_copyright), attribution(s_attribution), license(s_license) {}

		Tag_OSM(const Tag_OSM & other) 
			: version(other.version), generator(other.generator), copyright(other.copyright), attribution(other.attribution), license(other.license) {}

		void SetVersion(double d_version) { version = d_version; }
		void SetGenerator(std::wstring s_generator) { generator = s_generator; }
		void SetCopyright(std::wstring s_copyright) { copyright = s_copyright; }
		void SetAttribution(std::wstring s_attribution) { attribution = s_attribution; }
		void SetLicense(std::wstring s_license) { license = s_license; }

		double GetVersion(void) { return version; }
		std::wstring GetGenerator(void) { return generator; }
		std::wstring GetCopyright(void) { return copyright; }
		std::wstring GetAttribution(void) { return attribution; }
		std::wstring GetLicense(void) { return license; }

	public:
		double version;
		std::wstring generator;
		std::wstring copyright;
		std::wstring attribution;
		std::wstring license;
	};

	class Tag_Bounds
	{
	public:
		Tag_Bounds() {}

		Tag_Bounds(double d_minlat, double d_minlon, double d_maxlat, double d_maxlon)
			: minlat(d_minlat), minlon(d_minlon), maxlat(d_maxlat), maxlon(d_maxlon) {}

		Tag_Bounds(const Tag_Bounds & other)
			: minlat(other.minlat), minlon(other.minlon), maxlat(other.maxlat), maxlon(other.maxlon) {}

		void SetMinlat(double d_minlat) { minlat = d_minlat; }
		void SetMinlon(double d_minlon) { minlon = d_minlon; }
		void SetMaxlat(double d_maxlat) { maxlat = d_maxlat; }
		void SetMaxlon(double d_maxlon) { maxlon = d_maxlon; }

		double GetMinlat(void) { return minlat; }
		double GetMinlon(void) { return minlon; }
		double GetMaxlat(void) { return maxlat; }
		double GetMaxlon(void) { return maxlon; }

	public:
		double minlat;
		double minlon;
		double maxlat;
		double maxlon;
	};

	class Tag_Node
	{
	public:
		Tag_Node() {}

		Tag_Node(unsigned long long l_id, bool b_visible, int i_version, unsigned long long l_changeset, std::wstring s_timestamp,
			std::wstring s_user, unsigned long long l_uid, double d_lat, double d_lon)
			: id(l_id), visible(b_visible), version(i_version), changeset(l_changeset), timestamp(s_timestamp),
			user(s_user), uid(l_uid), lat(d_lat), lon(d_lon) {}

		Tag_Node(unsigned long long l_id, bool b_visible, int i_version, unsigned long long l_changeset, std::wstring s_timestamp,
			std::wstring s_user, unsigned long long l_uid, double d_lat, double d_lon, std::vector<Tag_Tag> v_tag)
			: id(l_id), visible(b_visible), version(i_version), changeset(l_changeset), timestamp(s_timestamp),
			user(s_user), uid(l_uid), lat(d_lat), lon(d_lon), tag(v_tag) {}

		Tag_Node(const Tag_Node & other) : 
			id(other.id), visible(other.visible), version(other.version), changeset(other.changeset), timestamp(other.timestamp),
			user(other.user), uid(other.uid), lat(other.lat), lon(other.lon), tag(other.tag) {}

		void SetID(unsigned long long l_id) { id = l_id; }
		void SetVisible(bool b_visible) { visible = b_visible; }
		void SetVersion(int i_version) { version = i_version; }
		void SetChangeset(unsigned long long l_changeset) { changeset = l_changeset; }
		void SetTimestamp(std::wstring s_timestamp) { timestamp = s_timestamp; }
		void SetUser(std::wstring s_user) { user = s_user; }
		void SetUID(unsigned long long l_uid) { uid = l_uid; }
		void SetLat(double d_lat) { lat = d_lat; }
		void SetLon(double d_lon) { lon = d_lon; }

		unsigned long long GetID(void) { return id; }
		bool GetVisible(void) { return visible; }
		int GetVersion(void) { return version; }
		unsigned long long GetChangeset(void) { return changeset; }
		std::wstring GetTimestamp(void) { return timestamp; }
		std::wstring GetUser(void) { return user; }
		unsigned long long GetUID(void) { return uid; }
		double GetLat(void) { return lat; }
		double GetLon(void) { return lon; }

	public:
		unsigned long long id;
		bool visible;
		int version;
		unsigned long long changeset;
		std::wstring timestamp;
		std::wstring user;
		unsigned long long uid;
		double lat;
		double lon;
		std::vector<Tag_Tag> tag;
	};

	class Tag_Way
	{
	public:
		Tag_Way() {}

		Tag_Way(unsigned long long l_id, bool b_visible, int i_version, unsigned long long l_changeset, std::wstring s_timestamp, std::wstring s_user, unsigned long long l_uid)
			: id(l_id), visible(b_visible), version(i_version), changeset(l_changeset), timestamp(s_timestamp), user(s_user), uid(l_uid) {}

		Tag_Way(unsigned long long l_id, bool b_visible, int i_version, unsigned long long l_changeset, std::wstring s_timestamp, std::wstring s_user,
			unsigned long long l_uid, std::vector<Tag_nd> v_nd, std::vector<Tag_Tag> v_tag)
			: id(l_id), visible(b_visible), version(i_version), changeset(l_changeset), timestamp(s_timestamp), user(s_user), uid(l_uid),
			nd(v_nd), tag(v_tag) {}

		Tag_Way(const Tag_Way & other)
			: id(other.id), visible(other.visible), version(other.version), changeset(other.changeset),
			timestamp(other.timestamp), user(other.user), uid(other.uid), nd(other.nd), tag(other.tag) {}

		void SetID(unsigned long long l_id) { id = l_id; }
		void SetVisible(bool b_visible) { visible = b_visible; }
		void SetVersion(int i_version) { version = i_version; }
		void SetChangeset(unsigned long long l_changeset) { changeset = l_changeset; }
		void SetTimestamp(std::wstring s_timestamp) { timestamp = s_timestamp; }
		void SetUser(std::wstring s_user) { user = s_user; }
		void SetUID(unsigned long long l_uid) { uid = l_uid; }

		unsigned long long GetID(void) { return id; }
		bool GetVisible(void) { return visible; }
		int GetVersion(void) { return version; }
		unsigned long long GetChangeset(void) { return changeset; }
		std::wstring GetTimestamp(void) { return timestamp; }
		std::wstring GetUser(void) { return user; }
		unsigned long long GetUID(void) { return uid; }

	public:
		unsigned long long id;
		bool visible;
		int version;
		unsigned long long changeset;
		std::wstring timestamp;
		std::wstring user;
		unsigned long long uid;
		std::vector<Tag_nd> nd;
		std::vector<Tag_Tag> tag;
	};

	class Tag_Relation
	{
	public:
		Tag_Relation() {}

		Tag_Relation(unsigned long long l_id, bool b_visible, int i_version, unsigned long long l_changeset, std::wstring s_timestamp, std::wstring s_user, unsigned long long l_uid)
			: id(l_id), visible(b_visible), version(i_version), changeset(l_changeset), timestamp(s_timestamp), user(s_user), uid(l_uid) {}

		Tag_Relation(unsigned long long l_id, bool b_visible, int i_version, unsigned long long l_changeset, std::wstring s_timestamp, std::wstring s_user,
			unsigned long long l_uid, std::vector<Tag_Member> v_member, std::vector<Tag_Tag> v_tag)
			: id(l_id), visible(b_visible), version(i_version), changeset(l_changeset), timestamp(s_timestamp), user(s_user), uid(l_uid),
			member(v_member), tag(v_tag) {}

		Tag_Relation(const Tag_Relation & other)
			: id(other.id), visible(other.visible), version(other.version), changeset(other.changeset),
			timestamp(other.timestamp), user(other.user), uid(other.uid), member(other.member), tag(other.tag) {}

		void SetID(unsigned long long l_id) { id = l_id; }
		void SetVisible(bool b_visible) { visible = b_visible; }
		void SetVersion(int i_version) { version = i_version; }
		void SetChangeset(unsigned long long l_changeset) { changeset = l_changeset; }
		void SetTimestamp(std::wstring s_timestamp) { timestamp = s_timestamp; }
		void SetUser(std::wstring s_user) { user = s_user; }
		void SetUID(unsigned long long l_uid) { uid = l_uid; }

		unsigned long long GetID(void) { return id; }
		bool GetVisible(void) { return visible; }
		int GetVersion(void) { return version; }
		unsigned long long GetChangeset(void) { return changeset; }
		std::wstring GetTimestamp(void) { return timestamp; }
		std::wstring GetUser(void) { return user; }
		unsigned long long GetUID(void) { return uid; }

	public:
		unsigned long long id;
		bool visible;
		int version;
		unsigned long long changeset;
		std::wstring timestamp;
		std::wstring user;
		unsigned long long uid;
		std::vector<Tag_Member> member;
		std::vector<Tag_Tag> tag;
	};

	class Tag_nd
	{
	public:
		Tag_nd(void) { }

		Tag_nd(unsigned long long l_ref) : ref(l_ref) { }

		Tag_nd(const Tag_nd & other) : ref(other.ref) { }

		void SetRef(unsigned long long l_ref) { ref = l_ref; }

		unsigned long long GetRef(void) { return ref; }

	public:
		unsigned long long ref;
	};

	class Tag_Tag
	{
	public:
		Tag_Tag() {}
		
		Tag_Tag(std::wstring s_k, std::wstring s_v) : k(s_k), v(s_v) {}

		Tag_Tag(const Tag_Tag & other) : k(other.k), v(other.v) {}

		void SetK(std::wstring s_k) { k = s_k; }
		void SetV(std::wstring s_v) { v = s_v; }

		std::wstring GetK(void) { return k; }
		std::wstring GetV(void) { return v; }

	public:
		std::wstring k;
		std::wstring v;
	};

	class Tag_Member
	{
	public:
		Tag_Member() {}

		Tag_Member(std::wstring s_type, unsigned long long l_ref, std::wstring s_role) : type(s_type), ref(l_ref), role(s_role) {}

		Tag_Member(const Tag_Member & other) : type(other.type), ref(other.ref), role(other.role) {}

		void SetType(std::wstring s_type) { type = s_type; }
		void SetRef(unsigned long long l_ref) { ref = l_ref; }
		void SetRole(std::wstring s_role) { role = s_role; }

		std::wstring GetType(void) { return type; }
		unsigned long long GetRef(void) { return ref; }
		std::wstring GetRole(void) { return role; }

	public:
		std::wstring type;
		unsigned long long ref;
		std::wstring role;
	};

	class Tag_ALL
	{
	public:
		Tag_ALL(void) {}
		
		Tag_ALL(Tag_XML t_xml, Tag_OSM t_osm, Tag_Bounds t_bounds) : xml(t_xml), osm(t_osm), bounds(t_bounds) {}
		
		Tag_ALL(Tag_XML t_xml, Tag_OSM t_osm, Tag_Bounds t_bounds, std::vector<Tag_Node> v_nodes, std::vector<Tag_Way> v_ways,
			std::vector<Tag_Relation> v_relation) 
			: xml(t_xml), osm(t_osm), bounds(t_bounds), nodes(v_nodes), ways(v_ways), relation(v_relation) {}

		Tag_ALL(const Tag_ALL & other)
			: xml(other.xml), osm(other.osm), bounds(other.bounds), nodes(other.nodes), ways(other.ways), relation(other.relation) {}

		void SetXML(Tag_XML t_xml) { xml = t_xml; }
		void SetOSM(Tag_OSM t_osm) { osm = t_osm; }
		void SetBounds(Tag_Bounds t_bounds) { bounds = t_bounds; }

		Tag_XML GetXML(void) { return xml; }
		Tag_OSM GetOSM(void) { return osm; }
		Tag_Bounds GetBounds(void) { return bounds; }

	public:
		Tag_XML xml;
		Tag_OSM osm;
		Tag_Bounds bounds;
		std::vector<Tag_Node> nodes;
		std::vector<Tag_Way> ways;
		std::vector<Tag_Relation> relation;
	};
};