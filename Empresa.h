/* Sistema de gestión de citas: una aplicación que permita a los pequeños negocios 
programar citas y recordatorios de citas para sus clientes, y enviar correos electrónicos 
o mensajes de texto para recordatorios. EQUIPO 7 */

#include "Citas.h"
#include "vector"
#include <sstream>
#include "algorithm"
using namespace std;

class Empresa{
    private:
        /*Atributos*/
        string nombre_Empresa, usuario, password;
        string destinario, txtRecordatorio;
        int numRegistroCita = 0;
        int numRegistroCliente = 0;
        int CNR = 0;
        /*Composición*/
        vector<Cliente> clientes;
        vector <Citas*> citas;
    public:
        /*Constructores*/
        Empresa();
        Empresa(string nom, string usr, string passw);
        /*------ Métodos ---------*/
        void menu();
        void RecuperarInfoClientes(); 
        void RecuperarInfoCitas();
        void GuardarInfoCliente(Cliente cliente);
        void GuardarInfoCitas(Citas citas); 
        void ImprimirListaClientes();
        void ImprimirCitasOrdenCronologico();
        void IngresarDatosEmpresa();
        void crearCliente();
        void crearCita(int _numRegistroCliente);
        void modificarInformacion();
        void verCitasProgramadas();
        void mandarRecordatorio();
        void buscador(string);
        void eliminarCliente();
        void eliminarCita();
        void InicioterminalCita(int _numRegistroCliente); //Estetico para confirmar nueva cita
        /*Getters*/
        string getUser();
        string getPassword();
        /*Destructor*/
        ~Empresa();
};

/*Constructor vacio*/
Empresa::Empresa(){}

/*Constructor parametrizado*/
Empresa::Empresa(string nom, string usr, string passw){
    nombre_Empresa = nom;
    usuario = usr;
    password = passw;
}

/*Metodo para el despliegue del menu*/
void Empresa::menu(){
    int opcion, numero;
    do{ //Se mantiene en un ciclo para que se repita hasta que el usuario desee salir
        do{
            system("cls");
            cout << "  ----- " << nombre_Empresa << " -----" << endl;
            cout << "1) Ingresar nuevo cliente" << endl;
            cout << "2) Ingresar nueva cita" << endl;
            cout << "3) Ver lista de clientes registrados" << endl;
            cout << "4) Ver lista de citas programadas" << endl;
            cout << "5) Modificar datos de citas y de clientes" << endl; // Modificar datos de citas y de clientes
            cout << "6) Mandar o programar mensajes y recordatorios" << endl;
            cout << "7) Salir" << endl;
            opcion = d.ComprobacionMenus("Ingrese una opcion: ", 1, 7, opcion);
        }while(opcion == 8);
        system("cls");
        string palabra;
        //Switch case para las opciones del menu
        switch (opcion){
            case 1://Caso de crear un cliene
                crearCliente();
                break;
            case 2://Caso de crear una cita
                /*Buscador de clientes*/
                ImprimirListaClientes();
                cout << endl;
                numero = d.capNum("Ingrese el numero de registro del cliente con el cual desea agendar cita: ");
                crearCita(numero);
                break;
            case 3://Caso de imprimir lista de clientes
                int opcion_sub_C;
                do
                {
                    system("cls");
                    ImprimirListaClientes();
                    cout << endl;
                    //Dentro de esta lista, se podra elegir si eliminar algun cliente 
                    cout << "    --- Submenu clientes --- " << endl;
                    cout << "1) Eliminar un cliente" << endl;
                    cout << "2) Regresar" << endl;
                    opcion_sub_C = d.ComprobacionMenus("Ingrese una opcion: ", 1, 2, opcion_sub_C);
                    //Si se indica que se elimine un cliente, se aplica su metodo
                    if (opcion_sub_C == 1){ 
                        eliminarCliente();
                    }
                } while (opcion_sub_C == 3 || opcion_sub_C == 1);
                
                break;
            case 4: //Caso de ver la lista de citas
                verCitasProgramadas();
                break;
            case 5: //Caso de modificar algun dato
                cout<<"    --- Buscador ---" << endl;
                //cout << "Aviso: Escriba 1 si desea simplemente ver la lista completa de clientes." << endl;

                palabra = d.capTxt("Ingrese nombre del cliente a buscar: ");
                buscador(palabra); //Se busca el cliente que se desea modificar
                cout << endl;
                modificarInformacion(); //se aplica metodo para modificar informacion 
                break; 
            case 6: //Caso de mandar recordatorios
            // Se generan archivos de texto con los datos del recordatorio
                mandarRecordatorio(); //Se aplica el metodo de recordatorios
                break;
            default:
                break;
        } 
    }while (opcion != 7);
    ofstream archivo("Citas.txt", ios::trunc); //Vacia el archivo txt, haciendo que este disponible para insertar la nueva información
    ofstream archivo1("Clientes.txt", ios::trunc);
    //Se guarda la informacion de citas en un texto
    for (int i = 0; i < clientes.size(); i++){
        if (clientes[i].getNombre() != ""){
            GuardarInfoCliente(clientes[i]);
        }
    }

    //ofstream escritura;
    //escritura.open("Informacion.txt",fstream::app);
    //escritura << "****" << endl;
    //escritura.close();
    //Se guarda la informacion de las citas en un archivo de texto
    for (int i = 0; i < citas.size(); i++){
        if (citas[i]->cliente.getNombre() != ""){
            GuardarInfoCitas(*citas[i]);
        }
    }
}

