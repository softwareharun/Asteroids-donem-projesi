#include <SDL.h>  //SDL kütüphanesini ekliyoruz
#include <stdio.h> // c fonksiyonlari icin
#include <stdbool.h> //game loop için bool kullanmak için
#include <SDL_image.h> // fotograf yukleyebilmek icin
#include <math.h> //sin ve cos fonkisyonlarýný eklemek icin
#include <SDL_ttf.h> //ekrana font yazdirmak icin
#include <time.h> // rastgele sayi uretmek icin

#include "gemiVeMermi.h"
#include "meteor.h"
#include "carpisma.h"
#include "arayuz.h"

#define PI 3.14159265 // pi yi tanýmlýyoruz

SDL_Window* pencere = NULL; //penceremizi tanýmlýyoruz bunlarý pointer ile tanýmlama sebebimiz bunlarýn aslýnda devasa bir struck yapýsý olmasýdýr main fonksiyonumuzda her çaðýrdýgýmýzda hepsinin çaðrýlmasý degil sadece o konumun gönderilmesidir. null atama sebebimiz ise pointer tanýmladýgmýz icin bize boþ bir adres tutmasýný saglamak.
SDL_Renderer* ekrancizici = NULL;//iþlemciyi kullanan surface yerine artik ekrankartini kullanan renderer kullaniyoruz surface ile yaptýgýmýz gemiyi döndüremiyoduk artýk döndürebilecegiz ve fotograf yukleyecegimiz icin renderer bizim icin daha mantikli buradaki ekrancizici degiskenimiz asagidaki tüm islemleri yapan bir mekanizma gibidir
SDL_Texture* uzayGemisi = NULL;//texture de renderer gibi ekran karti kullanir ve daha hizlidir saydam halde getirebilmek ve fotografi döndürebilmek icin kullaniyoruz
SDL_Texture* mermi = NULL; //mermi olusturuyoruz
SDL_Texture* meteor1 = NULL;
SDL_Texture* meteor2 = NULL;
SDL_Texture* meteor3 = NULL;
SDL_Texture* planet1 = NULL;
SDL_Texture* planet2 = NULL;
SDL_Texture* planet3 = NULL;
SDL_Texture* oyunSonuEkrani = NULL;
TTF_Font* font = NULL;

const int pencereUzunlugu = 600; //const(baska yerde degistirilmemesi icin) olarak pencerenin uzunlugunu ve genisligini tanimliyoruz 
const int pencereGenisligi = 800;
int skor = 0;
int enYuksekSkor = 0;
int oyunDurumu = 0;

const Uint8* tuslar; // parametre gönderirken bunuda göndermemek icin burda tanimladim 

bool pencereyiAC()//pencereyi açmayý ve sdl yi baþlatmayi bir fonksiyonla yapýyoruz mainin icindeki karmasa azalýyor
{
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0)//burada SDL mizi görüntü ve penceremizi baþlatýyoruz.
	{
		printf("Dosya aciliamadi.. SDL hatasi :%s\n", SDL_GetError()); //eger bir hata ile karsilasirsak geterror fonksiyonu ile bize hatanýn sebebini alýyoruz
		return false; //dosya açýlamazsa false döndür
	}
	IMG_Init(IMG_INIT_PNG);
	if (TTF_Init() == -1) 
	{
		printf("TTF baslatilamadi.. Hata: %s\n", TTF_GetError());
		return false;
	}
	font = TTF_OpenFont("resimler/arial.ttf", 20);
	if (font == NULL) 
	{
		printf("Font dosyasi bulunamadi.. Hata: %s\n", TTF_GetError());
	
	}
	pencere = SDL_CreateWindow("AsteroidsGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, pencereGenisligi, pencereUzunlugu, SDL_WINDOW_SHOWN); //penceremizi olusturuyoruz ilk parametremiz pencerenin üst cugubunda yazýcak olan isim, ikincisi pencerenin yatay konumda nerden baþlayacagý, üçüncüsü dikey konumda, dört ve besinciler ise pencremizin uzunlugu ve genisligi, sdl window shown yazarak da olusturur olusturmaz pencerenin açýlmasýný saglamak.
	if (pencere == NULL)//pencere acildi mi kontrol ediyoruz
	{
		printf("Pencere olusturualamdi... Hata :%s\n", SDL_GetError()); //ayný sekilde pencere acilamama durumunda hatanin sebebini almak icin 
		return false; //pencere olusmazsa false döndür
	}
	ekrancizici = SDL_CreateRenderer(pencere, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);//rendererimizi olusturuyoruz ilk parametre nerde iþ yapacagi ikincisi ise ekrankarti ile ne sekilde iletisime gececegi biz -1 diyerek sorudan kurtuluyoruz en sondaki ise donanim hizlandirma islemi burda rendereri guclendiriyoruz gibi
	if (ekrancizici == NULL)//kontrol
	{
		printf("Renderer olusturulamadi.. Hata :%s\n", SDL_GetError());
		return false;
	}
	oyunSonuEkrani = IMG_LoadTexture(ekrancizici, "resimler/gameover.png"); //oyun sonu ekranini tanimladim
	if (oyunSonuEkrani == NULL) 
	{
		printf("Oyun sonu ekrani yuklenemedi.. Hata : %s\n", SDL_GetError());
		return false;
	}
	
	
	return true;
}


