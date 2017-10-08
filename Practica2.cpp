#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
using namespace std;

//Definiciones
typedef enum{Salir, Sencillo, Dificil, Ranking, TopPlayers}tModo;
typedef enum{ Azul, Dorado, Rojo, Verde, Blanco, Marron, Naranja }tColores;
const int COLORES_SENCILLO = 12;
const int COLORES_DIFICIL = 5;
typedef tColores tSecuencia[COLORES_DIFICIL];
const int MAX_JUGADORES = 10;
typedef struct{
	string nombre;
	float puntuacion;
}tJugador;
typedef tJugador tPuntuacion[MAX_JUGADORES]; // array de structs.

//Funciones y Procedimientos
tColores charToColor(char color);
tColores intToColor(int numero);
void generarsecuenciainicial(tSecuencia secuenciaColores, tModo modo);
void prolongarsecuenciainicial(tSecuencia secuenciaColores, tModo modo, int longitud);
bool comprobarColor(const tSecuencia secuenciaColores, int indice, tColores color);
void mostrarSecuencia(const tSecuencia secuenciaColores, int numero);
float comenzarJuego(string nombre, tModo modo);
tModo menu();
bool utilizarAyuda(const tSecuencia secuenciaColores, int indice, int &numAyudas); 
void Puntuaciones(float &puntuacion, float puntos, tModo modo);
void cargarRanking(tPuntuacion ranking);
void visualizarRanking(tPuntuacion ranking);
void visualizarBestPlayer(tPuntuacion ranking);
void escribirRanking(tPuntuacion ranking);
void actualizarRanking(tPuntuacion ranking, float puntuacion, string nombre);

int main(){

	srand(time(NULL));
	tPuntuacion arrayJugador;
	cargarRanking(arrayJugador);
	cout << "Bienvenido a Simon Dice!" << endl;
	cout << "Como te llamas? ";
	string nombre;
	tModo modo;
	tPuntuacion ranking;
	float puntos;
	cin >> nombre;
	system("cls");
	cout << "Hola " << nombre << " ";
	modo = menu();
	while (modo != Salir){
				
		switch (modo){
		case Sencillo: puntos = comenzarJuego(nombre,modo); 
				       actualizarRanking(arrayJugador,puntos,nombre);
					   break;
		case Dificil:  puntos = comenzarJuego(nombre, modo); 
					   actualizarRanking(arrayJugador,puntos,nombre);
					   break;
		case Ranking:  visualizarRanking(arrayJugador); break;
		case TopPlayers: visualizarBestPlayer(arrayJugador); break;
		}
		cout << "Hola " << nombre << " ";
		modo = menu();

	}
	escribirRanking(arrayJugador);
	
	return 0;
}

tColores intToColor(int numero){

	if (numero == 0){
		return Azul;
	}
	else if (numero == 1){
		return Dorado;
	}
	else if (numero == 2){
		return Rojo;
	}
	else if (numero == 3){
		return Verde;
	}
	else if (numero == 4){
		return Blanco;
	}
	else if (numero == 5){
		return Marron;
	}
	else if (numero == 6){
		return Naranja;
	}
};

tColores charToColor(char color){

	if (color == 'a' || color == 'A'){
		return Azul;
	}
	else if (color == 'd' || color == 'D'){
		return Dorado;
	}
	else if (color == 'r' || color == 'R'){
		return Rojo;
	}
	else if (color == 'v' || color == 'V'){
		return Verde;
	}
	else if (color == 'b' || color == 'B'){
		return Blanco;
	}
	else if (color == 'n' || color == 'N'){
		return Naranja;
	}
	else if (color == 'm' || color == 'M'){
		return Marron;
	}
};

void generarsecuenciainicial(tSecuencia secuenciaColores, tModo modo){
	
	if (modo == Sencillo){
		for (int i = 0; i < 3; i++){
			int numero = rand() % 4;
			secuenciaColores[i] = intToColor(numero);
		}
	}
	else if (modo == Dificil){
		for (int i = 0; i < 4; i++){
			int numero = rand() % 7;
			secuenciaColores[i] = intToColor(numero);
		}
	}
};

