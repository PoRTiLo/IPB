#include "geoloc.h"

Geoloc::Geoloc( Tag* tag ): Extension(tag) 
{
	clear();
	parserTag( tag );
}


float Geoloc::accuracy( void ) {

	return this->m_accuracy;
}

void Geoloc::accuracy( const float accuracyE ) {

	this->m_accuracy = accuracyE;
}

float Geoloc::alt( void ) {

	return this->m_alt;
}

void Geoloc::alt( const float altE ) {

	this->m_alt = altE;
}

std::string Geoloc::area( void ) {

	return this->m_area;
}

void Geoloc::area( const std::string areaE ) {

	this->m_area = areaE;
}

float Geoloc::bearing( void ) {

	return this->m_bearing;
}

void Geoloc::bearing( float bearingE ) {

	this->m_bearing = bearingE;
}

std::string Geoloc::building( void ) {

	return this->m_building;
}

void Geoloc::building( const std::string buildingE ) {

	this->m_building = buildingE;
}

std::string Geoloc::country( void ) {

	return this->m_country;
}

void Geoloc::country( const std::string countryE ) {

	this->m_country = countryE;
}

std::string Geoloc::countrycode( void ) {

	return this->m_countrycode;
}

void Geoloc::countrycode( const std::string countrycodeE ) {

	this->m_countrycode = countrycodeE;
}

std::string Geoloc::datum( void ) {

	return this->m_datum;
}

void Geoloc::datum( const std::string datumE ) {

	this->m_datum = datumE;
}

std::string Geoloc::description( void ) {

	return this->m_description;
}

void Geoloc::description( const std::string descriptionE ) {

	this->m_description = descriptionE;
}

float Geoloc::error( void ) {

	return this->m_error;
}

void Geoloc::error( const float errorE ) {

	 this->m_error = errorE;
}

std::string Geoloc::floor( void ) {

	return this->m_floor;
}

void Geoloc::floor( const std::string floorE ) {

	this->m_floor = floorE;
}

float Geoloc::lat( void ) {

	return this->m_lat;
}

void Geoloc::lat( const float latE ) {

	this->m_lat = latE;
}

std::string Geoloc::locality( void ) {

	return this->m_locality;
}

void Geoloc::locality( const std::string localityE ) {

	this->m_locality = localityE;
}

float Geoloc::lon( void ) {

	return this->m_lon;
}

void Geoloc::lon( const float lonE ) {

	this->m_lon = lonE;
}

std::string Geoloc::postalcode( void ) {

	return this->m_postalcode;
}

void Geoloc::postalcode( const std::string postalcodeE ) {

	this->m_postalcode = postalcodeE;
}

std::string Geoloc::region( void ) {

	return this->m_region;
}

void Geoloc::region( const std::string regionE ) {

	this->m_region = regionE;
}

std::string Geoloc::street( void ) {

	return this->m_street;
}

void Geoloc::street( const std::string streetE ) {

	this->m_street = streetE;
}

std::string Geoloc::text( void ) {

	return this->m_text;
}

void Geoloc::text( const std::string textE ) {

	this->m_text = textE;
}

std::string Geoloc::timestamp( void ) {

	return this->m_timestamp;
}

void Geoloc::timestamp( const std::string timestampE ) {

	this->m_timestamp = timestampE;
}

float Geoloc::speed( void ) {

	return this->m_speed;
}

void Geoloc::speed( const float speedE ) {

	this->m_speed = speedE;
}
std::string Geoloc::uri( void ) {

	return this->m_uri;
}

std::string Geoloc::room( void ) {

	return this->m_room;
}

void Geoloc::room( const std::string roomE ) {

	this->m_room = roomE;
}

void Geoloc::uri( const std::string uriE ) {
	
	this->m_uri = uriE;
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
