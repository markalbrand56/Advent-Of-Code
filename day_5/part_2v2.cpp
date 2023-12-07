#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
#include <mutex>
#include <thread>

using namespace std;

mutex lowest_location_mutex;

long long convert_range(const vector<string> &range, long long num){
  	long long result = num;
	for(const auto& line: range){
		// DST | SRC | RANGE
		long long dst, src, rge = 0;
		istringstream stream(line);

		stream >> dst >> src >> rge;

		if(num >= src && num <= src + rge){
			result = dst + (num - src);
			break;
		}
	}

	return result;
}

void process_seeds_range(const vector<string> &seed_soil,
						 const vector<string> &soil_fertilizer,
						 const vector<string> &fertilizer_water,
						 const vector<string> &water_light,
						 const vector<string> &light_temp,
						 const vector<string> &temp_humidity,
						 const vector<string> &humidity_location,
						 const vector<long long> &seeds,
						 int start, int end, long long &lowest_location) {
	for (int h = start; h < end; h += 2) {
		long long num = seeds[h];
		long long range = seeds[h + 1];

		for (long long j = num; j < num + range; j++) {
			long long soil = convert_range(seed_soil, j);
			long long fertilizer = convert_range(soil_fertilizer, soil);
			long long water = convert_range(fertilizer_water, fertilizer);
			long long light = convert_range(water_light, water);
			long long temp = convert_range(light_temp, light);
			long long humidity = convert_range(temp_humidity, temp);
			long long location = convert_range(humidity_location, humidity);

			// Proteger la actualización de lowest_location con un mutex
			std::lock_guard<std::mutex> lock(lowest_location_mutex);
			if (location < lowest_location) {
				lowest_location = location;
			}
		}
	}
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
	vector<long long> seeds;

	long long numero;
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

	cout << "SOIL TO FERTILIZER" << endl;
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

	for(; !lineas[i].empty() && i < lineas.size(); i++){
		string linea_actual = lineas[i];

		if (!linea_actual.empty()){
			cout << lineas[i] << endl;
			humidity_location.push_back(lineas[i]);
		}
	}

	long long lowest_location = numeric_limits<long long>::max();
	const int num_threads = 6;
	vector<thread> threads;

	for (int t = 0; t < num_threads; ++t) {
		long long start = (t * seeds.size()) / num_threads;
		long long end = ((t + 1) * seeds.size()) / num_threads;
		threads.emplace_back(process_seeds_range, ref(seed_soil), ref(soil_fertilizer),
							 ref(fertilizer_water), ref(water_light), ref(light_temp),
							 ref(temp_humidity), ref(humidity_location), ref(seeds),
							 start, end, ref(lowest_location));
	}

	// Esperar a que todos los hilos finalicen
	for (auto &thread : threads) {
		thread.join();
	}

	cout << "Lowest location: " << lowest_location << endl;

	return 0;
}