#ifndef CARTA_H
#define CARTA_H
#include <sf2d.h>

class Carta
{
    public:
        //CONSTRUCTOR
        Carta();
		
        //CONSULTORS
        //Pre: -- //Post: Mostra la carta si aquesta està oberta o bé mostra dos asteriscs si és tancada
        void mostrar(int,int)const;
        //Pre: -- //Post: Retorna cert si la carta es de color negre
        bool esnegra()const;
        //Pre: -- //Post: Retorna cert si la carta és oberta
        bool esoberta()const;
        //Pre: -- //Post:Retorna el pal de la carta
        char Get_Pal()const;
        //Pre: -- //Post: Retorna cert si la carta entrada casa amb la actual(gran)
        bool Casen(Carta, bool espila=false)const;
        //Pre: -- //Post:Retorna cert si la carta és rei
        bool EsRei()const;
        //Pre: -- //Post:Retorna cert si la carta té el valor A
        bool EsA()const;
		
        //MODIFICADORS
        //Pre: -- //Post: La carta es modifica amb les dades entrades
        void Modificar(char valor, char pal, sf2d_texture *t, sf2d_texture *t2);
        //Pre: -- //Post: Els elements intercanviats
        void Intercanviar(Carta &b);
        //Pre: -- //Post: Modifica la carta i passa a estar en l'estat que hem entrat
        void Set_obrir(bool obrir);
        //METODES DE CLASE
        //Pre: Un vector de chars de tamany 13 o superior //Post: Retorna el vector omplert amb els caràcters corresponents als valors
        static void CrearVectorValors(char vecvalors[]);
		
    private:
        char a_valor, a_pal;
        bool a_oberta;
		sf2d_texture *a_tex, *a_tex_dar;
};

#endif // CARTA_H