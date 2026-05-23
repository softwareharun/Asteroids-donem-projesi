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
//--------------EKRANLAR----------// 
SDL_Texture* oyunSonuEkrani = NULL;
SDL_Texture* girisEkrani = NULL;
SDL_Texture* duraklatmaEkrani = NULL;
SDL_Texture* kontrollerMenu = NULL;
//------------EKRANLAR----------------// 
//----------BUTONLAR------------// 
SDL_Texture* btnbasla = NULL;
SDL_Texture* btnkntrl = NULL;
SDL_Texture* btncikis = NULL;
SDL_Texture* btnanamenu = NULL;
SDL_Texture* btndevamet = NULL;
SDL_Texture* btndrkltmacikis = NULL;
SDL_Texture* btnoynsonuanamenu = NULL;
SDL_Texture* btntekraroyna = NULL;
SDL_Texture* btncik = NULL;
SDL_Texture* btngeridon = NULL;
//-------------BUTONLAR------------//
SDL_Texture* arkaPlanResmi = NULL;
TTF_Font* font = NULL;

const int pencereUzunlugu = 600; //const(baska yerde degistirilmemesi icin) olarak pencerenin uzunlugunu ve genisligini tanimliyoruz 
const int pencereGenisligi = 800;
int skor = 0;
int enYuksekSkor = 0;
EkranDurumlari oyunDurumu = GIRIS_EKRANI;
bool oyunDevamEdiyor = true; //oyun döngüsünü kontrol etmek icin
bool tamEkran = false;
int fareX, fareY; // tam ekrana geldiðinde buton etkilesimini düzeltmek icin

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
	pencere = SDL_CreateWindow("AsteroidsGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, pencereGenisligi, pencereUzunlugu, SDL_WINDOW_SHOWN); //penceremizi olusturuyoruz ilk parametremiz pencerenin üst cugubunda yazýcak olan isim, ikincisi pencerenin yatay konumda nerden baþlayacagý, üçüncüsü dikey konumda, dört ve besinciler ise pencremizin uzunlugu ve genisligi, sdl window shown yazarak da olusturur olusturmaz pencerenin açýlmasýný saglamak. tam ekran tusunu ekledim
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
	SDL_RenderSetLogicalSize(ekrancizici, pencereGenisligi, pencereUzunlugu); // tam ekrana gecildiðinde oranlari bozmadan her seyi büyütüyoruz
	oyunSonuEkrani = IMG_LoadTexture(ekrancizici, "resimler/gameover.png"); //oyun sonu ekranini tanimladim
	if (oyunSonuEkrani == NULL) 
	{
		printf("Oyun sonu ekrani yuklenemedi.. Hata : %s\n", SDL_GetError());
		return false;
	}
	girisEkrani = IMG_LoadTexture(ekrancizici, "resimler/giris.png"); //giris ekrani tanimladim
	if (girisEkrani == NULL)
	{
		printf("Giris ekrani yuklenemedi.. Hata : %s\n", SDL_GetError());
		return false;
	}
	duraklatmaEkrani = IMG_LoadTexture(ekrancizici, "resimler/duraklatma.png");
	if (duraklatmaEkrani == NULL)
	{
		printf("Duraklatma ekrani yuklenemedi.. Hata : %s\n", SDL_GetError());
		return false;
	}
	btnbasla = IMG_LoadTexture(ekrancizici, "resimler/basla.png");
	if (btnbasla == NULL)
	{
		return false;
	}
	btnkntrl = IMG_LoadTexture(ekrancizici, "resimler/kontroller.png");
	if (btnkntrl == NULL)
	{
		return false;
	}
	btncikis = IMG_LoadTexture(ekrancizici, "resimler/cikis.png");
	if (btncikis == NULL)
	{
		return false;
	}
	btnanamenu = IMG_LoadTexture(ekrancizici, "resimler/duraklatma_anamenu.png");
	if (btnanamenu == NULL)
	{
		return false;
	}
	btndevamet = IMG_LoadTexture(ekrancizici, "resimler/devamet.png");
	if (btndevamet == NULL)
	{
		return false;
	}
	btndrkltmacikis = IMG_LoadTexture(ekrancizici, "resimler/duraklatma_cikis.png");
	if (btndrkltmacikis == NULL)
	{
		return false;
	}
	btnoynsonuanamenu = IMG_LoadTexture(ekrancizici, "resimler/anamenu.png" );
	if (btnoynsonuanamenu == NULL)
	{
		return false;
	}
	btntekraroyna = IMG_LoadTexture(ekrancizici, "resimler/tekraroyna.png");
	if (btntekraroyna == NULL)
	{
		return false;
	}
	btncik = IMG_LoadTexture(ekrancizici, "resimler/cik.png");
	if (btncik == NULL)
	{
		return false;
	}
	kontrollerMenu = IMG_LoadTexture(ekrancizici, "resimler/kontrollerMenu.png");
	if (kontrollerMenu == NULL)
	{
		return false;
	}
	btngeridon = IMG_LoadTexture(ekrancizici, "resimler/geridon.png");
	if (btngeridon == NULL)
	{
		return false;
	}
	arkaPlanResmi = IMG_LoadTexture(ekrancizici, "resimler/arkaplan.png");
	if (arkaPlanResmi == NULL)
	{
		return false;
	}

	return true;
}

