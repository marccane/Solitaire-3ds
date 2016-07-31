#include <iostream>
#include <string.h>
#include <sstream>
#include <stdlib.h> //rng
#include <time.h> //rng
#include <3ds.h>
#include <sf2d.h>
#include <sfil.h>
#include "Baralla.h"
#include "Joc.h"
#include "Constants.h"

using namespace std;

void Carregar_Cartes(sf2d_texture *c[]);

int main()
{	
	aptInit();
	srvInit();
	hidInit();
	ndspInit();	
	sf2d_init();
	sf2d_set_clear_color(RGBA8(0x40, 0xFF, 0x40, 0xFF));
	sf2d_set_3D(false);
	srand(time(NULL));
	consoleInit(GFX_TOP, NULL);
	
	sf2d_texture* cartes[53]; //+1 pel darrera de la carta
	Carregar_Cartes(cartes);
	bool touchframeanterior=false, acciofeta=false;
	Joc joc(rand()%12345,cartes);
	Posicio_Carta origen, desti;
	touchPosition touch;
	u32 held, down;
			
	while (aptMainLoop()) {
		hidScanInput();
		held = hidKeysHeld();
		down = hidKeysDown();
		if(!held)svcSleepThread(100000000);
		if(held & KEY_START) break;
		if(down & KEY_B) joc=Joc(rand()%12345,cartes);
		if(!joc.a_guanyada){
			if (held & KEY_TOUCH){
				hidTouchRead(&touch);
				if(!touchframeanterior){
					origen=joc.Localitzar_Carta(touch);
					joc.Processar_origen(origen); //return bool per saber si hem agafat una carta correcte?
				}
			}
			else if(touchframeanterior){
				desti=joc.Localitzar_Carta(touch);
				joc.Accio(origen,desti,acciofeta);
				joc.Netejar_Buffer();			
			}
			touchframeanterior=held & KEY_TOUCH;

			sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
				joc.mostrar(touch); 
			sf2d_end_frame();
			sf2d_swapbuffers();
		}
		else{
			cout<<"HAS GUANYAT ENJORAGUENA"<<endl;
			svcSleepThread(10000000000);
			break;
		}
	}
	for(int i=0;i<53;i++)sf2d_free_texture(cartes[i]);
	sf2d_fini();
	ndspExit();
	hidExit();
	srvExit();
	aptExit();
	return 0;
}

void Carregar_Cartes(sf2d_texture *c[]){
	string ruta="gamedata/", extensio=".png", nom;
	for(int i=0;i<53;i++){
		stringstream ss;
		ss<<i+1;
		nom=ruta+ss.str()+extensio;
		cout<<"Carregant: "<<ss.str()+extensio<<endl;
		c[i]=sfil_load_PNG_file(nom.c_str(), SF2D_PLACE_RAM);
	}
}