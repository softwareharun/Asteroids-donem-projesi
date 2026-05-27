#include <stdio.h>
#include <time.h>
#include "meteor.h"

void meteorOlustur(Meteor meteorlar[]) // meteorlari olusturuyoruz
{
	srand((unsigned)time(NULL)); // rastgele sayi uretmek icin srand ve time fonksiyonlarini kullaniyoruz unsigned ile cunku rand fonksiyonu unsigned int deger donduruyor
	meteor1 = IMG_LoadTexture(ekrancizici, "resimler/meteor.png");
	meteor2 = IMG_LoadTexture(ekrancizici, "resimler/meteor2.png");
	meteor3 = IMG_LoadTexture(ekrancizici, "resimler/meteor3.png");
	meteor4 = IMG_LoadTexture(ekrancizici, "resimler/meteor4.png");
	meteor5 = IMG_LoadTexture(ekrancizici, "resimler/meteor5.png");
	meteor6 = IMG_LoadTexture(ekrancizici, "resimler/meteor6.png");
	kalkanliMeteor = IMG_LoadTexture(ekrancizici, "resimler/kalkanliMeteor.png");
	ucluMeteor = IMG_LoadTexture(ekrancizici, "resimler/ucluMeteor.png");

	for (int i = 0; i < MAXMETEOR; i++)
	{
		meteorlar[i].canli = false;
	}

}

void meteorlariFirlat(Meteor meteorlar[]) //meteorlarin boyutlarini ayarliyoruz ve kenardan ortaya yonelmesini sagliyoruz
{
	double hedefX = pencereGenisligi / 2.0; //en ortayi hedefliyoruz
	double hedefY = pencereUzunlugu / 2.0;
	
	int meteorDogmaIhtimali = 100 - meteorCani * 4; // meteorlarin canina bagli olarak meteor olusma sýklýgýný artirdim
	if (meteorDogmaIhtimali < 20)
	{
		meteorDogmaIhtimali = 20;
	}
	
	if (rand() % meteorDogmaIhtimali == 0) 
	{
		for (int i = 0; i < MAXMETEOR; i++)
		{
			if (meteorlar[i].canli == false)
			{
				int ihtimal = rand() % 100; // 0 ile 99 arasý yüzdelik zar atýyoruz
				int normalSinir = 100 - guclendirmeIhtimali; // gucIhtimali 20 ise, 0-79 arasý normal meteordur

				if (ihtimal < normalSinir)
				{
					meteorlar[i].cesit = rand() % 6;    // Sadece 0-5 arasý normal meteorlar
					meteorlar[i].can = meteorCani; // Normal meteorlara o anki zorluk seviyesinin canýný ver!
				}
				else if (ihtimal >= normalSinir && ihtimal < normalSinir + (guclendirmeIhtimali / 2))
				{
					meteorlar[i].cesit = 6; // Kalkan Kutusu
					meteorlar[i].can = 1;   // Kutu olduðu için caný hep 1 kalmalý (tek yemelidir)
				}
				else
				{
					meteorlar[i].cesit = 7; // Üçlü Lazer Kutusu
					meteorlar[i].can = 1;   // Kutu olduðu için caný hep 1 kalmalý
				}

				if (meteorlar[i].cesit == 0) // hangi textureleriin hangi boyutta olcagi
				{
					meteorlar[i].meteorKutusu.w = 70;
					meteorlar[i].meteorKutusu.h = 70;
				}
				if (meteorlar[i].cesit == 1 || meteorlar[i].cesit == 2)
				{
					meteorlar[i].meteorKutusu.w = 90;
					meteorlar[i].meteorKutusu.h = 90;
				}
				if (meteorlar[i].cesit == 3 || meteorlar[i].cesit == 4 || meteorlar[i].cesit == 5)
				{
					meteorlar[i].meteorKutusu.w = 110;
					meteorlar[i].meteorKutusu.h = 110;
				}
				if (meteorlar[i].cesit == 6 || meteorlar[i].cesit == 7) // yeni meteorlarin boyutlari
				{
					meteorlar[i].meteorKutusu.w = 80;
					meteorlar[i].meteorKutusu.h = 80;
				}
				int kenar = rand() % 4; // kenardan olusmasi icin

				if (kenar == 0) 
				{
					meteorlar[i].x = rand() % pencereGenisligi;
					meteorlar[i].y = -50; 
				}
				if (kenar == 1) 
				{
					meteorlar[i].x = rand() % pencereGenisligi;
					meteorlar[i].y = pencereUzunlugu + 50; 
				}
				if (kenar == 2) 
				{
					meteorlar[i].x = -50; 
					meteorlar[i].y = rand() % pencereUzunlugu;
				}
				if (kenar == 3) 
				{
					meteorlar[i].x = pencereGenisligi + 50; 
					meteorlar[i].y = rand() % pencereUzunlugu;
				}
				double gidilecekX = hedefX - meteorlar[i].x; //meteorun rotasi
				double gidilecekY = hedefY - meteorlar[i].y;

				meteorlar[i].hizX = gidilecekX / 400.0; // burada hizini belirliyoruz
				meteorlar[i].hizY = gidilecekY / 400.0;

				meteorlar[i].aci = 0;
				meteorlar[i].donmeHizi = (rand() % 5) - 2.0; // donme hizini yapiyoruz
				meteorlar[i].meteorKutusu.x = (int)meteorlar[i].x; // hayalet meteorlarin olustugunu farkedip konumu guncelledim
				meteorlar[i].meteorKutusu.y = (int)meteorlar[i].y;
				meteorlar[i].canli = true;

				break; // döngüden cýkýyoruz
			}

		}
	}
}

