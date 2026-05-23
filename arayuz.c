#include <SDL.h>
#include <SDL_ttf.h>
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
        SDL_SetRenderDrawColor(ekrancizici, 0, 255, 0, 180); // yeşil
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

void skorYaz()
{
    if (font == NULL)
    {
        return;
    }
    char skorMetni[30];
    sprintf(skorMetni, "SKOR: %d", skor);
    SDL_Color sari = { 255, 255, 0, 255 };
    SDL_Surface* yaziYuzeyi = TTF_RenderText_Blended(font, skorMetni, sari);
    SDL_Texture* yaziDokusu = SDL_CreateTextureFromSurface(ekrancizici, yaziYuzeyi);
    SDL_Rect yaziKutusu;
    yaziKutusu.x = (pencereGenisligi - yaziYuzeyi->w) / 2;
    yaziKutusu.y = (20);
    yaziKutusu.w = yaziYuzeyi->w;
    yaziKutusu.h = yaziYuzeyi->h;

    SDL_RenderCopy(ekrancizici, yaziDokusu, NULL, &yaziKutusu);

    SDL_FreeSurface(yaziYuzeyi);
    SDL_DestroyTexture(yaziDokusu);
}

void rekoruOku() //rekoru okuyoruz 
{
    FILE* dosyadanOku;
    dosyadanOku = fopen("resimler/rekor.txt", "r");

    if (dosyadanOku != NULL)
    {
        (void)fscanf(dosyadanOku, "%d", &enYuksekSkor); // fscanf in bir deger döndürdügünü ignorlamak icin basina void koyduk
        fclose(dosyadanOku);
    }
}

void rekoruKaydet() //oyunu kapatıp actigimizda rekorun gitmemesi icin dosya acip oraya kaydediyoruz
{
    FILE* dosyayaYaz;
    dosyayaYaz = fopen("resimler/rekor.txt", "w");
    if (dosyayaYaz != NULL)
    {
        fprintf(dosyayaYaz, "%d", enYuksekSkor);
        fclose(dosyayaYaz);
    }
}

void rekoruVeSkoruYaz() // burda ise yazdirma islemi yapiyoruz
{
    if (font != NULL)
    {
        char sonSkorMetni[50];
        char yuksekSkorMetni[50];

        sprintf(sonSkorMetni, "Skor : %d", skor);
        sprintf(yuksekSkorMetni, "En Yuksek Skor : %d", enYuksekSkor);

        SDL_Color beyaz = { 255, 255, 255, 255 };
        SDL_Color sari = { 255, 215, 0, 255 };

        SDL_Surface* skorYuzeyi = TTF_RenderText_Solid(font, sonSkorMetni, beyaz);

        SDL_Texture* skorResmi = SDL_CreateTextureFromSurface(ekrancizici, skorYuzeyi);


        SDL_Rect skorKutusu = { 240, 360, skorYuzeyi->w, skorYuzeyi->h };


        SDL_RenderCopy(ekrancizici, skorResmi, NULL, &skorKutusu);


        SDL_FreeSurface(skorYuzeyi);
        SDL_DestroyTexture(skorResmi);

        SDL_Surface* rekorYuzeyi = TTF_RenderText_Solid(font, yuksekSkorMetni, sari);

        SDL_Texture* rekorResmi = SDL_CreateTextureFromSurface(ekrancizici, rekorYuzeyi);


        SDL_Rect rekorKutusu = { 360, 360, rekorYuzeyi->w, rekorYuzeyi->h };


        SDL_RenderCopy(ekrancizici, rekorResmi, NULL, &rekorKutusu);


        SDL_FreeSurface(rekorYuzeyi);
        SDL_DestroyTexture(rekorResmi);
    }
}

