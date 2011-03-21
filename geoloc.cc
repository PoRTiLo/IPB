#include "geoloc.h"

Geoloc::Geoloc( Tag* tag ) 
{
	clear();
	parserTag( tag );
}


float Geoloc::accuracy( void ) {

	return m_accuracy;
}

void Geoloc::accuracy( const float accuracy ) {

	m_accuracy = accuracy;
}

float Geoloc::alt( void ) {

	return m_alt;
}

void Geoloc::alt( const float alt ) {

	m_alt = alt;
}

string Geoloc::area( void ) {

	return m_area;
}

void Geoloc::area( const string area ) {

	m_area = area;
}

float Geoloc::bearing( void ) {

	return m_bearing;
}

void Geoloc::bearing( float bearing ) {

	m_bearing = bearing;
}

string Geoloc::building( void ) {

	return m_building;
}

void Geoloc::building( const string building ) {

	m_building = building;
}

string Geoloc::country( void ) {

	return m_country;
}

void Geoloc::country( const string country ) {

	m_country = country;
}

string Geoloc::countrycode( void ) {

	return m_countrycode;
}

void Geoloc::countrycode( const string countrycode ) {

	m_countrycode = countrycode;
}

string Geoloc::datum( void ) {

	return m_datum;
}

void Geoloc::datum( const string datum ) {

	m_datum = datum;
}

string Geoloc::description( void ) {

	return m_description;
}

void Geoloc::description( const string description ) {

	m_description = description;
}

float Geoloc::error( void ) {

	return m_error;
}

void Geoloc::error( const float error ) {

	 m_error = error;
}

string Geoloc::floor( void ) {

	return m_floor;
}

void Geoloc::floor( const string floor ) {

	m_floor = floor;
}

float Geoloc::lat( void ) {

	return m_lat;
}

void Geoloc::lat( const float lat ) {

	m_lat = lat;
}

string Geoloc::locality( void ) {

	return m_locality;
}

void Geoloc::locality( const string locality ) {

	m_locality = locality;
}

float Geoloc::lon( void ) {

	return m_lon;
}

void Geoloc::lon( const float lon ) {

	m_lon = lon;
}

string Geoloc::postalcode( void ) {

	return m_postalcode;
}

void Geoloc::postalcode( const string postalcode ) {

	m_postalcode = postalcode;
}

string Geoloc::region( void ) {

	return m_region;
}

void Geoloc::region( const string region ) {

	m_region = region;
}

string Geoloc::street( void ) {

	return m_street;
}

void Geoloc::street( const string street ) {

	m_street = street;
}

string Geoloc::text( void ) {

	return m_text;
}

void Geoloc::text( const string text ) {

	m_text = text;
}

string Geoloc::timestamp( void ) {

	return m_timestamp;
}

void Geoloc::timestamp( const string timestamp ) {

	m_timestamp = timestamp;
}

float Geoloc::speed( void ) {

	return m_speed;
}

void Geoloc::speed( const float speed ) {

	m_speed = speed;
}
string Geoloc::uri( void ) {

	return m_uri;
}

string Geoloc::room( void ) {

	return m_room;
}

void Geoloc::room( const string room ) {

	m_room = room;
}

void Geoloc::uri( const string uri ) {
	
	m_uri = uri;
}

string Geoloc::id( void ) {

	return m_id;
}

void Geoloc::id( const string id ) {

	m_id = id;
}

JID Geoloc::jid( void ) {

	return m_jid;
}
		
void Geoloc::jid( const string jid ) {

	m_jid.setJID(jid);
}

void Geoloc::clear( void ) {

	m_accuracy = 0.0;
	m_alt = 0.0;
	m_bearing = 0.0;
	m_error = 0.0;
	m_lat = 0.0;
	m_lon = 0.0;
	m_speed = 0.0;
}
void Geoloc::parserTag( const Tag * tag ) {

//mozna zjednodusit ptani se jestili to je ITEM A GEOLOC	
	if( tag->findChild("item") )
	{
		Tag * p_tag1 = tag->findChild("item")->clone();

		id( p_tag1->findAttribute("id") );

		if( p_tag1->findChild("geoloc") )
		{
			Tag * p_tag = p_tag1->findChild("geoloc")->clone();

			if( !p_tag->children().empty() )
			{
				if( p_tag->findChild("accuracy") )
					accuracy( stringToInt( (p_tag->findChild("accuracy"))->cdata() ));
				if( p_tag->findChild("alt") )
					alt( stringToInt((p_tag->findChild("alt"))->cdata() ));
				if( p_tag->findChild("area") )
					area( (p_tag->findChild("area"))->cdata() );
				if( p_tag->findChild("bearing") )
					bearing( stringToInt( (p_tag->findChild("bearing"))->cdata() ));
				if( p_tag->findChild("building") )
					building( (p_tag->findChild("building"))->cdata() );
				if( p_tag->findChild("country") )
					country( (p_tag->findChild("country"))->cdata() );
				if( p_tag->findChild("countrycode") )
					countrycode( (p_tag->findChild("countrycode"))->cdata() );
				if( p_tag->findChild("datum") )
					datum( (p_tag->findChild("datum"))->cdata() );
				if( p_tag->findChild("description") )
					description( (p_tag->findChild("description"))->cdata() );
				if( p_tag->findChild("error") )
					error( stringToInt( (p_tag->findChild("error"))->cdata() ));
				if( p_tag->findChild("floor") )
					floor( (p_tag->findChild("floor"))->cdata() );
				if( p_tag->findChild("lat") )
					lat( stringToInt((p_tag->findChild("lat"))->cdata() ));
				if( p_tag->findChild("locality") )
					locality( (p_tag->findChild("locality"))->cdata() );
				if( p_tag->findChild("lon") )
					lon( stringToInt((p_tag->findChild("lon"))->cdata() ));
				if( p_tag->findChild("postalcode") )
					postalcode( (p_tag->findChild("postalcode"))->cdata() );
				if( p_tag->findChild("region") )
					region( (p_tag->findChild("region"))->cdata() );
				if( p_tag->findChild("room") )
					room( (p_tag->findChild("room"))->cdata() );
				if( p_tag->findChild("speed") )
					speed( stringToInt((p_tag->findChild("speed"))->cdata() ));
				if( p_tag->findChild("street") )
					street( (p_tag->findChild("street"))->cdata() );
				if( p_tag->findChild("text") )
					text( (p_tag->findChild("text"))->cdata() );
				if( p_tag->findChild("timestamp") )
					timestamp( (p_tag->findChild("timestamp"))->cdata() );
				if( p_tag->findChild("uri") )
					uri( (p_tag->findChild("uri"))->cdata() );
			}
		}
	}
}
