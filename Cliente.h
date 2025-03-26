/* Sistema de gestión de citas: una aplicación que permita a los pequeños negocios 
programar citas y recordatorios de citas para sus clientes, y enviar correos electrónicos 
o mensajes de texto para recordatorios. EQUIPO 7 */

//#include "iostream"
//#include "string"
#include "Data.h"
#include "fstream"

using namespace std;

Data d; //Composicion con clase Data

class Cliente{
    private:
        string empresa, nombre, correo, telefono;
        bool ya_se_imprimio_o_no = false;
        int numRegistroCliente;
    public:
        /*Constructores*/
        Cliente();
        Cliente(string emp, string nom, string corr, string tel, int _numRegistroCliente);
        /*Métodos*/
        void ImpData(int, string);
        void ImprimirResumen();
        void modificarInfoCliente();
        /*Setters y getters*/
        bool get_ya_se_imprimio_o_no();
        void set_ya_se_imprimio_o_no(bool P);
        void setNombre();
        string getNombre();
        string getEmpresa();
        string getCorreo();
        string getTelefono();
        int getNumRegistroCliente();
        void ImpID_Cliente();

        ~Cliente();
};

/*Constructor vacio*/
Cliente::Cliente(){}

/*Constructor parametrizado*/
Cliente::Cliente(string emp, string nom, string corr, string tel, int _numRegistroCliente){
    empresa = emp;
    nombre = nom;
    correo = corr;
    telefono = tel;
    numRegistroCliente = _numRegistroCliente;
}

/*Derivacion de todos los getters de la clase*/
bool Cliente::get_ya_se_imprimio_o_no(){
    return ya_se_imprimio_o_no;
}

void Cliente::set_ya_se_imprimio_o_no(bool P){
    ya_se_imprimio_o_no = P;
}
void Cliente::setNombre(){
    nombre = "";
}

string Cliente::getNombre(){
    return nombre;
}

string Cliente::getEmpresa(){
    return empresa;
}

string Cliente::getCorreo(){
    return correo;
}

string Cliente::getTelefono(){
    return telefono;
}

int Cliente::getNumRegistroCliente(){
    return numRegistroCliente;
}

/*Metodo para imprimir los datos del cliente*/
void Cliente::ImpData(int n, string palabra){
    cout << " ";
    int espacio;
    //Si el espacio es suficiente, se imprime la palabra y modificamos el espacio
    if(palabra.size()<=n){
        cout << palabra;
        espacio = (n) - palabra.size();
    }else{
        //En caso que la palabra sea mas larga que el espacio indicado, se descompone el string
        n = n - 2;
        for(int i=0; i<n; i++){
            cout << palabra[i];
        }
        espacio = 2;
    }
    // Se escribe el espacio para la siguiente palabra 
    for (int i = 0; i < espacio; i++){
        cout << " ";
    }
}

/*Metodo para modificar la informacion del cliente*/
void Cliente::modificarInfoCliente(){
    int opcion;
    int bandera = 0;
    do{ //Ponemos el menu en un ciclo para que no se cierre hasta que el usuario lo indique 
        system("cls");
        cout << "--------- Modificacion de datos cliente ---------" << endl;
        cout << "1) Nombre del cliente" << endl;
        cout << "2) Empresa de procedencia" << endl;
        cout << "3) Correo registrado" << endl;
        cout << "4) Numero de contacto" << endl;
        cout << "5) Salir" << endl;
        cout << "\n Advertencia: El modificar los datos del cliente, hara que tambien se " << endl;
        cout << "                modifiquen los datos de todas las citas ligadas a esta persona"<< endl;
        opcion = d.capNum("\n Seleccione una opcion: ");
        if(opcion!=5){system("cls");}
        cout << endl;
        //Usamos un switch case para las opciones del menu
        switch (opcion){
            case 1: //Caso de cambio de nombre
                cout << "Nombre registrado: " << nombre << endl;
                nombre = d.capTxt("Inserte nuevo nombre: ");
                bandera = 1;
                break;
            case 2: //Caso de cambio de nommbre de empresa
                cout << "Empresa registrada: " << empresa << endl;
                empresa = d.capTxt("Inserte nueva Empresa: ");
                bandera = 1;
                break;
            case 3: //Caso de cambio de correo
                cout << "Correo registrado: " << correo << endl;
                correo = d.capTxt("Inserte nuevo correo: ");
                bandera = 1;
                break;
            case 4: //Caso de cambio de telefono
                cout << "Numero de telefono registrado: " << telefono << endl;
                telefono = d.capTxt("Inserte nuevo telefono: ");
                bandera = 1;
                break;
            default:
                break;
        }
        if (bandera == 1 && opcion != 5) //Si se cambio algo, se avisa al usuario que asi fue
        {
            cout << "La informacion se ha actualizado correctamente!" << endl;
            system("pause");
        }
        
    }while (opcion != 5);
}

/*Impresion de la informacion del cliente con numero de registro*/
void Cliente::ImpID_Cliente(){
    //Verificamos que se imprima como debe en base a el numero de registro
    if (numRegistroCliente < 10){
        cout << " 00" << numRegistroCliente << " ";
    }else if(numRegistroCliente < 100){
        cout << " 0" << numRegistroCliente << " ";
    }else{
        cout << " " << numRegistroCliente << " ";
    }
    //Usamos el metodo ImpData para que se imprima ordenadamente, parametrizado con el numero de espacio y su respectivo getter
    ImpData(22, getNombre());
    ImpData(17, getEmpresa());
    ImpData(30, getCorreo());
    ImpData(16, getTelefono());
    cout << endl;
}

Cliente::~Cliente(){}