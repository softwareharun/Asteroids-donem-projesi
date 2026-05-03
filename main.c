#include <SDL.h>  //SDL kütüphanesini ekliyoruz
#include <stdio.h> // c fonksiyonlari icin
#include <stdbool.h> //game loop için bool kullanmak için
#include <SDL_image.h> // fotograf yukleyebilmek icin
#include <math.h> //sin ve cos fonkisyonlarýný eklemek icin

#define PI 3.14159265 // pi yi tanýmlýyoruz
#define maxMermi 20 // degistirmicegimiz icin burada tanimladim


SDL_Window* pencere = NULL; //penceremizi tanýmlýyoruz bunlarý pointer ile tanýmlama sebebimiz bunlarýn aslýnda devasa bir struck yapýsý olmasýdýr main fonksiyonumuzda her çaðýrdýgýmýzda hepsinin çaðrýlmasý degil sadece o konumun gönderilmesidir. null atama sebebimiz ise pointer tanýmladýgmýz icin bize boþ bir adres tutmasýný saglamak.
SDL_Renderer* ekrancizici = NULL;//iþlemciyi kullanan surface yerine artik ekrankartini kullanan renderer kullaniyoruz surface ile yaptýgýmýz gemiyi döndüremiyoduk artýk döndürebilecegiz ve fotograf yukleyecegimiz icin renderer bizim icin daha mantikli buradaki ekrancizici degiskenimiz asagidaki tüm islemleri yapan bir mekanizma gibidir
SDL_Texture* uzayGemisi = NULL;//texture de renderer gibi ekran karti kullanir ve daha hizlidir saydam halde getirebilmek ve fotografi döndürebilmek icin kullaniyoruz
SDL_Texture* mermi = NULL; //mermi olusturuyoruz

const int pencereUzunlugu = 600; //const(baska yerde degistirilmemesi icin) olarak pencerenin uzunlugunu ve genisligini tanimliyoruz 
const int pencereGenisligi = 800;

const Uint8* tuslar; // parametre gönderirken bunuda göndermemek icin burda tanimladim 

bool pencereyiAC()//pencereyi açmayý ve sdl yi baþlatmayi bir fonksiyonla yapýyoruz mainin icindeki karmasa azalýyor
{
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0)//burada SDL mizi görüntü ve penceremizi baþlatýyoruz.
	{
		printf("Dosya aciliamadi.. SDL hatasi :%s\n", SDL_GetError()); //eger bir hata ile karsilasirsak geterror fonksiyonu ile bize hatanýn sebebini alýyoruz
		return false; //dosya açýlamazsa false döndür
	}
	IMG_Init(IMG_INIT_PNG);
	pencere = SDL_CreateWindow("AsteroidsGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, pencereGenisligi, pencereUzunlugu, SDL_WINDOW_SHOWN); //penceremizi olusturuyoruz ilk parametremiz pencerenin üst cugubunda yazýcak olan isim, ikincisi pencerenin yatay konumda nerden baþlayacagý, üçüncüsü dikey konumda, dört ve besinciler ise pencremizin uzunlugu ve genisligi, sdl window shown yazarak da olusturur olusturmaz pencerenin açýlmasýný saglamak.
	if (pencere == NULL)//pencere acildi mi kontrol ediyoruz
	{
		printf("Pencere olusturualamdi... Hata :%s\n", SDL_GetError()); //ayný sekilde pencere acilamama durumunda hatanin sebebini almak icin 
		return false; //pencere olusmazsa false döndür
	}
	ekrancizici = SDL_CreateRenderer(pencere, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);//rendererimizi olusturuyoruz ilk parametre nerde iþ yapacagi ikincisi ise ekrankarti ile ne sekilde iletisime gececegi biz -1 diyerek sorudan kurtuluyoruz en sondaki ise donanim hizlandirma islemi burda rendereri guclendiriyoruz gibi
	if(ekrancizici == NULL)//kontrol
	{
		printf("Renderer olusturulamadi.. Hata :%s\n", SDL_GetError());
		return false;
	}
	
	return true;
}


void ekraniBoya() // ekrani siyaha boyamayi ve temizleme isini fonksiyonla yaptik
{
	SDL_SetRenderDrawColor(ekrancizici, 0, 0, 0, 255); // bu fonksiyonla rengi ve þeffaflýgý belirliyoruz ilk parametre hangi rendererin iþ yaptýgý.
	SDL_RenderClear(ekrancizici);//burda ise hepsini boyuyoruz
}

typedef struct {
	double x; // eski gemiX ve Y miz bu konumu tutcak
	double y;
	double hizX; // ivmelenme icin hizX ve y tanýmladim
	double hizY;
	double aci; // eski gemiAci miz
	int atisSuresi; //eski atisSuremiz
    SDL_Rect kutu;// SDL_Rect gemi olan ve geminin baslangýc konumunu belirten structu buraya aldim kutu ile degistirdim
} Gemi;

