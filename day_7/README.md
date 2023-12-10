# Rust
Este es el primer proyecto que hago con Rust. Hasta el momento lo único que he hecho para aprender Rust ha sido
darle una leída superficial al [libro oficial de Rust](https://doc.rust-lang.org/book/), y hacer un par de ejercicios
como [rustlings](https://github.com/rust-lang/rustlings).

Para este ejericio sí me apoyé bastante de leer la documentación, Copilot y ChatGPT.
Aún así la mayoría de los algoritmos los tuve que hacer a mano sin la ayuda de estas IA,
pero sí me ayudaron enormemente a entender cómo funciona Rust.

Mi objetivo con este evento es reforzar mis habilidades con distintos lengujes de programación,
por lo que mi objetivo es desarrollar los programas aprovechando al máximo las características
del lenguaje, y no tanto el resultado final. Por ejemplo para ordenar los hashmaps mi primera idea
fue usar un algoritmo simple como Merge Sort o Quick Sort iterando sobre los hashmaps, pero
quise intentar usar la función `sort_by` de Rust, que es una manera propia de Rust de ordenar.

Aunque al principio había diseñado mal el programa en el sentido de cómo se debían de 
comparar las cartas (no había leído bien las instrucciones) el algoritmo que desarrollé
(sin ayuda de IA) para ordenar las cartas fue completamente diferente a la manera
en que la hubiera hecho en otros lenguajes. Con este algoritmo exploré bastante este 
funcionamiento en Rust, lo que considero que fue una lección muy valiosa.
```rust
full_houses.sort_by(|a, b| {
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
    let a_pair_value = *order.get(&a_pair).unwrap_or(&0);
    let b_pair_value = *order.get(&b_pair).unwrap_or(&0);
    
    let pair_comparison = a_pair_value.cmp(&b_pair_value);
    return pair_comparison;
});
```