/*Derivacion de getters*/
string Empresa::getUser(){
    return usuario;
}

string Empresa::getPassword(){
    return password;
}

/*Metodo para ingresar los datos de la empresa*/
void Empresa::IngresarDatosEmpresa(){
    //Se usa el objeto de Data para pedir y validar los datos
    cout << "     Registro de datos: " << endl;
    nombre_Empresa = d.capTxt("Nombre de la empresa: ");
    usuario = d.capTxt("Usuario: ");
    password = d.capTxt("Password: ");
}

/*Metodo para Imprimir las citas en orden cronologico*/
void Empresa::ImprimirCitasOrdenCronologico(){
    cout << " ---- Lista de citas programadas (Segun fecha) ----" << endl;
    cout << " Num |  Nombre de contacto  |     Empresa     |      Correo Electronico      |    Telefono    |  Fecha  |  Hora  |" << endl;
    for (int i = 0; i < citas.size(); i++) // Hace que se impriman el número registrados de citas
    {
        for (int j = 0; j < citas.size(); j++) // For que compara todo el vector con una fecha
        {
            if (citas[j]->cliente.get_ya_se_imprimio_o_no() == false)
            {
                if (citas[i]->getMes() > citas[j]->getMes())
                {
                    if (citas[j]->cliente.getNombre() != "")
                        {
                            citas[j]->ImprimirResumenCita();
                        }
                    //citas[j]->ImprimirResumenCita();
                    citas[j]->cliente.set_ya_se_imprimio_o_no(true);
                }else if(citas[i]->getMes() == citas[j]->getMes() && citas[i]->getDia() > citas[j]->getDia()){
                    if (citas[j]->cliente.getNombre() != "")
                        {
                            citas[j]->ImprimirResumenCita();
                        }
                    //citas[j]->ImprimirResumenCita();
                    citas[j]->cliente.set_ya_se_imprimio_o_no(true);
                } else if (citas[i]->getDia() == citas[j]->getDia() && citas[i]->getHoras() > citas[j]->getHoras()){
                    if (citas[j]->cliente.getNombre() != "")
                        {
                            citas[j]->ImprimirResumenCita();
                        }
                    //citas[j]->ImprimirResumenCita();
                    citas[j]->cliente.set_ya_se_imprimio_o_no(true);
                } else if (citas[i]->getHoras() == citas[j]->getHoras() && citas[i]->getMinutos() > citas[j]->getMinutos()){
                    if (citas[j]->cliente.getNombre() != "")
                        {
                            citas[j]->ImprimirResumenCita();
                        }
                    //citas[j]->ImprimirResumenCita();
                    citas[j]->cliente.set_ya_se_imprimio_o_no(true);
                }
            }
        }
    }
    for (int i = 0; i < citas.size(); i++){
        if (citas[i]->cliente.get_ya_se_imprimio_o_no()==false){
            if (citas[i]->cliente.getNombre() != "")
            {
                citas[i]->ImprimirResumenCita();
            }
            //citas[i]->ImprimirResumenCita();
        }else{
            citas[i]->cliente.set_ya_se_imprimio_o_no(false);
        }
    }
}

