/* Sistema de gestión de citas: una aplicación que permita a los pequeños negocios 
programar citas y recordatorios de citas para sus clientes, y enviar correos electrónicos 
o mensajes de texto para recordatorios. EQUIPO 7 */

/*Clase 'Data'. Sirve para captura de datos textuales y numéricos.*/
/*-----------------------------------------------------------------------------------*/

#include "iostream"
using namespace std;

#include "string.h"
#include "vector"

/*Aunque no estén definidos en los prototipos, los 'op' son parámetros opcionales. Al parecer cuando 
estas trabajando con prototipos de funciones, y no solo con las funciones per se, en el prototipo 
no puedes asignar valores default, sino que eso lo haces hasta la derivación*/

class Data{
    public:
        /*Metodos*/
        bool validarNumero(string string);
        double capNum(string op);
        string capTxt(string op);
        int ComprobacionMenus(string frase, int limite_superior, int limite_inferior, int error);
        int capturarMes(string);
        int capturarDia(string, int mes);
        int capturarHora(string);
        int capturarMinutos(string);
        string getMesPalabra(int);
};

/*Método para validar que todos los caracteres de una string sean números*/
bool Data::validarNumero(string string){
    //Si no hay nada, se regresa falso 
    if(string.size() == 0){
        return false;
    }
    else{
        //Si todo lo que hay son numeros se regresa verdadero, si no se regresa falso
        for(int i = 0; i < string.length(); i++){
            if(isdigit(string[i])){
                continue;
            }
            else{
                return false;
            }
        }
        return true;
    }
}

/*Método para ingresar números con un prompt opcional (op) para que el usuario sepa qué se le pide ingresar*/
double Data::capNum(string op = ""){
    string stringCapturada;
    bool status;
    //Se pide un numero hasta que se de correctamente
    do{
        cout << op;
        cin >> ws;
        getline(cin, stringCapturada);
        status = validarNumero(stringCapturada); //Usamos la funcion validarNumero para validar que solo sean numeros
        if(status == false){
            cout << "Entrada invalida. Por favor solo ingrese numeros. ";
        }
    }while(status == false);
    return stod(stringCapturada);
}

// Método para ingresar palabras con un prompt opcional (op) para que el usuario sepa qué se le pide ingresar
string Data::capTxt(string op = ""){
    string txt;
    cout << op;
    cin >> ws;
    getline(cin, txt);
    cout << endl;
    return txt;
}

/*Metodo para comprobar que las indicaciones de un menu sean numeros, y que esten en el rango*/
int Data::ComprobacionMenus(string frase, int limite_inferior, int limite_superior, int error){
    string entrada;
    int num = -1;
    cout << "\n";
    if (error == limite_superior + 1){
        cout<<"Dato Invalido!"<<endl;
    }
    cout << frase;
    cin>>ws;
    getline(cin,entrada);
    int isInt = 1;
    //Comprobacion  de que sea un numero
    for (int i = 0; i < entrada.size(); i++){
        char b = entrada [i];
        int c = b - 48;
        if(not(c>-1 && c<10)){
            isInt = 0; // 0 si es letra, 1 si es un numero
        }
    }
    //Se define el numero que se regresa, dependiendo de que se escriba
    if (isInt == 1){
        num = stoi(entrada);
    }

    if(num < limite_inferior || num > limite_superior){
        num = limite_superior + 1;
    }
    return num;
}

/*Metodo para capturar el mes y validar que sea correcto el dato*/
int Data::capturarMes(string frase){
    int mes = 1;
    //Ciclo para que el usuario ponga el dato hasta que lo haga correctamente
    do{
        //Validacion
        if (mes<1 || mes >12){
            cout << "Dato invalido, intente de nuevo. ";
        }
        mes = capNum(frase);
    } while (mes<1 || mes >12);
    return mes;
}

/*Metodo para validar que el dato de dia fue dado correctamente*/
int Data::capturarDia(string frase, int mes){
    int dia = 1;
    //Usamos una condicion para cada tipo de mes, si tiene 30, 31, o 29 dias
    if (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12)
    {
        //Ciclo para que el usuario ingrese el dato hasta hacerlo correctamente
        do{
            //Vallidacion 31 dias
            if (dia<1 || dia >31){
                cout << "Dato invalido, intente de nuevo. ";
            }
            dia = capNum(frase);
        } while (dia<1 || dia>31);
    }
    else if (mes == 4 || mes == 6 || mes == 9 || mes == 11)
    {
        do{
            //Validacion 30 dias
            if (dia<1 || dia >30){
                cout << "Dato invalido, intente de nuevo. ";
            }
            dia = capNum(frase);
        } while (dia<1 || dia>30);
    }
    else if (mes==2){
        do{
            //Validacion 29 dias
            if (dia<1 || dia >29){
                cout << "Dato invalido, intente de nuevo. ";
            }
            dia = capNum(frase);
        } while (dia<1 || dia>29);
    }
    return dia;
}

/*Metodo para capturar la hora y validarla*/
int Data::capturarHora(string frase){
    int hora = 1;
    do{//Ciclo para que el usuario ingrese el dato hasta hacerlo correctamente
        if (hora<0 || hora >23){ //Validacion horas
            cout << "Dato invalido, intente de nuevo. ";
        }
        hora = capNum(frase);
    } while (hora<0 || hora >23);
    return hora;
}

/*Metodo para capturar los minutos y validarlos*/
int Data::capturarMinutos(string frase){
    int minutos = 1;
    do{
        //Ciclo para que el usuario ingrese el dato hasta hacerlo correctamente
        if (minutos<0 || minutos >59){ //Validacion minutos
            cout << "Dato invalido, intente de nuevo. ";
        }
        minutos = capNum(frase);
    } while (minutos<0 || minutos >59);
    return minutos;
}

/*Getter para obtener el mes en forma de palabra*/
string Data::getMesPalabra(int MesCita){
    string MesPalabra;
    switch (MesCita)
    {
    case 1:
        MesPalabra = "Enero";
        break;
    case 2:
        MesPalabra = "Febrero";
        break;
    case 3:
        MesPalabra = "Marzo";
        break;
    case 4:
        MesPalabra = "Abril";
        break;
    case 5:
        MesPalabra = "Mayo";
        break;
    case 6:
        MesPalabra = "Junio";
        break;
    case 7:
        MesPalabra = "Julio";
        break;
    case 8:
        MesPalabra = "Agosto";
        break;
    case 9:
        MesPalabra = "Septiembre";
        break;
    case 10:
        MesPalabra = "Octubre";
        break;
    case 11:
        MesPalabra = "Noviembre";
        break;
    case 12:
        MesPalabra = "Diciembre";
        break;
    
    default:
        break;
    }
    return MesPalabra;
}