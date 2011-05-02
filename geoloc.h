#ifndef GEOLOC_H__
#define GEOLOC_H__

#include "extension.h"

using namespace gloox;

/**
 * Implementace XEP-0080: User Location.
 */
class Geoloc : public Extension
{
	private:

	protected:
		float m_accuracy;
		float m_alt;
		std::string m_area;
		float m_bearing;
		std::string m_building;
		std::string m_country;
		std::string m_countrycode;
		std::string m_datum;
		std::string m_description;
		float m_error;
		std::string m_floor;
		float m_lat;
		std::string m_locality;
		float m_lon;
		std::string m_postalcode;
		std::string m_region;
		std::string m_room;
		float m_speed;
		std::string m_street;
		std::string m_text;
		std::string m_timestamp;
		std::string m_uri;

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

		std::string area( void );
		void area( const std::string area );

		float bearing( void );
		void bearing( float bearing );

		std::string building( void );
		void building( const std::string building );

		std::string country( void );
		void country( const std::string country );

		std::string countrycode( void );
		void countrycode( const std::string countrycode );

		std::string datum( void );
		void datum( const std::string datum );

		std::string description( void );
		void description( const std::string description );

		float error( void );
		void error( const float error );

		std::string floor( void );
		void floor( const std::string floor );

		float lat( void );
		void lat( const float lat );

		std::string locality( void );
		void locality( const std::string locality );

		float lon( void );
		void lon( const float lon );

		std::string postalcode( void );
		void postalcode( const std::string postalcode );

		std::string region( void );
		void region( const std::string region );

		std::string street( void );
		void street( const std::string street );

		std::string text( void );
		void text( const std::string text );

		std::string timestamp( void );
		void timestamp( const std::string timestamp );

		float speed( void );
		void speed( const float speed );

		std::string room( void );
		void room( const std::string room );

		std::string uri( void );
		void uri( const std::string uri );

		virtual void parserTag( const Tag * tag );

		virtual void clear( void );
};

#endif
