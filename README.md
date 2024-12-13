# Sistema di Investigazione M.E.G. v1.0

Un gioco testuale horror di investigazione ambientato nell'universo dei Backrooms, dove vesti i panni di un agente M.E.G. (Major Explorer Group) che indaga su entità anomale.

## Caratteristiche

- Diverse classi di personaggi con abilità uniche
- Sistema dinamico di comportamento delle entità 
- Visualizzazione mappe in ASCII
- Sistema di combattimento tattico
- Meccaniche di raccolta indizi
- Meccaniche di furtività
- Livelli di difficoltà multipli
- Varie armi e strumenti
- Incontri generati proceduralmente

  Dipendenze
C++17 o superiore
Libreria Standard
Terminale con supporto colori ANSI

## Installazione

git clone https://github.com/MastermindOfBackrooms/M.E.G.-Analyzer

cd M.E.G.-Analyzer

g++ -std=c++17 main.cpp entita.cpp livelli.cpp grafica.cpp -o meg_game

./meg_game
