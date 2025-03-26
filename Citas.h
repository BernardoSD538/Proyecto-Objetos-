/* Sistema de gestión de citas: una aplicación que permita a los pequeños negocios 
programar citas y recordatorios de citas para sus clientes, y enviar correos electrónicos 
o mensajes de texto para recordatorios. EQUIPO 7 */

#include "iostream"
using namespace std;
#include "vector"

#include "Cliente.h"

class Citas{
    private:
        /*Atributos*/
        int dia, mes, horas, minutos;
        int numRegistroCita;
        int NumeroDeCliente;
    public:
        /*Composición*/
        Cliente cliente;
        /*Constructores*/
        Citas();
        Citas(Cliente _cliente, int _dia, int _mes, int _horas, int _minutos, int _numRegistroCita, int _NumeroDeCliente);
        /*Métodos*/
        void modificarInfoCita();
        void ImprimirResumenCita();
        /*Setters y getters*/
        void setNumRegistroCita(int);
        int getNumRegistroCita();
        int getMinutos();
        int getHoras();
        int getDia();
        int getMes();
        int getNumeroDeCliente();
        string getMesPalabra();
        void setCliente(Cliente _cliente);
};

Citas::Citas(){} /*Constructor vacio*/

/*Constructor parametrizado*/
Citas::Citas(Cliente _cliente, int _dia, int _mes, int _horas, int _minutos, int _numRegistroCita, int _NumeroDeCliente): cliente(_cliente){
    dia = _dia;
    mes = _mes;
    horas = _horas;
    minutos = _minutos;
    numRegistroCita = _numRegistroCita;
    NumeroDeCliente = _NumeroDeCliente;
}

/*Derivacion de setters*/
void Citas::setCliente(Cliente _cliente){
    cliente = _cliente;
}

int Citas::getNumeroDeCliente(){
    return NumeroDeCliente;
}

void Citas::setNumRegistroCita(int n){
    numRegistroCita = n;
}

/*Derivacion de los getters*/
int Citas::getMinutos(){
    return minutos;
}

int Citas::getHoras(){
    return horas;
}

int Citas::getDia(){
    return dia;
}

int Citas::getMes(){
    return mes;
}

int Citas::getNumRegistroCita(){
    return numRegistroCita;
}

string Citas::getMesPalabra(){
    int MesCita = getMes();
    string MesPalabra;
    switch (MesCita) //Switch case para cada caso del mes
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

/*Metodo para modificar la informacion de la cita*/
void Citas::modificarInfoCita(){
    int opcion;
    int bandera = 0;
    do{
        system("cls");
        cout << "--------- Modificacion de datos cita ---------" << endl;
        cout << "1) Dia y mes" << endl;
        cout << "2) Hora y Minutos" << endl;
        cout << "3) Salir " << endl;
        opcion = d.capNum("\n Seleccione una opcion: ");
        if (opcion != 3)
        {
            system("cls");
        }
        //Switch case para los casos del menu
        switch (opcion){
            case 1: //Caso de cambio de dia y mes
                cout << " - Dia registrado: " << dia << endl;
                cout << " - Mes registrado: " << mes << endl;
                cout << "Inserte nueva fecha: " << endl;
                mes = d.capturarMes("Mes: ");

                system("cls");
                cout << " - Dia registrado: " << dia << endl;
                cout << " - Mes registrado: " << mes << endl;
                cout << "Inserte nueva fecha: " << endl;
                cout << "Mes: " << mes << endl;
                dia = d.capturarDia("Dia: ", mes);
                bandera = 1;
                break;
            case 2: //Caso de cambio de hora y minutos
                cout << " - Hora registrada: " << horas << ":"; 
                if (minutos < 10)
                {
                    cout << "0";
                }
                cout << minutos << endl;
                cout << "Inserte nueva hora de encuentro: " << endl;
                horas = d.capturarHora("Hora: ");

                system("cls");
                cout << " - Hora registrada: " << horas << ":"; 
                if (minutos < 10)
                {
                    cout << "0";
                }
                cout << minutos << endl;
                cout << "Inserte nueva hora de encuentro: " << endl;
                cout << "Hora: " << horas << endl;
                minutos = d.capturarMinutos("Minutos: ");
                bandera = 1;
                break;
            default:
                /*Falta poner validación aquí por si el usuario la riega*/
                break;
            }
        //Se informa al usuario en caso de que se haya cambiado la informacion
        if (bandera == 1 && opcion != 3){
            cout << "La informacion se ha actualizado correctamente!" << endl;
            system("pause");
        }
    } while (opcion != 3);
}

/*Metodo para imprimir la informacion de la cita*/
void Citas::ImprimirResumenCita(){
    //Condicionamos para que se imprima correctamente el registro dependiendo del tamaño
    if (numRegistroCita < 10){
        cout << " 00" << numRegistroCita << " ";
    }else if(numRegistroCita < 100){
        cout << " 0" << numRegistroCita << " ";
    }else{
        cout << " " << numRegistroCita << " ";
    }
    //Usamos el objeto cliente para imprimir su informacion
    cliente.ImpData(22, cliente.getNombre());
    cliente.ImpData(17, cliente.getEmpresa());
    cliente.ImpData(30, cliente.getCorreo());
    cliente.ImpData(16, cliente.getTelefono());
    
    cout << "  ";
    // dia y mes, condicionados para que se impriman correctamente dependiendo del tamaño de dia y mes
    if (dia<10){
        cout << "0" << dia;
    }else{
        cout << dia;
    }
    cout << " / ";
    if (mes<10){
        cout << "0" << mes;
    }else{
        cout << mes;
    }
    for (int i = 0; i < (9-6); i++){
        cout << " ";
    }
    cout << " ";
    // hora
    if (horas<10){
        cout << "0" << horas;
    }else{
        cout << horas;
    }
    cout << ":";
    if (minutos<10){
        cout << "0" << minutos;
    }else{
        cout << minutos;
    }
    cout << endl;
}