#ifndef meteor_h
#define meteor_h

#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>
#include <stdlib.h>

#define maxMeteor 20

extern const int pencereUzunlugu;
extern const int pencereGenisligi;
extern int skor;
extern SDL_Renderer* ekrancizici;

extern SDL_Texture* meteor1;
extern SDL_Texture* meteor2;
extern SDL_Texture* meteor3;
extern SDL_Texture* planet1;
extern SDL_Texture* planet2;
extern SDL_Texture* planet3;

typedef struct { //meteorumuzun konumunu hizini acisini durumunu tutucak
	double x;
	double y;
	double hizX;
	double hizY;
	double aci;
	double donmeHizi;
	bool canli;
	int cesit;
	SDL_Rect meteorKutusu;

}Meteor;

void meteorOlustur(Meteor meteorlar[]);
void meteorlariFirlat(Meteor meteorlar[]);
void meteorlariHareketEttir(Meteor meteorlar[]);
void meteorlariCiz(Meteor meteorlar[]);

#endif
