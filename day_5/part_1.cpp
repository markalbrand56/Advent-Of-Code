#include <fstream>
#include <iostream>
#include <map>
#include <ostream>
#include <string>
#include <vector>
using namespace std;

int main() {
  cout << "Hello World" << endl;

  // DST | SRC | RANGE
  
  ifstream file("sample.txt");

  if(!file.is_open()){
    cerr << "Error al abrir el archivo" << endl;
    return 1;
  }

  vector<string> lineas;
  string linea_actual;
  while(getline(file, linea_actual)){
    lineas.push_back(linea_actual);
  }
  file.close();

  for (const auto& l : lineas) {

    if(l.empty()){  // Lineas en blanco
      cout << "Vacio" << endl;
    } else {
      cout << l << endl;
    }
  }

  // División de líneas
  string seeds = lineas[0];  // lineas[1]: ""
  int i = 2;


  // Seed to soil
  cout << "SEED TO SOIL" << endl;
  for(; !lineas[i].empty(); i++){
    cout << lineas[i] << endl;
  }

  cout << "SOILD TO FERTILIZER" << endl;
  i++;

  for(; !lineas[i].empty(); i++){
    cout << lineas[i] << endl;
  }

  cout << "FERTILIZER TO WATER" << endl;
  i++;

  for(; !lineas[i].empty(); i++){
    cout << lineas[i] << endl;
  }

  cout << "WATER TO LIGHT" << endl;
  i++;

  for(; !lineas[i].empty(); i++){
    cout << lineas[i] << endl;
  }

  cout << "LIGHT TO TEMP" << endl;
  i++;

  for(; !lineas[i].empty(); i++){
    cout << lineas[i] << endl;
  }

  cout << "TEMP TO HUMIDITY" << endl;
  i++;

  for(; !lineas[i].empty(); i++){
    cout << lineas[i] << endl;
  }

  cout << "HUMIDITY TO LOCATION" << endl;
  i++;

  for(; !lineas[i].empty(); i++){
    cout << lineas[i] << endl;
  }


  return 0;
}
