#ifndef arayuz_h
#define arayuz_h

#include <SDL_mixer.h>

#include "gemiVeMermi.h"

extern SDL_Window* pencere;
extern SDL_Renderer* ekrancizici;
extern TTF_Font* font;
extern SDL_Texture* oyunSonuEkrani;
extern SDL_Texture* girisEkrani;
extern SDL_Texture* duraklatmaEkrani;
extern SDL_Texture* kontrollerMenu;
extern int skor;
extern int enYuksekSkor;
extern int aktifButon;
extern const int pencereGenisligi;
extern const int pencereUzunlugu;
extern bool oyunDevamEdiyor;
extern int fareX;
extern int fareY;
extern SDL_Texture* btnbasla;
extern SDL_Texture* btnkntrl;
extern SDL_Texture* btncikis;
extern SDL_Texture* btnanamenu;
extern SDL_Texture* btndevamet;
extern SDL_Texture* btndrkltmacikis;
extern SDL_Texture* btnoynsonuanamenu;
extern SDL_Texture* btntekraroyna;
extern SDL_Texture* btncik;
extern SDL_Texture* btngeridon;
extern Mix_Chunk* butonSesi;
void canBari(Gemi* gemi);
void canSayisi(Gemi* gemi);
void skorYaz();
void rekoruOku();
void rekoruKaydet();
void rekoruVeSkoruYaz();
void girisEkraniniCiz();
void duraklatmaEkraniCiz();
void oyunsonuEkraniCiz();
void kontrollerMenusuCiz();

#endif