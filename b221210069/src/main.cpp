/*
* @file main.cpp
* @description Dna.txt üzerinden okuma yapan ve okunan kromozomları çeşitli işlemlere sokan programın main fonksiyonu
* @course 1. Öğretim C Grubu
* @assignment 1. Ödev
* @date 26.11.2024
* @author Seray Eğe seray.ege@ogr.sakarya.edu.tr
*/


#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include<sstream>
#include "BagliListe.hpp"
#include "Satir.hpp"

using namespace std;

int main()
{
    Satir* ilkSatir = nullptr;
    Satir* sonSatir = nullptr;
    int satirSayisi = 0;
    int sutunSayisi=0;

    // dosyayı okuma ve listeye ekleme
    ifstream dosya("Dna.txt");
    ifstream islemlerDosyasi("Islemler.txt");

    if (dosya.is_open())
    {
        string satir;
        while (getline(dosya, satir))
        {
            Satir* yeniSatir = new Satir();

            stringstream satirOku(satir);
            char siradaki;

            //okunanları bağlı listeye ekleme
            while (satirOku >> siradaki)
            {
                yeniSatir->liste->ekle(siradaki);
            }

            if (ilkSatir == nullptr) {
                ilkSatir = yeniSatir;
            } else {
                sonSatir->sonraki = yeniSatir;
            }

            sonSatir = yeniSatir; 
            satirSayisi++;
        }
        dosya.close();
    }

    int secim;
    
    // menü işlemleri
    cout << "\n-----MENU-----\n";
    cout << "1- Caprazlama\n";
    cout << "2- Mutasyon\n";
    cout << "3- Otomatik Islemler\n";
    cout << "4- Ekrana Yaz\n";
    cout << "5- Cikis\n";

    do
    {
        cout << "Seciminiz:";
        cin >> secim;

        switch (secim)
        {
            case 1:
            {
                
                int satir1, satir2;
                cout << "Caprazlama icin ilk kromozomun satir numarasi: ";
                cin >> satir1;
                cout << "Caprazlama icin ikinci kromozomun satir numarasi: ";
                cin >> satir2;

                if (satir1 < 0 || satir2 < 0 || satir1 >= satirSayisi || satir2 >= satirSayisi) {
                cout << "Gecersiz satir numaralari.\n";
                break;
            }

            if (satir1 == satir2) {
                cout << "Ayni satirlar uzerinde caprazlama yapilamaz.\n";
                break;
            }

                Satir* kromozom1 = ilkSatir;
                Satir* kromozom2 = ilkSatir;
                for (int i = 0; i < satir1; i++) kromozom1 = kromozom1->sonraki;
                for (int i = 0; i < satir2; i++) kromozom2 = kromozom2->sonraki;

                BagliListe* yeniKromozom1 = BagliListe::caprazlama(kromozom1->liste, kromozom2->liste, true);
                BagliListe* yeniKromozom2 = BagliListe::caprazlama(kromozom1->liste, kromozom2->liste, false);

            cout << "Caprazlanan satirlar:" <<endl;
            yeniKromozom1->yazdir();
            yeniKromozom2->yazdir();


            // yeni oluşan kromozomları Dna.txt'ye eklemek istersek
            /*ofstream dosyaYaz("Dna.txt", ios::app);


                if (dosyaYaz.is_open()) {
                    // Yeni kromozom 1 yazma
                    Dugum* dugum1 = yeniKromozom1->ilk;
                    dosyaYaz<<endl;
                    while (dugum1 != nullptr) {
                        dosyaYaz << dugum1->veri << " ";
                        dugum1 = dugum1->sonraki;
                    }
                    dosyaYaz << endl;

                    // Yeni kromozom 2 yazma
                    Dugum* dugum2 = yeniKromozom2->ilk;
                    while (dugum2 != nullptr) {
                        dosyaYaz << dugum2->veri << " ";
                        dugum2 = dugum2->sonraki;
                    }
                    dosyaYaz << endl;

                    dosyaYaz.close();
                    cout << "Yeni kromozomlar Dna.txt dosyasina eklendi." << endl;
                } else {
                    cerr << "Dna.txt dosyasina yazilamadi!" << endl;
                }
            */

            //yeni oluşan kromozomları bağlı listeye ekleme
            Satir* yeniSatir1 = new Satir();
            yeniSatir1->liste=yeniKromozom1;

             Satir* yeniSatir2 = new Satir();
             yeniSatir2->liste = yeniKromozom2;

             yeniSatir1->sonraki=yeniSatir2;
             yeniSatir2->sonraki=nullptr;
             sonSatir->sonraki=yeniSatir1;
             sonSatir = yeniSatir2;

            satirSayisi+=2;

            cout << "Caprazlama islemi tamamlandi.\n";

			//kontrol için
            //ilkSatir->tumListeyiYazdir(ilkSatir);
            
            //delete yeniKromozom1;
            //delete yeniKromozom2;
            break;
            }
            case 2:
            {

                int satir, sutun;

			// satır sayısı
			int satirSayisi = 0;
			Satir* tmp = ilkSatir;
			while (tmp != nullptr) {
				satirSayisi++;
				tmp = tmp->sonraki;
			}

			// kullanıcıdan satır numarası alma
			cout << "Mutasyon yapilacak satir numarasi: ";
			cin >> satir;

			// alınan satır numarası için geçerlilik kontrolü
			if (satir < 0 || satir >= satirSayisi) {
				cout << "Gecersiz satir numarasi." << endl;
				break;
			}

			// istenen satıra gitmek için 
			Satir* secilenSatir = ilkSatir;
			for (int i = 0; i < satir; i++) {
				secilenSatir = secilenSatir->sonraki;
			}

			// sutun sayısı
			int sutunSayisi = secilenSatir->liste->sutunSayisi();
			cout << "Mutasyon yapilacak sutun numarasi: ";
			cin >> sutun;

			if (sutun < 0 || sutun >= sutunSayisi) {
				cout << "Gecersiz sutun numarasi." << endl;
				break;
			}

			// mutasyon fonksiyonunu çağırma
			secilenSatir->liste->mutasyon(sutun);

			// sonuçları yazdırma
			secilenSatir->liste->yazdir();
			cout << "Mutasyon islemi tamamlandi.\n";

			// kontrol için
			//secilenSatir->tumListeyiYazdir(ilkSatir);
			
			break;

                // mutasyonu dosyaya yazmak istersek
                /*ofstream dosyaYaz("Dna.txt");  
                if (dosyaYaz.is_open())
                {
                    Satir* geciciSatir = ilkSatir;
                    while (geciciSatir != nullptr)
                    {
                        Dugum* geciciDugum = geciciSatir->liste->ilk;
                        while (geciciDugum != nullptr)
                        {
                            dosyaYaz << geciciDugum->veri << " ";
                            geciciDugum = geciciDugum->sonraki;
                        }
                        dosyaYaz << endl;
                        geciciSatir = geciciSatir->sonraki;
                    }
                    dosyaYaz.close();
                    cout << "Mutasyon islemi tamamlandi\nDna.txt dosyasi guncellendi.\n";
                }
                else
                {
                    cout << "Dosya yazma işlemi başarısız oldu!\n";
                }*/
            }

			// otomatik işlemler
            case 3:
            {
                if(!islemlerDosyasi.is_open())
                {
                    cerr<<"Islemler.txt dosyası acilamadi." << endl;
                }

				//işlem dosyasını okuma
                string islem;
                 while (getline(islemlerDosyasi, islem)) {
                        stringstream ss(islem);
                        string secilenIslem;
                        ss>>secilenIslem;
                        int satir1, satir2;
                        int sutun;
                    
                    if (secilenIslem=="C")
                    {
                        ss >> satir1 >>  satir2;

                        if (satir1 < 0 || satir2 < 0 || satir1 >= satirSayisi || satir2 >= satirSayisi) {
                        std::cerr << "Caprazlama icin gecersiz satir numarasi, degerler 0 ve " << satirSayisi << " arasinda olmali." << std::endl;
                        continue; 
    }
                        Satir* kromozom1=ilkSatir;
                        for(int i=0;i<satir1;i++)
                        {
                            kromozom1=kromozom1->sonraki;

                        }

                        Satir* kromozom2=ilkSatir;
                        for(int i=0;i<satir2;i++)
                        {
                            kromozom2=kromozom2->sonraki;
                        }

                        BagliListe* yeniKromozom1 = BagliListe::caprazlama(kromozom1->liste,kromozom2->liste,true);
                        BagliListe* yeniKromozom2 = BagliListe::caprazlama(kromozom1->liste,kromozom2->liste,false);
                        
                        Satir* yeniSatir1 = new Satir();
                        yeniSatir1->liste = yeniKromozom1;
                        sonSatir->sonraki = yeniSatir1;
                        sonSatir = yeniSatir1;

                        Satir* yeniSatir2 = new Satir();
                        yeniSatir2->liste = yeniKromozom2;
                        sonSatir->sonraki = yeniSatir2;
                        sonSatir = yeniSatir2;

                        sonSatir->sonraki=nullptr;

                        satirSayisi+=2;

                    //delete yeniKromozom1;
                    //delete yeniKromozom2;

   
                    }

                    else if(secilenIslem=="M")
                    {
                        int satir, sutun;
                        ss >> satir >> sutun;

                        //satır sayısını güncelleme
                        int satirSayisi=0;
                        Satir* tmp= ilkSatir;
                        while(tmp!=nullptr){
                            satirSayisi++;
                            tmp=tmp->sonraki;
                        }

                        //Islemler.txt dosyasında girilen değerlerin geçerliliğini doğrulamak için
                        if (satir < 0 || satir >= satirSayisi) {
                            std::cerr << "Mutasyon icin gecersiz satir numarasi, degerler 0 ve " << satirSayisi << " arasinda olmali." << std::endl;
                            continue; 
                        }

                        Satir* secilenSatir=ilkSatir;
                        for (int i = 0; i < satir; i++)
                        {
                            secilenSatir = secilenSatir->sonraki;
                        } 

                         int sutunSayisi = secilenSatir->liste->sutunSayisi();
                         if (sutun < 0 || sutun >= sutunSayisi) {
                            std::cerr << "Mutasyon icin gecersiz sutun numarasi, degerler 0 ve " << sutunSayisi << " arasinda olmali." << std::endl;
                            continue; 
                        }

                        secilenSatir->liste->mutasyon(sutun);

                    }

                }
                islemlerDosyasi.close();

                Satir* tmp= ilkSatir;
                while(tmp!=nullptr)
                {
                    //tmp->liste->yazdir();
                    tmp=tmp->sonraki;
                }
				
				cout<< "Islemler Dna'ya uygulandi.\n";

                break;
            }
			// ekrana yazma fonksiyonu 
            case 4:
            {
                Satir* satir= ilkSatir;

                while(satir!=nullptr){
                    char kucuk=satir->liste->karsilastirma();
                    cout << kucuk << " ";
                    satir=satir->sonraki;
                }

                cout<<endl;
                break;
            }

            case 5:
                cout << "Menuden cikis yapiliyor...\n";
                break;

            default:
                cout << "Gecerli bir secenek giriniz.\n";
        }

    } while (secim != 5);

    while (ilkSatir != nullptr) {
        Satir* tmp = ilkSatir;
        ilkSatir = ilkSatir->sonraki;

        // satırdaki bağlı listeyi ve dinamik belleği serbest bırakma
        delete tmp->liste;
        delete tmp;
    }

    return 0;
}
