#include "version.h"

// Konstruktor
Version::Version( string toJid, string toResource )
{
	this->jid = toJid;
	this->resource = toResource;
}

// Tvorba IQ dotazu
Tag* Version::createIqStanza( string fromJid ) {

	Tag *myTagIq = new Tag("iq");
	myTagIq->addAttribute("from", fromJid);
	myTagIq->addAttribute("to", this->jid + "/" + this->resource);
	myTagIq->addAttribute("id", "asdr534f3g3");
	myTagIq->addAttribute("type", "get");
	myTagIq->addAttribute("xml:lang", "en-US");
	Tag *myTag = new Tag("query");
	myTag->setXmlns("jabber:iq:version");
	myTagIq->addChildCopy(myTag);

	return myTagIq;
}

// Nastaveni JID prijemce
void Version::setJid( string toJid ) {

	this->jid = toJid;
}

// Nastaveni resource prijemce
void Version::setResource( string toResource ) {

	this->resource = toResource;
}

// Ziskani JID prijemce
string Version::getJid( void ) {

	return this->jid;
}

// Ziskani resource prijemce
string Version::getResource( void ) {

	return this->resource;
}