void ekraniBoya() // ekrani siyaha boyamayi ve temizleme isini fonksiyonla yaptik
{
	SDL_RenderClear(ekrancizici);//burda ise hepsini boyuyoruz
	SDL_SetRenderDrawColor(ekrancizici, 0, 0, 0, 255); // tam ekrandaki kenarlari siyah yapiyoruz
	SDL_RenderClear(ekrancizici);
	SDL_RenderCopy(ekrancizici, arkaPlanResmi, NULL, NULL);
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
	SDL_DestroyTexture(girisEkrani);
	SDL_DestroyTexture(duraklatmaEkrani);
	SDL_DestroyTexture(btnbasla);
	SDL_DestroyTexture(btnkntrl);
	SDL_DestroyTexture(btnanamenu);
	SDL_DestroyTexture(btncikis);
	SDL_DestroyTexture(btndrkltmacikis);
	SDL_DestroyTexture(btndevamet);
	SDL_DestroyTexture(btnoynsonuanamenu);
	SDL_DestroyTexture(btntekraroyna);
	SDL_DestroyTexture(btncik);
	SDL_DestroyRenderer(ekrancizici);//rendereri kapatiyoruz
	SDL_DestroyWindow(pencere); //olusturdugumuz pencereyi kapatayiyoruz
	IMG_Quit();//png yi okumayi saglayan motoru durduruyoruz 
	SDL_Quit(); //baþlattýgýmýz sdl lerin hepsini kapatiyoruz
}

