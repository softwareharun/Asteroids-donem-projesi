#ifndef carpisma_h
#define carpisma_h

#include "gemiVeMermi.h"
#include "meteor.h"

typedef enum {
	GIRIS_EKRANI = 0,
	OYUN_EKRANI = 1,
	DURAKLATMA_EKRANI = 2,
	OYUNSONU_EKRANI = 3


}EkranDurumlari;

extern EkranDurumlari oyunDurumu;

void meteorVurma(Mermi mermiler[], Meteor meteorlar[]);
void hasarAlma(Gemi* gemi, Meteor meteorlar[]);

#endif