/*Metodo para crear un cliente*/
/*Le puse '_' a unas variables ndms para asegurarme que no se confundieran con otros de Empresa*/
void Empresa::crearCliente(){
    //Usamos el objeto de Data para registrar y validar datos
    cout << "----- Nuevo cliente -----" << endl; 
    string _nombre = d.capTxt("Nombre de cliente: ");
    string _empresa = d.capTxt("Empresa de procedencia: ");
    string _correo = d.capTxt("Correo: ");
    string _telefono = d.capTxt("Telefono: ");
    numRegistroCliente += 1;
    clientes.push_back(Cliente(_empresa, _nombre, _correo, _telefono, numRegistroCliente));
}

/*Metodo para mostrar la informacion del cliente a la hora de generar una nueva cita*/
void Empresa::InicioterminalCita(int _numRegistroCliente){
        system("cls");
        cout << "   -- Informacion del cliente seleccionado: --" << endl;
        cout << " Num |  Nombre de contacto  |     Empresa     |      Correo Electronico      |    Telefono    |" << endl;
        clientes[_numRegistroCliente-1].ImpID_Cliente();
        cout << "\n----- Nueva Cita -----" << endl;
}

/*Metodo para crear una cita*/
void Empresa::crearCita(int _numRegistroCliente){
    //Se pide toda la informacion de la cita
    InicioterminalCita(_numRegistroCliente);
    int _mes = d.capturarMes("Ingrese el mes: ");

    InicioterminalCita(_numRegistroCliente);
    cout << "Ingrese el mes: " << _mes << endl;
    int _dia = d.capturarDia("Ingrese el dia: ",_mes);

    InicioterminalCita(_numRegistroCliente); 
    cout << "Ingrese el mes: " << _mes << endl;
    cout << "Ingrese el dia: " << _dia << endl;
    int _horas = d.capturarHora("Ingrese la hora: ");

    InicioterminalCita(_numRegistroCliente);
    cout << "Ingrese el mes: " << _mes << endl;
    cout << "Ingrese el dia: " << _dia << endl;
    cout << "Ingrese la hora: " << _horas << endl;
    int _minutos = d.capturarMinutos("Ingrese los minutos: ");

    system("cls");
    //Se muestra la informacion finalmente
        cout << "   -- Informacion del cliente seleccionado: --" << endl;
        cout << " Num |  Nombre de contacto  |     Empresa     |      Correo Electronico      |    Telefono    |" << endl;
        clientes[_numRegistroCliente-1].ImpID_Cliente();
        cout << "\n----- Nueva Cita -----" << endl;
    cout << "Cita programada para el " << _dia << " de " << d.getMesPalabra(_mes) << " a las " << _horas << ":";
    if (_minutos < 10)
    {
        cout << "0";
    }
    cout << _minutos << endl;
    cout << endl;
    numRegistroCita += 1;
    citas.push_back(new Citas(clientes[_numRegistroCliente-1], _dia, _mes, _horas, _minutos, numRegistroCita, _numRegistroCliente));
    system("pause");
}

/*Metodo para modificar informacion*/
void Empresa::modificarInformacion(){
    int opcion;
    do{
        int numero = d.capNum("Ingrese el numero de registro de la cita que deseas cambiar: ");
        cout << "\nDeseas modificar la informacion del cliente o de la cita con este?" << endl;
        cout << "1) Cliente" << endl;
        cout << "2) Cita" << endl;
        opcion = d.capNum();
        //Condicional para la opcion 1
        if(opcion == 1){
            int Cliente_a_modificar = citas[numero-1]->cliente.getNumRegistroCliente();
            clientes[Cliente_a_modificar-1].modificarInfoCliente();

            for (int i = 0; i < citas.size(); i++)
            {
                if(citas[i]->getNumeroDeCliente() == Cliente_a_modificar){
                    citas[i]->setCliente(clientes[Cliente_a_modificar-1]);
                }
            }
        }
        else if(opcion == 2){ //Condicion para opcion 2
            citas[numero-1]->modificarInfoCita();
        }
        else{
            //Validacion
            cout << "Entrada invalida. " << endl;
        }
    }while(opcion != 1 && opcion != 2);
}

