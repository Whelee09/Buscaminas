#include <iostream>
#include <time.h>
#include <cstdlib>

using namespace std;
void llenarAleatorio();
int aleatorio();
void mostrarMatriz();
void mostrarTablero();
int calcularCercanos(int i,int j);//funcion para saber cuantas minas hay cerca
void jugar(int cantMinasTotales);
void verificarGanar(int cantMinasTotales);
void mostrarTableroJuegoPerdido();
int cantMinas();

bool juegoPerdido=false;
bool juegoGanado=false;
int n; // tamano del tablero 3,9 o 12
int M[12][12];//variable global matriz con la solucion del juego, 
//el valor uno significa que hay mina, cero que no la hay
int MC[12][12];//variable global matriz que indica si la posición ya fue jugada 0
// es no jugada 1 es jugada 

int main(int argc, char** argv) {
	int opcion,opcion2;
	cout<<"\t*********Ingrese una opcion*********"<<endl;
	cout<<"\t\t 0-salir\n";
	cout<<"\t\t 1-Juego 3x3\n";
	cout<<"\t\t 2-Juego 9x9\n";
	cout<<"\t\t 3-Juego 12x12\n";
	cin>>opcion;
	llenarAleatorio();
	switch(opcion){
		case 1:n=3;break;
	    case 2:n=9;break;
		case 3:n=12;break;
	}

	mostrarMatriz();//muestra la solucion
	mostrarTablero();
	int cantMinasTotales = cantMinas();
	do{
		if(juegoPerdido==false&&juegoGanado==false&&opcion!=0){
	 		cout<<"\t*********Ingrese una opcion*********"<<endl;
	 		cout<<"\t\t 1-Jugar\n";
     		cout<<"\t\t 2-Terminar partida\n";
	 		cin>>opcion2;
	 		switch(opcion2){
				case 1: 
					jugar(cantMinasTotales);

				break;
				
				case 2: //bloque opcion 2
				cout<<"Fin del juego"<<endl;
				break;
				
				default://bloque por defecto 
				cout<<"Ingrese una opcion válida..."<<endl;
			}
			
		}else{
		    opcion2=2;//finaliza el bluce de juego
		    if(juegoPerdido==true){ cout<<"\n*******Perdiste la partida*******"<<endl;}
		    if(juegoGanado==true){ cout<<"\n*******Ganaste la partida*******"<<endl;}
		}
	}while(opcion2!=2);
	
	cout<<"\n\t*********Fin del programa*********"<<endl;
	return 0;
}

 void jugar(int cantMinasTotales){
    //int temp = cantMinasTotales;
     int fila;
     int columna;
     cout<<"Ingrese el número de la fila"<<endl;
     cin>>fila;
     cout<<"Ingrese el número de la columna"<<endl;
     cin>>columna;
     if(M[fila-1][columna-1]==1){
         //perder juego cayó en una mina
         juegoPerdido=true;
         mostrarTableroJuegoPerdido();
     }else{
        //destapar posicion
        MC[fila-1][columna-1]=1;  
        verificarGanar(cantMinasTotales);
        mostrarTablero();
     }
}

int cantMinas(){
    int totalMinas=0;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
           if(M[i][j]==1){
            totalMinas++;
            //cout<<"MINA"<<endl;
           }
        }
    }
    return totalMinas;
}

void mostrarTableroJuegoPerdido(){
	char mina = 157; 
	char noMina = 240;

    cout<<"Esto es una mina: "<<mina<<endl;
    cout<<"Esto NO es una mina: "<<noMina<<endl;

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
           if(M[i][j]==0){
               cout<<"   "<<noMina;
           }else{
               cout<<"   "<<mina;
           }
        }
        cout<<endl;
    }
    
}

void mostrarTablero(){
	char mar =254;
     for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
           if(MC[i][j]==0){
               cout<<"   "<<mar;
           }else{
                cout<<"   "<<calcularCercanos(i,j);
           }
        }
        cout<<endl;
    }
}
void mostrarMatriz(){
     for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
           cout<<"\t"<<M[i][j];
        }
        cout<<"   "<<endl<<endl;
    }
}

int calcularCercanos(int i,int j){
	int minas=0;
    if(M[i][j+1]==1 && (j+1)<n){
    	minas++;
        //cout<<"MIna en "<<i<<" "<<j+1<<endl;
        //cout<<"caso 1"<<endl;
	}
	if(M[i][j-1]==1 && (j-1)>=0){
    	minas++;
        //cout<<"MIna en "<<i<<" "<<j-1<<endl;
        //cout<<"caso 2"<<endl;
	}
	if(M[i+1][j]==1 && (i+1)<n){
    	minas++;//cout<<"MIna en "<<i+1<<" "<<j<<endl;
        //cout<<"caso 3"<<endl;
	}
	if(M[i-1][j]==1 && (i-1)>=0){
    	minas++;//cout<<"MIna en "<<i-1<<" "<<j<<endl;
        //cout<<"caso 4"<<endl;
	}
	
//diagonales
	if(M[i-1][j+1]==1 && (i-1)>=0 && (j+1)<n){
    	minas++;//cout<<"MIna en "<<i-1<<" "<<j+1<<endl;
        //cout<<"caso 5"<<endl;
	}
	if(M[i-1][j-1]==1 && (i-1)>=0 && (j-1)>=0){
    	minas++;//cout<<"MIna en "<<i-1<<" "<<j-1<<endl;
        //cout<<"caso 6"<<endl;
	}
	if(M[i+1][j+1]==1 && (i+1)<n && (j+1)<n){
    	minas++;//cout<<"MIna en "<<i+1<<" "<<j<<endl;
        //cout<<"caso 7"<<endl;
	}
	if(M[i+1][j-1]==1 && (i+1)<n && (j-1)>=0){
    	minas++;//cout<<"MIna en "<<i+1<<" "<<j-1<<endl;
       // cout<<"caso 8"<<endl;
	}
    return minas;
}

void verificarGanar(int cantMinasTotales){
    juegoGanado=false;
    int casillasTotales = n*n;
    int posicionesDescubiertas=0;
    //tu codigo acá 
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if(MC[i][j]==1){
                posicionesDescubiertas++;
            }
        }
    }
    // cout<<"Verficando si ganamos"<<endl;
    // cout<<"casillas totales "<<casillasTotales<<endl;
    // cout<<"cantMinasTotales"<< cantMinasTotales<<endl;
    // cout<<"resta"<<casillasTotales-cantMinasTotales<<endl;
    // cout<<"posiciones descubiertas"<<posicionesDescubiertas<<endl;

    if(casillasTotales-cantMinasTotales == posicionesDescubiertas){
        cout << "Has ganado!" << endl;
        juegoGanado=true;
    }
    if(cantMinasTotales == 0){
        cout<<"Y las minitas bro?"<<endl;
        juegoGanado=true;
    }
    
}
void llenarAleatorio(){
    int num;
    srand(time(NULL));
    for(int i=0; i<12; i++){
        for(int j=0; j<12; j++){
            num=1 + rand() % (10);
            if(num<=3){
                M[i][j]=1;
            }else{
                M[i][j]=0;
            }
            MC[i][j]=0;//no tocada
        }
    }
}