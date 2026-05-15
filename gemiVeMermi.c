#include <stdio.h> 
#include "gemiVeMermi.h" 

void gemiOlustur(Gemi* gemi) //gemiyi olusturmayi fonkiyonla yapiyoruz mainin icindeki karmasayi azaltiyoruz
{
	uzayGemisi = IMG_LoadTexture(ekrancizici, "resimler/gemi.png");//fotografimizi burda png olarak aliyoruz ilk parametre yine islemi kimin yapicagi img load ile almamýz ise bu sekilde ekrana basilmaya hazir png olarak vermesi
	if (uzayGemisi == NULL) {
		printf("gemi yuklenemedi Hata : %s\n", IMG_GetError());
	}
	gemi->gemikutusu.w = 56;//geminin enini boyunu ve yerini belirliyoruz
	gemi->gemikutusu.h = 56;
	gemi->x = (pencereGenisligi / 2.0) - (gemi->gemikutusu.w / 2.0); // geminin degiskenlerini struct yapisina adigim icin artik tüm fonksiyonlarda gemi-> þeklinde tanimliyoruz nokta yerine ok kullanma sebebimiz ise fonksiyonlara bir kutu degil adres gönderdigimiz icin
	gemi->y = (pencereUzunlugu / 2.0) - (gemi->gemikutusu.h / 2.0);

	gemi->hizX = 0.00;
	gemi->hizY = 0.00;
	gemi->aci = 0.00;
	gemi->atisSuresi = 15;
	gemi->can = 100;

	gemi->gemikutusu.x = (int)gemi->x;
	gemi->gemikutusu.y = (int)gemi->y;
}

void gemiCiz(Gemi* gemi) //gemi cizmeyi de fonksiyonla yapiyoruz
{
	SDL_RenderCopyEx(ekrancizici, uzayGemisi, NULL, &gemi->gemikutusu, gemi->aci, NULL, SDL_FLIP_NONE); // sdlrendercopy ile sadece gemimizi getiriyoruz. ilk parametremiz çizim iþini hangi rendererin yaptýgýný ikinci parametre neyi getirdiðini üçüncüsü fotografin ne kadarini göstercegi null yaparak hepsini seciyoruz sonuncusu ise nereye ve hangi boyutta oldugu. 
}

void gemiyiHareketEttir(Gemi* gemi) // gemi hareketini fonksiyonla yapiyoruz degistirmek istediklerimizi pointer ile sabit kalmasini istediklerimizin degerini alýyoruz
{
	gemi->itisHizi = 0.10;
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
		gemi->hizX += sin(radyan) * gemi->itisHizi;  // gemimizin yeni konumunu sin ve cos fonkisyonlari ile tüm yönlere dagýtýyoruz x in sin olma sebebi 0 derecenin kuzeye bakmasi
		gemi->hizY -= cos(radyan) * gemi->itisHizi;
	}

	gemi->x += gemi->hizX;
	gemi->y += gemi->hizY;

	if (tuslar[SDL_SCANCODE_S] | tuslar[SDL_SCANCODE_DOWN]) // hareket mekaniðini degistirdigim icin geri giderken cok yavas gidiyordu geri gitmeyi de ileri gitme gibi yaptim
	{
		gemi->hizX -= sin(radyan) * gemi->itisHizi / 2;
		gemi->hizY += cos(radyan) * gemi->itisHizi / 2;

	}
	if (tuslar[SDL_SCANCODE_LSHIFT]) // ek olarak fren ekledim oldugu yerde kalabilmesi icin
	{
		gemi->hizX *= 0.95;
		gemi->hizY *= 0.95;
	}
	gemi->hizX *= 0.99;
	gemi->hizY *= 0.99;

	gemi->gemikutusu.x = (int)gemi->x;
	gemi->gemikutusu.y = (int)gemi->y;
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

void mermiOlustur(Mermi mermiler[]) // burda mermimizi olusturuyoruz olusan mermilerin durumlarini false yaparak baska bir deger atanmasýný engelliyoruz
{
	mermi = IMG_LoadTexture(ekrancizici, "resimler/mermi.png");
	for (int i = 0; i < maxMermi; i++)
	{
		mermiler[i].canli = false;
	}

}

void mermiAtesle(Mermi mermiler[], Gemi* gemi) // mermimizi ateslemek icin mainden basilcak tus mermi sayisi ve dizisi her mermi arasindaki bosluk ve geminin konumlarini aliyoruz
{
	if (gemi->atisSuresi > 0) // eger atis süresi kadar kare gecmediyse
	{
		(gemi->atisSuresi)--;
	}
	if (tuslar[SDL_SCANCODE_SPACE] && gemi->atisSuresi == 0) // eger space ye basildiysa ve aradan atis süresi kadar kare gectiyse
	{
		for (int i = 0; i < maxMermi; i++)
		{
			if (mermiler[i].canli == false) // siradaki atilmaya hazir ise 
			{
				mermiler[i].x = gemi->x + 28; // konumlari giriyoruz
				mermiler[i].y = gemi->y + 28;
				mermiler[i].aci = gemi->aci; // geminin baktigi yönle esitliyoruz
				mermiler[i].canli = true; // o sýradaki mermiyi 1 yaparak atesliyoruz
				gemi->atisSuresi = 20;
				mermiler[i].mermikutusu.x = (int)mermiler[i].x; //baska fonksiyonu beklemeden burada mermiyi geminin ucunda baslatiyoruz ve artik mermi meteora carptikdan sonra o konumda kalmasini engelliyoruz
				mermiler[i].mermikutusu.y = (int)mermiler[i].y;
				mermiler[i].mermikutusu.w = 16; //mermi boyutlari
				mermiler[i].mermikutusu.h = 16;
				break;
			}
		}
	}
}

void mermiCiz(Mermi mermiler[]) // mermiyi ekrana cizdirmek icin mermileri tutan diziyi rendererimizi ve mermi texturemizi aliyoruz 
{
	mermiler->mermiHizi = 5.0;
	for (int i = 0; i < maxMermi; i++)
	{
		mermiler[i].mermikutusu.w = 16; //mermi boyutlari
		mermiler[i].mermikutusu.h = 16;
		if (mermiler[i].canli) // eger mermi ekranda ise
		{
			double mermiRadyan = mermiler[i].aci * (PI / 180.0); // burada yönleri dagitiyoruz

			mermiler[i].x += sin(mermiRadyan) * mermiler->mermiHizi; // merminin yeni konumlarini giriyoruz ayni mantik ile
			mermiler[i].y -= cos(mermiRadyan) * mermiler->mermiHizi;

			if (mermiler[i].x < 0 || mermiler[i].x > pencereGenisligi || mermiler[i].y < 0 || mermiler[i].y > pencereUzunlugu) { // eger mermi ekrandan ciktiysa
				mermiler[i].canli = false; // o mermiyi ölü yap
			}
			mermiler[i].mermikutusu.x = (int)mermiler[i].x; //merminin o andaki konumu
			mermiler[i].mermikutusu.y = (int)mermiler[i].y;

			SDL_RenderCopyEx(ekrancizici, mermi, NULL, &(mermiler[i].mermikutusu), mermiler[i].aci, NULL, SDL_FLIP_NONE); // mermimizi nereye getircegimizi kimin getirecegini ve aynalama yapip yapmayacagimizi aliyoruz
		}
	}
}
