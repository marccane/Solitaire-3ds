#include "Tauler.h"
#include "Baralla.h"
#include <3ds.h>
#include "Constants.h"

Tauler::Tauler(){
	a_quantitat=0;
    a_n=7;
    a_mida=new int[a_n];
    a_mat=new Carta*[a_n];
    for(int i=0;i<a_n;i++){
        a_mat[i]=new Carta[13+i];
    }
}

Tauler::~Tauler(){
    for(int i=0;i<a_n;i++){
        delete []a_mat[i];
    }
    delete []a_mat;
    delete []a_mida;
}

void Tauler::repartir(Baralla bar){
    int comptador=51;
    for(int i=0;i<a_n;i++){
        for(int j=i;j<a_n;j++){
            a_mat[j][i]=bar.Get_Carta(comptador--);
            if(i==j){
                a_mat[i][j].Set_obrir(true);
                a_mida[i]=j+1;
            }
        }
    }
}

void Tauler::mostrar(const touchPosition &t)const{
	int px=margeD,py;
	for(int i=0;i<a_n;i++){
		//px=margeD*(i+1)+Card_Width*i;  
		py=margeA+Card_Height+margeB;
		for(int j=0;j<a_mida[i];j++){
			a_mat[i][j].mostrar(px,py);
			py+=(a_mat[i][j].esoberta()?MOS:MPL);
		}
		px+=margeD+Card_Width;
	}
	py=t.py;
	for(int i=0;i<a_quantitat;i++){
		a_agafades[i].mostrar(t.px-Card_Width/2,py-Card_Height/2);
		py+=MOS;
	}
}

void Tauler::Inserir_Carta_Tauler(Carta inserir, int col){
    a_mat[col-1][a_mida[col-1]]=inserir;//aqui no va un +1 pk -1++1=0
    a_mida[col-1]++;
}

Carta Tauler::Get_Carta_Tauler(int col, int fila)const{
    if(fila==-1)return a_mat[col-1][a_mida[col-1]-1];
    else return a_mat[col-1][fila-1];
}

int Tauler::Mida_Col(int col)const{
    return a_mida[col-1];
}

void Tauler::Treure_Carta(int col){
	a_mida[col-1]--;
}

void Tauler::Obrir_ultima(int col){
    if(!Get_Carta_Tauler(col).esoberta())
        a_mat[col-1][a_mida[col-1]-1].Set_obrir(true);
}

void Tauler::Restaurar_Cartes(){
	//a_mida[a_col_rest-1]+=a_quantitat;
}

void Tauler::NumCartesColumna(int col, int &obertes, int &tancades)const{
	obertes=tancades=0;
	for(int i=0;i<a_mida[col-1];i++){
		if(a_mat[col-1][i].esoberta())obertes++;
		else tancades++;
		/*bool temp=a_mat[col-1][i].esoberta();
		obertes+=temp;
		tancades+=!temp;*/
	}
}

void Tauler::Processar_origen(Posicio_Carta origen, Carta c){
	if(origen.alapila){
		if(c.esoberta()){
			a_agafades[0]=c;
			a_quantitat=1;
			//a_col_rest=-1;
			//a_pila_rest=origen.pila;
		}
	}
	else{
		int comptador=0;
		const int filbona=origen.fila-1, colbona=origen.columna-1;
		if(a_mat[colbona][filbona].esoberta()){
			for(int i=filbona;i<a_mida[colbona];i++)
				a_agafades[comptador++]=a_mat[colbona][i];
			//a_mida[colbona]-=comptador;
			a_quantitat=comptador;
			//a_col_rest=colbona+1;
		}		
	}
}

void Tauler::Netejar_Buffer(){
	a_quantitat=0;
}