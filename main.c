#include <SDL.h>  //SDL kütüphanesini ekliyoruz
#include <stdio.h> // c fonksiyonlari icin
#include <stdbool.h> //game loop için bool kullanmak için

SDL_Window* pencere = NULL; //penceremizi ve ekranyüzeyimizi tanýmlýyoruz bunlarý pointer ile tanýmlama sebebimiz bunlarýn aslýnda devasa bir struck yapýsý olmasýdýr main fonksiyonumuzda her çaðýrdýgýmýzda hepsinin çaðrýlmasý degil sadece o konumun gönderilmesidir. null atama sebebimiz ise pointer tanýmladýgmýz icin bize boþ bir adres tutmasýný saglamak.
SDL_Surface* ekranYuzeyi = NULL;

const int pencereUzunlugu = 400; //const(baska yerde degistirilmemesi icin) olarak pencerenin uzunlugunu ve genisligini tanimliyoruz 
const int pencereGenisligi = 700;
SDL_Rect gemi, kanat1, kanat2, burun;//gemi olusturmak icin bir SDL_Rect ile gemi ve diger seyleri tanimliyoruz
Uint32 arkaplanrenk, gemirenk, kanat1renk, kanat2renk, burunrenk;//int yerine undefined int ile ayný iþlevli olan sdl kütüphanesinin içinde bulunan 32 bit yer kapalayan Uint32 ile gemirengini ve digerlerini tanýmlýyoruz

bool pencereyiAC()//pencereyi açmayý ve sdl yi baþlatmayi bir fonksiyonla yapýyoruz mainin icindeki karmasa azalýyor
{
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0)//burada SDL mizi görüntü ve penceremizi baþlatýyoruz.
	{
		printf("Dosya aciliamadi.. SDL hatasi :%s\n", SDL_GetError()); //eger bir hata ile karsilasirsak geterror fonksiyonu ile bize hatanýn sebebini alýyoruz
		return false; //dosya açýlamazsa false döndür
	}
	pencere = SDL_CreateWindow("AsteroidsGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, pencereGenisligi, pencereUzunlugu, SDL_WINDOW_SHOWN); //penceremizi olusturuyoruz ilk parametremiz pencerenin üst cugubunda yazýcak olan isim, ikincisi pencerenin yatay konumda nerden baþlayacagý, üçüncüsü dikey konumda, dört ve besinciler ise pencremizin uzunlugu ve genisligi, sdl window shown yazarak da olusturur olusturmaz pencerenin açýlmasýný saglamak.
	if (pencere == NULL)//pencere acildi mi kontrol ediyoruz
	{
		printf("Pencere olusturualamdi... Hata :%s\n", SDL_GetError()); //ayný sekilde pencere acilamama durumunda hatanin sebebini almak icin 
		return false; //pencere olusmazsa false döndür
	}
	ekranYuzeyi = SDL_GetWindowSurface(pencere); // penceremizi olusturuyoruz
	if (ekranYuzeyi == NULL)//ekran yuzeyinin null olup olmamasini kontrol ediyoruz
	{
		printf("ekran yuzeyi olusturulamadi... Hata:%s\n", SDL_GetError());
		return false;
	}
	return true;
}

