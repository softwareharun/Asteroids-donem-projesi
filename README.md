# AsteroidsGame: Uzayda Hayatta Kalma

Bu proje, C programlama dili ve SDL2 kütüphanesi kullanılarak sıfırdan geliştirilmiş, modüler mimariye sahip dinamik bir 2D uzay hayatta kalma oyunudur. Kocaeli Üniversitesi akademik projesi kapsamında geliştirilmiş olup, fizik mekanikleri ve zorluk seviyeleri içermektedir.

## Ekran Goruntuleri ve Oynanış

![Ana Menü](ekrangoruntuleri/anamenu.png)
![Oynanış Ekranı](ekrangoruntuleri/oyunici.png)

https://github.com/user-attachments/assets/78a3b250-e846-4de9-88be-9f3422fddc6b



## Oyun Ozellikleri

* **Modüler Mimari :** Proje tek bir dosyaya yığılmamış; arayüz, çarpışma, fizik ve yapay zeka sistemleri bağımsız `.h` ve `.c` dosyalarına bölünmüştür.
* **Zorluk Sistemi:** Oyuncu her 500 puana ulaştığında oyun hızı, meteorların dayanıklılığı ve doğma sıklığı otomatik olarak artar.
* **Meteor Parçalanması:** Belirli bir büyüklüğün üzerindeki meteorlar yok edildiğinde, rastgele açılar ve hızlarla daha küçük meteorlara bölünerek oyun alanına saçılır.
* **Çarpışma :** Mermi ve meteor etkileşimleri milisaniyelik hassasiyetle hesaplanır. Gemi hasar aldığında çarpışma yönüne göre savrulur.
* **Güçlendirmeler :** Uzaydan düşen özel kutular sayesinde gemiye geçici kalkan veya 10 saniyelik 3'lü Lazer yeteneği kazandırılabilir.
* **Kalıcı Skor Sistemi:** En yüksek skor yerel diske kaydedilir ve oyun kapansa dahi korunur.

## Oynanıs

Amacınız uzay boşluğunda geminizi hayatta tutarak üzerinize gelen meteor dalgalarını yok etmektir. Ekranın dışına çıkan objeler ekranın diğer tarafından geri gelir. Oyun ilerledikçe hayatta kalmak zorlaşır; doğru zamanda güçlendirmeleri toplamak ve geminin mekaniklerini iyi kullanmak sizi daha fazla hayatta tutar. Canınız sıfıra düştüğünde oyun biter.

## Kontroller

* **W / Yön Tuşu Yukarı:** İleri git
* **A - D / Sağ - Sol Yön Tuşları:** Gemiyi döndür
* **S / Yön Tuşu Aşağı:** Geri git
* **L-SHIFT:** Fren 
* **BOŞLUK (Space):** Lazer ateşle
* **ESC:** Oyunu Duraklat / Menü
* **F11:** Tam Ekran 

## Kurulum

Oyunu kendi bilgisayarınızda derlemek ve çalıştırmak için aşağıdaki adımları izleyin:

1. Sisteminizde bir C derleyicisi (GCC/MinGW veya Visual Studio) kurulu olmalıdır.
2. Proje bağımlılıkları olan SDL2 kütüphanelerini kurun: SDL2, SDL2_image, SDL2_mixer ve SDL2_ttf.
3. Projeyi bilgisayarınıza klonlayın: git clone [https://github.com/softwareharun/Asteroids-donem-projesi.git](https://github.com/softwareharun/Asteroids-donem-projesi.git)
4. IDE'niz üzerinden kütüphane yollarını (Include ve Lib klasörleri) projeye tanıtın ve main.c üzerinden projeyi derleyip çalıştırın.

## Kullanılan Kütüphaneler

* **C Programlama Dili:** Oyunun temel algoritması ve motor mimarisi.
* **SDL2:** Pencere yönetimi, donanım hızlandırmalı (Renderer) grafik çizimleri.
* **SDL2_image:** Şeffaf PNG dokularının (Texture) işlenmesi.
* **SDL2_mixer:** Çok kanallı SFX (patlama, lazer, motor sesi) ve arka plan müziği yönetimi.
* **SDL2_ttf:** Ekrana dinamik yazı (Can, Skor, HP) basımı.

## Teşekkürler ve Kaynaklar

Bu projenin geliştirilme ve test aşamalarında aşağıdaki kişi ve kaynaklardan destek alınmıştır:

* **Grafik ve Ses Varlıkları:** Oyunda kullanılan uzay gemisi, kalkan, meteor tasarımları ve ses efektleri [Kenney.nl, Freesound.org, Pixabay.com] üzerinden telifsiz / lisanslı olarak temin edilmiştir.
* **Arayüz Fontu:** Oyun içi skor ve menülerde kullanılan yazı tipi Arial yazı tipidir.
* **Teknik Destek ve Fikir Alışverişi:** Oyunun modüler mimarisinin kurulmasında, çarpışma algoritmalarının test edilmesinde ve proje vizyonunun şekillenmesinde bana destek olan [Gemini.com, Arkadasim Zeynep] teşekkür ederim.

## Lisans

Eğitim ve kişisel gelişim amaçlı serbestçe kullanılabilir ve değiştirilebilir.
