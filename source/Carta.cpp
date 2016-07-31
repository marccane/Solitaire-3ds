#include "Carta.h"
#include "Constants.h"

Carta::Carta(){
    a_oberta=false;
}

void Carta::CrearVectorValors(char vecvalors[]){//aixo es podrà borrar
    const int temp[]={0,9,10,11,12};
    const char temp2[]={'A','D','J','Q','K'};
    for(char i='2';i<='9';i++)vecvalors[i-'1']=i;
    for(int i=0;i<5;i++)vecvalors[temp[i]]=temp2[i];
}

void Carta::Modificar(char valor, char pal, sf2d_texture *t, sf2d_texture *t2){
    a_valor=valor;
    a_pal=pal;
	a_tex=t;
	a_tex_dar=t2;
}

void Carta::Intercanviar(Carta &b){
    Carta temp=b;
    b=*this;
    *this=temp;
}

bool Carta::esnegra()const{
    return a_pal=='P' or a_pal=='T';
}

bool Carta::esoberta()const{
    return a_oberta;
}

void Carta::Set_obrir(bool obrir){
    a_oberta=obrir;
}

void Carta::mostrar(int posx, int posy)const{
	if(a_oberta)sf2d_draw_texture(a_tex,posx,posy);
	else sf2d_draw_texture(a_tex_dar,posx,posy);
}

bool Carta::Casen(Carta a, bool espila)const{//!aquesta funció s'ha doptimitzar
    char vecvalors[13];
    CrearVectorValors(vecvalors);
    bool cas=false;
    int index=0, index2=0; //petita =2 , grossa =1
    if(a.esnegra()!=esnegra() or espila){
        for(int i=0;i<=12;i++){
            if(a_valor==vecvalors[i])index=i;
            if(a.a_valor==vecvalors[i])index2=i;
        }
        if(index-1==index2)cas=true;
    }
    return cas;
}

bool Carta::EsRei()const{
    return a_valor=='K';
}

bool Carta::EsA()const{
    return a_valor=='A';
}

char Carta::Get_Pal()const{
    return a_pal;
}