#ifndef BagliListe_hpp
#define BagliListe_hpp
#include "Dugum.hpp"
class BagliListe
{
public:
    BagliListe();
    ~BagliListe();
    void ekle(char veri);
    //void satirEkle(Satir* yeniSatir);
    
    void yazdir();
    void cikar();
	
    int satirSayisi();
    int sutunSayisi();
    BagliListe* solTaraf();
    BagliListe* sagTaraf();
    static BagliListe* caprazlama(BagliListe* liste1, BagliListe* liste2, bool solBirlestir);
    void mutasyon(int konum);
    //void otomatikIslemler();
    bool kucukMu(char gen1, char gen2);
    char karsilastirma();

    Dugum* ilk;
    Dugum* son;
};

#endif