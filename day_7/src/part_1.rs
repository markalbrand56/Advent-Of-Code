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

pub fn part_1(){
    println!("Part 1");
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

    // Highs
    highs.sort_by(|a, b| {
        let a_values: Vec<i32> = a.hand.chars().map(|c| *order.get(&c).unwrap_or(&0)).collect();
        let b_values: Vec<i32> = b.hand.chars().map(|c| *order.get(&c).unwrap_or(&0)).collect();
        a_values.cmp(&b_values)
    });

    // Assign rank to each hand
    for hand in highs {
        rank += 1;
        ranked_hands.insert(rank, hand.clone());
    }

    // One pair
    one_pairs.sort_by(|a, b| {
        // find the pair
        let mut a_pair = ' ';
        let mut a_other = ' ';
        let mut b_pair = ' ';
        let mut b_other = ' ';

        let mut counts = HashMap::new();
        for c in a.hand.chars() {
            let counter = counts.entry(c).or_insert(0);
            *counter += 1;
        }
        for (key, value) in &counts {
            if *value == 2 {
                a_pair = *key;
            } else {
                a_other = *key;
            }
        }

        counts = HashMap::new();
        for c in b.hand.chars() {
            let counter = counts.entry(c).or_insert(0);
            *counter += 1;
        }
        for (key, value) in &counts {
            if *value == 2 {
                b_pair = *key;
            } else {
                b_other = *key;
            }
        }

        // compare the pair
        let a_pair_value = *order.get(&a_pair).unwrap_or(&0);
        let b_pair_value = *order.get(&b_pair).unwrap_or(&0);
        let pair_comparison = a_pair_value.cmp(&b_pair_value);
        if pair_comparison != std::cmp::Ordering::Equal {
            return pair_comparison;
        }

        // compare the other cards
        let a_other_value = *order.get(&a_other).unwrap_or(&0);
        let b_other_value = *order.get(&b_other).unwrap_or(&0);
        let other_comparison = a_other_value.cmp(&b_other_value);
        if other_comparison != std::cmp::Ordering::Equal {
            return other_comparison;
        }

        // compare the hand
        let a_values: Vec<i32> = a.hand.chars().map(|c| *order.get(&c).unwrap_or(&0)).collect();
        let b_values: Vec<i32> = b.hand.chars().map(|c| *order.get(&c).unwrap_or(&0)).collect();
        a_values.cmp(&b_values)
    });

    // Assign rank to each hand
    for hand in one_pairs {
        rank += 1;
        ranked_hands.insert(rank, hand.clone());
    }

    // Two pair
    two_pairs.sort_by(|a, b| {
        // so KKQQ3 > KKQQ1 > JJAAK

        let mut a_pair1 = ' ';
        let mut a_pair2 = ' ';
        let mut a_other = ' ';
        let mut b_pair1 = ' ';
        let mut b_pair2 = ' ';
        let mut b_other = ' ';

        let mut counts = HashMap::new();
        for c in a.hand.chars() {
            let counter = counts.entry(c).or_insert(0);
            *counter += 1;
        }
        for (key, value) in &counts {
            if *value == 2 {
                if a_pair1 == ' ' {
                    a_pair1 = *key;
                } else {
                    a_pair2 = *key;
                }
            } else {
                a_other = *key;
            }
        }

        counts = HashMap::new();
        for c in b.hand.chars() {
            let counter = counts.entry(c).or_insert(0);
            *counter += 1;
        }
        for (key, value) in &counts {
            if *value == 2 {
                if b_pair1 == ' ' {
                    b_pair1 = *key;
                } else {
                    b_pair2 = *key;
                }
            } else {
                b_other = *key;
            }
        }

        // compare the pairs
        let a_pair1_value = *order.get(&a_pair1).unwrap_or(&0);
        let a_pair2_value = *order.get(&a_pair2).unwrap_or(&0);
        let b_pair1_value = *order.get(&b_pair1).unwrap_or(&0);
        let b_pair2_value = *order.get(&b_pair2).unwrap_or(&0);

        let a_higher = if a_pair1_value > a_pair2_value { a_pair1_value } else { a_pair2_value };  // Find the higher pair
        let b_higher = if b_pair1_value > b_pair2_value { b_pair1_value } else { b_pair2_value };  // Find the higher pair

        let pair_comparison = a_higher.cmp(&b_higher);
        if pair_comparison != std::cmp::Ordering::Equal {
            return pair_comparison;
        } else {  // If the higher pairs are equal, compare the lower pairs
            let a_lower = if a_pair1_value < a_pair2_value { a_pair1_value } else { a_pair2_value };
            let b_lower = if b_pair1_value < b_pair2_value { b_pair1_value } else { b_pair2_value };

            let pair_comparison = a_lower.cmp(&b_lower);
            if pair_comparison != std::cmp::Ordering::Equal {
                return pair_comparison;
            }
        }

        // if both pairs are equal, compare the other card
        let a_other_value = *order.get(&a_other).unwrap_or(&0);
        let b_other_value = *order.get(&b_other).unwrap_or(&0);
        let other_comparison = a_other_value.cmp(&b_other_value);

        if other_comparison != std::cmp::Ordering::Equal {
            return other_comparison;
        }

        // compare the hand
        let a_values: Vec<i32> = a.hand.chars().map(|c| *order.get(&c).unwrap_or(&0)).collect();
        let b_values: Vec<i32> = b.hand.chars().map(|c| *order.get(&c).unwrap_or(&0)).collect();
        a_values.cmp(&b_values)
    });

    // Assign rank to each hand
    for hand in two_pairs {
        rank += 1;
        ranked_hands.insert(rank, hand.clone());
    }

    // Three of a kind
    three_of_kinds.sort_by(|a, b| {
        // Find the three of a kind and the other cards
        let mut a_three = ' ';
        let mut a_other1 = ' ';
        let mut a_other2 = ' ';
        let mut b_three = ' ';
        let mut b_other1 = ' ';
        let mut b_other2 = ' ';

        let mut counts = HashMap::new();
        for c in a.hand.chars() {
            let counter = counts.entry(c).or_insert(0);
            *counter += 1;
        }
        for (key, value) in &counts {
            if *value == 3 {
                a_three = *key;
            } else {
                if a_other1 == ' ' {
                    a_other1 = *key;
                } else {
                    a_other2 = *key;
                }
            }
        }

        counts = HashMap::new();
        for c in b.hand.chars() {
            let counter = counts.entry(c).or_insert(0);
            *counter += 1;
        }
        for (key, value) in &counts {
            if *value == 3 {
                b_three = *key;
            } else {
                if b_other1 == ' ' {
                    b_other1 = *key;
                } else {
                    b_other2 = *key;
                }
            }
        }

        // Compare the three of a kind
        let three_comparison = compare_cards(a_three, b_three);
        if three_comparison != std::cmp::Ordering::Equal {
            return three_comparison;
        }

        // Compare the other cards
        let a_other1_value = *order.get(&a_other1).unwrap_or(&0);
        let a_other2_value = *order.get(&a_other2).unwrap_or(&0);
        let b_other1_value = *order.get(&b_other1).unwrap_or(&0);
        let b_other2_value = *order.get(&b_other2).unwrap_or(&0);

        let a_other_comparison = a_other1_value.cmp(&a_other2_value);
        let b_other_comparison = b_other1_value.cmp(&b_other2_value);

        if a_other_comparison != std::cmp::Ordering::Equal {
            return a_other_comparison;
        }
        if b_other_comparison != std::cmp::Ordering::Equal {
            return b_other_comparison;
        }

        // Compare the hand
        let a_values: Vec<i32> = a.hand.chars().map(|c| *order.get(&c).unwrap_or(&0)).collect();
        let b_values: Vec<i32> = b.hand.chars().map(|c| *order.get(&c).unwrap_or(&0)).collect();
        a_values.cmp(&b_values)
    });

    // Assign rank to each hand
    for hand in three_of_kinds {
        rank += 1;
        ranked_hands.insert(rank, hand.clone());
    }

    // Full house
    full_houses.sort_by(|a, b| {
        // Find the three of a kind and the pair
        let mut a_three = ' ';
        let mut a_pair = ' ';
        let mut b_three = ' ';
        let mut b_pair = ' ';

        let mut counts = HashMap::new();
        for c in a.hand.chars() {
            let counter = counts.entry(c).or_insert(0);
            *counter += 1;
        }
        for (key, value) in &counts {
            if *value == 3 {
                a_three = *key;
            } else {
                a_pair = *key;
            }
        }

        counts = HashMap::new();
        for c in b.hand.chars() {
            let counter = counts.entry(c).or_insert(0);
            *counter += 1;
        }
        for (key, value) in &counts {
            if *value == 3 {
                b_three = *key;
            } else {
                b_pair = *key;
            }
        }

        // Compare the three of a kind
        let three_comparison = compare_cards(a_three, b_three);
        if three_comparison != std::cmp::Ordering::Equal {
            return three_comparison;
        }

        // Compare the pair
        compare_cards(a_pair, b_pair)
    });

    // Assign rank to each hand
    for hand in full_houses {
        rank += 1;
        ranked_hands.insert(rank, hand.clone());
    }

    // Four of a kind
    four_of_kinds.sort_by(|a, b| {
        // Find the four of a kind and the other card
        let mut a_four = ' ';
        let mut a_other = ' ';
        let mut b_four = ' ';
        let mut b_other = ' ';

        let mut counts = HashMap::new();
        for c in a.hand.chars() {
            let counter = counts.entry(c).or_insert(0);
            *counter += 1;
        }
        for (key, value) in &counts {
            if *value == 4 {
                a_four = *key;
            } else {
                a_other = *key;
            }
        }

        counts = HashMap::new();
        for c in b.hand.chars() {
            let counter = counts.entry(c).or_insert(0);
            *counter += 1;
        }
        for (key, value) in &counts {
            if *value == 4 {
                b_four = *key;
            } else {
                b_other = *key;
            }
        }

        // Compare the four of a kind
        let four_comparison = compare_cards(a_four, b_four);
        if four_comparison != std::cmp::Ordering::Equal {
            return four_comparison;
        }

        // Compare the other card
        compare_cards(a_other, b_other)
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

    // print key, value of ranked_hands
    for key in ranked_hands.keys().sorted() {
        let hand = ranked_hands.get(key).unwrap();
        println!("{key} {} {} {:?}", hand.hand, hand.bet, hand.type_hand);

    }
}

fn find_pairs(hand: &String) -> (char, char) {
    let mut counts = HashMap::new();
    let mut pair1 = ' ';
    let mut pair2 = ' ';

    for c in hand.chars() {
        let counter = counts.entry(c).or_insert(0);
        *counter += 1;
    }

    for (key, value) in &counts {
        if *value == 2 {
            if pair1 == ' ' {
                pair1 = *key;
            } else {
                pair2 = *key;
            }
        }
    }

    (pair1, pair2)
}

// Function to find the remaining card in a hand
fn find_remaining_card(hand: &String, pair1: char, pair2: char) -> char {
    for c in hand.chars() {
        if c != pair1 && c != pair2 {
            return c;
        }
    }
    ' '
}

// Function to compare cards based on their rank
fn compare_cards(card1: char, card2: char) -> std::cmp::Ordering {
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

    let value1 = *order.get(&card1).unwrap_or(&0);
    let value2 = *order.get(&card2).unwrap_or(&0);

    value1.cmp(&value2)
}