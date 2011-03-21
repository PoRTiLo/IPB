#include "mood.h"

Mood::Mood( const Tag* tag )
{
	parserTag( tag );
}
		
string Mood::mood( void ) {

	return m_mood;
}

void Mood::mood( const string mood ) {

	m_mood = mood;
}

string Mood::text( void ) {

	return this->m_text;
}

void Mood::text( const string text ) {

	m_text = text;
}

string Mood::id( void ) {

	return m_id;
}

void Mood::id( const string id ) {

	m_id = id;
}

JID Mood::jid( void ) {

	return m_jid;
}
		
void Mood::jid( const string jid ) {

	m_jid.setJID(jid);
}

void Mood::parserTag( const Tag * tag ) {

//mozna zjednodusit ptani se jestili to je ITEM A GEOLOC	
	if( tag->findChild("item") )
	{
		Tag * p_tag1 = tag->findChild("item")->clone();

		id( p_tag1->findAttribute("id") );

		if( p_tag1->findChild("mood") )
		{
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
}
 const string Mood::m_moodTab[85] = { "afraid","amazed","amorous","angry","annoyed","anxious","aroused","ashamed","bored","brave","calm","cautious",
                                      "cold","confident","confused","contemplative","contented","cranky","crazy","creative","curious","dejected","depressed","disappointed","disgusted",
                                      "dismayed","distracted","embarrassed","envious","excited","flirtatious","frustrated","grateful","grieving","grumpy","guilty","happy","hopeful","hot",
                                      "humbled","humiliated","hungry","hurt","hurt","impressed","in_awe","in_love","indignant","interested","intoxicated","invincible","jealous","lonely",
                                      "lost","lucky","mean","moody","nervous",	"neutral","offended","outraged","playful","proud","relaxed","relieved","remorseful","restless",	"sad",
                                      "sarcastic","satisfied","serious","shocked","shy","sick","sleepy","spontaneous","stressed","strong","surprised",	"thankful","thirsty","tired","undefined","weak","worried"};

						
/*			AFRAID,
			AMAZED
			AMOROUS,
			ANGRY,
			ANNOYED,
			ANXIOUS,
			AROUSED,
			ASHAMED,
			BORED,
			BRAVE,
			CALM,
			CAUTIOUS,
			COLD,
			CONFIDENT,
			CONFUSED,
			CONTEMPLATIVE,
			CONTENTED,
			CRANKY,
			CRAZY,
			CREATIVE,
			CURIOUS,
			DEJECTED,
			DEPRESSED,
			DISAPPOINTED,
			DISGUSTED,
			DISMAYED,
			DISTRACTED,
			EMBARRASSED,
			ENVIOUS,
			EXCITED,
			FLIRTATIOUS,
			FRUSTRATED,
			GRATEFUL,
			GRIEVING,
			GRUMPY,
			GUILTY,
			HAPPY,
			HOPEFUL,
			HOT,
			HUMBLED,
			HUMILIATED,
			HUNGRY,
			HURT,
			IMPRESSED,
			IN_AWE,
			IN_LOVE,
			INDIGNANT,
			INTERESTED,
			INTOXICATED,
			INVINCIBLE,
			JEALOUS,
			LONELY,
			LOST,
			LUCKY,
			MEAN,
			MOODY,
			NERVOUS,
			NEUTRAL,
			OFFENDED,
			OUTRAGED,
			PLAYFUL,
			PROUD,
			RELAXED,
			RELIEVED,
			REMORSEFUL,
			RESTLESS,
			SAD,
			SARCASTIC,
			SATISFIED,
			SERIOUS,
			SHOCKED,
			SHY,
			SICK,
			SLEEPY,
			SPONTANEOUS,
			STRESSED,
			STRONG,
			SURPRISED,
			THANKFUL,
			THIRSTY,
			TIRED,
			UNDEFINED,
			WEAK,
			WORRIED
		};
		*/