const double itisHizi = 0.10; // ilk basta yaparken mainde olan ve sabit oldugu icin degismicek olan hýzýmýzý depolicak olan degisken
void gemiOlustur(Gemi* gemi) //gemiyi olusturmayi fonkiyonla yapiyoruz mainin icindeki karmasayi azaltiyoruz
	{
	uzayGemisi = IMG_LoadTexture(ekrancizici, "gemi.png");//fotografimizi burda png olarak aliyoruz ilk parametre yine islemi kimin yapicagi
	if (uzayGemisi == NULL) {
		printf("gemi yuklenemedi Hata : %s\n", IMG_GetError());
		}
	gemi->kutu.w = 64;//geminin enini boyunu ve yerini belirliyoruz
	gemi->kutu.h = 64;
	gemi->x = (pencereGenisligi / 2.0) - (gemi->kutu.w / 2.0); // geminin degiskenlerini struct yapisina adigim icin artik tüm fonksiyonlarda gemi-> þeklinde tanimliyoruz nokta yerine ok kullanma sebebimiz ise fonksiyonlara bir kutu degil adres gönderdigimiz icin
	gemi->y = (pencereUzunlugu / 2.0) - (gemi->kutu.h / 2.0);

	gemi->hizX = 0.00;
	gemi->hizY = 0.00;
	gemi->aci = 0.00;
	gemi->atisSuresi = 0;

	gemi->kutu.x = (int)gemi->x;
	gemi->kutu.y = (int)gemi->y;
	}

void gemiCiz(Gemi* gemi) //gemi cizmeyi de fonksiyonla yapiyoruz
{
	SDL_RenderCopyEx(ekrancizici, uzayGemisi, NULL, &(gemi->kutu), gemi->aci, NULL, SDL_FLIP_NONE); // sdlrendercopy ile sadece gemimizi getiriyoruz. ilk parametremiz çizim iþini hangi rendererin yaptýgýný ikinci parametre neyi getirdiðini üçüncüsü fotografin ne kadarini göstercegi null yaparak hepsini seciyoruz sonuncusu ise nereye ve hangi boyutta oldugu. 
}

void gemiyiHareketEttir(Gemi* gemi) // gemi hareketini fonksiyonla yapiyoruz degistirmek istediklerimizi pointer ile sabit kalmasini istediklerimizin degerini alýyoruz
{
	if (tuslar[SDL_SCANCODE_D] | tuslar[SDL_SCANCODE_RIGHT])//sdlscancode ile tus kontrolleri yapýyoruz
	{
		gemi->aci += 2.50;//aciyi degistiriyoruz
	}
	if (tuslar[SDL_SCANCODE_A] | tuslar[SDL_SCANCODE_LEFT])
	{
		gemi->aci -= 2.50;
	}
	double radyan = gemi->aci * (PI / 180.0); // degisen aciya göre radyanýmýz degisicek
	if (tuslar[SDL_SCANCODE_W] | tuslar[SDL_SCANCODE_UP])
	{
		gemi->hizX += sin(radyan) * itisHizi;  // gemimizin yeni konumunu sin ve cos fonkisyonlari ile tüm yönlere dagýtýyoruz x in sin olma sebebi 0 derecenin kuzeye bakmasi
		gemi->hizY -= cos(radyan) * itisHizi;
	}

	gemi->x += gemi->hizX;
	gemi->y += gemi->hizY;
	
	if (tuslar[SDL_SCANCODE_S] | tuslar[SDL_SCANCODE_DOWN]) // hareket mekaniðini degistirdigim icin geri giderken cok yavas gidiyordu geri gitmeyi de ileri gitme gibi yaptim
	{
		gemi->hizX -= sin(radyan) * itisHizi;
		gemi->hizY += cos(radyan) * itisHizi;

	}
	if (tuslar[SDL_SCANCODE_LSHIFT]) // ek olarak fren ekledim oldugu yerde kalabilmesi icin
	{
		gemi->hizX *= 0.95;
		gemi->hizY *= 0.95;
	}
	gemi->hizX *= 0.99;
	gemi->hizY *= 0.99;

	gemi->kutu.x = (int)gemi->x;
	gemi->kutu.y = (int)gemi->y;
}

void gemiyiPenceredeTut(Gemi* gemi) //gemiyi pencerede tutmak icin 
{
	if (gemi->x < 0) //eger ekranin solundan cikarsa
	{
		gemi->x = pencereGenisligi; //sagdan gelsin
	}
	if (gemi->x > pencereGenisligi) // sagdan
	{
		gemi->x = 0; // sola isinla
	}
	if (gemi->y < 0) // yukardan
	{
		gemi->y = pencereUzunlugu; // asagi
	}
	if (gemi->y > pencereUzunlugu) // asagidan
	{
		gemi->y = 0; //yukari
	}
}

SDL_Rect mermikutusu; //mermimizin konumunu ve boyutlarini tutcak

