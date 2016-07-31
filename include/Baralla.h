#ifndef BARALLA_H
#define BARALLA_H
#include "Carta.h"
#include <sf2d.h>

class Baralla
{
    public:
        // CONSTRUCTORS
        Baralla();
		Baralla(int llavor, sf2d_texture *p[]);
		//CONSULTORS
		//Pre: Index>=0 i index<52 //Post: Retorna la carta que es troba en aquella posicio de la baralla
        Carta Get_Carta(int index)const;

    private:
        //METODES DE CLASSE
        void iniLlavor(int llavor);
        int aleatori(int max);
        //ATRIBUT
        Carta a_baralla[52];
        // atribut de classe
        unsigned a_llavor;
};

#endif // BARRALLA_H