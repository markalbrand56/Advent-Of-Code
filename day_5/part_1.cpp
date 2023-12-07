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

    for (int i = 0; i < rge; i++){
      range[src] = dst;
      //cout << src << "->" << dst << endl;
      src++;
      dst++;
    }
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

  // División de líneas
  string seeds_input = lineas[0];  // lineas[1]: ""
  size_t pos = seeds_input.find("seeds: ");
  seeds_input = seeds_input.substr(pos + 7);

  istringstream stream(seeds_input);
  vector<int> seeds;

  int numero;

        // Leer los números de la cadena y almacenarlos en el vector
  while (stream >> numero) {
    seeds.push_back(numero);
  }

  for (const auto& num : seeds) {
    std::cout << "Seed: " << num << endl;
  }


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

  vector<int> results;

  for (const auto& num: seeds){
    int soil;
    int fertilizer;
    int water;
    int light;
    int temp;
    int humidity;
    int location;

    soil = (r_seed_soil.count(num) > 0) ? r_seed_soil[num] : num;
    fertilizer = (r_soil_fertilizer.count(soil) > 0) ? r_soil_fertilizer[soil] : soil;
    water = (r_fertilizer_water.count(fertilizer) > 0) ? r_fertilizer_water[fertilizer] : fertilizer;
    light = (r_water_light.count(water) > 0) ? r_water_light[water] : water;
    temp = (r_light_temp.count(light) > 0) ? r_light_temp[light] : light;
    humidity = (r_temp_humidity.count(temp) > 0) ? r_temp_humidity[temp] : temp;
    location = (r_humidity_location.count(humidity) > 0) ? r_humidity_location[humidity] : humidity;

    cout << "seed " << num << " soil " << soil << " fertilizer " << fertilizer << " water " << water << " light " << light << " temp " << temp << " humidity " << humidity << " location " << location << endl;
  }

  return 0;
}