void oyunuSýfýrla(Gemi* gemi, Mermi mermiler[], Meteor meteorlar[]) //oyunu sýfýrlýyoruz
{
	gemi->x = (pencereGenisligi / 2.0) - (gemi->gemikutusu.w / 2.0); //gemiyi en ortaya aliyoruz
	gemi->y = (pencereUzunlugu / 2.0) - (gemi->gemikutusu.h / 2.0);

	gemi->gemikutusu.x = (int)gemi->x;
	gemi->gemikutusu.y = (int)gemi->y;

	gemi->hizX = 0.0; //diger bilesenleri de sifirliyoruzgit
	gemi->hizY = 0.0;
	gemi->aci = 0.0;
	gemi->can = 100;

	for (int i = 0; i < MAXMERMI; i++) // tüm mermileri false yapiyoruz
	{
		mermiler[i].canli = false;
	}

	for (int i = 0; i < MAXMETEOR; i++) //meteorlarida
	{
		meteorlar[i].canli = false;
	}

	skor = 0;
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
			if (olay.type == SDL_MOUSEMOTION) // mouse hareketlerini degiskene atýyoruz artik fonksiyonda tanimlamadik
			{
				fareX = olay.motion.x;
				fareY = olay.motion.y;
			}
			if (olay.type == SDL_MOUSEBUTTONDOWN) // mouseye basýldýysa
			{
				if (olay.button.button == SDL_BUTTON_LEFT) //sol týka basýldýysa
				{
					int tikX = olay.button.x; //konumlari tutuyoruz
					int tikY = olay.button.y;

					if (oyunDurumu == GIRIS_EKRANI)
					{
						if (tikX > 254 && tikX < 554 && tikY > 336 && tikY < 396)
						{
							oyunDurumu = OYUN_EKRANI;
						}
						if (tikX > 254 && tikX < 554 && tikY > 403 && tikY < 463)
						{
							oyunDurumu = KONTROLLER_EKRANI;
						}
						if (tikX > 254 && tikX < 554 && tikY > 470 && tikY < 560)
						{
							oyunDevamEdiyor = false;
						}
					}
					else if (oyunDurumu == DURAKLATMA_EKRANI)
					{
						if (tikX > 227 && tikX < 577 && tikY > 321 && tikY < 381)
						{
							oyunDurumu = GIRIS_EKRANI;
						}
						if (tikX > 227 && tikX < 577 && tikY > 393 && tikY < 453)
						{
							oyunDurumu = OYUN_EKRANI;
						}
						if (tikX > 227 && tikX < 577 && tikY > 467 && tikY < 527)
						{
							oyunDevamEdiyor = false;
						}
					}
					else if (oyunDurumu == OYUNSONU_EKRANI)
					{
						if (tikX > 238 && tikX < 588 && tikY > 400 && tikY < 460)
						{
							oyunDurumu = GIRIS_EKRANI;
						}
						if (tikX > 238 && tikX < 588 && tikY > 458 && tikY < 518)
						{
							oyunuSýfýrla(&gemi, mermiler, meteorlar);

							oyunDurumu = OYUN_EKRANI;
						}
						if (tikX > 238 && tikX < 588 && tikY > 516 && tikY < 576)
						{
							oyunDevamEdiyor = false;
						}
					}
					else if (oyunDurumu == KONTROLLER_EKRANI)
					{
						if (tikX > 260 && tikX < 510 && tikY > 540 && tikY < 590)
						{
							oyunDurumu = GIRIS_EKRANI;
						}
					}

				}
				
			}
			if (olay.type == SDL_KEYDOWN)
			{
				if (oyunDurumu == OYUN_EKRANI)
				{
					if (olay.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
					{
						oyunDurumu = DURAKLATMA_EKRANI;
					}
				}
				if (olay.key.keysym.scancode == SDL_SCANCODE_F11) // f11 ile tam ekrana gecis
				{
					tamEkran = !tamEkran;
					if (tamEkran == true)
					{
						SDL_SetWindowFullscreen(pencere, SDL_WINDOW_FULLSCREEN_DESKTOP); // tam ekrana geciriyoruz
					}
					if (tamEkran == false)
					{
						SDL_SetWindowFullscreen(pencere, 0);
					}
				}
			}
		}

		ekraniBoya(); //cagiriyoruz

		if (oyunDurumu == GIRIS_EKRANI) // giris ekrani ile baslatiyoruz
		{
			girisEkraniniCiz();
		}
		if (oyunDurumu == KONTROLLER_EKRANI)
		{
			kontrollerMenusuCiz();
		}
		
		if (oyunDurumu == OYUN_EKRANI) // artik ekranimiz 1 den fazla olucagi icin ana oyunu ve diger ekranlari ayirdim
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
			oyunDurumu = OYUNSONU_EKRANI;
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

		if (oyunDurumu == DURAKLATMA_EKRANI)
		{
			duraklatmaEkraniCiz();
		}

		else if (oyunDurumu == OYUNSONU_EKRANI) // oyun sonu ekranini gösteriyoruz
		{
			oyunsonuEkraniCiz();
			rekoruVeSkoruYaz(); // oyun sonu ekraninda rekoru ve skoru gosteriyoruz
		}

		SDL_RenderPresent(ekrancizici);//sdlrenderpresent ile gösterme iþini yapar içindeki parametre yine hangi renderin kullanýldýgý.
	}
	
	pencereyiKapat();//pencereyi kapatiyoruz

	return 0;
}




