#include <iostream>
#include <vector>

namespace TagNS
{
	typedef class C_Tag_All Tag_ALL;
	typedef class C_Tag_XML Tag_XML;
	typedef class C_Tag_OSM Tag_OSM;
	typedef class C_Tag_Bounds Tag_Bounds;
	typedef class C_Tag_Node Tag_Node;
	typedef class C_Tag_Way Tag_Way;
	typedef class C_Tag_Relation Tag_Relation;
	typedef class C_Tag_nd Tag_nd;
	typedef class C_Tag_Tag Tag_Tag;
	typedef class C_Tag_Member Tag_Member;

	typedef class C_Tag_XML
	{
	public:
		C_Tag_XML() {}

		C_Tag_XML(double d_version, std::string s_encoding) : version(d_version), encoding(s_encoding) {}

		C_Tag_XML(const C_Tag_XML & other) : version(other.version), encoding(other.encoding) {}

		void SetVersion(double d_version) { version = d_version; }
		void SetEncoding(std::string s_encoding) { encoding = s_encoding; }

	public:
		double version;
		std::string encoding;
	} Tag_XML;
	
	typedef class C_Tag_OSM
	{
	public:
		C_Tag_OSM() {}

		C_Tag_OSM(double d_version, std::string s_generator, std::string s_copyright, std::string s_attribution, std::string s_license)
			: version(d_version), generator(s_generator), copyright(s_copyright), attribution(s_attribution), license(s_license) {}

		C_Tag_OSM(const C_Tag_OSM & other) 
			: version(other.version), generator(other.generator), copyright(other.copyright), attribution(other.attribution), license(other.license) {}

		void SetVersion(double d_version) { version = d_version; }
		void SetGenerator(std::string s_generator) { generator = s_generator; }
		void SetCopyright(std::string s_copyright) { copyright = s_copyright; }
		void SetAttribution(std::string s_attribution) { attribution = s_attribution; }
		void SetLicense(std::string s_license) { license = s_license; }

	public:
		double version;
		std::string generator;
		std::string copyright;
		std::string attribution;
		std::string license;
	} Tag_OSM;

	typedef class C_Tag_Bounds
	{
	public:
		C_Tag_Bounds() {}

		C_Tag_Bounds(double d_minlat, double d_minlon, double d_maxlat, double d_maxlon)
			: minlat(d_minlat), minlon(d_minlon), maxlat(d_maxlat), maxlon(d_maxlon) {}

		C_Tag_Bounds(const C_Tag_Bounds & other)
			: minlat(other.minlat), minlon(other.minlon), maxlat(other.maxlat), maxlon(other.maxlon) {}

		void SetMinlat(double d_minlat) { minlat = d_minlat; }
		void SetMinlon(double d_minlon) { minlon = d_minlon; }
		void SetMaxlat(double d_maxlat) { maxlat = d_maxlat; }
		void SetMaxlon(double d_maxlon) { maxlon = d_maxlon; }

	public:
		double minlat;
		double minlon;
		double maxlat;
		double maxlon;
	} Tag_Bounds;

	typedef class C_Tag_Node
	{
	public:
		C_Tag_Node() {}

		C_Tag_Node(long l_id, bool b_visible, int i_version, long l_changeset, std::string s_timestamp,
			std::string s_user, long l_uid, double d_lat, double d_lon)
			: id(l_id), visible(b_visible), version(i_version), changeset(l_changeset), timestamp(s_timestamp),
			user(s_user), uid(l_uid), lat(d_lat), lon(d_lon) {}

		C_Tag_Node(long l_id, bool b_visible, int i_version, long l_changeset, std::string s_timestamp,
			std::string s_user, long l_uid, double d_lat, double d_lon, std::vector<Tag_Tag> v_tag)
			: id(l_id), visible(b_visible), version(i_version), changeset(l_changeset), timestamp(s_timestamp),
			user(s_user), uid(l_uid), lat(d_lat), lon(d_lon), tag(v_tag) {}

		C_Tag_Node(const C_Tag_Node & other) : 
			id(other.id), visible(other.visible), version(other.version), changeset(other.changeset), timestamp(other.timestamp),
			user(other.user), uid(other.uid), lat(other.lat), lon(other.lon), tag(other.tag) {}

		void SetID(long l_id) { id = l_id; }
		void SetVisible(bool b_visible) { visible = b_visible; }
		void SetVersion(int i_version) { version = i_version; }
		void SetChangeset(long l_changeset) { changeset = l_changeset; }
		void SetTimestamp(std::string s_timestamp) { timestamp = s_timestamp; }
		void SetUser(std::string s_user) { user = s_user; }
		void SetUID(long l_uid) { uid = l_uid; }
		void SetLat(double d_lat) { lat = d_lat; }
		void SetLon(double d_lon) { lon = d_lon; }

	public:
		long id;
		bool visible;
		int version;
		long changeset;
		std::string timestamp;
		std::string user;
		long uid;
		double lat;
		double lon;
		std::vector<Tag_Tag> tag;
	} Tag_Node;