void prolongarsecuenciainicial(tSecuencia secuenciaColores, tModo modo, int longitud){

	if (modo==Sencillo){
		int numero = rand() % 4;
		secuenciaColores[longitud - 1] = intToColor(numero);
	}
	else if (modo == Dificil){
		int numero = rand() % 7;
		secuenciaColores[longitud - 1] = intToColor(numero);
	}
};

bool comprobarColor(const tSecuencia secuenciaColores, int indice, tColores color){

	return color == secuenciaColores[indice];
};

void mostrarSecuencia(const tSecuencia secuenciaColores, int numero){

	cout << "La secuencia es: ";
	for (int i = 0; i < numero; i++){
		
		if (secuenciaColores[i] == Azul) cout << "Azul-";
		else if (secuenciaColores[i] == Dorado) cout << "Dorado-";
		else if (secuenciaColores[i] == Rojo) cout << "Rojo-";
		else if (secuenciaColores[i] == Verde) cout << "Verde-";
		else if (secuenciaColores[i] == Blanco) cout << "Blanco-";
		else if (secuenciaColores[i] == Marron) cout << "Marron-";
		else if (secuenciaColores[i] == Naranja) cout << "Naranja-";
		
	}	
};

float comenzarJuego(string nombre, tModo modo){
	
	int tamaño;
	int MAX_COLORES;
	float puntuacion = 0;

	if (modo == Sencillo){ //VARIABLES SENCILLO
		tamaño = 3;
		MAX_COLORES = COLORES_SENCILLO;
		cout << endl << "Bienvenido al modo sencillo!" << endl;
	}
	else if (modo == Dificil){ //VARIABLES DIFICIL
		tamaño = 4;
		MAX_COLORES = COLORES_DIFICIL;
		cout << endl << "Bienvenido al modo dificil!" << endl;
	}

		tSecuencia array;
		bool salir = false;
		generarsecuenciainicial(array, modo);
		int numAyudas = 3;

		do{ //BUCLE PARTIDAS 
			mostrarSecuencia(array, tamaño);
			cout << endl << endl << nombre << " cuando este listo ";
			system("pause");
			system("cls");

			cout << nombre << ", introduce la sequencia de " << tamaño << " colores: ";
			char c;

			cin >> c;
			int i = 0;
			while (c == 'x'){ //AYUDA PRIMER VALOR
				utilizarAyuda(array, i, numAyudas);
				Puntuaciones(puntuacion, -7, modo);
				cout << "Introduce el siguiente color: ";
				cin >> c;
			}

			while (i < tamaño - 1 && comprobarColor(array, i, charToColor(c))){ //COMPARACION COLORES
				Puntuaciones(puntuacion, 5, modo);
				cin >> c;
				while(c == 'x' && utilizarAyuda){ //AYUDA DEMAS VALORES
					utilizarAyuda(array, i+1, numAyudas);
					Puntuaciones(puntuacion, -7, modo);
					cout << "Introduce el siguiente color: ";
					cin >> c;
				}
				i++;

			}
			if (comprobarColor(array, i, charToColor(c))){ 
				cout << "correcto" << endl << endl;
				if (tamaño < MAX_COLORES){
					tamaño = tamaño + 1;
					prolongarsecuenciainicial(array, modo, tamaño);
				}
				else{
					salir = true;
					cout << "Has finalizado el Juego! ENHORABUENA!" << endl;
					system("pause");
				}

				Puntuaciones(puntuacion, 15, modo);
			}
			else{
				cout << "Te has equivocado" << endl;
				salir = true;
				system("pause");
			}
		} while (tamaño <= MAX_COLORES && !salir);
	
		if (puntuacion < 0) puntuacion = 0;

	return puntuacion;
}

