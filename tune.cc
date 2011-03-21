#include "tune.h"

Tune::Tune( const Tag* tag ) 
{
	clear();
	parserTag( tag );
}

string Tune::artist( void ) {

	return m_artist;
}

void Tune::artist( const string artist ) {

	m_artist = artist;
}

short int Tune::length( void ) {

	return m_length;
}

void Tune::length( const short int length ) {

	m_length = length;
}

unsigned int Tune::rating( void ) {

	return m_rating;
}

void Tune::rating( const unsigned int rating ) {

	m_rating = rating;
}

string Tune::source( void ) {

	return m_source;
}

void Tune::source( const string source ) {

	m_source = source;
}

string Tune::title( void ) {

	return m_title;
}

void Tune::title( const string title ) {

	m_title = title;
}

string Tune::track( void ) {

	return m_track;
}

void Tune::track( const string track ) {

	m_track = track;
}

string Tune::uri( void ) {

	return m_uri;
}

void Tune::uri( const string uri ) {

	m_uri = uri;
}

string Tune::id( void ) {

	return m_id;
}

void Tune::id( const string id ) {

	m_id = id;
}

JID Tune::jid( void ) {

	return m_jid;
}
		
void Tune::jid( const string jid ) {

	m_jid.setJID(jid);
}

void Tune::parserTag( const Tag * tag ) {

//mozna zjednodusit ptani se jestili to je ITEM A GEOLOC	
	if( tag->findChild("item") )
	{
		Tag * p_tag1 = tag->findChild("item")->clone();

		id( p_tag1->findAttribute("id") );
		
		if( p_tag1->findChild("tune") )
		{
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
}


void Tune::clear( void ) {

	m_length = 0;
	m_rating = 0;
}
