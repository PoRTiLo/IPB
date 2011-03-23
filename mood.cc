#include "mood.h"

// Konstruktor
Mood::Mood( const Tag* tag )
{
	parserTag( tag );
}

// get
std::string Mood::mood( void ) {

	return this->m_mood;
}

// set
void Mood::mood( const std::string mood ) {

	this->m_mood = mood;
}

// get
std::string Mood::text( void ) {

	return this->m_text;
}

// set
void Mood::text( const std::string text ) {

	this->m_text = text;
}

// get
std::string Mood::id( void ) {

	return this->m_id;
}

// set
void Mood::id( const std::string id ) {

	this->m_id = id;
}

// get
JID Mood::jid( void ) {

	return this->m_jid;
}

// set
void Mood::jid( const std::string jid ) {

	this->m_jid.setJID(jid);
}


void Mood::parserTag( const Tag * tag ) {

	if( tag->hasChild("item") )
	{
		Tag * p_tag1 = tag->findChild("item")->clone();

		id( p_tag1->findAttribute("id") );

		Tag * p_tag = p_tag1->findChild("mood")->clone();

		if( !p_tag->children().empty() )
		{
			for( int i = 0; i != 85; i++ )
			{
				if( p_tag->hasChild( m_moodTab[i] ) )
				{
					mood( (p_tag->findChild(m_moodTab[i]))->name() );
					break;
				}
			}
			if( p_tag->findChild("text") )
				text( (p_tag->findChild("text"))->cdata() );
		}
	}
}

const std::string Mood::m_moodTab[85] = { "afraid","amazed","amorous","angry","annoyed","anxious","aroused","ashamed","bored","brave","calm","cautious",
                                      "cold","confident","confused","contemplative","contented","cranky","crazy","creative","curious","dejected","depressed","disappointed","disgusted",
                                      "dismayed","distracted","embarrassed","envious","excited","flirtatious","frustrated","grateful","grieving","grumpy","guilty","happy","hopeful","hot",
                                      "humbled","humiliated","hungry","hurt","hurt","impressed","in_awe","in_love","indignant","interested","intoxicated","invincible","jealous","lonely",
                                      "lost","lucky","mean","moody","nervous",	"neutral","offended","outraged","playful","proud","relaxed","relieved","remorseful","restless",	"sad",
                                      "sarcastic","satisfied","serious","shocked","shy","sick","sleepy","spontaneous","stressed","strong","surprised",	"thankful","thirsty","tired","undefined","weak","worried"};

