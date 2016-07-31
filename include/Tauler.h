#ifndef TAULER_H
#define TAULER_H
#include "Carta.h"
//#include "PilaCartes.h" //cal?
#include "Baralla.h"
#include <3ds.h>

struct Posicio_Carta{
	bool alapila;
	int pila, columna, fila; 
};

class Tauler
{
    public:
        // CONSTRUCTOR I DESTRUCTOR
        Tauler();
        ~Tauler();
		
        //CONSULTORS
        //Pre: -- //Post: Mostra el tauler
        void mostrar(const touchPosition&)const;
        //Pre: 0<col<8 //Post: Retorna la ultima carta de la columna col o bé la "fila" carta de la columna col
        Carta Get_Carta_Tauler(int col, int fila=-1)const;
        //Pre: 0<col<8 //Post: Inserteix la carta inserir a la ultima posicio de la columna col
        int Mida_Col(int col)const;
		
        //MODIFICADORS
        //Pre: 0<col<8 //Post: Treu una carta de la columna col
        void Inserir_Carta_Tauler(Carta inserir, int col);
        //Pre: 0<col<8 //Post: Retorna la mida de la columna col
        void Treure_Carta(int col);
        //Pre: 0<col<8 //Post: Obre la ultimam carta de la columna col
        void Obrir_ultima(int col);
        //Pre: Baralla amb 52 cartes //Post: Reparteix les primeres 28 cartes al tauler
        void repartir(Baralla);
		void Restaurar_Cartes();
		void NumCartesColumna(int, int &, int &)const;
		void Processar_origen(Posicio_Carta, Carta);
		void Netejar_Buffer();

    private:
        //METODES PRIVATS
        //ATRIBUTS
        Carta **a_mat;
        int a_n, *a_mida; //Tauler dinàmic
		int a_quantitat; //num de cartes tretes/que es restauraran a en cas de que laccio no es pugui realitzar. Columna a la que es restauraràn.
		Carta a_agafades[13]; //buffer per les cartes que estem moguent
	};

#endif // TAULER_H