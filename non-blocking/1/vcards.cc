#include "vcards.h"


VCards::VCards(JID jid, Client *j)
{
	m_count = 0;
}

void VCards::start( const char* sJid ) {
// nacist vsechny uzivatele
// cyklus, ve kterem volam handleVcard na kazdeho uzivatele(rozparsruje an jednotlive udaje)
// zkontroluji zda je to v databazi
// jinak ulozim do databaze

	m_vManager = new VCardManager(j);
	printf("jid name: %s\n", sJid);
//	JID jid(sJid);
//	handleVCard( jid,v);
}

void VCards::handleVCard( const JID& jid, const VCard* v ) {
printf("jsme tady a nevim jaktooooooooooooo jsem se sem dostal\n\n");

}

void VCards::handleVCardResult( VCardContext context, const JID& jid, StanzaError se = StanzaErrorUndefined ) {

}
