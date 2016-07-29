#include "Joc.h"
#include "PilaCartes.h"
#include "Tauler.h"
#include "Carta.h"
#include <3ds.h>
#include "Constants.h"

Joc::Joc(Baralla a)
{
    a_guanyada=false;
	for(int i=0;i<4;i++){
		a_pals[i].a_x=320-margeD-Card_Width*(4-i)-margeE*((4-i)-1);
		a_pals[i].a_y=margeA;
	}
	a_ma.a_x=margeD;
	a_descartades.a_y=a_ma.a_y=margeA;
	a_descartades.a_x=margeD+Card_Width+margeE;
    a_tauler.repartir(a);
    emplenar_ma(a);
}

void Joc::mostrar(const touchPosition &t){
	for(int i=0;i<4;i++)
        a_pals[i].Mostrar_Cim_Pila();
    a_ma.Mostrar_Cim_Pila();
    a_descartades.Mostrar_Cim_Pila();
	a_tauler.mostrar(t);
}

void Joc::NumCartesColumna(int col, int &obertes, int &tancades){
	a_tauler.NumCartesColumna(col,obertes,tancades);
}

void Joc::Processar_origen(Posicio_Carta origen){ //array de referencies?? //referenccies a punters?
	static const PilaCartes *llista[]={&a_ma,&a_descartades,&a_pals[0],&a_pals[1],&a_pals[2],&a_pals[3]};
	Carta temp;
	if(origen.alapila and !llista[origen.pila]->buida()) //and llista[origen.pila]->cim().esoberta()
		temp=llista[origen.pila]->cim();
	a_tauler.Processar_origen(origen,temp);
}

void Joc::Netejar_Buffer(){
	a_tauler.Netejar_Buffer();
}

void Joc::emplenar_ma(Baralla bar){
    for(int i=0;i<=23;i++)
        a_ma.empila(bar.Get_Carta(i));
}

bool Joc::PosarAlTauler(Carta car, int col){
    bool HaSigutPossible=true;
    if(col<=7 and col>0)
        if(a_tauler.Get_Carta_Tauler(col).Casen(car) or (a_tauler.Mida_Col(col)==0 and car.EsRei()))
            a_tauler.Inserir_Carta_Tauler(car,col);
        else HaSigutPossible=false;
    else HaSigutPossible=false;
    return HaSigutPossible;
}

bool Joc::Partida_Guanyada(){
    bool guanyada=true;
    for(int i=0;i<4;i++)
        if(!(a_pals[i].Pila_Completada() and guanyada))guanyada=false;
    return guanyada;
}

bool Joc::PosarALaPila(Carta car){
    bool HaSigutPossible=false;
    const char pals[]={'P','c','d','T'};
    int index_pila=0xCACABACA;
    char temp=car.Get_Pal();
    for(int i=0;i<4;i++)if(temp==pals[i])index_pila=i;
    bool condicio1, condicio2=false;
    condicio1=a_pals[index_pila].buida() and car.EsA();
    if(!a_pals[index_pila].buida())condicio2=car.Casen(a_pals[index_pila].cim(),true);
    if(condicio1 or condicio2){
        a_pals[index_pila].empila(car);
        HaSigutPossible=true;
    }
    return HaSigutPossible;
}

int Joc::Triar_Opcio(Posicio_Carta origen, Posicio_Carta desti){//todo: referencies constants
	int opcio=0;
	if(origen.alapila){//aquet tros és optimitzable pero li deixo la feina al compilador/al futur
		if(origen.pila==0)opcio=1;
		else if(!desti.alapila and origen.pila==1)opcio=2;
		else if(desti.alapila and origen.pila==1 and desti.pila>1)opcio=3;
		else if(!desti.alapila)opcio=6;
	}
	else{
		if(!desti.alapila)opcio=4;
		else if(desti.pila>1)opcio=5;
	}
	return opcio;
}

void Joc::Accio(Posicio_Carta origen, Posicio_Carta desti, bool &acciofeta){
    int fila, col, col_d, pila, opcio=Triar_Opcio(origen,desti);
    Carta c_origen;
	switch(opcio){
		case 1:
			if(a_ma.buida() and !a_descartades.buida())
				a_descartades.Girar_Cartes(a_ma);
			else if(!a_ma.buida()){
				Carta temp=a_ma.cim();
				temp.Set_obrir(true);
				a_ma.desempila();
				a_descartades.empila(temp);
			}
			break;
		case 2:
			if(!a_descartades.buida()){
				col=desti.columna;
				if(PosarAlTauler(a_descartades.cim(),col))
					a_descartades.desempila();
				else acciofeta=false; //cout<<"LA CARTA NO ES POT POSAR A LA COLUMNA "<<col<<endl;
			}
			else acciofeta=false; //cout<<"NO HI HA CAP CARTA PER AGAFAR"<<endl;
			break;
		case 3:
			if(!a_descartades.buida())
				if(PosarALaPila(a_descartades.cim()))
					a_descartades.desempila();
				else acciofeta=false; //cout<<"NO ES POT APILAR LA CARTA"<<endl;
			else acciofeta=false; //cout<<"NO HI HA CAP CARTA PER AGAFAR"<<endl;
			break;
		case 4:
			col=origen.columna; fila=origen.fila; col_d=desti.columna;
			if(a_tauler.Get_Carta_Tauler(col,fila).esoberta()){
				c_origen=a_tauler.Get_Carta_Tauler(col,fila);
				if(a_tauler.Get_Carta_Tauler(col_d).Casen(c_origen) or (c_origen.EsRei() and a_tauler.Mida_Col(col_d)==0)){
					const int limit=a_tauler.Mida_Col(col);
					for(int i=fila;i<=limit;i++){
						a_tauler.Inserir_Carta_Tauler(a_tauler.Get_Carta_Tauler(col,i),col_d);
						a_tauler.Treure_Carta(col);
					}
					a_tauler.Obrir_ultima(col);
				}
				else acciofeta=false; //cout<<"LA CARTA NO ES POT POSAR A LA COLUMNA "<<col_d<<endl;
			}
			else acciofeta=false; //cout<<"LA CARTA NO ES POT MOURE"<<endl;
			break;
		case 5:
			col=origen.columna;
			if(a_tauler.Mida_Col(col)>0)
				if(PosarALaPila(a_tauler.Get_Carta_Tauler(col))){
					a_tauler.Treure_Carta(col);
					a_tauler.Obrir_ultima(col);
				}
				else acciofeta=false; //cout<<"LA CARTA NO ES POT APILAR"<<endl;
			else acciofeta=false; //cout<<"LA CARTA NO ES POT APILAR"<<endl;
			break;
		case 6:
			pila=origen.pila-2; col=desti.columna;
			if(!a_pals[pila].buida())
				if(a_tauler.Get_Carta_Tauler(col).Casen(a_pals[pila].cim())){
					a_tauler.Inserir_Carta_Tauler(a_pals[pila].cim(),col);
					a_pals[pila].desempila();
				}
				else acciofeta=false; //cout<<"LA CARTA NO ES POT POSAR A LA COLUMNA "<<col<<endl;
			else acciofeta=false; //cout<<"A LA PILA NO HI HA CAP CARTA PER RECUPERAR"<<endl;
			break;
		default:
			acciofeta=false;
			break;
	}
	a_guanyada=Partida_Guanyada();
}