	typedef class C_Tag_Way
	{
	public:
		C_Tag_Way() {}

		C_Tag_Way(long l_id, bool b_visible, int i_version, long l_changeset, std::string s_timestamp, std::string s_user, long l_uid)
			: id(l_id), visible(b_visible), version(i_version), changeset(l_changeset), timestamp(s_timestamp), user(s_user), uid(l_uid) {}

		C_Tag_Way(long l_id, bool b_visible, int i_version, long l_changeset, std::string s_timestamp, std::string s_user, 
			long l_uid, std::vector<Tag_nd> v_nd, std::vector<Tag_Tag> v_tag)
			: id(l_id), visible(b_visible), version(i_version), changeset(l_changeset), timestamp(s_timestamp), user(s_user), uid(l_uid),
			nd(v_nd), tag(v_tag) {}

		C_Tag_Way(const C_Tag_Way & other)
			: id(other.id), visible(other.visible), version(other.version), changeset(other.changeset), 
			timestamp(other.timestamp), user(other.user), uid(other.uid), nd(other.nd), tag(other.tag) {}

		void SetID(long l_id) { id = l_id; }
		void SetVisible(bool b_visible) { visible = b_visible; }
		void SetVersion(int i_version) { version = i_version; }
		void SetChangeset(long l_changeset) { changeset = l_changeset; }
		void SetTimestamp(std::string s_timestamp) { timestamp = s_timestamp; }
		void SetUser(std::string s_user) { user = s_user; }
		void SetUID(long l_uid) { uid = l_uid; }

	public:
		long id;
		bool visible;
		int version;
		long changeset;
		std::string timestamp;
		std::string user;
		long uid;
		std::vector<Tag_nd> nd;
		std::vector<Tag_Tag> tag;
	} Tag_Way;

	typedef class C_Tag_Relation
	{
	public:
		C_Tag_Relation() {}

		C_Tag_Relation(long l_id, bool b_visible, int i_version, long l_changeset, std::string s_timestamp, std::string s_user, long l_uid)
			: id(l_id), visible(b_visible), version(i_version), changeset(l_changeset), timestamp(s_timestamp), user(s_user), uid(l_uid) {}

		C_Tag_Relation(long l_id, bool b_visible, int i_version, long l_changeset, std::string s_timestamp, std::string s_user, 
			long l_uid, std::vector<Tag_Member> v_member, std::vector<Tag_Tag> v_tag)
			: id(l_id), visible(b_visible), version(i_version), changeset(l_changeset), timestamp(s_timestamp), user(s_user), uid(l_uid),
			member(v_member), tag(v_tag) {}

		C_Tag_Relation(const C_Tag_Relation & other)
			: id(other.id), visible(other.visible), version(other.version), changeset(other.changeset),
			timestamp(other.timestamp), user(other.user), uid(other.uid), member(other.member), tag(other.tag) {}

		void SetID(long l_id) { id = l_id; }
		void SetVisible(bool b_visible) { visible = b_visible; }
		void SetVersion(int i_version) { version = i_version; }
		void SetChangeset(long l_changeset) { changeset = l_changeset; }
		void SetTimestamp(std::string s_timestamp) { timestamp = s_timestamp; }
		void SetUser(std::string s_user) { user = s_user; }
		void SetUID(long l_uid) { uid = l_uid; }

	public:
		long id;
		bool visible;
		int version;
		long changeset;
		std::string timestamp;
		std::string user;
		long uid;
		std::vector<Tag_Member> member;
		std::vector<Tag_Tag> tag;
	} Tag_Relation;

	typedef class C_Tag_nd
	{
	public:
		C_Tag_nd() {}

		C_Tag_nd(long l_ref) : ref(l_ref) {}

		C_Tag_nd(const C_Tag_nd & other) : ref(other.ref) {}

		void SetRef(long l_ref) { ref = l_ref; }

	public:
		long ref;
	} Tag_nd;

	typedef class C_Tag_Tag
	{
	public:
		C_Tag_Tag() {}

		C_Tag_Tag(std::string s_k, std::string s_v) : k(s_k), v(s_v) {}

		C_Tag_Tag(const C_Tag_Tag & other) : k(other.k), v(other.v) {}

		void SetK(std::string s_k) { k = s_k; }
		void SetV(std::string s_v) { v = s_v; }

	public:
		std::string k;
		std::string v;
	} Tag_Tag;

	typedef class C_Tag_Member
	{
	public:
		C_Tag_Member() {}

		C_Tag_Member(std::string s_type, long l_ref, std::string s_role) : type(s_type), ref(l_ref), role(s_role) {}

		C_Tag_Member(const C_Tag_Member & other) : type(other.type), ref(other.ref), role(other.role) {}

		void SetType(std::string s_type) { type = s_type; }
		void SetRef(long l_ref) { ref = l_ref; }
		void SetRole(std::string s_role) { role = s_role; }

	public:
		std::string type;
		long ref;
		std::string role;
	} Tag_Member;

	typedef class C_Tag_All
	{
		C_Tag_All() {}

		C_Tag_All(Tag_XML t_xml, Tag_OSM t_osm, Tag_Bounds t_bounds) : xml(t_xml), osm(t_osm), bounds(t_bounds) {}

		C_Tag_All(Tag_XML t_xml, Tag_OSM t_osm, Tag_Bounds t_bounds, std::vector<Tag_Node> v_nodes, std::vector<Tag_Way> v_ways, 
			std::vector<Tag_Relation> v_relation) 
			: xml(t_xml), osm(t_osm), bounds(t_bounds), nodes(v_nodes), ways(v_ways), relation(v_relation) {}

		C_Tag_All(const C_Tag_All & other) 
			: xml(other.xml), osm(other.osm), bounds(other.bounds), nodes(other.nodes), ways(other.ways), relation(other.relation) {}

		void SetXML(Tag_XML t_xml) { xml = t_xml; }
		void SetOSM(Tag_OSM t_osm) { osm = t_osm; }
		void SetBounds(Tag_Bounds t_bounds) { bounds = t_bounds; }

	public:
		Tag_XML xml;
		Tag_OSM osm;
		Tag_Bounds bounds;
		std::vector<Tag_Node> nodes;
		std::vector<Tag_Way> ways;
		std::vector<Tag_Relation> relation;
	} Tag_ALL;
}