void girisEkraniniCiz() 
{
    if (girisEkrani != NULL) {
        SDL_RenderCopy(ekrancizici, girisEkrani, NULL, NULL);
    }
    SDL_Rect baslaKutu = { 254, 336, 300, 60 }; 
    SDL_Rect kntrlKutu = { 254, 403, 300, 60 };
    SDL_Rect cikisKutu = { 254, 470, 300, 60 };

    if (fareX > baslaKutu.x && fareX < (baslaKutu.x + baslaKutu.w) && fareY > baslaKutu.y && fareY < (baslaKutu.y + baslaKutu.h)) //eger faremiz butonun icindeyse
    {
        if (aktifButon != 1)
        {
            Mix_PlayChannel(3, butonSesi, 0); // hani kanalı kullancagini hangi ses oldugunu ve kac kez calıcagini belirliyoruz
            aktifButon = 1;
        }
        SDL_Rect yeniBasla = { //yeni buton daha buyuk
            baslaKutu.x - 10,     
            baslaKutu.y - 8,    
            baslaKutu.w + 10,   
            baslaKutu.h + 10     
        };

        if (btnbasla != NULL) {
            SDL_RenderCopy(ekrancizici, btnbasla, NULL, &yeniBasla); //ustune yapistiriyoruz
        }
    }
    else if (fareX > kntrlKutu.x && fareX < (kntrlKutu.x + kntrlKutu.w) && fareY > kntrlKutu.y && fareY < (kntrlKutu.y + kntrlKutu.h))
    {
        if (aktifButon != 2)
        {
            Mix_PlayChannel(3, butonSesi, 0);
            aktifButon = 2; 
        }
        SDL_Rect yeniKntrl = {
            kntrlKutu.x - 10,
            kntrlKutu.y - 8,
            kntrlKutu.w + 10,
            kntrlKutu.h + 10
        };
        if (btnkntrl != NULL)
        {
            SDL_RenderCopy(ekrancizici, btnkntrl, NULL, &yeniKntrl);
        }
    }
    else if (fareX > cikisKutu.x && fareX < (cikisKutu.x + cikisKutu.w) && fareY > cikisKutu.y && fareY < (cikisKutu.y + cikisKutu.h))
    {
        if (aktifButon != 3)
        {
            Mix_PlayChannel(3, butonSesi, 0);
            aktifButon = 3; 
        }
        SDL_Rect yeniCikis = {
            cikisKutu.x - 10,
            cikisKutu.y - 8,
            cikisKutu.w + 10,
            cikisKutu.h + 10
        };
        if (btncikis != NULL)
        {
            SDL_RenderCopy(ekrancizici, btncikis, NULL, &yeniCikis);
        }
    }
    else
    {
        aktifButon = 0;
    }
}

void duraklatmaEkraniCiz()
{
    if (duraklatmaEkrani != NULL)
    {
        SDL_RenderCopy(ekrancizici, duraklatmaEkrani, NULL, NULL);
    }

    SDL_Rect anaMenuKutu = { 227, 321, 350, 60 };
    SDL_Rect devametKutu = { 227, 393, 350, 60 };
    SDL_Rect drkltmacikisKutu = { 227, 467, 350, 60 };

    if (fareX > anaMenuKutu.x && fareX < (anaMenuKutu.x + anaMenuKutu.w) && fareY > anaMenuKutu.y && fareY < (anaMenuKutu.y + anaMenuKutu.h)) 
    {
        if (aktifButon != 4)
        {
            
            Mix_PlayChannel(3, butonSesi, 0);
            aktifButon = 4; 
        }
        SDL_Rect yeniAnamenu = {
            anaMenuKutu.x - 10,
            anaMenuKutu.y - 8,
            anaMenuKutu.w + 10,
            anaMenuKutu.h + 10
        };
        if (btnanamenu != NULL)
        {
            SDL_RenderCopy(ekrancizici, btnanamenu, NULL, &yeniAnamenu);
        }
    }


    else if (fareX > devametKutu.x && fareX < (devametKutu.x + devametKutu.w) && fareY > devametKutu.y && fareY < (devametKutu.y + devametKutu.h))
    {
        if (aktifButon != 5)
        {
            Mix_PlayChannel(3, butonSesi, 0);
            aktifButon = 5;
        }
       
        SDL_Rect yenidevamet = {
            devametKutu.x - 10,
            devametKutu.y - 8,
            devametKutu.w + 10,
            devametKutu.h + 10
        };
        if (btndevamet != NULL)
        {
            SDL_RenderCopy(ekrancizici, btndevamet, NULL, &yenidevamet);
        }
    }

    else if (fareX > drkltmacikisKutu.x && fareX < (drkltmacikisKutu.x + drkltmacikisKutu.w) && fareY > drkltmacikisKutu.y && fareY < (drkltmacikisKutu.y + drkltmacikisKutu.h))
    {
        if (aktifButon != 6)
        {
            Mix_PlayChannel(3, butonSesi, 0);
            aktifButon = 6;
        }
            
        SDL_Rect yenidrkltmacikis = {
            drkltmacikisKutu.x - 10,
            drkltmacikisKutu.y - 8,
            drkltmacikisKutu.w + 10,
            drkltmacikisKutu.h + 10
        };

        if (btndrkltmacikis != NULL)
        {
            SDL_RenderCopy(ekrancizici, btndrkltmacikis, NULL, &yenidrkltmacikis);
        }
    }
    else
    {
        aktifButon = 0;
    }
}

