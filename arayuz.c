#include <SDL.h>
#include "arayuz.h"

extern SDL_Renderer* ekrancizici;

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