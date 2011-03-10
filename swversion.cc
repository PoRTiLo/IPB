#include "swversion.h"

// Konstruktor
//Version::Version( string name, string version, string os )
//{
//	this->m_name = toJid;
//	this->resource = toResource;
//}

// Tvorba IQ dotazu
Tag* SwVersion::createIqStanza( string fromJid, string toJid, string toResource ) {

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

void SwVersion::parserTagX( const Tag * xTag ) {


			if(xTag->findChild("field","var","ip_version") )
			{
				Tag * fieldTag = xTag->findChild("field","var","ip_version")->clone();
//				swVersion->setIP( (fieldTag->findChild("value"))->cdata() );					//dodelat, mozno i IP6
			}
			if(xTag->findChild("field","var","os") )
			{
				Tag * fieldTag = xTag->findChild("field","var","os")->clone();
				setOs( (fieldTag->findChild("value"))->cdata() );
			}
			if(xTag->findChild("field","var","os_version") )
			{
				Tag * fieldTag = xTag->findChild("field","var","os_version")->clone();
				setOsVersion( (fieldTag->findChild("value"))->cdata() );
			}
			if(xTag->findChild("field","var","software") )
			{
				Tag * fieldTag = xTag->findChild("field","var","software")->clone();
				setSoftware( (fieldTag->findChild("value"))->cdata() );
			}
			if(xTag->findChild("field","var","software_version") )
			{
				Tag * fieldTag = xTag->findChild("field","var","software_version")->clone();
				setVersion( (fieldTag->findChild("value"))->cdata() );
			}
}

const string& SwVersion::filterString () const {

}

StanzaExtension * SwVersion::newInstance (const Tag *tag) const {

}
Tag * SwVersion::tag () const {

}

StanzaExtension * SwVersion::clone() const {

}

// Nastaveni JID prijemce
void SwVersion::setName( string name ) {

	this->m_name = name;
}

// Nastaveni resource prijemce
void SwVersion::setVersion( string version ) {

	this->m_version = version;
}

// Ziskani JID prijemce
void SwVersion::setOs( string os ) {

	 this->m_os = os;
}

// Ziskani resource prijemce
string SwVersion::name( void ) {

	return this->m_name;
}
// Ziskani resource prijemce
string SwVersion::version( void ) {

	return this->m_version;
}
// Ziskani resource prijemce
string SwVersion::os( void ) {

	return this->m_os;
}

void SwVersion::setIP4( bool ip4 ) {

	this->m_ip4 = ip4;
}

void SwVersion::setIP6( bool ip6 ) {

	this->m_ip6 = ip6;
}

void SwVersion::setOsVersion( string osVersion ) {

	this->m_osVersion = osVersion;
}

void SwVersion::setCategory( string category ) {

	this->m_category = category;
}


void SwVersion::setSoftware( string software ) {

	this->m_software = software;
}

void SwVersion::setType( string type ) {

	this->m_type = type;
}

string SwVersion::osVersion( void ) {

	return this->m_osVersion;
}

bool SwVersion::ip4( void ) {

	return this->m_ip4;
}

bool SwVersion::ip6( void ) {

	return this->m_ip6;
}

string SwVersion::category( void ) {

	return this->m_category;
}
