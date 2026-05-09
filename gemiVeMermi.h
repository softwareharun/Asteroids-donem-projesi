#ifndef gemiVeMermi_h //daha once tanimlanmamissa
#define gemiVeMermi_h

#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>

#define PI 3.14159265
#define maxMermi 20

extern const int pencereUzunlugu;
extern const int pencereGenisligi;

extern SDL_Renderer* ekrancizici;//iþlemciyi kullanan surface yerine artik ekrankartini kullanan renderer kullaniyoruz surface ile yaptýgýmýz gemiyi döndüremiyoduk artýk döndürebilecegiz ve fotograf yukleyecegimiz icin renderer bizim icin daha mantikli buradaki ekrancizici degiskenimiz asagidaki tüm islemleri yapan bir mekanizma gibidir
extern SDL_Texture* uzayGemisi;//texture de renderer gibi ekran karti kullanir ve daha hizlidir saydam halde getirebilmek ve fotografi döndürebilmek icin kullaniyoruz
extern SDL_Texture* mermi; //mermi olusturuyoruz

extern const Uint8* tuslar;

typedef struct {
	double x; // eski gemiX ve Y miz bu konumu tutcak
	double y;
	double hizX; // ivmelenme icin hizX ve y tanýmladim
	double hizY;
	double aci; // eski gemiAci miz
	int atisSuresi; //eski atisSuremiz
	double itisHizi; // ilk basta yaparken mainde olan ve sabit oldugu icin degismicek olan hýzýmýzý depolicak olan degisken
	SDL_Rect gemikutusu;// SDL_Rect gemi olan ve geminin baslangýc konumunu belirten structu buraya aldim kutu ile degistirdim
} Gemi;

typedef struct { // mermimizin konumlari icin x y acisi icin aci ve merminin hayatta oldugnu kontrol etmek icin canli bulunduran bir struct olusturuyoruz
	double x, y, aci;
	bool canli;
	double mermiHizi; // hizi belirliyoruz
	SDL_Rect mermikutusu; //mermimizin konumunu ve boyutlarini tutcak
}Mermi;

void gemiOlustur(Gemi* gemi);
void gemiCiz(Gemi* gemi);
void gemiyiHareketEttir(Gemi* gemi);
void gemiyiPenceredeTut(Gemi* gemi);

void mermiOlustur(Mermi mermiler[]);
void mermiAtesle(Mermi mermiler[], Gemi* gemi);
void mermiCiz(Mermi mermiler[]);

#endif