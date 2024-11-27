/*
* @file BagliListe.cpp
* @description Dna.txt üzerinden okuma yapan ve okunan kromozomları çeşitli işlemlere sokan programın bağlı liste yapısı
* @course 1. Öğretim C Grubu
* @assignment 1. Ödev
* @date 26.11.2024
* @author Seray Eğe seray.ege@ogr.sakarya.edu.tr
*/

#include "BagliListe.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>

BagliListe::BagliListe()
{
    ilk=nullptr;
    son=nullptr;
}
BagliListe::~BagliListe()
{
    Dugum* gecici = ilk;

    while(gecici!=0)
    {
        Dugum* silinecek = gecici;

        gecici= gecici->sonraki;
        delete silinecek;
    }
    son=nullptr;


}
void BagliListe::ekle(char veri)
{
    Dugum* yeni=new Dugum(veri);
    if(ilk==nullptr){
        ilk=yeni;
        son=yeni;
    } else{
        son->sonraki=yeni;
        yeni->onceki=son;
        son=yeni;
    }

}

/*void BagliListe::satirEkle(Satir* yeniSatir)
{
    if (ilkSatir == nullptr)
    {
        ilkSatir = yeniSatir;
    }
    else
    {
        Satir* gecici = ilkSatir;
        while (gecici->sonraki != nullptr)
        {
            gecici = gecici->sonraki;
        }
        gecici->sonraki = yeniSatir;
    }
}*/

void BagliListe::yazdir()
{
    using namespace std;

    Dugum* gecici=ilk;

    while(gecici!=0)
    {
        cout << gecici->veri;

        if(gecici->sonraki!=0)
        {
            cout << " ";
        }

        gecici=gecici->sonraki;

    }

    cout<<endl;

}

void BagliListe::cikar()
{
    if(ilk==0)  return;

    if(ilk->sonraki==0)
    {
        delete ilk;
        ilk=0;
    }
    else
    {
        Dugum* gecici = ilk;

        while(gecici->sonraki->sonraki!=0)
        {
            gecici=gecici->sonraki;
        }

        delete gecici->sonraki;
        gecici->sonraki = 0;
    }
}

int BagliListe::satirSayisi()
{
     int satirSayisi = 0;
    Dugum* gecici = ilk;

    while (gecici != 0)
    {
        if (gecici->veri == '\n')  // düğüm yeni satır karakteriyse satır sayısı artmalı
        {
            satirSayisi++;
        }
        gecici = gecici->sonraki;
    }

    return satirSayisi + 1;
}

int BagliListe::sutunSayisi()
{
    int sutunSayisi = 0;
    Dugum* gecici = ilk;

    while (gecici != 0 && gecici->veri != '\n') // yeni satır karakterine kadar sayma
    {
        sutunSayisi++;
        gecici = gecici->sonraki;
    }

    return sutunSayisi;
}


// çaprazlama fonksiyonu için
BagliListe* BagliListe::solTaraf()
{
    BagliListe* sol = new BagliListe();
    

    int orta = sutunSayisi() / 2;

    Dugum* gecici = ilk;
    for (int i = 0; i < orta; i++)
    {
        sol->ekle(gecici->veri);
        gecici = gecici->sonraki;
    }
    return sol;
}

BagliListe* BagliListe::sagTaraf()
{
    BagliListe* sag = new BagliListe();

    int sutun = sutunSayisi();
    int orta = sutunSayisi() / 2;
    
    if(sutun%2==0)
    {
        Dugum* gecici = ilk;
          for (int i = 0; i < orta; i++)
        gecici = gecici->sonraki;
          while (gecici != nullptr)
         {
        sag->ekle(gecici->veri);
        gecici = gecici->sonraki;
         }
    }
    else
    {
        Dugum* gecici = ilk;
          for (int i = 0; i < orta+1; i++)
        gecici = gecici->sonraki;
          while (gecici != nullptr)
         {
        sag->ekle(gecici->veri);
        gecici = gecici->sonraki;
         }
    }

    return sag;
}


// çaprazlama fonksiyonu
BagliListe* BagliListe::caprazlama(BagliListe* liste1, BagliListe* liste2, bool solBirlestir)
{
    BagliListe* yeniKromozom = new BagliListe();

    // ilk listenin sol veya sağ kısmını almak için
    BagliListe* parca1 = solBirlestir ? liste1->solTaraf() : liste1->sagTaraf();
    BagliListe* parca2 = solBirlestir ? liste2->sagTaraf() : liste2->solTaraf();

    // kromozomu birleştirme
    Dugum* gecici = parca1->ilk;
    while (gecici != nullptr)
    {
        yeniKromozom->ekle(gecici->veri);
        gecici = gecici->sonraki;
    }

    gecici = parca2->ilk;
    while (gecici != nullptr)
    {
        yeniKromozom->ekle(gecici->veri);
        gecici = gecici->sonraki;
    }

    delete parca1;
    delete parca2;
    return yeniKromozom;
}


// mutasyon fonksiyonu
void BagliListe::mutasyon(int konum)
{
    
    int uzunluk = sutunSayisi();  // bağlı listedeki düğüm sayısı
    if (konum < 0 || konum >= uzunluk)  // eğer konum geçersizse işlem yapma
    {
        std::cout << "Hatalı konum girdiniz!" << std::endl;
        return;
    }

	// istenen düğümü bulma
    Dugum* gecici = ilk;
    for (int i = 0; i < konum; i++)  
    {
        gecici = gecici->sonraki;
    }

    gecici->veri = 'X'; 
}

bool BagliListe::kucukMu(char gen1, char gen2){
    return (int)gen1<(int)gen2;
}


// ekrana yazdır fonksiyonu 
char BagliListe::karsilastirma(){

    if (ilk == nullptr) {
        std::cerr << "Liste boş." << std::endl;
        return 0;
    }

    Dugum* gecici = son; // sağdan başlaması için
    char ilkGen = ilk->veri;

    while (gecici != nullptr) {
        if (gecici->veri < ilkGen) {
            return gecici->veri;
        }
        gecici = gecici->onceki; // sağdan sola doğru hareket edebilmesi için, iki yönlü bağlı liste
    }

    return ilkGen;
}





