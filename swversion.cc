#include "swversion.h"

// Konstruktor
//Version::Version( std::string name, string version, string os )
//{
//	this->m_name = toJid;
//	this->resource = toResource;
//}

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

void SwVersion::parserTag( const Tag * xTag ) {


	if(xTag->findChild("field","var","ip_version") )
	{
		Tag * fieldTag = xTag->findChild("field","var","ip_version")->clone();
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
		software( (fieldTag->findChild("value"))->cdata() );
	}
	if(xTag->findChild("field","var","software_version") )
	{
		Tag * fieldTag = xTag->findChild("field","var","software_version")->clone();
		version( (fieldTag->findChild("value"))->cdata() );
	}
}


// Nastaveni JID prijemce
void SwVersion::name( std::string name ) {

	this->m_name = name;
}

// Nastaveni resource prijemce
void SwVersion::version( std::string version ) {

	this->m_version = version;
}

// Ziskani JID prijemce
void SwVersion::os( std::string os ) {

	 this->m_os = os;
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

void SwVersion::ip4( bool ip4 ) {

	this->m_ip4 = ip4;
}

void SwVersion::ip6( bool ip6 ) {

	this->m_ip6 = ip6;
}

void SwVersion::osVersion( std::string osVersion ) {

	this->m_osVersion = osVersion;
}

void SwVersion::category( std::string category ) {

	this->m_category = category;
}


void SwVersion::software( std::string software ) {

	this->m_software = software;
}

void SwVersion::type( std::string type ) {

	this->m_type = type;
}

std::string SwVersion::osVersion( void ) {

	return this->m_osVersion;
}

bool SwVersion::ip4( void ) {

	return this->m_ip4;
}

bool SwVersion::ip6( void ) {

	return this->m_ip6;
}

std::string SwVersion::category( void ) {

	return this->m_category;
}
