#pragma once

#ifndef GEOLOC_H__
#define GEOLOC_H__


#include <string>

#include <gloox/tag.h>
#include <gloox/jid.h>

#include "func.h"
using namespace std;
using namespace gloox;

/**
 * Implementace XEP-0080.
 */
class Geoloc
{
	private:

	protected:
		float m_accuracy;
		float m_alt;
		string m_area;
		float m_bearing;
		string m_building;
		string m_country;
		string m_countrycode;
		string m_datum;
		string m_description;
		float m_error;
		string m_floor;
		float m_lat;
		string m_locality;
		float m_lon;
		string m_postalcode;
		string m_region;
		string m_room;
		float m_speed;
		string m_street;
		string m_text;
		string m_timestamp;
		string m_uri;
		string m_id;
		JID m_jid;

	public:

		/**
		 * Konstruktor.
		 */
		Geoloc( Tag* tag );

		/**
		 * Destruktor.
		 */
		~Geoloc(){}

		float accuracy( void ) ;
		void accuracy( float accuracy );

		float alt( void );
		void alt( const float alt );

		string area( void );
		void area( const string area );

		float bearing( void );
		void bearing( float bearing );

		string building( void );
		void building( const string building );

		string country( void );
		void country( const string country );

		string countrycode( void );
		void countrycode( const string countrycode );

		string datum( void );
		void datum( const string datum );

		string description( void );
		void description( const string description );

		float error( void );
		void error( const float error );

		string floor( void );
		void floor( const string floor );

		float lat( void );
		void lat( const float lat );

		string locality( void );
		void locality( const string locality );

		float lon( void );
		void lon( const float lon );

		string postalcode( void );
		void postalcode( const string postalcode );

		string region( void );
		void region( const string region );

		string street( void );
		void street( const string street );

		string text( void );
		void text( const string text );

		string timestamp( void );
		void timestamp( const string timestamp );

		float speed( void );
		void speed( const float speed );

		string room( void );
		void room( const string room );

		string uri( void );
		void uri( const string uri );

		string id( void );
		void id( const string id );

		JID jid( void );
		void jid( const string jid );

		void parserTag( const Tag * tag );

		void clear( void );
};

#endif