/*Metodo para buscar un cliente en especifico con su nombre*/
void Empresa::buscador(string palabra){
    bool b;
    vector<int> resultados;
    for (int i = 0; i < citas.size(); i++)
    {
        string s = citas[i]->cliente.getNombre();
        string lectura;  // Aquí vamos a ir leyendo cada valor por separado
        stringstream input_stringstream(s);
        while (getline(input_stringstream, lectura, ' '))
        {
            b=true;
            for(int j=0;  j<palabra.size(); j++){
                if(lectura[j] != palabra[j]){
                    b=false;
                    break;
                }
            }
            if(b){
                resultados.push_back(i);
            }
        }
    }
    //Si se encuentra, se imprime lo buscado
    cout << "\n Num |  Nombre de contacto  |     Empresa     |      Correo Electronico      |    Telefono    |  Fecha  |  Hora  |" << endl;
    for (int i = 0; i < resultados.size(); i++){
        citas[resultados[i]]->ImprimirResumenCita();
    }
}

/*Metodo para mandar recordatorios*/
void Empresa::mandarRecordatorio(){
    int opcion;
    do{   
        //Se mantiene en ciclo hasta que el usuario termine 
        do{
            system("cls");
            cout << "   --- Tipo de formato del recordatorio ---" << endl;
            cout << "1) Mensaje de texto"<< endl;
            cout << "2) Correo electronico" << endl;
            cout << "3) Regresar" << endl;
            opcion = d.ComprobacionMenus("Ingrese una opcion: ", 1, 3, opcion);
        }while(opcion == 4);
        system("cls");

        int NumeroCita;
        if (opcion !=3)
        {
            //Se usa el buscador para buscar el cliente al que se desea mandar el recordatorio
           cout << "\n -- Buscador --" << endl;
           cout << "Ingrese el nombre del cliente que desea contactar: " << endl;
           string name;
           cin >> ws;
           getline(cin, name);
           buscador(name);
           cout << "\n Ingrese el numero de cita para el que desea generar un recordatorio: " << endl;
           cin >> NumeroCita;
        }
        
        ofstream escritura;
        string Mensaje;
        string NameArchivo;
        int contExtraOpcion;
        switch (opcion){ //Switch case para opciones del menu
        case 1: //Caso para mensaje de texto
            do{
                system("cls");
                //Se imprime plantilla del mensaje
                cout << "    --- Mensaje de texto para " << citas[NumeroCita-1]->cliente.getNombre() << " ---" << endl;
                cout << "Enviando al " << citas[NumeroCita-1]->cliente.getTelefono()<< endl;
                cout << "Contenido del mensaje: " << endl;
                cout << "  Recordatorio cita: Con " << nombre_Empresa << ", el dia " << citas[NumeroCita-1]->getDia();
                cout << " de " << citas[NumeroCita-1]->getMesPalabra() << " a las " << citas[NumeroCita-1]->getHoras();
                cout << ":" << citas[NumeroCita-1]->getMinutos() << endl;
                //Si el usuario desea, puede agregar informacion extra
                contExtraOpcion = d.ComprobacionMenus("Desea agregar algun contenido extra? Si[1], No[0]: ", 0, 1, contExtraOpcion);
            }while(contExtraOpcion == 2);

            if (contExtraOpcion == 1)
            {
                cout << "\n Tecle el contenido que desea agregar al mensaje:" << endl;
                cin >> ws;
                getline(cin,Mensaje);
            }
            //Se crea un archivo especifico para el recordatorio y se guarda el recordatorio en ese archivo
            NameArchivo = "Recordatorio_Mensaje_" + citas[NumeroCita-1]->cliente.getTelefono() + "__" + to_string(citas[NumeroCita-1]->getDia()) + to_string(citas[NumeroCita-1]->getMes());
            escritura.open(NameArchivo,fstream::app);
            escritura << "Enviando a " << citas[NumeroCita-1]->cliente.getTelefono() << endl;
            escritura << "Hola " << citas[NumeroCita-1]->cliente.getNombre() << endl;
            escritura << "Recordatorio cita: Con " << nombre_Empresa << ", el dia " << citas[NumeroCita-1]->getDia();
            escritura << " de " << citas[NumeroCita-1]->getMesPalabra() << " a las " << citas[NumeroCita-1]->getHoras();
            escritura << ":" << citas[NumeroCita-1]->getMinutos() << endl;
            escritura << Mensaje << endl;
            escritura.close();

            break;
        case 2: //Caso para correo electronico
            do{
                system("cls");
                //Se imprime plantilla del correo
                cout << "    --- Correo electronico para " << citas[NumeroCita-1]->cliente.getNombre() << " ---" << endl;
                cout << "Para: " << citas[NumeroCita-1]->cliente.getCorreo()<< endl;
                cout << "Asunto: Recordatorio cita con " << nombre_Empresa << endl;
                cout << "\nContenido: " << endl;
                cout << "Estimado " << citas[NumeroCita-1]->cliente.getNombre() << endl;
                cout << "Esperemos se encuentre muy bien, le recordamos amablemente que tiene programada una cita con nosotros el dia " << citas[NumeroCita-1]->getDia();
                cout << " de " << citas[NumeroCita-1]->getMesPalabra() << " a las " << citas[NumeroCita-1]->getHoras();
                cout << ":" << citas[NumeroCita-1]->getMinutos() << endl;
                cout << "\nAtentamente " << nombre_Empresa << endl;
                //Si el usuario lo desea, puede escribir informacion extra
                contExtraOpcion = d.ComprobacionMenus("Desea agregar algun contenido extra? Si[1], No[0]: ", 0, 1, contExtraOpcion);
            }while(contExtraOpcion == 2);

            if (contExtraOpcion == 1)
            {
                cout << "\n Tecle el contenido que desea agregar al mensaje:" << endl;
                cin >> ws;
                getline(cin,Mensaje);
            }
            //Se crea un archivo especifico para el recordatorio, y se guarda el correo en este 
            NameArchivo = "Recordatorio_Mensaje_" + citas[NumeroCita-1]->cliente.getCorreo() + "__" + to_string(citas[NumeroCita-1]->getDia()) + to_string(citas[NumeroCita-1]->getMes());

            escritura.open(NameArchivo,fstream::app);
            escritura << "Enviando a  " << citas[NumeroCita-1]->cliente.getCorreo() << endl;
            escritura << "Para: " << citas[NumeroCita-1]->cliente.getCorreo()<< endl;
            escritura << "Asunto: Recordatorio cita con " << nombre_Empresa << endl;
            escritura << "\nContenido: " << endl;
            escritura << "Estimado " << citas[NumeroCita-1]->cliente.getNombre() << endl;
            escritura << "Esperemos se encuentre muy bien, le recordamos amablemente que tiene programada una cita con nosotros el dia " << citas[NumeroCita-1]->getDia();
            escritura << " de " << citas[NumeroCita-1]->getMesPalabra() << " a las " << citas[NumeroCita-1]->getHoras();
            escritura << ":" << citas[NumeroCita-1]->getMinutos() << endl;
            escritura << Mensaje << endl;
            escritura << "\nAtentamente " << nombre_Empresa << endl;
            escritura.close();
            break;
        default:
            break;
        }
    } while (opcion != 3);
}

