use std::collections::HashMap;
use std::fs;
use itertools::Itertools;

#[derive(Debug, Clone)]
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

#[derive(Debug, Clone)]
struct Hand {
    hand: String,
    bet: i32,
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
}

pub fn part_2(){
    println!("Part 2");
    let order = HashMap::from([
        ('A', 14),
        ('K', 13),
        ('Q', 12),
        ('J', 11),
        ('T', 10),
        ('9', 9),
        ('8', 8),
        ('7', 7),
        ('6', 6),
        ('5', 5),
        ('4', 4),
        ('3', 3),
        ('2', 2),
        ('1', 1),
    ]);

    let contents = fs::read_to_string("src/input.txt")
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
                type_hand: HandType::None,
            };
            h.determine_hand_type();
            hands.push(h);
        }
    }

    let mut ranked_hands: HashMap<i32, Hand> = HashMap::new();
    let mut five_of_kinds = Vec::new();
    let mut four_of_kinds = Vec::new();
    let mut full_houses = Vec::new();
    let mut three_of_kinds = Vec::new();
    let mut two_pairs = Vec::new();
    let mut one_pairs = Vec::new();
    let mut highs = Vec::new();

    for hand in &hands {
        // println!("{} {} {:?}", hand.hand, hand.bet, hand.type_hand);
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

    /*
    If two hands have the same type, a second ordering rule takes effect. Start by comparing the
    first card in each hand. If these cards are different, the hand with the stronger first card
    is considered stronger. If the first card in each hand have the same label, however, then move
    on to considering the second card in each hand. If they differ, the hand with the higher second
    card wins; otherwise, continue with the third card in each hand, then the fourth, then the fifth.
    */

    // Highs
    highs.sort_by(|a, b| {
        for i in 0..5 {
            let a_value = *order.get(&a.hand.chars().nth(i).unwrap()).unwrap_or(&0);
            let b_value = *order.get(&b.hand.chars().nth(i).unwrap()).unwrap_or(&0);

            let comparison = a_value.cmp(&b_value);
            if comparison != std::cmp::Ordering::Equal {
                return comparison;
            }
        }
        return std::cmp::Ordering::Equal;
    });

    // Assign rank to each hand
    for hand in highs {
        rank += 1;
        ranked_hands.insert(rank, hand.clone());
    }

    // One pair
    one_pairs.sort_by(|a, b| {
        for i in 0..5 {
            let a_value = *order.get(&a.hand.chars().nth(i).unwrap()).unwrap_or(&0);
            let b_value = *order.get(&b.hand.chars().nth(i).unwrap()).unwrap_or(&0);

            let comparison = a_value.cmp(&b_value);
            if comparison != std::cmp::Ordering::Equal {
                return comparison;
            }
        }
        return std::cmp::Ordering::Equal;
    });

    // Assign rank to each hand
    for hand in one_pairs {
        rank += 1;
        ranked_hands.insert(rank, hand.clone());
    }

    // Two pair
    two_pairs.sort_by(|a, b| {
        for i in 0..5 {
            let a_value = *order.get(&a.hand.chars().nth(i).unwrap()).unwrap_or(&0);
            let b_value = *order.get(&b.hand.chars().nth(i).unwrap()).unwrap_or(&0);

            let comparison = a_value.cmp(&b_value);
            if comparison != std::cmp::Ordering::Equal {
                return comparison;
            }
        }
        return std::cmp::Ordering::Equal;
    });

    // Assign rank to each hand
    for hand in two_pairs {
        rank += 1;
        ranked_hands.insert(rank, hand.clone());
    }

    // Three of a kind
    three_of_kinds.sort_by(|a, b| {
        for i in 0..5 {
            let a_value = *order.get(&a.hand.chars().nth(i).unwrap()).unwrap_or(&0);
            let b_value = *order.get(&b.hand.chars().nth(i).unwrap()).unwrap_or(&0);

            let comparison = a_value.cmp(&b_value);
            if comparison != std::cmp::Ordering::Equal {
                return comparison;
            }
        }
        return std::cmp::Ordering::Equal;
    });

    // Assign rank to each hand
    for hand in three_of_kinds {
        rank += 1;
        ranked_hands.insert(rank, hand.clone());
    }

    // Full house
    full_houses.sort_by(|a, b| {
        for i in 0..5 {
            let a_value = *order.get(&a.hand.chars().nth(i).unwrap()).unwrap_or(&0);
            let b_value = *order.get(&b.hand.chars().nth(i).unwrap()).unwrap_or(&0);

            let comparison = a_value.cmp(&b_value);
            if comparison != std::cmp::Ordering::Equal {
                return comparison;
            }
        }
        return std::cmp::Ordering::Equal;
    });

    // Assign rank to each hand
    for hand in full_houses {
        rank += 1;
        ranked_hands.insert(rank, hand.clone());
    }

    // Four of a kind
    four_of_kinds.sort_by(|a, b| {
        for i in 0..5 {
            let a_value = *order.get(&a.hand.chars().nth(i).unwrap()).unwrap_or(&0);
            let b_value = *order.get(&b.hand.chars().nth(i).unwrap()).unwrap_or(&0);

            let comparison = a_value.cmp(&b_value);
            if comparison != std::cmp::Ordering::Equal {
                return comparison;
            }
        }
        return std::cmp::Ordering::Equal;
    });

    // Assign rank to each hand
    for hand in four_of_kinds {
        rank += 1;
        ranked_hands.insert(rank, hand.clone());
    }

    // Five of a kind
    five_of_kinds.sort_by(|a, b| {
        // Compare the hand
        let a_values: Vec<i32> = a.hand.chars().map(|c| *order.get(&c).unwrap_or(&0)).collect();
        let b_values: Vec<i32> = b.hand.chars().map(|c| *order.get(&c).unwrap_or(&0)).collect();
        a_values.cmp(&b_values)
    });

    // Assign rank to each hand
    for hand in five_of_kinds {
        rank += 1;
        ranked_hands.insert(rank, hand.clone());
    }

    // Calculate winnings
    let mut winnings: i64 = 0;
    for key in ranked_hands.keys().sorted() {
        let hand = ranked_hands.get(key).unwrap();
        println!("{key} {} {} {:?}", hand.hand, hand.bet, hand.type_hand);
        winnings += (key * hand.bet) as i64;
    }

    println!("Winnings: {winnings}")
}