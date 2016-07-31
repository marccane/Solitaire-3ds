#include "PilaCartes.h"

// Pre: --; Post: pila buida
// COST: O(1)
PilaCartes::PilaCartes(){
    a_cim= NULL;
}

// Pre: --; Post: aquesta pila és còpia de la pila o
// COST: O(n)
PilaCartes::PilaCartes(const PilaCartes& o){
    a_cim= NULL;
    copia(o); // crida a mètode privat
}

// Pre: --; Post: memòria alliberada
// COST: O(n)
PilaCartes::~PilaCartes(){
    allibera(); // crida a mètode privat
}

// CONSULTORS -------------------------------------------------
// Pre: --
// Post: retorna cert si la pila és buida; fals en c.c.
// COST: O(1)
bool PilaCartes::buida() const{
    return a_cim==NULL;
}

// Pre: pila no buida
// Post: retorna el valor del cim de la pila
// COST: O(1)
Carta PilaCartes::cim() const{
    //if(a_cim==NULL)cout<<"ERROR! LA PILA ES BUIDA!, posa els checks on toquen!"<<endl;
    if(!buida())return a_cim->valor;
	else { //per anar bé aixo no s'hauria dexecutar mai
		Carta temp;
		return temp; 
	}
}

// MODIFICADORS -----------------------------------------------
// Pre: --; Post: ha afegit s dalt de la pila
// COST: O(1)
// Pre: --; Post: ha afegit s a dalt de la pila
// COST: O(1)
void PilaCartes::empila(Carta s){
    Node* nou= new Node; // necessari reservar memoria
    nou->valor= s;
    nou->seg= a_cim;
    a_cim= nou;
}

// Pre: pila no buida
// Post: ha eliminat element de dalt de la pila
// COST: O(1)
void PilaCartes::desempila(){
    Node* aux= a_cim;
    a_cim= a_cim->seg;
    delete aux;
}

// OPERADORS ---------------------------------------------
// Pre: -- ; Post: aquesta pila es copia de o
// COST: O(n)
PilaCartes& PilaCartes::operator=(const PilaCartes& o){
    if (this != &o){
        allibera();
        copia(o);
    }
    return *this;
}

// METODES PRIVATS ------------------------------------------
// Pre: pila buida; Post: aquesta pila es copia de o
// COST: O(n)
void PilaCartes::copia(const PilaCartes& o) {
    if(!o.buida()){
        Node *p, *q, *aux;
        p = new Node; a_cim = p;
        aux = o.a_cim; p->valor = aux->valor; p->seg = NULL;
        q = p;
        while (aux->seg!=NULL) {
            aux = aux->seg;
            p = new Node; q->seg = p;
            p->valor = aux->valor; p->seg = NULL;
            q = p;
        }
    }
}

// Pre: --; Post: memòria alliberada
// COST: O(n)
void PilaCartes::allibera(){
    while (!buida()) {
        Node* aux= a_cim;
        a_cim= a_cim->seg;
        delete aux;
    }
}

void PilaCartes::Girar_Cartes(PilaCartes &b){
    while(!buida()){
        Carta temp=cim();
        temp.Set_obrir(false);
        b.empila(temp);
        desempila();
    }
}

bool PilaCartes::Pila_Completada()const{
    if(buida())return false;
    else return cim().EsRei();
}

void PilaCartes::Mostrar_Cim_Pila()const{
    if(!buida())cim().mostrar(a_x,a_y);
}