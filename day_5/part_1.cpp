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
        std::cout << l << std::endl;
  }

  return 0;
}
