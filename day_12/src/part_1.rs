use std::collections::HashMap;
use std::fs;

pub fn part_1(){
    println!("Part 1");

    let contents = fs::read_to_string("sample.txt")
        .expect("Something went wrong reading the file");

    let lines = contents.lines();
    let mut records: HashMap<&str, Vec<u32>> = HashMap::new();

    for line in lines {
        let data: Vec<&str> = line.split_whitespace().collect();
        let key = data[0];
        let values = data[1].split(",").map(|x| x.parse::<u32>().unwrap()).collect();
        records.insert(key, values);
    }

    for record in records.keys() {
        let groups = records.get(record).unwrap();
        println!("'{}': '{:?}'", record, groups);

        // ???.### 1,1,3

        let mut data = record.clone();
        let mut arranged = false;

        while !arranged {
            let mut splits: Vec<&str> = data
                .split(".").collect()
                .retain(|&x| x != "");

            println!("splits: {:?}", splits);

            if (splits.len() == groups.len()){
                arranged = true;
                continue;
            }

            for i in 0..groups.len(){
                // En cada grupo, ya se quitaron todos los '.'
                // Los vectores dentro de splits siempre estarán separados
                // Si en splits[0] cabe groups[0] (por longitud)
                    // modificar
            }


        }
    }
}