void meteorlariHareketEttir(Meteor meteorlar[]) // meteorlari hareket ettiriyoruz
{
	for (int i = 0; i < MAXMETEOR; i++)
	{
		if (meteorlar[i].canli)
		{
			meteorlar[i].x += meteorlar[i].hizX; // onceden belirledigimiz hiz ile yapiyoruz
			meteorlar[i].y += meteorlar[i].hizY;

			if (meteorlar[i].x > pencereGenisligi + 50) {
				meteorlar[i].x = -50;
			}
			else if (meteorlar[i].x < -50) {
				meteorlar[i].x = pencereGenisligi + 50;
			}
			if (meteorlar[i].y > pencereUzunlugu + 50) {
				meteorlar[i].y = -50;
			}
			else if (meteorlar[i].y < -50) {
				meteorlar[i].y = pencereUzunlugu + 50;
			}

			meteorlar[i].meteorKutusu.x = (int)meteorlar[i].x; // en son olarak konumu guncelliyoruz
			meteorlar[i].meteorKutusu.y = (int)meteorlar[i].y;
			meteorlar[i].aci += meteorlar[i].donmeHizi;
		}
	}
}

void meteorlariCiz(Meteor meteorlar[]) // ekrana cizme
{
	SDL_Texture* basilacakResim = NULL;
	for (int i = 0; i < MAXMETEOR; i++)
	{
		if (meteorlar[i].canli)
		{
			if (meteorlar[i].cesit == 0)
			{
				basilacakResim = meteor1;
			}
			if (meteorlar[i].cesit == 1)
			{
				basilacakResim = meteor2;
			}
			if (meteorlar[i].cesit == 2)
			{
				basilacakResim = meteor3;
			}
			if (meteorlar[i].cesit == 3)
			{
				basilacakResim = meteor4;
			}
			if (meteorlar[i].cesit == 4)
			{
				basilacakResim = meteor5;
			}
			if (meteorlar[i].cesit == 5)
			{
				basilacakResim = meteor6;
			}
			if (meteorlar[i].cesit == 6)
			{
				basilacakResim = kalkanliMeteor;
			}
			if (meteorlar[i].cesit == 7)
			{
				basilacakResim = ucluMeteor;
			}

			SDL_RenderCopyEx(ekrancizici, basilacakResim, NULL, &meteorlar[i].meteorKutusu, meteorlar[i].aci, NULL, SDL_FLIP_NONE); // meteorun hangi resimle cizilecegini belirliyoruz ve ciziyoruz
	
			meteorCaniYaz(&meteorlar[i]);
	
		}
	}
}


