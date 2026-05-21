#ifndef arayuz_h
#define arayuz_h

#include "gemiVeMermi.h"

extern SDL_Renderer* ekrancizici;
extern TTF_Font* font;
extern SDL_Texture* oyunSonuEkrani;
extern SDL_Texture* girisEkrani;
extern SDL_Texture* duraklatmaEkrani;
extern int skor;
extern int enYuksekSkor;
extern const int pencereGenisligi;
extern const int pencereUzunlugu;
extern SDL_Texture* btnbasla;
extern SDL_Texture* btnkntrl;
extern SDL_Texture* btncikis;
extern SDL_Texture* btnanamenu;
extern SDL_Texture* btndevamet;
extern SDL_Texture* btndrkltmacikis;
extern SDL_Texture* btnoynsonuanamenu;
extern SDL_Texture* btntekraroyna;
extern SDL_Texture* btncik;
void canBari(Gemi* gemi);
void canSayisi(Gemi* gemi);
void skorYaz();
void rekoruOku();
void rekoruKaydet();
void rekoruVeSkoruYaz();
void girisEkraniniCiz();
void duraklatmaEkraniCiz();
void oyunsonuEkraniCiz();

#endif