/*Metodo para ver las citas existentes*/
void Empresa::verCitasProgramadas(){
    int opcion2;
    do{
        do{
            system("cls");
            cout << "  ----- Como desea desplegar la lista -----" << endl;
            cout << " 1) En orden de registro  (Segun Numero de registro o Num)" << endl;
            cout << " 2) Cronologicamente  (Como calendario, de la cita mas proxima a la mas apartada)" << endl;
            cout << " 3) Regresar al menu principal" << endl;
            opcion2 = d.ComprobacionMenus("Ingrese una opcion: ", 1, 3, opcion2);
        }while(opcion2 == 4);

        system("cls");
        //Switch case para las opciones del menu
        switch (opcion2){
            case 1: //Caso de orden de registro
                int opcion_sub_C;
                do
                {
                    system("cls");
                    cout << " ---- Lista de citas programadas (Segun Numero de registro) ----" << endl;
                    cout << " Num |  Nombre de contacto  |     Empresa     |      Correo Electronico      |    Telefono    |  Fecha  |  Hora  |" << endl;
                    for (int i = 0; i < citas.size(); i++){
                        if (citas[i]->cliente.getNombre() != "")
                        {
                            citas[i]->ImprimirResumenCita();
                        }
                    }
                    cout << endl;
                    //Aqui se puede elegir si se ddesea elmminiar alguna cita
                    cout << "    --- Submenu citas --- " << endl;
                    cout << "1) Eliminar cita" << endl;
                    cout << "2) Regresar" << endl;
                    opcion_sub_C = d.ComprobacionMenus("Ingrese una opcion: ", 1, 2, opcion_sub_C);
                    //se usa su propio metodo para eliminar la cita
                    if (opcion_sub_C == 1){
                        eliminarCita();
                    }
                } while (opcion_sub_C == 3 || opcion_sub_C == 1);
                break;
            case 2: // Caso de orden cronologico
                do
                {
                    system("cls");
                    ImprimirCitasOrdenCronologico();
                    cout << endl;
                    //Aqui se puede elegir si se desea elmminiar alguna cita
                    cout << "    --- Submenu citas --- " << endl;
                    cout << "1) Eliminar cita" << endl;
                    cout << "2) Regresar" << endl;
                    opcion_sub_C = d.ComprobacionMenus("Ingrese una opcion: ", 1, 2, opcion_sub_C);
                    // metodo para eliminar la cita
                    if (opcion_sub_C == 1){
                        eliminarCita();
                    }
                } while (opcion_sub_C == 3 || opcion_sub_C == 1);
                break;
            default:
                break;
            }
    } while (opcion2 != 3);
}