void oyunsonuEkraniCiz()
{
    if (oyunSonuEkrani != NULL)
    {
        SDL_RenderCopy(ekrancizici, oyunSonuEkrani, NULL, NULL);
    }
    SDL_Rect oynsonuanamenuKutu = { 238, 400, 350, 60 };
    SDL_Rect tekraroynaKutu = { 238, 458, 350, 60 };
    SDL_Rect cikKutu = { 238, 516, 350, 60 };

    if (fareX > oynsonuanamenuKutu.x && fareX < (oynsonuanamenuKutu.x + oynsonuanamenuKutu.w) && fareY > oynsonuanamenuKutu.y && fareY < (oynsonuanamenuKutu.y + oynsonuanamenuKutu.h))
    {
        if (aktifButon != 7)
        {
            Mix_PlayChannel(3, butonSesi, 0);
            aktifButon = 7;
        }
        SDL_Rect yenioynsonuanamenu = {
            oynsonuanamenuKutu.x - 15,
            oynsonuanamenuKutu.y - 12,
            oynsonuanamenuKutu.w + 7,
            oynsonuanamenuKutu.h + 7
        };

        if (btnoynsonuanamenu != NULL)
        {
            SDL_RenderCopy(ekrancizici, btnoynsonuanamenu, NULL, &yenioynsonuanamenu);
        }
    }
    else if (fareX > tekraroynaKutu.x && fareX < (tekraroynaKutu.x + tekraroynaKutu.w) && fareY > tekraroynaKutu.y && fareY < (tekraroynaKutu.y + tekraroynaKutu.h))
    {
        if (aktifButon != 8)
        {
            Mix_PlayChannel(3, butonSesi, 0);
            aktifButon = 8;
        }
        SDL_Rect yenitekraroyna = {
            tekraroynaKutu.x - 15,
            tekraroynaKutu.y - 12,
            tekraroynaKutu.w + 7,
            tekraroynaKutu.h + 7
        };

        if (btntekraroyna != NULL)
        {
            SDL_RenderCopy(ekrancizici, btntekraroyna, NULL, &yenitekraroyna);
        }
    }
    else if (fareX > cikKutu.x && fareX < (cikKutu.x + cikKutu.w) && fareY > cikKutu.y && fareY < (cikKutu.y + cikKutu.h))
    {
        if (aktifButon != 9)
        {
            Mix_PlayChannel(3, butonSesi, 0);
            aktifButon = 9;
        }
        SDL_Rect yenicik = {
            cikKutu.x - 15,
            cikKutu.y - 12,
            cikKutu.w + 7,
            cikKutu.h + 7
        };

        if (btncik != NULL)
        {
            SDL_RenderCopy(ekrancizici, btncik, NULL, &yenicik);
        }
    }
    else
    {
        aktifButon = 0;
    }
}

void kontrollerMenusuCiz()
{
    if (kontrollerMenu != NULL)
    {
        SDL_RenderCopy(ekrancizici, kontrollerMenu, NULL, NULL);
    }
    SDL_Rect geriDonKutu = { 260, 540, 250, 50 };

    if (fareX > geriDonKutu.x && fareX < (geriDonKutu.x + geriDonKutu.w) && fareY > geriDonKutu.y && fareY < (geriDonKutu.y + geriDonKutu.h))
    {
        if (aktifButon != 10)
        {
            Mix_PlayChannel(3, butonSesi, 0);
            aktifButon = 10;
        }
        SDL_Rect yeniGeriDon = {
            geriDonKutu.x - 10,
            geriDonKutu.y - 5,
            geriDonKutu.w + 6,
            geriDonKutu.h + 6
        };

        if (btngeridon != NULL)
        {
            SDL_RenderCopy(ekrancizici, btngeridon, NULL, &yeniGeriDon);
        }
    }
    else
    {
        aktifButon = 0;
    }

}