void ekraniBoya() // ekrani siyaha boyamayi ve temizleme isini fonksiyonla yaptik
{
	SDL_SetRenderDrawColor(ekrancizici, 0, 0, 0, 255); // bu fonksiyonla rengi ve þeffaflýgý belirliyoruz ilk parametre hangi rendererin iþ yaptýgý.
	SDL_RenderClear(ekrancizici);//burda ise hepsini boyuyoruz
}

void pencereyiKapat()//pencereyi kapatmayi da bir fonksiyona atiyoruz mainde bunu çaðýrmamýz yeticek
{
	if (font != NULL) {
		TTF_CloseFont(font);
	}
	TTF_Quit();
	SDL_DestroyTexture(uzayGemisi);//burda fotografi siliyoruz
	SDL_DestroyTexture(mermi);
	SDL_DestroyTexture(meteor1);
	SDL_DestroyTexture(meteor2);
	SDL_DestroyTexture(meteor3);
	SDL_DestroyTexture(planet1);
	SDL_DestroyTexture(planet2);
	SDL_DestroyTexture(planet3);
	SDL_DestroyTexture(oyunSonuEkrani);
	SDL_DestroyRenderer(ekrancizici);//rendereri kapatiyoruz
	SDL_DestroyWindow(pencere); //olusturdugumuz pencereyi kapatayiyoruz
	IMG_Quit();//png yi okumayi saglayan motoru durduruyoruz 
	SDL_Quit(); //baþlattýgýmýz sdl lerin hepsini kapatiyoruz
}


	int main(int argc, char* args[]) //mainimizi açýyoruz fakat parantez içlerine dýþardan uygulamayý açarken gelicek olan komutlarýn sayýsýný tutmak icin int argc, dýþardan gelen komutlarýn ne oldugunu tutabilcegimiz bir char pointer dizisi olusturuyoruz.  
	//pointer þeklinde olusturmamýzýn sebebi ise birden fazla string yapýsýný tutabilmek
{		
		if (!pencereyiAC())//pencere ac fonksiyonunu çaðýrýp false veya true döndürdügünü kontrol ediyoruz
		{
			printf("Pencere veya dosya acilamadi.. Hata%s\n", SDL_GetError());
	
		}

	tuslar = SDL_GetKeyboardState(NULL); // burada tus kontrolu yapicaz sadece evet ve hayýr döndürdüðü icin 8 bit yeterli
	Gemi gemi; // yukarda acitigimiz stuctu fonksiyonlara gondermek icin degisken atiyoruz
	gemiOlustur(&gemi); //gemiyi cagiriyoruz
	Mermi mermiler[MAXMERMI]; //mermilerimizi tutmasi icin dizi olusturuyoruz
	mermiOlustur(mermiler); // mermiyi olusturma fonksiyonunu cagiriyoruz
	Meteor meteorlar[MAXMETEOR]; //dizi olusturuyoruz
	meteorOlustur(meteorlar); // cagiriyoruz
	bool oyunDevamEdiyor = true; //oyun döngüsünü kontrol etmek icin
	SDL_Event olay; //basýlan tuslari tutmamiz icin


	rekoruOku();

		
	while (oyunDevamEdiyor) //oyun döngüsünü aciyoruz

	{
		while (SDL_PollEvent(&olay)) // burada tuslarin durmunu kontrol ediyoruz if yerine while kullanma sebebimiz ve adres olarak tutmamiz delay olmamasi icin ayrica poll event tek kerelik basýmlar için
		{
			if (olay.type == SDL_QUIT) // eger kapatma tusuna basilirsa 
			{
				oyunDevamEdiyor = false; // döngüden cikart
			}
			
		}
		ekraniBoya(); //cagiriyoruz
		
		if (oyunDurumu == 0) // artik ekranimiz 1 den fazla olucagi icin ana oyunu ve diger ekranlari ayirdim
		{
			
			gemiyiHareketEttir(&gemi);
			gemiyiPenceredeTut(&gemi);
			mermiAtesle(mermiler, &gemi);
			meteorlariFirlat(meteorlar);
			meteorlariHareketEttir(meteorlar);
			meteorVurma(mermiler, meteorlar);
			hasarAlma(&gemi, meteorlar);

		if (gemi.can <= 0) // hasarAlma fonksiyonundan sonra geminin canini kontrol ediyoruz
		{
			oyunDurumu = 1;
			if (skor > enYuksekSkor)
			{
				enYuksekSkor = skor;
				rekoruKaydet();
			}
		}

			gemiCiz(&gemi);
			mermiCiz(mermiler);
			meteorlariCiz(meteorlar);
			canBari(&gemi);
			canSayisi(&gemi);
			skorYaz();
		}
		else if (oyunDurumu == 1) // oyun sonu ekranini gösteriyoruz
		{
			SDL_RenderCopy(ekrancizici, oyunSonuEkrani, NULL, NULL);
			rekoruVeSkoruYaz(); // oyun sonu ekraninda rekoru ve skoru gosteriyoruz
		}

		SDL_RenderPresent(ekrancizici);//sdlrenderpresent ile gösterme iþini yapar içindeki parametre yine hangi renderin kullanýldýgý.
	}
	
	pencereyiKapat();//pencereyi kapatiyoruz

	return 0;
}




