#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

using namespace std;

map<string, string> crearDiccionario() {
    map<string, string> dict;
    dict["int"] = "entero";
    dict["float"] = "flotante";
    dict["char"] = "caracter";
    dict["if"] = "si";
    dict["else"] = "sino";
    dict["while"] = "mientras";
    dict["for"] = "para";
    dict["return"] = "retornar";
    dict["void"] = "vacio";
    dict["switch"] = "segun";
    return dict;
}

int main() {

    map<string, string> diccionario = crearDiccionario();

   
    ifstream archivo("programa.cpp");
    
    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir 'programa.c'" << endl;
        return 1;
    }

    string buffer = "";
    char c;

  
    while (archivo.get(c)) {
        if (isalnum(c) || c == '_') {
           
            buffer += c;
        } else {
          
            if (!buffer.empty()) {
                if (diccionario.count(buffer)) {
                    cout << diccionario[buffer];
                } else {
                    cout << buffer;
                }
                buffer = ""; 
            }
            cout << c; 
        }
    }

    archivo.close();
    return 0;
}