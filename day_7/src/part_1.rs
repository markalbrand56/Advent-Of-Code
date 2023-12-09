use std::collections::HashMap;
use std::fs;

#[derive(Debug)]
enum HandType{
    FiveOfKind,
    FourOfKind,
    FullHouse,
    ThreeOfKind,
    TwoPair,
    OnePair,
    High,
    None,
}

struct Hand {
    hand: String,
    bet: i32,
    rank: i32,
    type_hand: HandType,
}

impl Hand {
    fn determine_hand_type(&mut self) {
        let mut counts = HashMap::new();

        for c in self.hand.chars() {
            let counter = counts.entry(c).or_insert(0); // Si no encuentra ingresa 0
            *counter +=1;
        }

        let max_count = counts.values().cloned().max().unwrap();

        match max_count {
            5 => self.type_hand = HandType::FiveOfKind,
            4 => self.type_hand = HandType::FourOfKind,
            3 => {
                if counts.len() == 2 {
                    self.type_hand = HandType::FullHouse;  // Si solo hay dos cartas, significa que hay un par
                } else {
                    self.type_hand = HandType::ThreeOfKind;  // Si hay más, solo es un trío
                }
            }
            2 => {
                if counts.len() == 3 {
                    self.type_hand = HandType::TwoPair;
                } else {
                    self.type_hand = HandType::OnePair;
                }
            }
            _ => self.type_hand = HandType::High,
        }
    }
    fn set_rank(&mut self, r: i32){
        self.rank = r
    }
}

pub fn part_1(){
    println!("Part 1");
    let order = HashMap::from([
        ("A", 14),
        ("K", 13),
        ("Q", 12),
        ("J", 11),
        ("T", 10),
        ("9", 9),
        ("8", 8),
        ("7", 7),
        ("6", 6),
        ("5", 5),
        ("4", 4),
        ("3", 3),
        ("2", 2),
        ("1", 1)
    ]);

    let contents = fs::read_to_string("src/sample.txt")
        .expect("Debería abrir el archivo");

    let lines = contents.split("\r\n");
    let mut hands = Vec::new();

    for line in lines {
        let words: Vec<&str> = line.split_whitespace().collect();

        if words.len() >= 2 {
            let key = words[0];
            let value = words[1].parse::<i32>().unwrap();

            let mut h = Hand{
                hand: String::from(key),
                bet: value,
                rank: 0,
                type_hand: HandType::None,
            };
            h.determine_hand_type();
            hands.push(h);
        }
    }

    let mut five_of_kinds = Vec::new();
    let mut four_of_kinds = Vec::new();
    let mut full_houses = Vec::new();
    let mut three_of_kinds = Vec::new();
    let mut two_pairs = Vec::new();
    let mut one_pairs = Vec::new();
    let mut highs = Vec::new();

    for hand in &hands {
        println!("{} {} {:?}", hand.hand, hand.bet, hand.type_hand);
        match hand.type_hand {
            HandType::FiveOfKind => five_of_kinds.push(hand),
            HandType::FourOfKind => four_of_kinds.push(hand),
            HandType::FullHouse => full_houses.push(hand),
            HandType::ThreeOfKind => three_of_kinds.push(hand),
            HandType::TwoPair => two_pairs.push(hand),
            HandType::OnePair => one_pairs.push(hand),
            HandType::High => highs.push(hand),
            _ => (),
        }
    }

    let mut rank = 0;  // The strongest hand has the highest rank

    for hand in &mut highs {
        // ordenar las manos de más debil a mas fuerte
        // A > K > Q > ... > 1
    }
}