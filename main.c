#include <SDL.h>  //SDL kütüphanesini ekliyoruz
#include <stdio.h> // c fonksiyonlari icin
#include <stdbool.h> //game loop için bool kullanmak için

const int pencereUzunlugu = 400; //const(baska yerde degistirilmemesi icin) olarak pencerenin uzunlugunu ve genisligini tanimliyoruz 
const int pencereGenisligi = 700;

SDL_Window* pencere = NULL; //penceremizi ve ekranyüzeyimizi tanýmlýyoruz bunlarý pointer ile tanýmlama sebebimiz bunlarýn aslýnda devasa bir struck yapýsý olmasýdýr main fonksiyonumuzda her çaðýrdýgýmýzda hepsinin çaðrýlmasý degil sadece o konumun gönderilmesidir. null atama sebebimiz ise pointer tanýmladýgmýz icin bize boþ bir adres tutmasýný saglamak.
SDL_Surface* ekranYuzeyi = NULL;

	int main(int argc, char* args[]) //mainimizi açýyoruz fakat parantez içlerine dýþardan uygulamayý açarken gelicek olan komutlarýn sayýsýný tutmak icin int argc, dýþardan gelen komutlarýn ne oldugunu tutabilcegimiz bir char pointer dizisi olusturuyoruz.  
//pointer þeklinde olusturmamýzýn sebebi ise birden fazla string yapýsýný tutabilmek
{

	SDL_Init(SDL_INIT_VIDEO); //burada SDL mizi görüntü ve penceremizi baþlatýyoruz.

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Dosya aciliamadi.. SDL hatasi :%s\n", SDL_GetError()); //eger bir hata ile karsilasirsak geterror fonksiyonu ile bize hatanýn sebebini alýyoruz
	}

	pencere = SDL_CreateWindow("AsteroidsGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, pencereGenisligi, pencereUzunlugu, SDL_WINDOW_SHOWN); //penceremizi olusturuyoruz ilk parametremiz pencerenin üst cugubunda yazýcak olan isim, ikincisi pencerenin yatay konumda nerden baþlayacagý, üçüncüsü dikey konumda, dört ve besinciler ise pencremizin uzunlugu ve genisligi, sdl window shown yazarak da olusturur olusturmaz pencerenin açýlmasýný saglamak.

	if (pencere == NULL)
	{
		printf("Pencere olusturualamdi... Hata :%s\n", SDL_GetError()); //ayný sekilde pencere acilamama durumunda hatanin sebebini almak icin 
	}

	ekranYuzeyi = SDL_GetWindowSurface(pencere); // penceremizi olusturuyoruz
	SDL_FillRect(ekranYuzeyi, NULL, SDL_MapRGB(ekranYuzeyi->format, 0xFF, 0xFF, 0xFF)); // ekranyüzeyin yüzeyinin boyamak istegimiz alanýný boyuyoruz null yazarak hepsini boyuyoruz .format yaparak ise rgb formatýna sabitliyoruz.


	bool oyunDevamEdiyor = true; //oyun döngüsünü kontrol etmek icin
	SDL_Event olay; //basýlan tuslari tutmamiz icin
	while (oyunDevamEdiyor) 
	{
		while (SDL_PollEvent(&olay)) // burada tuslarin durmunu kontrol ediyoruz if yerine while kullanma sebebimiz ve adres olarak tutmamiz delay olmamasi icin 
		{
			if (olay.type == SDL_QUIT) // eger kapatma tusuna basilirsa 
			{
				oyunDevamEdiyor = false; // döngüden cikart
			}

		}
	
		SDL_UpdateWindowSurface(pencere); //her tusa basýldýktan sonra oyun penceresini guncelliyoruz
	}

	SDL_DestroyWindow(pencere); //olusturdugumuz pencereyi kapatayiyoruz
	SDL_Quit; //baþlattýgýmýz sdl lerin hepsini kapatiyoruz

	return 0;
}



