#include "swversion.h"

// Konstruktor
//Version::Version( std::string name, string version, string os )
//{
//	this->m_name = toJid;
//	this->resource = toResource;
//}

SwVersion::SwVersion( )
{

	clear();
}
SwVersion::SwVersion( const Tag* tag ) : Extension(tag)
{

	clear();
}
// Tvorba IQ dotazu
Tag* SwVersion::createIqStanza( std::string fromJid, std::string toJid, std::string toResource ) {

	Tag *myTagIq = new Tag("iq");
	myTagIq->addAttribute("from", fromJid);
	myTagIq->addAttribute("to", toJid + "/" + toResource);
	myTagIq->addAttribute("id", "asdr534f3g3");	
	myTagIq->addAttribute("type", "get");
	myTagIq->addAttribute("xml:lang", "en-US");
	Tag *myTag = new Tag("query");
	myTag->setXmlns("jabber:iq:version");
	myTagIq->addChildCopy(myTag);

	return myTagIq;
}

void SwVersion::parserTag( const Tag * queryTag ) {


}


void SwVersion::parserTagVer( const Tag * queryTag ) {

	if( queryTag->findChild("name") )
		name( queryTag->findChild("name")->cdata() );
	if( queryTag->findChild("version") )
		version( queryTag->findChild("version")->cdata() );
	if( queryTag->findChild("os") )
		os( queryTag->findChild("os")->cdata() );
}

void SwVersion::parserTagI( const Tag * identTag ) {

	if( identTag->hasAttribute("category") )
		category(identTag->findAttribute("category") );
	if( identTag->hasAttribute("name") )
		name( identTag->findAttribute("name") );
	if( identTag->hasAttribute("type") )
		type( identTag->findAttribute("type") );
}

void SwVersion::parserTagF( const Tag * queryTag ) {


	if( queryTag->hasChild("feature","var", "http://www.google.com/xmpp/protocol/voice/v1" ) )
		googleVoice( "TRUE" );
	if( queryTag->hasChild("feature","var", "http://www.google.com/xmpp/protocol/video/v1" ) )
		googleVideo( "TRUE" );	
	if( queryTag->hasChild("feature", "var", "urn:xmpp:jingle:apps:rtp:audio" ) )
		jingleVoice( "TRUE" );	
	if( queryTag->hasChild("feature","var", "urn:xmpp:jingle:apps:rtp:video" ) )
		jingleVideo( "TRUE" );	
}


void SwVersion::parserTagX( const Tag * xTag ) {


	if(xTag->findChild("field","var","ip_version") )
	{
//		Tag * fieldTag = xTag->findChild("field","var","ip_version")->clone();
//		swVersion->setIP( (fieldTag->findChild("value"))->cdata() );					//dodelat, mozno i IP6
	}
	if(xTag->findChild("field","var","os") )
	{
		Tag * fieldTag = xTag->findChild("field","var","os")->clone();
		os( (fieldTag->findChild("value"))->cdata() );
	}
	if(xTag->findChild("field","var","os_version") )
	{
		Tag * fieldTag = xTag->findChild("field","var","os_version")->clone();
		osVersion( (fieldTag->findChild("value"))->cdata() );
	}
	if(xTag->findChild("field","var","software") )
	{
		Tag * fieldTag = xTag->findChild("field","var","software")->clone();
		name( (fieldTag->findChild("value"))->cdata() );
	}
	if(xTag->findChild("field","var","software_version") )
	{
		Tag * fieldTag = xTag->findChild("field","var","software_version")->clone();
		version( (fieldTag->findChild("value"))->cdata() );
	}
}

// Nastaveni JID prijemce
void SwVersion::name( std::string nameE ) {

	this->m_name = nameE;
}

// Nastaveni resource prijemce
void SwVersion::version( std::string versionE ) {

	this->m_version = versionE;
}

// Ziskani JID prijemce
void SwVersion::os( std::string osE ) {

	 this->m_os = osE;
}

// Ziskani resource prijemce
std::string SwVersion::name( void ) {

	return this->m_name;
}
// Ziskani resource prijemce
std::string SwVersion::version( void ) {

	return this->m_version;
}
// Ziskani resource prijemce
std::string SwVersion::os( void ) {

	return this->m_os;
}

// set
void SwVersion::ip4( bool ip4E ) {

	this->m_ip4 = ip4E;
}

// set
void SwVersion::ip6( bool ip6E ) {

	this->m_ip6 = ip6E;
}

// set
void SwVersion::osVersion( std::string osVersionE ) {

	this->m_osVersion = osVersionE;
}

// set
void SwVersion::category( std::string categoryE ) {

	this->m_category = categoryE;
}

// set
void SwVersion::type( std::string typeE ) {

	this->m_type = typeE;
}

// get
std::string SwVersion::type( void ) {

	return this->m_type;
}

// get
std::string SwVersion::osVersion( void ) {

	return this->m_osVersion;
}

// get
bool SwVersion::ip4( void ) {

	return this->m_ip4;
}

// get
bool SwVersion::ip6( void ) {

	return this->m_ip6;
}

// get
std::string SwVersion::category( void ) {

	return this->m_category;
}

void SwVersion::clear( void ) {

	this->m_name = "";
	this->m_version = "";
	this->m_os = "";
	this->m_ip4 = false;
	this->m_ip6 = false;;
	this->m_osVersion = "";
	this->m_category = "";
	this->m_type = "";
	this->m_jingleVoice = "FALSE";	//	urn:xmpp:jingle:apps:rtp:audio
	this->m_jingleVideo = "FALSE";	//	urn:xmpp:jingle:apps:rtp:video
	this->m_googleVoice = "FALSE";	//	http://www.google.com/xmpp/protocol/voice/v1
	this->m_googleVideo = "FALSE";	//	http://www.google.com/xmpp/protocol/video/v1
}

// get
std::string SwVersion::jingleVoice( void ) {

	return this->m_jingleVoice;
}

// get
std::string SwVersion::jingleVideo( void ) {

	return this->m_jingleVideo;
}

// get
std::string SwVersion::googleVideo( void ) {

	return this->m_googleVideo;
}

// get
std::string SwVersion::googleVoice( void ) {

	return this->m_googleVoice;
}

// set
void SwVersion::jingleVoice( std::string voice ) {

	this->m_jingleVoice = voice;
}

// set
void SwVersion::jingleVideo( std::string video ) {

	this->m_jingleVideo = video;
}

// set
void SwVersion::googleVoice( std::string voice ) {

	this->m_googleVoice = voice;
}

// set
void SwVersion::googleVideo( std::string video ) {

	this->m_googleVideo = video;
}

