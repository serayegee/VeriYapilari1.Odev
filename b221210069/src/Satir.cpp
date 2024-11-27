/*
* @file Satir.cpp
* @description Dna.txt üzerinden okuma yapan ve okunan kromozomları çeşitli işlemlere sokan programın satır (kromozom) yapısı
* @course 1. Öğretim C Grubu
* @assignment 1. Ödev
* @date 26.11.2024
* @author Seray Eğe seray.ege@ogr.sakarya.edu.tr
*/

#include "Satir.hpp"
#include <iostream>

using namespace std;

Satir::Satir() {
    liste = new BagliListe();  // her satır için bağlı liste oluşturuyoruz
    sonraki = nullptr;  
    ilkSatir=nullptr;
}

Satir::~Satir() {
    delete liste;
    delete sonraki;  // bağlı listeyi serbest bırakma
}


void Satir::satirYazdir(){

/*
    while(gecici!=0)
    {
        std::cout << gecici->veri;

        if(gecici->sonraki!=0)
        {
            cout << " ";
        }

        gecici=gecici->sonraki;

    }

    cout<<endl;
    */
}

void Satir::tumListeyiYazdir(Satir* baslangic){
    Satir* mevcutSatir=baslangic;
    int satirNumarasi=0;

    while (mevcutSatir != nullptr) {
        cout << "Satir " << satirNumarasi << ": ";
        mevcutSatir->liste->yazdir(); // bagliListe'nin yazdir fonksiyonu
        mevcutSatir = mevcutSatir->sonraki;
        satirNumarasi++;
    }
}
