#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>

using namespace std;


vector<string> split(const string& s, char delim) {
    vector<string> tokens;
    size_t start = 0, end = 0;
    while ((end = s.find(delim, start)) != string::npos) {
        tokens.push_back(s.substr(start, end - start));
        start = end + 1;
    }
    tokens.push_back(s.substr(start));
    return tokens;
}


bool esNumeroValido(const string& s, bool positivo) {
    if (s.empty()) return false;
    
    for (char c : s) if (!isdigit(c)) return false;
    
    if (s == "0") return !positivo;  
   
    if (s[0] == '0') return false;
   
    return true;
}


bool enroqueValido(const string& s) {
    if (s == "-") return true;
    if (s.empty()) return false;
    string permitido = "KQkq";
    
    bool visto[256] = {false};
    int ultimaPos = -1;
    for (char c : s) {
        size_t pos = permitido.find(c);
        if (pos == string::npos) return false;       
        if (visto[(unsigned char)c]) return false;   
        if ((int)pos <= ultimaPos) return false;     
        visto[(unsigned char)c] = true;
        ultimaPos = (int)pos;
    }
    return true;
}


bool tableroValido(const string& s) {
    vector<string> filas = split(s, '/');
    if (filas.size() != 8) return false;
    for (const string& fila : filas) {
        int suma = 0;
        bool anteriorDigito = false;
        for (char c : fila) {
            if (isdigit(c)) {
                if (anteriorDigito) return false;   
                int val = c - '0';
                if (val < 1 || val > 8) return false;
                suma += val;
                anteriorDigito = true;
            } else if (isalpha(c)) {
                
                if (string("prnbqkPRNBQK").find(c) == string::npos) return false;
                suma += 1;
                anteriorDigito = false;
            } else {
                return false; 
            }
        }
        if (suma != 8) return false; 
        
    }
    return true;
}


bool alPasoValido(const string& s) {
    if (s == "-") return true;
    if (s.length() != 2) return false;
    char col = s[0];
    char fila = s[1];
    if (col < 'a' || col > 'h') return false;
    if (fila < '1' || fila > '8') return false;

    return true;
}


bool esFENValido(const string& fen) {
    
    if (fen.empty() || fen.front() == ' ' || fen.back() == ' ') return false;

    
    vector<string> campos = split(fen, ' ');
    if (campos.size() != 6) return false;

    
    if (!tableroValido(campos[0])) return false;
    if (campos[1] != "w" && campos[1] != "b") return false;
    if (!enroqueValido(campos[2])) return false;
    if (!alPasoValido(campos[3])) return false;
    if (!esNumeroValido(campos[4], false)) return false; 
    if (!esNumeroValido(campos[5], true))  return false; 

    return true;
}

int main() {
    string entrada;
    cout << "Introduce una cadena en notacion FEN: ";
    getline(cin, entrada);

    if (esFENValido(entrada))
        cout << "La cadena ES una notacion FEN valida." << endl;
    else
        cout << "La cadena NO es una notacion FEN valida." << endl;

    return 0;
}