//#include <stdio.h>
//#include <math.h> //sin
#include <string.h>
#include <iostream>
#include <stdlib.h> //rng
#include <time.h> //rng
#include <sstream>
#include <3ds.h>
#include <sf2d.h>
#include <sfil.h>
#include "Baralla.h"
#include "Joc.h"
#include "Constants.h"

using namespace std;

Joc inicialitzar_joc(sf2d_texture *c[]);
void Carregar_Cartes(sf2d_texture *c[]);
Posicio_Carta Localitzar_Carta(touchPosition t, Joc &joc);

int main()
{	
	aptInit();
	srvInit();
	hidInit();
	ndspInit();	
	sf2d_init();
	sf2d_set_clear_color(RGBA8(0x40, 0xFF, 0x40, 0xFF));
	sf2d_set_3D(false);
	consoleInit(GFX_TOP, NULL);
	sf2d_texture* cartes[53]; //+1 pel darrera de la carta
	Carregar_Cartes(cartes);
	bool touchframeanterior=false, acciofeta=false;
	
	Joc joc=inicialitzar_joc(cartes);
	Posicio_Carta origen, desti;
	touchPosition touch;
	u32 held;
			
	while (aptMainLoop()) {
		hidScanInput();
		held = hidKeysHeld();
		if(!held)svcSleepThread(100000000);
		if(held & KEY_START) break;
		if(!joc.a_guanyada){
			if (held & KEY_TOUCH){
				hidTouchRead(&touch);
				if(!touchframeanterior){
					origen=Localitzar_Carta(touch,joc);
					joc.Processar_origen(origen); //return bool per saber si hem agafat una carta correcte?
				}
			}
			else if(touchframeanterior){
				desti=Localitzar_Carta(touch,joc);
				joc.Accio(origen,desti,acciofeta);
				joc.Netejar_Buffer();			
			}
			touchframeanterior=held & KEY_TOUCH;

			sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
				joc.mostrar(touch); 
			sf2d_end_frame();
			sf2d_swapbuffers();
		}
	}
	for(int i=0;i<53;i++)sf2d_free_texture(cartes[i]);
	sf2d_fini();
	return 0;
}

Joc inicialitzar_joc(sf2d_texture *c[]){
	int llavor=rand()%123456, passos=rand()%1000+20;
    Baralla baralla(llavor, passos, c);
    Joc joc(baralla);
	return joc;
}

void Carregar_Cartes(sf2d_texture *c[]){
	string davant="data/", darrera=".png", nom;
	for(int i=0;i<53;i++){
		stringstream ss;
		ss<<i+1;
		nom=davant+ss.str()+darrera;
		cout<<"Carregant: "<<ss.str()+darrera<<" ...";
		c[i]=sfil_load_PNG_file(nom.c_str(), SF2D_PLACE_RAM);
		cout<<"OK"<<endl;
	}
}

Posicio_Carta Localitzar_Carta(touchPosition t, Joc &joc){
	Posicio_Carta resultat;
	if(t.py<(margeA+Card_Height+margeB)){
		resultat.alapila=true;
		if(t.px<margeD+Card_Width*2+margeE*2)
			resultat.pila=t.px/(margeD+Card_Width+(margeE/2));
		else{
			const int tpx=320-t.px-(margeD-margeE/2), temp=5-tpx/(margeE+Card_Width);
			resultat.pila=(temp<2?2:temp);
		}
	}
	else{
		resultat.alapila=false;
		int migmarge=margeD/2, tpx=t.px-migmarge, unitat=margeD+Card_Width;
		resultat.columna=(tpx/unitat)+1; //seguim la convencio de la notació de columnes de lusuari i no pas la de les dades
		int tpy=t.py-margeA-Card_Height-margeB, numtancades, numobertes;
		joc.NumCartesColumna(resultat.columna, numobertes, numtancades);
		resultat.fila=(tpy/MPL)+1;
		if(resultat.fila>numtancades){
			const int total=numobertes+numtancades;
			tpy-=MPL*numtancades;
			resultat.fila=(tpy/MOS)+1;
			resultat.fila+=numtancades;
			if(resultat.fila>total)
				resultat.fila=total;
		}
	}
	if(resultat.alapila)cout<<"pila="<<resultat.pila<<endl;
	else cout<<"col="<<resultat.columna<<" fila="<<resultat.fila<<endl;
	return resultat;
}