#include "activity.h"

Activity::Activity( const Tag* tag )
{
	parserTag( tag );
}
		
string Activity::activity( void ) {

	return this->m_activity;
}

void Activity::activity( const string activity ) {

	m_activity = activity;
}

string Activity::spec( void ) {

	return this->m_spec;
}

void Activity::spec( const string spec ) {

	m_spec = spec;
}
string Activity::text( void ) {

	return this->m_text;
}

void Activity::text( const string text ) {

	m_text = text;
}

string Activity::id( void ) {

	return m_id;
}

void Activity::id( const string id ) {

	m_id = id;
}

JID Activity::jid( void ) {

	return m_jid;
}
		
void Activity::jid( const string jid ) {

	m_jid.setJID(jid);
}

void Activity::parserTag( const Tag * tag ) {

//mozna zjednodusit ptani se jestili to je ITEM A GEOLOC	
	if( tag->findChild("item") )
	{
		Tag * p_tag1 = tag->findChild("item")->clone();

		id( tag->findAttribute("id") );
		if( p_tag1->findChild("activity") )
		{
			Tag * p_tag = p_tag1->findChild("activity")->clone();
			if( !p_tag->children().empty() )
			{
				for( int i = 0; i != 11; i++ )
				{
					if( p_tag->hasChild( m_activityTab[i][0] ) )
					{
						for( int j = 0; j != 13; j++ )
						{
							Tag * p_tag2 = p_tag->findChild(m_activityTab[i][0])->clone();
							if( p_tag2->hasChild( m_activityTab[i][j] ) )
							{
								spec( (p_tag2->findChild(m_activityTab[i][j]))->name() );
								break;
							}
						}
						activity( (p_tag->findChild(m_activityTab[i][0]))->name() );
						break;
					}
				}
				if( p_tag->findChild("text") )
					text( (p_tag->findChild("text"))->cdata() );
			}
		}
	}
}
 const string Activity::m_activityTab[11][13] = {{"doing_chores","buying_groceries", "cleaning", "cooking", "doing_maintenance", "doing_the_dishes", "doing_the_laundry", "gardening", "running_an_errand", "walking_the_dog"},
 															{"drinking"," having_a_beer", "having_coffee", "having_tea"},
															{"eating", "having_a_snack", "having_breakfast", "having_dinner", "having_lunch"},
 															{"exercising", "cycling", "dancing", "hiking", "jogging", "playing_sports", "running", "skiing", "swimming", "working_out"},
															{"grooming", "at_the_spa", "brushing_teeth", "getting_a_haircut", "shaving", "taking_a_bath", "taking_a_shower"},
															{"having_appointment"}, 
															{"inactive", "day_off", "hanging_out", "hiding", "on_vacation", "praying", "scheduled_holiday", "sleeping", "thinking"},
															{"relaxing",  "fishing", "gaming", "going_out", "partying", "reading", "rehearsing", "shopping", "smoking", "socializing", "sunbathing", "watching_tv", "watching_a_movie"},
															{"talking", "in_real_life", "on_the_phone", "on_video_phone"},
															{"traveling", "commuting", "cycling", "driving", "in_a_car"," on_a_bus","on_a_plane", "on_a_train", "on_a_trip", "walking"},
															{"working", "coding", "in_a_meeting", "studying"," writing"}
 };

