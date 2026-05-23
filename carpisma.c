#include <stdio.h>
#include "carpisma.h"
#include "gemiVeMermi.h"
#include "meteor.h"

void meteorVurma(Mermi mermiler[], Meteor meteorlar[]) // meteor vurma durumunu kontrol ediyoruz eger mermi ve meteorun kutulari kesisiyorsa her ikisini de ölü yaparak ekrandan kaybolmalarini sagliyoruz
{
	for (int i = 0; i < MAXMERMI; i++)
	{
		if (mermiler[i].canli == true)
		{
			for (int j = 0; j < MAXMETEOR; j++)
			{
				if (meteorlar[j].canli == true && mermiler[i].canli == true)
				{
					if (SDL_HasIntersection(&mermiler[i].mermikutusu, &meteorlar[j].meteorKutusu)) // mermi ve meteor kesiþti mi
					{

						mermiler[i].canli = false;
						meteorlar[j].canli = false;

						int patlamaKanali = (rand() % 10) + 20;
						Mix_PlayChannel(patlamaKanali, patlamaSesi, 0);

						skor += 10;

						if (meteorlar[j].meteorKutusu.w > 70) // meteor kücük degilse
						{
							int yeniMeteor = 0; // 2 mermi olusturmak icin
							for (int k = 0; k < MAXMETEOR; k++) // yeni meteorlari tutucaz
							{
								if (meteorlar[k].canli == false && k != j) // bos bir yer bulup orda bolunen parcayi dogurcaz ama buyuk olanýn ustune yazmasini istemiyoruz
								{
									meteorlar[k].canli = true;

									meteorlar[k].cesit = meteorlar[j].cesit; // resmin ayni kalmasini istiyoruz

									meteorlar[k].x = meteorlar[j].x; //ayni konumdan firlicaklar
									meteorlar[k].y = meteorlar[j].y;

									meteorlar[k].meteorKutusu.x = (int)meteorlar[k].x; //BURADA KONUMU GUNCELLÝYORUZ OLENIN YERINDE PARLAMA SORUNUNU COZDUM
									meteorlar[k].meteorKutusu.y = (int)meteorlar[k].y;

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
	gemi->savrulmaHizi = 1.0;
	for (int i = 0; i < MAXMETEOR; i++)
	{
		if (meteorlar[i].canli == true)
		{
			if (SDL_HasIntersection(&gemi->gemikutusu, &meteorlar[i].meteorKutusu))
			{
				meteorlar[i].canli = false;

				if (meteorlar[i].meteorKutusu.w == 110)
				{
					gemi->can -= 50;
				}
				if (meteorlar[i].meteorKutusu.w == 90)
				{
					gemi->can -= 30;
				}
				if (meteorlar[i].meteorKutusu.w == 70)
				{
					gemi->can -= 20;
				}
				double gMerkezX = gemi->x + (gemi->gemikutusu.w / 2.0);
				double gMerkezY = gemi->y + (gemi->gemikutusu.h / 2.0);
				double mMerkezX = meteorlar[i].meteorKutusu.x + (meteorlar[i].meteorKutusu.w / 2.0);
				double mMerkezY = meteorlar[i].meteorKutusu.y + (meteorlar[i].meteorKutusu.h / 2.0);

				if (gMerkezX < mMerkezX) 
				{
					gemi->hizX -= gemi->savrulmaHizi; // Gemi soldaysa sola doðru it 
				}
				else
				{
					gemi->hizX += gemi->savrulmaHizi; // Gemi saðdaysa saða doðru it 
				}
				if (gMerkezY < mMerkezY) 
				{
					gemi->hizY -= gemi->savrulmaHizi; // Gemi yukarýdaysa yukarý doðru it 
				}
				else 
				{
					gemi->hizY += gemi->savrulmaHizi; // Gemi aþaðýdaysa aþaðý doðru it 
				}

				if (gemi->can <= 0)
				{
					gemi->can = 0;
					Mix_HaltChannel(1);
					oyunDurumu = OYUNSONU_EKRANI; // oyun durumunu degistirdim
				}
			}
		}
	}
}

