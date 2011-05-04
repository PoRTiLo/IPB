/**
 *@file tune.cc
 */

#include "tune.h"

Tune::Tune( const Tag* tag ):Extension(tag) 
{
	clear();
	parserTag( tag );
}

// get
std::string Tune::artist( void ) {

	return this->m_artist;
}

// set
void Tune::artist( const std::string artist ) {

	this->m_artist = artist;
}

// get
short int Tune::length( void ) {

	return this->m_length;
}

// set
void Tune::length( const short int length ) {

	this->m_length = length;
}

// get
unsigned int Tune::rating( void ) {

	return this->m_rating;
}

// set
void Tune::rating( const unsigned int rating ) {

	this->m_rating = rating;
}

// get
std::string Tune::source( void ) {

	return this->m_source;
}

// set
void Tune::source( const std::string source ) {

	this->m_source = source;
}

// get
std::string Tune::title( void ) {

	return this->m_title;
}

// set
void Tune::title( const std::string title ) {

	this->m_title = title;
}

// get
std::string Tune::track( void ) {

	return this->m_track;
}

// set
void Tune::track( const std::string track ) {

	this->m_track = track;
}

// get
std::string Tune::uri( void ) {

	return this->m_uri;
}

// set
void Tune::uri( const std::string uri ) {

	this->m_uri = uri;
}

void Tune::parserTag( const Tag * tag ) {

	if( tag->hasChild("item" ))
	{
		Tag * p_tag1 = tag->findChild("item")->clone();

		id( p_tag1->findAttribute("id") );
		
		Tag * p_tag = p_tag1->findChild("tune")->clone();
		if( !p_tag->children().empty() )
		{
			if( p_tag->findChild("artist") )
				artist( (p_tag->findChild("artist"))->cdata() );
			if( p_tag->findChild("length") )
				length( stringToShortInt((p_tag->findChild("length"))->cdata()) );
			if( p_tag->findChild("rating") )
				rating( stringToUnsignedInt((p_tag->findChild("rating"))->cdata()) );
			if( p_tag->findChild("source") )
				source( (p_tag->findChild("source"))->cdata() );
			if( p_tag->findChild("title") )
				title( (p_tag->findChild("title"))->cdata() );
			if( p_tag->findChild("track") )
				track( (p_tag->findChild("track"))->cdata() );
			if( p_tag->findChild("uri") )
				uri( (p_tag->findChild("uri"))->cdata() );
		}
	}
}

void Tune::clear( void ) {

	this->m_length = 0;
	this->m_rating = 0;
}
