/*
* @file Dugum.cpp
* @description Dna.txt üzerinden okuma yapan ve okunan kromozomları çeşitli işlemlere sokan programın düğüm yapısı
* @course 1. Öğretim C Grubu
* @assignment 1. Ödev
* @date 26.11.2024
* @author Seray Eğe seray.ege@ogr.sakarya.edu.tr
*/

#include "Dugum.hpp"
Dugum::Dugum(char veri)
{
    this->veri=veri;
    sonraki = nullptr;
    onceki=nullptr;
}