/*Metodo para leee el archivo txt y recupera todos los datos con ayuda de un constructor parametrizado*/
void Empresa::RecuperarInfoClientes(){
    string emp, nom, corr, tel;
    int CNR = 0;
    ifstream archivo1;
    archivo1.open("Clientes.txt");
    if (archivo1.is_open()){
        string linea;
        string Variable;
        string aux;
        int bandera = 0;
        int contador = 0;
        //Se repite hasta que aparezcan 4 asterizcos
        //Los asterizcos separan la parte de registro de datos de clientes de la de citas
        while (getline(archivo1, linea) && linea != "****") {
        /*while (getline(archivo1, linea)) {
            if (linea == "****")
            {
                archivo1.close();//Se cierra el archivo
                break;
            }
            */
            
            for (int i = 0; i < linea.size(); i++){
                if (linea[i] != '$' && linea[i] != '%'){
                    if (linea[i] != '#'){Variable += linea[i];}
                    switch (contador) //Switch para casos de variable
                    {
                    case 1: //Caso nombre
                        nom = Variable;
                        //cout << "  -nom: " << nom << endl;
                        if (nom[0]>47 && nom[0]<58)
                        {   
                            //cout << "numero" << endl;
                            bandera = 1;
                        }else{
                            //cout << "letra" << endl;
                            bandera = 0;
                        }
                        
                        break;
                    case 2: //Caso empresa
                        emp = Variable;
                        break;
                    case 3: //Caso correo
                        corr = Variable;
                        break;
                    case 4: //Caso telefono
                        tel = Variable;
                        if (linea[i] == '#'){contador = 0;}
                        break;
                    default:
                        break;
                    }
                }else{
                    //cout << Variable << endl;
                    Variable = "";
                    contador++;
                }
            }
            //cout << "nom: " << nom << "   aux:" << aux << endl;
            if (aux != nom and bandera != 1)
            {
                CNR++;
                Cliente _cliente(emp, nom, corr, tel, CNR); //Se crea el cliente
                clientes.push_back(_cliente);
                //cout << "*" << endl;
            }
            aux = nom;
            //cout << "nom: " << nom << "   aux:" << aux << endl;
        }
    archivo1.close();//Se cierra el archivo
    }
    //cout << "CNR: " << CNR << endl;
    numRegistroCliente = CNR;
    //cout << numRegistroCliente << endl;
    //system("pause");
    //cout << "+" << endl;
    //system("pause");
}

