#include "Baralla.h"
#include "Carta.h"
#include <sf2d.h>

const int CARTES_MAX=52, ITERACIONS=1000;

Baralla::Baralla(int llavor, sf2d_texture *p[]){
    const char vecpals[]={'P','c','d','T'};
    char vecvalors[13];
    Carta::CrearVectorValors(vecvalors);
    int comptador=0;
	for(int i=0;i<4;i++)
        for(int j=0;j<13;j++){
			a_baralla[comptador].Modificar(vecvalors[j],vecpals[i],p[comptador],p[52]);
			comptador++;
		}
    iniLlavor(llavor);
    for(int i=0;i<ITERACIONS;i++)
        a_baralla[aleatori(CARTES_MAX)].Intercanviar(a_baralla[aleatori(CARTES_MAX)]);
}

Carta Baralla::Get_Carta(int index)const{
    return a_baralla[index];
}

void Baralla::iniLlavor(int llavor){
    a_llavor = llavor;
}

int Baralla::aleatori(int max){
    a_llavor = a_llavor * 1103515245 + 12345;
    int res = (a_llavor/32) % 32768;
    return res % max;
}