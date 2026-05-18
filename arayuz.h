#ifndef arayuz_h
#define arayuz_h

#include "gemiVeMermi.h"

extern SDL_Renderer* ekrancizici;
extern TTF_Font* font;
extern SDL_Texture* oyunSonuEkrani;
extern int skor;
extern int enYuksekSkor;
extern const int pencereGenisligi;
extern const int pencereUzunlugu;


void canBari(Gemi* gemi);
void canSayisi(Gemi* gemi);
void skorYaz();
void rekoruOku();
void rekoruKaydet();
void rekoruVeSkoruYaz();

#endif