/*Metodo para leer las citas y recuperar todos los datos con ayuda de un string*/
void Empresa::RecuperarInfoCitas(){
    int NC, d, me, h, mi;
    int CNR = 0;
    ifstream archivo;
    archivo.open("Citas.txt");
    if (archivo.is_open()){
        string linea;
        string Variable;
        int contador = 0;
        int bandera = 1;
        int auxEmergencia = 0;
        //Se realiza el procedimiento hasta terminar de leer el archivo 
        while (getline(archivo, linea)) {
            //auxEmergencia ++;
            //if (auxEmergencia > clientes.size()+1)
            //{
            
                if (bandera == 1){
                    for (int i = 0; i < linea.size(); i++){
                        if (linea[i] != '$' && linea[i] != '%'){
                            if(linea[i] != '#'){Variable += linea[i];}
                            switch (contador) //Switch case para las variables
                            {
                            case 1: //Caso de numero de registro cliente
                                NC = stoi(Variable);
                                break;
                            case 2: //Caso de dia
                                d = stoi(Variable);
                                break;
                            case 3: //Caso de mes
                                me = stoi(Variable);
                                break;
                            case 4: //Caso de hora
                                h = stoi(Variable);
                                break;
                            case 5: //Caso de minuto
                                mi = stoi(Variable);
                                if(linea[i] == '#'){contador = 0;}
                                break;
                            default:
                                break;
                            }
                        }else{
                            Variable = "";
                            contador++;
                        }
                    }
                CNR++;
                citas.push_back(new Citas(clientes[NC-1], d, me, h, mi, CNR, NC));
                //}
            } //
            if (linea == "****"){bandera = 1;}
        }
    archivo.close(); //Se cierra el archivo 
    }
    //numRegistroCliente = CNR;
    numRegistroCita = CNR;
}

/*Metodo para guardar la informacion de los clientes*/
void Empresa::GuardarInfoCliente(Cliente cliente){
    ofstream escritura;
    escritura.open("Clientes.txt",fstream::app);
    //Usamos los getters para obtener la informacion, y escribimos todo de cierta manera para que al reingresar el programa sea capaz de leer el archivo
    escritura << "%" << cliente.getNombre() << "$" << cliente.getEmpresa() << "$" << cliente.getCorreo() << "$" << cliente.getTelefono() << "#" << endl;
}

/*Metodo para guadar la informacion de las citas*/
void Empresa::GuardarInfoCitas(Citas citas){
    ofstream escritura;
    escritura.open("Citas.txt",fstream::app);
    //Usamos los getters para obtener la informacion, y escribimos todo de cierta manera para que al reingresar el programa sea capaz de leer el archivo
    escritura << "%" << citas.cliente.getNumRegistroCliente() << "$" << citas.getDia() << "$" << citas.getMes() << "$" << citas.getHoras() << "$" << citas.getMinutos() << "#" << endl;
    escritura.close();
}

/*Metodo para imprimir la lista de clientes*/
void Empresa::ImprimirListaClientes(){
    cout << "                            ---- Lista de clientes registrados ----                            " << endl;
    cout << " Num |  Nombre de contacto  |     Empresa     |      Correo Electronico      |    Telefono    |" << endl;

    for (int i = 0; i < clientes.size(); i++){
        if (clientes[i].getNombre() != "")
        {
            clientes[i].ImpID_Cliente();
        }
    }
}

/*Metodo para eliminar un cliente*/
void Empresa::eliminarCliente(){
    system("cls");
    ImprimirListaClientes();
    cout << "\nADVERTENCIA: El eliminar la informacion de un cliente hara que se eliminen todas las citas ligadas a este." << endl;
    cout << "\nIngrese el numero del cliente que desea eliminar: ";
    int n;
    n = d.capNum();

    //usamos erase en las citas del cliente indicado
    for (int i = 0; i < citas.size(); i++)
    {
        if(citas[i]->getNumeroDeCliente() == (n)){
            citas[i]->cliente.setNombre();
        }
    }
    //clientes.erase(clientes.begin() -1 + n); //Borramos el cliente
    clientes[n-1].setNombre();
    system("cls");
    cout << "\n - Cliente eliminado con exito, volviendo al menu submenu..." << endl;
    cout << endl;
    system("pause");
}

/*Metodo para borrar citas*/
void Empresa::eliminarCita(){
    cout << "\nIngrese el numero de la cita que desea eliminar: ";
    int n;
    n = d.capNum();

    for (int i = 0; i < citas.size(); i++)
    {
        if(citas[i]->getNumRegistroCita() == (n)){
            citas.erase(citas.begin() + i); //Usamos erase para eliminar la cita indicada
        }
    }

    //clientes.erase(clientes.begin() -1 + n); //Borramos la informacion del cliente en esa cita
    system("cls");
    cout << "\n - Cita cancelada, volviendo al menu submenu..." << endl;
    cout << endl;
    system("pause");
}

/*Destructor*/
Empresa::~Empresa(){
    for(int i = 0; i < CNR; i++){
        delete[] citas[i]; //Borramos las citas ya que son apuntadores
    }
}