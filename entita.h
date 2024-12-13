#ifndef ENTITA_H
#define ENTITA_H

#include <string>
#include <vector>
#include <map>

enum Armi {
    UV_TORCH,
    MEG_TASER,
    SOUND_CANNON,
    REALITY_ANCHOR,
    QUANTUM_DESTABILIZER
};

class Entita {
private:
    std::string nome;
    std::string descrizione;
    int pericolosita;
    bool puo_essere_uccisa;
    std::vector<std::string> indizi;
    std::vector<std::string> comportamenti;
    std::string arma_efficace;
    int livello_aggressivita;
    int intelligenza;
    bool caccia_attiva;
    int pazienza;
    int salute;
    std::string posizione_attuale;

public:
    Entita(std::string n, std::string d, int p, bool kill, std::string arma);
    
    // Getters
    std::string getNome() const { return nome; }
    std::string getDescrizione() const { return descrizione; }
    int getPericolosita() const { return pericolosita; }
    bool getPuoEssereUccisa() const { return puo_essere_uccisa; }
    std::string getArmaEfficace() const { return arma_efficace; }
    std::vector<std::string> getIndizi() const { return indizi; }
    bool isEliminata() const { return salute <= 0; }
    bool isNellaZona(std::string zona) const { return zona == posizione_attuale; }
    
    // Setters
    void setPosizione(std::string nuova_pos) { posizione_attuale = nuova_pos; }
    void aggiungiIndizio(const std::string& indizio) { indizi.push_back(indizio); }
    void aggiungiComportamento(const std::string& comportamento) { comportamenti.push_back(comportamento); }
    
    // Gameplay methods
    void setComportamento(int situazione);
    bool reagisciAArma(std::string arma);
    void updateAI(std::string azione_giocatore);
    int calcolaAggressivita(std::string azione_giocatore);
    bool decidiAttacco();
    void danneggia(int danno) { salute -= danno; }
    int attacca();
    void perdiTraccia() { caccia_attiva = false; }
    void individuaGiocatore(std::string pos);
    void aumentaAggressivita(int amount) { livello_aggressivita += amount; }
    void rivelaPresenza();
};

std::vector<Entita> creaEntita();
Entita selezionaEntitaCasuale(std::vector<Entita>& pool);

#endif
