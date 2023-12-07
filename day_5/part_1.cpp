#include <fstream>
#include <iostream>
#include <map>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

map<int, int> build_map(vector<string> &vec) {
  map<int, int> range;

  for(const auto& line: vec){
    // DST | SRC | RANGE
    int dst, src, rge = 0;
    istringstream stream(line);

    stream >> dst >> src >> rge;

    cout << "dst: " << dst << " src: " << src << " range: " << rge << endl;
  }


  return range;
}

int main() {
  cout << "Hello World" << endl;

  
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
  vector<string> seed_soil;
  int i = 3;


  // Seed to soil
  cout << "SEED TO SOIL" << endl;
  for(; !lineas[i].empty(); i++){
    cout << lineas[i] << endl;
    seed_soil.push_back(lineas[i]);
  }

  cout << "SOILD TO FERTILIZER" << endl;
  vector<string> soil_fertilizer;
  i+=2;

  for(; !lineas[i].empty(); i++){
    cout << lineas[i] << endl;
    soil_fertilizer.push_back(lineas[i]);
  }

  cout << "FERTILIZER TO WATER" << endl;
  vector<string> fertilizer_water;
  i+=2;

  for(; !lineas[i].empty(); i++){
    cout << lineas[i] << endl;
    fertilizer_water.push_back(lineas[i]);
  }

  cout << "WATER TO LIGHT" << endl;
  vector<string> water_light;
  i+=2;

  for(; !lineas[i].empty(); i++){
    cout << lineas[i] << endl;
    water_light.push_back(lineas[i]);
  }

  cout << "LIGHT TO TEMP" << endl;
  vector<string> light_temp;
  i+=2;

  for(; !lineas[i].empty(); i++){
    cout << lineas[i] << endl;
    light_temp.push_back(lineas[i]);
  }

  cout << "TEMP TO HUMIDITY" << endl;
  vector<string> temp_humidity;
  i+=2;

  for(; !lineas[i].empty(); i++){
    cout << lineas[i] << endl;
    temp_humidity.push_back(lineas[i]);
  }

  cout << "HUMIDITY TO LOCATION" << endl;
  vector<string> humidity_location;
  i+=2;

  for(; !lineas[i].empty(); i++){
    cout << lineas[i] << endl;
    humidity_location.push_back(lineas[i]);
  }

  // Construir maps
  map<int, int> r_seed_soil = build_map(seed_soil);
  map<int, int> r_soil_fertilizer = build_map(soil_fertilizer);
  map<int, int> r_fertilizer_water = build_map(fertilizer_water);
  map<int, int> r_water_light = build_map(water_light);
  map<int, int> r_light_temp = build_map(light_temp);
  map<int, int> r_temp_humidity = build_map(temp_humidity);
  map<int, int> r_humidity_location = build_map(humidity_location);

  return 0;
}
