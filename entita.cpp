#include "entita.h"
#include <random>
#include <algorithm>

Entita::Entita(std::string n, std::string d, int p, bool kill, std::string arma) {
    nome = n;
    descrizione = d;
    pericolosita = p;
    puo_essere_uccisa = kill;
    arma_efficace = arma;
    livello_aggressivita = 0;
    intelligenza = 0;
    caccia_attiva = false;
    pazienza = 100;
    salute = 100;
}

void Entita::setComportamento(int situazione) {
    if(situazione < comportamenti.size()) {
        std::cout << nome << ": " << comportamenti[situazione] << "\n";
    }
}

bool Entita::reagisciAArma(std::string arma) {
    if(arma == arma_efficace) {
        livello_aggressivita += 30;
        return true;
    }
    livello_aggressivita += 10;
    return false;
}

void Entita::updateAI(std::string azione_giocatore) {
    int mod_agg = calcolaAggressivita(azione_giocatore);
    livello_aggressivita = std::clamp(livello_aggressivita + mod_agg, 0, 100);
    
    if(azione_giocatore == "corri") {
        caccia_attiva = true;
        pazienza -= 15;
    } else if(azione_giocatore == "nascondi") {
        pazienza -= 10;
    } else if(azione_giocatore == "osserva") {
        pazienza += 5;
    }
}

int Entita::calcolaAggressivita(std::string azione_giocatore) {
    if(azione_giocatore == "attacca") return 25;
    if(azione_giocatore == "corri") return 20;
    if(azione_giocatore == "nascondi") return -10;
    if(azione_giocatore == "osserva") return -5;
    return 0;
}

bool Entita::decidiAttacco() {
    return (livello_aggressivita > 70 || pazienza < 30 || caccia_attiva);
}

int Entita::attacca() {
    int danno_base = pericolosita * 10;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-5, 5);
    return danno_base + dis(gen);
}

void Entita::individuaGiocatore(std::string pos) {
    posizione_attuale = pos;
    caccia_attiva = true;
    livello_aggressivita += 15;
}

void Entita::rivelaPresenza() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, comportamenti.size() - 1);
    setComportamento(dis(gen));
}

std::vector<Entita> creaEntita() {
    std::vector<Entita> entita;
    
    // Creazione delle entità base
    entita.push_back(Entita("Smiler", "Entità umanoide con sorriso innaturale", 7, true, "UV_TORCH"));
    entita.push_back(Entita("Hound", "Creatura canide con comportamenti anomali", 5, true, "MEG_TASER"));
    entita.push_back(Entita("Bacteria", "Colonia batterica senziente", 3, true, "SOUND_CANNON"));
    entita.push_back(Entita("Static Dancer", "Figura umanoide che si muove a scatti", 6, true, "REALITY_ANCHOR"));
    entita.push_back(Entita("Window Walker", "Entità che si muove attraverso i riflessi", 8, true, "QUANTUM_DESTABILIZER"));
    
    return entita;
}

Entita selezionaEntitaCasuale(std::vector<Entita>& pool) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, pool.size() - 1);
    return pool[dis(gen)];
}
