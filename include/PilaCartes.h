#ifndef PILACartes_H
#define PILACartes_H
#include "Carta.h"

class PilaCartes {
    // Descripcio: una pila dÕCartess
    public:
        // CONSTRUCTORS I DESTRUCTOR ----------------------------------
        // Pre: --; Post: pila buida
        PilaCartes();
        // Pre: --; Post: aquesta pila es copia de la pila o
        PilaCartes(const PilaCartes& o);  // const. de copia
        // Pre: --; Post: memoria alliberada
        ~PilaCartes();

        // CONSULTORS -------------------------------------------------
        // Pre: -- ; Post: retorna cert si la pila es buida; fals en c.c.
        bool buida() const;
        // Pre: pila no buida; Post: retorna el valor del cim de la pila
        Carta cim() const;
		void Mostrar_Cim_Pila() const;

        // MODIFICADORS -----------------------------------------------
        // Pre: --; Post: ha afegit s a dalt de la pila
        void empila(Carta s);
        // Pre: pila no buida; Post: ha eliminat element de dalt de la pila
        void desempila();
        // Pre: -- ; Post: Les cartes de la pila girades
        void Girar_Cartes(PilaCartes &b);
        // Pre: -- ; Post: Retorna cert si la pila té el rei al cim
        bool Pila_Completada()const;
        // OPERADORS REDEFINITS ---------------------------------------
        // Pre: -- ; Post: aquesta pila es copia de la pila o
        PilaCartes& operator=(const PilaCartes& o);
		
		int a_x, a_y;		
    private:
        struct Node {
            Carta valor;
            Node* seg;
        };
        // ATRIBUTS
        Node* a_cim; // punter al cim de la pila

        // METODES PRIVATS
        // Pre: pila buida; Post: aquesta pila es copia de o
        void copia(const PilaCartes& o);
        // Pre: --; Post: memoria alliberada
        void allibera();
};

#endif // PILACartes_H