void gemiOlustur() //gemiyi olusturmayi fonkiyonla yapiyoruz mainin icindeki karmasayi azaltiyoruz
	{
	gemi.h = 80;
	gemi.w = 40;
	gemi.x = (pencereGenisligi / 2) - (gemi.w / 2);//geminin koordinatlarýný giriyoruz x=x ekseninde nerede oldugu, y=yekseninde nerede oldudu, h geminin yukleklik, w geminin genislik
	gemi.y = pencereUzunlugu - gemi.h - 10;
	kanat1.h = 55;
	kanat1.w = 12;
	kanat1.x = (gemi.x) - (kanat1.w);
	kanat1.y = pencereUzunlugu - kanat1.h - 10;
	kanat2.h = 55;
	kanat2.w = 12;
	kanat2.x = (gemi.x) + (gemi.w);
	kanat2.y = pencereUzunlugu - kanat2.h - 10;
	burun.h = 20;
	burun.w = 12;
	burun.x = (gemi.x) + (gemi.w / 2) - (burun.w / 2);
	burun.y = (gemi.y) - burun.h;
	arkaplanrenk = SDL_MapRGB(ekranYuzeyi->format, 0xFF, 0xFF, 0xFF);//arka plan rengini olusturuyoruz formatý rgb olarak tanýmlýyoruz
	gemirenk = SDL_MapRGB(ekranYuzeyi->format, 0xFF, 0x00, 0x00);//geminin rengini veriyoruz
	kanat1renk = SDL_MapRGB(ekranYuzeyi->format, 0xFF, 0x00, 0x00);
	kanat2renk = SDL_MapRGB(ekranYuzeyi->format, 0xFF, 0x00, 0x00);
	burunrenk = SDL_MapRGB(ekranYuzeyi->format, 0xFF, 0x00, 0x00);
	}
void pencereyiKapat()//pencereyi kapatmayi da bir fonksiyona atiyoruz mainde bunu çaðýrmamýz yeticek
{
	SDL_DestroyWindow(pencere); //olusturdugumuz pencereyi kapatayiyoruz
	pencere = NULL;//pencerenin adresini de siliyoruz
	SDL_Quit(); //baþlattýgýmýz sdl lerin hepsini kapatiyoruz
}
	int main(int argc, char* args[]) //mainimizi açýyoruz fakat parantez içlerine dýþardan uygulamayý açarken gelicek olan komutlarýn sayýsýný tutmak icin int argc, dýþardan gelen komutlarýn ne oldugunu tutabilcegimiz bir char pointer dizisi olusturuyoruz.  
//pointer þeklinde olusturmamýzýn sebebi ise birden fazla string yapýsýný tutabilmek
{
		
	bool oyunDevamEdiyor = true; //oyun döngüsünü kontrol etmek icin
	SDL_Event olay; //basýlan tuslari tutmamiz icin
		
		if (!pencereyiAC())//pencere ac fonksiyonunu çaðýrýp false veya true döndürdügünü kontrol ediyoruz
		{
			printf("Pencere veya dosya acilamadi.. Hata%s\n", SDL_GetError());
	
		}
		gemiOlustur(); //gemiyi cagiriyoruz
		
		while (oyunDevamEdiyor) //oyun döngüsünü aciyoruz

	{
		while (SDL_PollEvent(&olay)) // burada tuslarin durmunu kontrol ediyoruz if yerine while kullanma sebebimiz ve adres olarak tutmamiz delay olmamasi icin 
		{
			if (olay.type == SDL_QUIT) // eger kapatma tusuna basilirsa 
			{
				oyunDevamEdiyor = false; // döngüden cikart
			}

		}
	
		SDL_FillRect(ekranYuzeyi, NULL, arkaplanrenk); // ekranyüzeyin yüzeyinin boyamak istegimiz alanýný boyuyoruz null yazarak hepsini boyuyoruz. neyi boyuyacaðimizi sona yaziyoruz fonksiyon yapýsý geregi ve her seyi almamasi icin pointer olarak gönderiyoruz.
		SDL_FillRect(ekranYuzeyi, &kanat1, kanat1renk);
		SDL_FillRect(ekranYuzeyi, &gemi, gemirenk);//geminin icini boyuyoruz
		SDL_FillRect(ekranYuzeyi, &kanat2, kanat2renk);
		SDL_FillRect(ekranYuzeyi, &burun, burunrenk);
		SDL_UpdateWindowSurface(pencere); //her tusa basýldýktan sonra oyun penceresini guncelliyoruz
	}
	
	pencereyiKapat();//pencereyi kapatiyoruz

	return 0;
}



