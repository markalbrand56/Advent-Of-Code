#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>
#include <thread>
using namespace std;

map<long long, long long> build_map(const vector<string> &vec) {
  map<long long, long long> range;

  int x = 1;
  for(const auto& line: vec){
    // DST | SRC | RANGE
    long long dst, src, rge = 0;
    istringstream stream(line);

    stream >> dst >> src >> rge;

    cout << "line " << x << "/" << vec.size() << " dst " << dst << " src " << src << " rge " << rge << endl;

    for (long long i = 0; i < rge; i++){
      range[src] = dst;
      //cout << src << "->" << dst << endl;
      src++;
      dst++;
    }
	x++;
  }


  return range;
}

void build_map_thread(const vector<string> &vec, map<long long, long long>& result_map) {
    result_map = build_map(vec);
}

int main() {
  cout << "Hello World" << endl;

  
  ifstream file("input.txt");

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
    map<long long, long long> r_seed_soil;
    map<long long, long long> r_soil_fertilizer;
    map<long long, long long> r_fertilizer_water;
    map<long long, long long> r_water_light;
    map<long long, long long> r_light_temp;
    map<long long, long long> r_temp_humidity;
    map<long long, long long> r_humidity_location;

    std::thread t1(build_map_thread, seed_soil, std::ref(r_seed_soil));
    std::thread t2(build_map_thread, soil_fertilizer, std::ref(r_soil_fertilizer));
    std::thread t3(build_map_thread, fertilizer_water, std::ref(r_fertilizer_water));
    std::thread t4(build_map_thread, water_light, std::ref(r_water_light));
    std::thread t5(build_map_thread, light_temp, std::ref(r_light_temp));
    std::thread t6(build_map_thread, temp_humidity, std::ref(r_temp_humidity));
    std::thread t7(build_map_thread, humidity_location, std::ref(r_humidity_location));

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();

  vector<long long> results;

  for (const auto& num: seeds){
    long long soil;
    long long fertilizer;
    long long water;
    long long light;
    long long temp;
    long long humidity;
    long long location;

    soil = (r_seed_soil.count(num) > 0) ? r_seed_soil[num] : num;
    fertilizer = (r_soil_fertilizer.count(soil) > 0) ? r_soil_fertilizer[soil] : soil;
    water = (r_fertilizer_water.count(fertilizer) > 0) ? r_fertilizer_water[fertilizer] : fertilizer;
    light = (r_water_light.count(water) > 0) ? r_water_light[water] : water;
    temp = (r_light_temp.count(light) > 0) ? r_light_temp[light] : light;
    humidity = (r_temp_humidity.count(temp) > 0) ? r_temp_humidity[temp] : temp;
    location = (r_humidity_location.count(humidity) > 0) ? r_humidity_location[humidity] : humidity;

    //cout << "seed " << num << " soil " << soil << " fertilizer " << fertilizer << " water " << water << " light " << light << " temp " << temp << " humidity " << humidity <<
    //" location " << location << endl;

    results.push_back(location);
}

  auto min = min_element(results.begin(), results.end());

  cout << "Lowest location: " << *min << endl;

  return 0;
}
