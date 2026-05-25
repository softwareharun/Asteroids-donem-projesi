#ifndef carpisma_h
#define carpisma_h

#include "gemiVeMermi.h"
#include "meteor.h"

typedef enum {
	GIRIS_EKRANI = 0,
	OYUN_EKRANI = 1,
	DURAKLATMA_EKRANI = 2,
	OYUNSONU_EKRANI = 3,
	KONTROLLER_EKRANI = 4

}EkranDurumlari;

extern EkranDurumlari oyunDurumu;
extern Mix_Chunk* patlamaSesi;
extern Mix_Chunk* hasarSesi;

void meteorVurma(Gemi* gemi, Mermi mermiler[], Meteor meteorlar[]);
void hasarAlma(Gemi* gemi, Meteor meteorlar[]);

#endif
