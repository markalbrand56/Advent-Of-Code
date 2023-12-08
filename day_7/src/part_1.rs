use std::fs;

struct Hand {
    hand: String,
    bet: i32,
    rank: i32,
    type_hand: i32,
}

pub fn part_1(){
    println!("Part 1");

    let contents = fs::read_to_string("src/sample.txt")
        .expect("Debería abrir el archivo");

    let lines = contents.split("\r\n");
    let mut hands = Vec::new();

    for line in lines {
        let words: Vec<&str> = line.split_whitespace().collect();

        // Asegúrate de que haya al menos dos palabras en la línea
        if words.len() >= 2 {
            let key = words[0];
            let value = words[1].parse::<i32>().unwrap();

            let h = Hand{
                hand: String::from(key),
                bet: value,
                rank: 0,
                type_hand: 0,
            };

            hands.push(h);
        }
    }

    for hand in &hands {
        println!("{} {}", hand.hand, hand.bet)
    }
}