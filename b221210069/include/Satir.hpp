#ifndef Satir_hpp
#define Satir_hpp

#include "BagliListe.hpp"

class Satir {
public:
    BagliListe* liste;  // her satır için bağlı liste
    Satir* sonraki;  

    Satir();  
    ~Satir();  
    void satirYazdir();
    void tumListeyiYazdir(Satir* baslangic);
    Satir* ilkSatir;
};

#endif