typedef struct { // mermimizin konumlari icin x y acisi icin aci ve merminin hayatta oldugnu kontrol etmek icin canli bulunduran bir struct olusturuyoruz
	double x, y, aci;
	bool canli;
}Mermi;

void mermiOlustur(Mermi mermiler[], int max) // burda mermimizi olusturuyoruz olusan mermilerin durumlarini false yaparak baska bir deger atanmasýný engelliyoruz
{
	mermi = IMG_LoadTexture(ekrancizici, "mermi.png");
	for (int i = 0; i < max; i++)
	{
		mermiler[i].canli = false;
	}

}

void mermiAtesle(Mermi mermiler[], Gemi* gemi) // mermimizi ateslemek icin mainden basilcak tus mermi sayisi ve dizisi her mermi arasindaki bosluk ve geminin konumlarini aliyoruz
{
	if (gemi->atisSuresi > 0)
	{
		(gemi->atisSuresi)--;
	}
	if(tuslar[SDL_SCANCODE_SPACE] && gemi->atisSuresi==0) // eger space ye basildiysa ve aradan atis süresi kadar kare gectiyse
	{ 
	for(int i = 0; i < maxMermi; i++)
		{
		if (mermiler[i].canli == false) // siradaki atilmaya hazir ise 
			{
		mermiler[i].x = gemi->x + 32; // konumlari giriyoruz
		mermiler[i].y = gemi->y + 32;
		mermiler[i].aci = gemi->aci; // geminin baktigi yönle esitliyoruz
		mermiler[i].canli = true; // o sýradaki mermiyi 1 yaparak atesliyoruz
		gemi->atisSuresi = 20;
		break;
			}
		}
	}
}

void mermiCiz(Mermi mermiler[]) // mermiyi ekrana cizdirmek icin mermileri tutan diziyi rendererimizi ve mermi texturemizi aliyoruz 
{
mermikutusu.w = 16; //mermi boyutlari
mermikutusu.h = 16;
	for (int i = 0; i < maxMermi; i++) 
	{
		if (mermiler[i].canli) // eger mermi ekranda ise
		{
			double mermiRadyan = mermiler[i].aci * (PI / 180.0); // burada yönleri dagitiyoruz
			double mermiHizi = 3.00; // hizi belirliyoruz

			mermiler[i].x += sin(mermiRadyan) * mermiHizi; // merminin yeni konumlarini giriyoruz ayni mantik ile
			mermiler[i].y -= cos(mermiRadyan) * mermiHizi;

			if (mermiler[i].x < 0 || mermiler[i].x > pencereGenisligi || mermiler[i].y < 0 || mermiler[i].y > pencereUzunlugu) { // eger mermi ekrandan ciktiysa
				mermiler[i].canli = false; // o mermiyi ölü yap
			}
			mermikutusu.x = (int)mermiler[i].x; //merminin o andaki konumu
			mermikutusu.y = (int)mermiler[i].y;
			
			SDL_RenderCopyEx(ekrancizici, mermi, NULL, &mermikutusu, mermiler[i].aci, NULL, SDL_FLIP_NONE); // mermimizi nereye getircegimizi kimin getirecegini ve aynalama yapip yapmayacagimizi aliyoruz
		}
	}
}

void pencereyiKapat()//pencereyi kapatmayi da bir fonksiyona atiyoruz mainde bunu çaðýrmamýz yeticek
{
	SDL_DestroyTexture(uzayGemisi);//burda fotografi siliyoruz
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
	Mermi mermiler[20]; //mermilerimizi tutmasi icin dizi olusturuyoruz
	mermiOlustur(mermiler, 20); // mermiyi olusturma fonksiyonunu cagiriyoruz
	bool oyunDevamEdiyor = true; //oyun döngüsünü kontrol etmek icin
	SDL_Event olay; //basýlan tuslari tutmamiz icin
		
	while (oyunDevamEdiyor) //oyun döngüsünü aciyoruz

	{
		while (SDL_PollEvent(&olay)) // burada tuslarin durmunu kontrol ediyoruz if yerine while kullanma sebebimiz ve adres olarak tutmamiz delay olmamasi icin ayrica poll event tek kerelik basýmlar için
		{
			if (olay.type == SDL_QUIT) // eger kapatma tusuna basilirsa 
			{
				oyunDevamEdiyor = false; // döngüden cikart
			}
			
		}

		gemiyiHareketEttir(&gemi);// cagiriyoruz
		gemiyiPenceredeTut(&gemi); // cagiriyoruz
		mermiAtesle(mermiler, &gemi);//cagiriyoruz
		ekraniBoya(); //cagiriyoruz
		gemiCiz(&gemi); //cagiriyoruz
		mermiCiz(mermiler); //cagiriyoruz
		SDL_RenderPresent(ekrancizici);//sdlrenderpresent ile gösterme iþini yapar içindeki parametre yine hangi renderin kullanýldýgý.
	}
	
	pencereyiKapat();//pencereyi kapatiyoruz

	return 0;
}



