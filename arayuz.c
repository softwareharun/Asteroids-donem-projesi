#include <SDL.h>
#include <SDL_ttf.h>
#include "arayuz.h"

extern SDL_Renderer* ekrancizici;
extern TTF_Font* font;
extern SDL_Texture* oyunSonuEkrani;

#include <SDL.h>
#include "arayuz.h"

void canBari(Gemi* gemi) {
   
    SDL_SetRenderDrawBlendMode(ekrancizici, SDL_BLENDMODE_BLEND); //arka plan gözükmesi icin bunu ekliyoruz
    
    SDL_Rect arkaPlanKutusu;
    arkaPlanKutusu.x = 20;
    arkaPlanKutusu.y = 20;
    arkaPlanKutusu.w = 200;
    arkaPlanKutusu.h = 25;

    SDL_SetRenderDrawColor(ekrancizici, 50, 50, 50, 120);
    SDL_RenderFillRect(ekrancizici, &arkaPlanKutusu);

    SDL_Rect canKutusu;
    canKutusu.x = 20;
    canKutusu.y = 20;
    canKutusu.w = gemi->can * 2;
    canKutusu.h = 25;

    if (gemi->can > 50) 
    {
        SDL_SetRenderDrawColor(ekrancizici, 0, 255, 0, 180); // yeþil
    }
    if (gemi->can > 20 && gemi->can <= 50) 
    {
        SDL_SetRenderDrawColor(ekrancizici, 255, 255, 0, 180); // sari
    }
    if(gemi->can <= 20)
    {
        SDL_SetRenderDrawColor(ekrancizici, 255, 0, 0, 180); // kirmizi
    }
    SDL_RenderFillRect(ekrancizici, &canKutusu);

    SDL_SetRenderDrawColor(ekrancizici, 255, 255, 255, 200);
    SDL_RenderDrawRect(ekrancizici, &arkaPlanKutusu);

    SDL_SetRenderDrawBlendMode(ekrancizici, SDL_BLENDMODE_NONE); //blend modu kapatiyoruz diger cizimler etkilenmesin diye 
}

void canSayisi(Gemi* gemi)
{
    if (font == NULL) 
    {
        return;
    }
    char canMetni[10];
	sprintf(canMetni, "%d", gemi->can); // can sayisini stringe ceviriyoruz 
    SDL_Color beyaz = { 255, 255, 255, 255 }; 
    SDL_Surface* yaziYuzeyi = TTF_RenderText_Solid(font, canMetni, beyaz);
	SDL_Texture* yaziDokusu = SDL_CreateTextureFromSurface(ekrancizici, yaziYuzeyi); // burada yaziyi ekrana basmak icin yuzeyi dokuya cevirmemiz gerekiyor
    SDL_Rect yaziKutusu;
	yaziKutusu.x = 30;
	yaziKutusu.y = 22;
	yaziKutusu.w = yaziYuzeyi->w; // yazinin genisligi ve uzunlugu yuzeyin genisligi ve uzunlugu kadar olsun diye yazinin genisligini ve uzunlugunu yuzeyden aliyoruz
	yaziKutusu.h = yaziYuzeyi->h;

	SDL_RenderCopy(ekrancizici, yaziDokusu, NULL, &yaziKutusu); //NULL yaparak yazinin tamamini seciyoruz ve nereye basacagimizi belirtiyoruz

  
    SDL_FreeSurface(yaziYuzeyi);
    SDL_DestroyTexture(yaziDokusu);
}


