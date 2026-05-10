#include <stdio.h>
#include "gemiVeMermi.h"
#include "meteor.h"

void meteorVurma(Mermi mermiler[], Meteor meteorlar[]) // meteor vurma durumunu kontrol ediyoruz eger mermi ve meteorun kutulari kesisiyorsa her ikisini de ölü yaparak ekrandan kaybolmalarini sagliyoruz
{
	for (int i = 0; i < maxMermi; i++)
	{
		if (mermiler[i].canli == true)
		{
			for (int j = 0; j < maxMeteor; j++)
			{
				if (meteorlar[j].canli == true)
				{
					if (SDL_HasIntersection(&mermiler[i].mermikutusu, &meteorlar[j].meteorKutusu)) // mermi ve meteor kesiþti mi
					{

						mermiler[i].canli = false;
						meteorlar[j].canli = false;

						if (meteorlar[j].meteorKutusu.w > 70) // meteor kücük degilse
						{
							int yeniMeteor = 0; // 2 mermi olusturmak icin
							for (int k = 0; k < maxMeteor; k++) // yeni meteorlari tutucaz
							{
								if (meteorlar[k].canli == false && k != j) // bos bir yer bulup orda bolunen parcayi dogurcaz ama buyuk olanýn ustune yazmasini istemiyoruz
								{
									meteorlar[k].canli = true;

									meteorlar[k].cesit = meteorlar[j].cesit; // resmin ayni kalmasini istiyoruz

									meteorlar[k].x = meteorlar[j].x; //ayni konumdan firlicaklar
									meteorlar[k].y = meteorlar[j].y;

									if (meteorlar[j].meteorKutusu.w == 110) //enbuyukse 2 tane orta yap
									{
										meteorlar[k].meteorKutusu.w = 90;
										meteorlar[k].meteorKutusu.h = 90;
									}
									else //orta ise 2 tane kucuk yap
									{
										meteorlar[k].meteorKutusu.w = 70;
										meteorlar[k].meteorKutusu.h = 70;
									}
									meteorlar[k].hizX = ((rand() % 5) - 2.0); //rastgele hizlarla gitsinler
									meteorlar[k].hizY = ((rand() % 5) - 2.0);

									if (meteorlar[k].hizX == 0) //eger 0 cýkarsa meteorun durmamasi icin
									{
										meteorlar[k].hizX = 1.5;
									}
									if (meteorlar[k].hizY == 0)
									{
										meteorlar[k].hizY = -1.5;
									}

									meteorlar[k].aci = 0;
									meteorlar[k].donmeHizi = 2.0; //donme acisi sabit olsun

									yeniMeteor++;
									if (yeniMeteor == 2)
									{
										break; //donguden cikart
									}
								}
							}
						}

						break;
					}
				}
			}
		}
	}
}

void hasarAlma(Gemi* gemi, Meteor meteorlar[])//GEMÝ VE METEOR CARPÝSMASÝNDA CANÝMÝZÝ AZALTÝYORUZ
{
	for (int i = 0; i < maxMeteor; i++)
	{
		if (meteorlar[i].canli == true)
		{
			if (SDL_HasIntersection(&gemi->gemikutusu, &meteorlar[i].meteorKutusu))
			{
				meteorlar[i].canli = false;

				if (meteorlar[i].meteorKutusu.w == 110)
				{
					gemi->can -= 50;
					printf("buyuk meteora carptin kalan can : %d\n", gemi->can);
				}
				if (meteorlar[i].meteorKutusu.w == 90)
				{
					gemi->can -= 30;
					printf("orta meteora carptin kalan can : %d\n", gemi->can);
				}
				if (meteorlar[i].meteorKutusu.w == 70)
				{
					gemi->can -= 20;
					printf("Kucuk meteora carptin kalan can : %d\n", gemi->can);
				}
				if (gemi->can <= 0)
				{
					printf("Oldun..");
				}
			}
		}
	}
}

