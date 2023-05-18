#include <iostream>
#include <string>
#include <fstream>
#include <locale.h>
#include <time.h>
#include <math.h>
using namespace std;

string isimdizisi[50]; //ad.txt dosyasından verileri çeken dizi
string soyaddizisi[50]; //soyisim.txt dosyasından verileri çeken dizi
string cevaplar[10]; //kişinin girdiği cevaplar için olan dizi
string olankisiler[2500][5]; //random kişi oluşturmada kullanılan dizi
string kisi_yanitlari[10]; // random kişilerin cevaplarını göstermek için kullanılan dizi
int siralama_sekli; //kişilerin sıralama şeklini belirleyen dizi


void isimyaz() { //Ad dosyasının çalışmasını sağlayan fonksiyon
	ifstream ad("ad.txt");
	string isim;
	int i = 0;
	if (ad.is_open())
	{
		while (i < 50)
		{
			getline(ad, isim);
			isimdizisi[i] = isim;
			i++;
		}
	}
}


void soyadyaz() { //Soyad dosyasının çalışmasını sağlayan fonksiyon
	ifstream soyisim("soyisim.txt");
	string soyad;
	int i = 0;
	if (soyisim.is_open())
	{
		while (i < 50)
		{
			getline(soyisim, soyad);
			soyaddizisi[i] = soyad;
			i++;
		}

	}
}



void cevap_anahtari_isaretle() { //Kişinin cevap anahtarını oluşturmasını sağlayan fonksiyon
	string cvp;
	for (int i = 0; i < 10; i++)
	{
		cout << "Cevabınızı giriniz(D/Y):" << endl; //Cevapları D/Y şeklinde girerek cevap anahtarı oluşturun
		cin >> cvp;

		if (cvp != "D" && cvp != "Y")
		{
			cout << "Yanlış giriş tarzı lütfen büyük küçük harflere dikkat edip tekrar deneyiniz." << endl;
		}

		else {
			cevaplar[i] = cvp;
		}


	}
}


void kisi_cevap_uretme(int id_kisi) { //Rastgele oluşacak kişilerin cevaplarınıveren fonksiyon
	char yanit;

	for (int i = 0; i < 10; i++)
	{
		yanit = rand() % 2; //Kişinin cevabını rastgele vermeye yarayan kod
		if (yanit == 1)
		{
			kisi_yanitlari[i] = 'D';
		}

		else
		{
			kisi_yanitlari[i] = 'Y';
		}
	}
}


int cevap_karsilastir() { //Oluşturulan cevap anahtarına göre kişilerin cevaplarını karşılaştırıp her doğru cevap için 10puan veren fonksiyon
	int dogrucvp = 0;

	for (int i = 0; i < 10; i++)
	{
		if (kisi_yanitlari[i] == cevaplar[i])
		{
			dogrucvp++;
		}
	}

	return dogrucvp * 10; //Her doğru cevapta 10 puan veren kod
}
//Mesala cevap anahtarını  DYDYYYYYYY olarak belirledik cevap anahtarı DYDYDDYYDY olan biri 70puan alır. 


int randomad, randomsoyad, yas, kisisayisi, puancik = 0; //Tüm kodda bu değişkenleri kullanabilmek için fonksiyon dışına yazdım.
void kisiyi_olustur() { //Ad ve soyisim dosyalarına göre ratgele kişiler üreten , yaşını 18-60 arasında rastgele veren ve puanı ekrana yazdıran fonksiyon

	cout << "Kişi Sayisi Giriniz: ";
	cin >> kisisayisi;

	if (kisisayisi > 2500)//2500'den büyük sayı girildiğinde hata veren kod
	{
		cout << "İstenilenden Büyük Bir Sayı Girdiniz";
	}

	else {
		for (int i = 0; i < kisisayisi; i++)
		{
			yas = rand() % 43 + 18;
			randomad = rand() % 50;
			randomsoyad = rand() % 50;
			olankisiler[i][0] = to_string(i); // değişken türü diye stringe çevirdim
			olankisiler[i][1] = isimdizisi[randomad];
			olankisiler[i][2] = soyaddizisi[randomsoyad];
			olankisiler[i][3] = to_string(yas);
			kisi_cevap_uretme(i);
			puancik = cevap_karsilastir();

			cout << isimdizisi[randomad] << " " << soyaddizisi[randomsoyad] << " " << yas << " Yaşında." << endl << "Cevaplar:";

			for (auto x : kisi_yanitlari)
			{
				cout << x << " ";
			}
			cout << "   " << "Kişinin Puanı: " << " \t" << puancik << endl;
			olankisiler[i][4] = to_string(puancik); //PUANLARI KİŞİLERLE BAĞLAYAN YER
			puancik = 0;
			cout << "------------------------------------------------------------------------------- " << endl;
		}
	}
}

void duzenli_sirala() {// Sıralama kısmının olduğu fonksiyon
	cout << "Sıralama yapmak istediğiniz şekli seçiniz(1=Puan/0=Ad)" << endl;
	cin >> siralama_sekli; //Kullanıcı 1 seçerse listedeki kişileri verileri ile sıralar, 0 seçerse yüksek puandan düşük puana göre sıralar

	while (siralama_sekli != 1 && siralama_sekli != 0) //1 ve 0 girildiğinde  puan ve ada göre seçmemizi isteyen döngü
	{
		cout << "Lütfen sıralamak istediğiniz seçeneği seçiniz (1=Puan\0=Ad)" << endl;
		cin >> siralama_sekli;
	}
	if (siralama_sekli == 0)
	{
		cout << "AD\tSOYAD\tYAŞ PUAN" << endl;
		for (int i = 0; i < kisisayisi; i++)
		{
			cout << to_string(i + 1) << "- ";
			for (int j = 1; j < 5; j++)
			{
				cout << olankisiler[i][j] << " ";
			}
			cout << endl;
		}

	}
	else if (siralama_sekli == 1)
	{
		string sira;
		cout << "AD\tSOYAD\tYAŞ PUAN" << endl;
		for (int i = 0; i < kisisayisi; i++)
			for (int j = 0; j < kisisayisi; j++)
			{
				if (olankisiler[i][4] > olankisiler[j][4])
				{
					sira = olankisiler[i][4];
					olankisiler[i][4] = olankisiler[j][4];
					olankisiler[j][4] = sira;
				}
			}
	}
	for (int i = 0; i < kisisayisi; i++)
	{
		cout << (i + 1) << "- ";
		for (int j = 1; j < 5; j++)
		{
			cout << olankisiler[i][j] << " ";
		}
		cout << endl;
	}
}

int main()
{
	setlocale(LC_ALL, "TURKISH");
	srand(time(NULL));
	isimyaz();
	soyadyaz();

	cevap_anahtari_isaretle();
	kisiyi_olustur();

	duzenli_sirala();
}