bool utilizarAyuda(const tSecuencia secuenciaColores, int indice, int &numAyudas){
	
	if (numAyudas > 0){
		     if (secuenciaColores[indice] == Azul) cout << "El siguiente color es Azul";
		else if (secuenciaColores[indice] == Dorado) cout << "El siguiente color es Dorado";
		else if (secuenciaColores[indice] == Rojo) cout << "El siguiente color es Rojo";
		else if (secuenciaColores[indice] == Verde) cout << "El siguiente color es Verde";
		else if (secuenciaColores[indice] == Blanco) cout << "El siguiente color es Blanco";
		else if (secuenciaColores[indice] == Marron) cout << "El siguiente color es Marron";
		else if (secuenciaColores[indice] == Naranja) cout << "El siguiente color es Naranja";
		numAyudas--;
		cout << " te quedan " << numAyudas << " ayudas." << endl;	
	}
	else cout << "No te quedan ayudas disponibles." << endl;

	return numAyudas > 0;
}

tModo menu(){
	
	cout << "a que modo te gustaria jugar: " << endl << endl;
	cout << "0. Salir." << endl;
	cout << "1. Sencillo." << endl;
	cout << "2. Dificil." << endl;
	cout << "3. Ver 10 mejores jugadores." << endl;
	cout << "4. Ver jugador(es) con la puntuacion mas alta." << endl;
	cout << "Opcion: ";
	tModo modo;
	char menu;
	cin >> menu;
	while (menu != '2' && menu != '1' && menu != '0' && menu != '3' && menu != '4' ){

		cout << "Error, opcion no valida, prueba de nuevo: ";
		cin >> menu;
	}
	if (menu == '1') modo = Sencillo;
	else if (menu == '2') modo = Dificil;
	else if (menu == '3') modo = Ranking;
	else if (menu == '4') modo = TopPlayers;
	else modo = Salir;

	return modo;
}

void Puntuaciones(float &puntuacion,float puntos, tModo modo){

	if (modo == Sencillo)
		puntuacion = puntuacion + puntos;
	else if (modo == Dificil)
		puntuacion = puntuacion + (puntos * 1.5);
}

void cargarRanking(tPuntuacion ranking){

	ifstream archivo;
	archivo.open("top.txt");

	if (archivo.is_open()){
		int i = 0;
		bool seguir = true;
		while (seguir && i < MAX_JUGADORES ){
			archivo >> ranking[i].puntuacion;
			archivo >> ranking[i].nombre;
			if (ranking[i].puntuacion == -1) seguir = false;
			else i++;
		}
		archivo.close();
	}
	else cout << " No se encontro el archo top.txt " << endl;
}

void visualizarRanking(tPuntuacion ranking){

	system("cls");
	int i = 0;
	bool seguir = true;
	while (i < MAX_JUGADORES && seguir){
		cout << i+1 << ". " << ranking[i].nombre << " " << ranking[i].puntuacion << endl;
		i++;
		if (ranking[i].puntuacion == -1) seguir = false;
	}
	cout << endl;
	system("pause");
	system("cls");
}

void visualizarBestPlayer(tPuntuacion ranking){
	
	system("cls");
	int i = 0; 
	cout << i + 1 << ". " << ranking[i].nombre << " " << ranking[i].puntuacion << endl;
	while (ranking[i].puntuacion == ranking[i + 1].puntuacion){
		i++;
		cout << i + 1 << ". " << ranking[i].nombre << " " << ranking[i].puntuacion << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
}

void escribirRanking(tPuntuacion ranking){

	ofstream archivo;
	archivo.open("top.txt");

	if (archivo.is_open()){
		int i = 0;
		bool seguir = true;
		while (seguir && i < MAX_JUGADORES){
			archivo << ranking[i].puntuacion;
			archivo << " ";
			archivo << ranking[i].nombre << endl;
			if (ranking[i].puntuacion == -1) seguir = false;
			else i++;
		}
		if (seguir) archivo << -1;
	}
		archivo.close();
	




}

void actualizarRanking(tPuntuacion ranking, float puntuacion, string nombre){

	int pos = 0;
	while (pos < MAX_JUGADORES && puntuacion <= ranking[pos].puntuacion ){
		pos++;
	}
	int i;
	for (i = MAX_JUGADORES-1; i > pos ; i--){
		ranking[i].puntuacion = ranking[i-1].puntuacion;
		ranking[i].nombre = ranking[i-1].nombre;
	}
	ranking[pos].puntuacion = puntuacion;
	ranking[pos].nombre = nombre;

}
