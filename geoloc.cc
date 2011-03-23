#include "geoloc.h"

Geoloc::Geoloc( Tag* tag ) 
{
	clear();
	parserTag( tag );
}


float Geoloc::accuracy( void ) {

	return this->m_accuracy;
}

void Geoloc::accuracy( const float accuracy ) {

	this->m_accuracy = accuracy;
}

float Geoloc::alt( void ) {

	return this->m_alt;
}

void Geoloc::alt( const float alt ) {

	this->m_alt = alt;
}

std::string Geoloc::area( void ) {

	return this->m_area;
}

void Geoloc::area( const std::string area ) {

	this->m_area = area;
}

float Geoloc::bearing( void ) {

	return this->m_bearing;
}

void Geoloc::bearing( float bearing ) {

	this->m_bearing = bearing;
}

std::string Geoloc::building( void ) {

	return this->m_building;
}

void Geoloc::building( const std::string building ) {

	this->m_building = building;
}

std::string Geoloc::country( void ) {

	return this->m_country;
}

void Geoloc::country( const std::string country ) {

	this->m_country = country;
}

std::string Geoloc::countrycode( void ) {

	return this->m_countrycode;
}

void Geoloc::countrycode( const std::string countrycode ) {

	this->m_countrycode = countrycode;
}

std::string Geoloc::datum( void ) {

	return this->m_datum;
}

void Geoloc::datum( const std::string datum ) {

	this->m_datum = datum;
}

std::string Geoloc::description( void ) {

	return this->m_description;
}

void Geoloc::description( const std::string description ) {

	this->m_description = description;
}

float Geoloc::error( void ) {

	return this->m_error;
}

void Geoloc::error( const float error ) {

	 this->m_error = error;
}

std::string Geoloc::floor( void ) {

	return this->m_floor;
}

void Geoloc::floor( const std::string floor ) {

	this->m_floor = floor;
}

float Geoloc::lat( void ) {

	return this->m_lat;
}

void Geoloc::lat( const float lat ) {

	this->m_lat = lat;
}

std::string Geoloc::locality( void ) {

	return this->m_locality;
}

void Geoloc::locality( const std::string locality ) {

	this->m_locality = locality;
}

float Geoloc::lon( void ) {

	return this->m_lon;
}

void Geoloc::lon( const float lon ) {

	this->m_lon = lon;
}

std::string Geoloc::postalcode( void ) {

	return this->m_postalcode;
}

void Geoloc::postalcode( const std::string postalcode ) {

	this->m_postalcode = postalcode;
}

std::string Geoloc::region( void ) {

	return this->m_region;
}

void Geoloc::region( const std::string region ) {

	this->m_region = region;
}

std::string Geoloc::street( void ) {

	return this->m_street;
}

void Geoloc::street( const std::string street ) {

	this->m_street = street;
}

std::string Geoloc::text( void ) {

	return this->m_text;
}

void Geoloc::text( const std::string text ) {

	this->m_text = text;
}

std::string Geoloc::timestamp( void ) {

	return this->m_timestamp;
}

void Geoloc::timestamp( const std::string timestamp ) {

	this->m_timestamp = timestamp;
}

float Geoloc::speed( void ) {

	return this->m_speed;
}

void Geoloc::speed( const float speed ) {

	this->m_speed = speed;
}
std::string Geoloc::uri( void ) {

	return this->m_uri;
}

std::string Geoloc::room( void ) {

	return this->m_room;
}

void Geoloc::room( const std::string room ) {

	this->m_room = room;
}

void Geoloc::uri( const std::string uri ) {
	
	this->m_uri = uri;
}

std::string Geoloc::id( void ) {

	return this->m_id;
}

void Geoloc::id( const std::string id ) {

	this->m_id = id;
}

JID Geoloc::jid( void ) {

	return this->m_jid;
}
		
void Geoloc::jid( const std::string jid ) {

	this->m_jid.setJID(jid);
}

void Geoloc::clear( void ) {

	this->m_accuracy = 0.0;
	this->m_alt = 0.0;
	this->m_bearing = 0.0;
	this->m_error = 0.0;
	this->m_lat = 0.0;
	this->m_lon = 0.0;
	this->m_speed = 0.0;
}
void Geoloc::parserTag( const Tag * tag ) {

	if( tag->hasChild("item" ))
{
	Tag * p_tag1 = tag->findChild("item")->clone();
	id( p_tag1->findAttribute("id") );
	Tag * p_tag = p_tag1->findChild("geoloc")->clone();

	if( !p_tag->children().empty() )
	{
		if( p_tag->findChild("accuracy") )
			accuracy( stringToFloat( (p_tag->findChild("accuracy"))->cdata() ));
		if( p_tag->findChild("alt") )
			alt( stringToFloat((p_tag->findChild("alt"))->cdata() ));
		if( p_tag->findChild("area") )
			area( (p_tag->findChild("area"))->cdata() );
		if( p_tag->findChild("bearing") )
			bearing( stringToFloat( (p_tag->findChild("bearing"))->cdata() ));
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
			error( stringToFloat( (p_tag->findChild("error"))->cdata() ));
		if( p_tag->findChild("floor") )
			floor( (p_tag->findChild("floor"))->cdata() );
		if( p_tag->findChild("lat") )
			lat( stringToFloat((p_tag->findChild("lat"))->cdata() ));
		if( p_tag->findChild("locality") )
			locality( (p_tag->findChild("locality"))->cdata() );
		if( p_tag->findChild("lon") )
			lon( stringToFloat((p_tag->findChild("lon"))->cdata() ));
		if( p_tag->findChild("postalcode") )
			postalcode( (p_tag->findChild("postalcode"))->cdata() );
		if( p_tag->findChild("region") )
			region( (p_tag->findChild("region"))->cdata() );
		if( p_tag->findChild("room") )
			room( (p_tag->findChild("room"))->cdata() );
		if( p_tag->findChild("speed") )
			speed( stringToFloat((p_tag->findChild("speed"))->cdata() ));
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
