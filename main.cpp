#include "miniwin.h"
#include <iostream>
#include <sstream>
using namespace std;
using namespace miniwin;
//tamaño de los cuadros
const int px=10;
//tamaño de la matris y mapa
const int f_=50;
const int c_=50;

//taaño de la ventana
const int f=px * f_;
const int c=px * c_;

//variable de la tecla
int T=tecla();

//variable muro
int Muro=AZUL;

//variable de fin
int fin=ROJO;

//booleanos para ver donde se estubo
    bool ar=false;
    bool der=false;
    bool aba=false;
    bool izq=false;

//matris
typedef int Tablero[f_][c_];
struct Cord{
    int x;
    int y;
};
struct Pieza{
    Cord orig;
    bool ar=false;
    bool der=false;
    bool aba=false;
    bool izq=false;
    int col_m=BLANCO;
    int col_o=VERDE;
};
/*inicio de funciones*/

//funcion que pinta los cuadros
void pinta_pieza(int y, int x){
    rectangulo_lleno( 1 + x   * px,
                      1 + y   * px,
                      x * px + px,
                      y * px + px );
}


//rellena el tablero con el color blanco para indicar que no es muro
void llenar_tablero( Pieza& P ,Tablero& Ta){
    for ( int i=0; i < f_; i++ ){
        for ( int j=0; j < c_; j++ ){
            Ta[i][j]=P.col_m;
        }
    }
    for ( int i=0; i < f_ ; i++ ){
        Ta[i][0]=Muro;
    }
    for ( int i=0; i < c_ ; i++ ){
        Ta[0][i]=Muro;
    }
    for ( int i=0; i < f_ ; i++ ){
        Ta[i][c_-1]=Muro;
    }
    for ( int i=0; i < c_ ; i++ ){
        Ta[f_-1][i]=Muro;

    }
}
void muestra_tablero( Tablero& Ta){
for ( int i=0; i < f_; i++ ){
        for ( int j=0; j < c_; j++ ){
            color(Ta[i][j]);
            pinta_pieza(i, j);
        }
    }
}

//ver las piesas alrededor de la central
void mapea( Pieza& P, Tablero& Ta  ){
    Cord auz;
    int col;
    //arriba
    auz.x = P.orig.x;
    auz.y = P.orig.y;
    auz.x = auz.x -1;
    col=Ta[auz.x][auz.y];
    if ( col == Muro ){
        P.ar=false;
    }else {
        P.ar=true;
    }
    if ( col == P.col_o ){
        ar=false;
    }else {
        ar=true;
    }

    //derecha
    auz.x = P.orig.x;
    auz.y = P.orig.y;
    auz.y = auz.y+1;
    col=Ta[auz.x][auz.y];
    if ( col == Muro ){
        P.der=false;
    }else {
        P.der=true;
    }
    if ( col == P.col_o ){
        der=false;
    }else {
        der=true;
    }

    //abajo
    auz.x = P.orig.x;
    auz.y = P.orig.y;
    auz.x = auz.x+1;
    col=Ta[auz.x][auz.y];
    if ( col == Muro ){
        P.aba=false;
    }else {
        P.aba=true;
    }
    if ( col == P.col_o ){
        aba=false;
    }else {
        aba=true;
    }

    //abajo
    auz.x = P.orig.x;
    auz.y = P.orig.y;
    auz.y = P.orig.y-1;
    col=Ta[auz.x][auz.y];
    if ( col == Muro ){
        P.izq=false;
    }else {
        P.izq=true;
    }
    if ( col == P.col_o ){
        izq=false;
    }else {
        izq=true;
    }



}

void colocar_pieza( Pieza& P, Tablero& Ta){
    Ta[P.orig.x][P.orig.y]=P.col_o;
}
string salida(int x, int y){
    stringstream sal;
    sal <<"x: "<<x<<" y: "<<y<<endl;
    return sal.str();

}
void coloca_muros(int x, int y, Tablero& Ta){
    Ta[x][y]=Muro;
}

void Ac(Tablero& Ta, Pieza& P){
        Ta[10][1]=Muro;
        Ta[10][2]=Muro;
        Ta[46][10]=Muro;
        Ta[45][10]=Muro;
        Ta[44][10]=Muro;
        Ta[43][10]=Muro;
        Ta[42][10]=Muro;
        Ta[41][10]=Muro;

        Ta[46][12]=Muro;
        Ta[45][12]=Muro;
        Ta[44][12]=Muro;
        Ta[43][12]=Muro;
        Ta[42][12]=Muro;
        Ta[41][12]=Muro;
        colocar_pieza(P, Ta);
        muestra_tablero( Ta );
        color(BLANCO);
        texto( 10, f + 40, salida(P.orig.x, P.orig.y));
        refresca();
        espera(1);

}
void orden_1(Pieza& P, Tablero& Ta ){
    mapea(P, Ta);
         if ( /*T == int('A') &&*/ P.izq && izq ){//izquierda
            P.orig.y--;
            Ac(Ta, P);
        }else if ( /*T == int('S') && */P.aba && aba ){ //abajo
            P.orig.x++;
            Ac(Ta, P);

        }else if ( /*T == int('D') &&*/ P.der && der ){//derecha
            P.orig.y++;
            Ac(Ta, P);
        }else if ( /*T == int('W') && */ P.ar && ar){//arriba
            P.orig.x--;
            Ac(Ta, P);
        }
}
void orden_2(Pieza& P, Tablero& Ta ){
    mapea(P, Ta);
        if ( /*T == int('S') && */P.aba && aba ){ //abajo
            P.orig.x++;
            Ac(Ta, P);

        }else if ( /*T == int('A') &&*/ P.izq && izq ){//izquierda
            P.orig.y--;
            Ac(Ta, P);
        }else if ( /*T == int('D') &&*/ P.der && der ){//derecha
            P.orig.y++;
            Ac(Ta, P);
        }else if ( /*T == int('W') && */ P.ar && ar){//arriba
            P.orig.x--;
            Ac(Ta, P);
        }
}
int main() {
    vredimensiona( f+80, c);
    //inicializacion de las variables
    Pieza P;
    Tablero Ta;
    P.orig.x=1;
    P.orig.y=1;
    borra();
    llenar_tablero( P, Ta);

    //usando funciones
    while ( T != ESCAPE ){
        borra();
        T=tecla();
        orden_1(P, Ta);
        orden_2(P, Ta);


        }//final de la funcion main
    vcierra();
        return 0;
    }
