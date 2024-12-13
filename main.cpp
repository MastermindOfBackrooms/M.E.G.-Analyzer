#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <map>
#include <random>
#include "entita.h"
#include "livelli.h"

class Giocatore {
private:
    std::string posizione;
    int salute;
    std::vector<std::string> inventario;
    std::vector<std::string> indizi;
    std::string arma;
    bool nascosto;
    int livello_allerta;
    bool entita_identificata;
    ClasseInvestigatore classe;
    int exp;
    int livello;

public:
    Giocatore() : salute(100), nascosto(false), livello_allerta(0), 
                  entita_identificata(false), exp(0), livello(1) {
        posizione = "Reception Principale"; // Posizione iniziale
    }
    
    // Getters
    std::string getPosizione() const { return posizione; }
    int getSalute() const { return salute; }
    std::vector<std::string> getIndizi() const { return indizi; }
    std::string getArma() const { return arma; }
    bool isNascosto() const { return nascosto; }
    int getLivelloAllerta() const { return livello_allerta; }
    bool haIdentificatoEntita() const { return entita_identificata; }
    
    // Setters
    void setPosizione(std::string pos) { posizione = pos; }
    void setArma(std::string a) { arma = a; }
    void setNascosto(bool n) { nascosto = n; }
    void setEntitaIdentificata(bool id) { entita_identificata = id; }
    void setClasse(ClasseInvestigatore c) { classe = c; }
    
    // Gameplay methods
    void danneggia(int danno) { 
        salute = std::max(0, salute - danno);
    }
    
    void cura(int amount) {
        salute = std::min(100, salute + amount);
    }
    
    void aggiungiIndizio(std::string indizio) {
        indizi.push_back(indizio);
    }
    
    void aggiungiOggetto(std::string oggetto) {
        inventario.push_back(oggetto);
    }
    
    bool hasOggetto(std::string oggetto) {
        return std::find(inventario.begin(), inventario.end(), oggetto) != inventario.end();
    }
    
    void aumentaAllerta() {
        livello_allerta = std::min(livello_allerta + 1, 10);
    }
    
    void diminuisciAllerta() {
        livello_allerta = std::max(livello_allerta - 1, 0);
    }
    
    bool verificaIndizi(const Entita& entita) {
        int indizi_corretti = 0;
        for(const auto& indizio : indizi) {
            if(std::find(entita.getIndizi().begin(), entita.getIndizi().end(), indizio) != entita.getIndizi().end()) {
                indizi_corretti++;
            }
        }
        return indizi_corretti >= 3;
    }
    
    void guadagnaExp(int amount) {
        exp += amount;
        while(exp >= livello * 1000) {
            levelUp();
        }
    }
    
    void levelUp() {
        exp -= livello * 1000;
        livello++;
    }
};

class Gioco {
private:
    Giocatore giocatore;
    Livello* livello_corrente;
    Entita* entita_corrente;
    bool gioco_attivo;
    
    std::vector<std::string> armi_disponibili = {
        "UV_TORCH - Torcia UV tattica M.E.G.",
        "MEG_TASER - Taser ad alto voltaggio",
        "SOUND_CANNON - Cannone sonico sperimentale",
        "REALITY_ANCHOR - Ancora di realtà portatile",
        "QUANTUM_DESTABILIZER - Destabilizzatore quantico"
    };

    void gestisciMovimento() {
        std::cout << "\nZone disponibili:\n";
        auto zone_adiacenti = livello_corrente->getZoneAdiacenti(giocatore.getPosizione());
        
        for(int i = 0; i < zone_adiacenti.size(); i++) {
            std::cout << i+1 << ". " << zone_adiacenti[i] << "\n";
        }
        
        std::cout << "Scegli dove muoverti (0 per annullare): ";
        int scelta;
        std::cin >> scelta;
        
        if(scelta > 0 && scelta <= zone_adiacenti.size()) {
            giocatore.setPosizione(zone_adiacenti[scelta-1]);
            std::cout << "\nTi sei spostato in: " << zone_adiacenti[scelta-1] << "\n";
        }
    }

    void gestisciRicerca() {
        Zona& zona_attuale = livello_corrente->getZona(giocatore.getPosizione());
        std::cout << "\nOggetti trovati:\n";
        for(const auto& oggetto : zona_attuale.oggetti) {
            std::cout << "- " << oggetto << "\n";
        }
        std::cout << "\nIndizi trovati:\n";
        for(const auto& indizio : zona_attuale.indizi) {
            std::cout << "- " << indizio << "\n";
            giocatore.aggiungiIndizio(indizio);
        }
    }

    void gestisciNascondino() {
        giocatore.setNascosto(!giocatore.isNascosto());
        std::cout << "\nStato nascosto: " << (giocatore.isNascosto() ? "Sì" : "No") << "\n";
    }

    void gestisciCombattimento() {
        if(entita_corrente->isNellaZona(giocatore.getPosizione())) {
            std::cout << "\nCombattimento con " << entita_corrente->getNome() << "!\n";
            bool colpito = entita_corrente->reagisciAArma(giocatore.getArma());
            if(colpito) {
                std::cout << "Hai colpito l'entità!\n";
                entita_corrente->danneggia(20);
            } else {
                std::cout << "L'entità evita l'attacco!\n";
                giocatore.danneggia(entita_corrente->attacca());
            }
        } else {
            std::cout << "\nNessuna entità presente in questa zona.\n";
        }
    }

public:
    void inizializzaGioco() {
        mostraIntro();
        selezionaDifficolta();
        selezionaClasse();
        selezionaEquipaggiamento();
        selezionaLivello();
        gioco_attivo = true;
    }

    void mostraIntro() {
        std::cout << "\n=== M.E.G. FIELD INVESTIGATION SYSTEM v1.0 ===\n";
        std::cout << "Developed by Jashin L.\n";
        std::cout << "Welcome, Agent. System initialization...\n\n";
    }

    void selezionaDifficolta() {
        std::cout << "\nSeleziona difficoltà:\n";
        std::cout << "1. ROOKIE - Per iniziare l'avventura\n";
        std::cout << "2. STANDARD - Esperienza bilanciata\n";
        std::cout << "3. VETERAN - Per agenti esperti\n";
        std::cout << "4. NIGHTMARE - Sfida intensa\n";
        std::cout << "5. IMPOSSIBLE - Solo per i migliori\n";
        
        int scelta;
        std::cin >> scelta;
    }

    void selezionaClasse() {
        std::cout << "\nSeleziona classe:\n";
        std::cout << "1. ANALISTA - Esperto nell'analisi degli indizi\n";
        std::cout << "2. COMBATTENTE - Specialista nel combattimento\n";
        std::cout << "3. SOPRAVVISSUTO - Maggiore resistenza\n";
        std::cout << "4. TECNICO - Abile con gli strumenti\n";
        std::cout << "5. INFILTRATO - Esperto nel nascondersi\n";
        
        int scelta;
        std::cin >> scelta;
        giocatore.setClasse(static_cast<ClasseInvestigatore>(scelta - 1));
    }

    void selezionaEquipaggiamento() {
        std::cout << "\nSeleziona equipaggiamento:\n";
        for(int i = 0; i < armi_disponibili.size(); i++) {
            std::cout << i+1 << ". " << armi_disponibili[i] << "\n";
        }
        
        int scelta;
        std::cin >> scelta;
        giocatore.setArma(armi_disponibili[scelta-1]);
    }

    void selezionaLivello() {
        std::cout << "\nSeleziona livello:\n";
        std::cout << "1. Level 0 - The Lobby\n";
        std::cout << "2. Level 1 - The Warehouse\n";
        std::cout << "3. Level 2 - The Pipe Dreams\n";
        
        int scelta;
        std::cin >> scelta;
        
        switch(scelta) {
            case 1: livello_corrente = new Livello("Level 0", "The Lobby", 1); break;
            case 2: livello_corrente = new Livello("Level 1", "The Warehouse", 2); break;
            case 3: livello_corrente = new Livello("Level 2", "The Pipe Dreams", 3); break;
        }

        std::vector<Entita> pool_entita = creaEntita();
        entita_corrente = new Entita(selezionaEntitaCasuale(pool_entita));
    }

    void loopGioco() {
        while(gioco_attivo && giocatore.getSalute() > 0) {
            mostraStatoGioco();
            gestisciInput();
            aggiornaSituazione();
        }
        terminaGioco();
    }

    void mostraStatoGioco() {
        std::cout << "\n=== STATO ATTUALE ===\n";
        std::cout << "Posizione: " << giocatore.getPosizione() << "\n";
        std::cout << "Salute: " << giocatore.getSalute() << "\n";
        std::cout << "Arma: " << giocatore.getArma() << "\n";
        std::cout << "Nascosto: " << (giocatore.isNascosto() ? "Sì" : "No") << "\n";
        std::cout << "==================\n";
    }

    void gestisciInput() {
        std::cout << "\nCosa vuoi fare?\n";
        std::cout << "1. Muovi\n2. Cerca\n3. Nascondi\n4. Combatti\n5. Usa oggetto\n6. Esci\n";
        
        int scelta;
        std::cin >> scelta;
        
        switch(scelta) {
            case 1: gestisciMovimento(); break;
            case 2: gestisciRicerca(); break;
            case 3: gestisciNascondino(); break;
            case 4: gestisciCombattimento(); break;
            case 5: // TODO: implementa usa oggetto
                    break;
            case 6: gioco_attivo = false; break;
        }
    }

    void aggiornaSituazione() {
        if(entita_corrente->isNellaZona(giocatore.getPosizione()) && !giocatore.isNascosto()) {
            std::cout << "\nATTENZIONE: " << entita_corrente->getNome() << " è presente in questa zona!\n";
            giocatore.aumentaAllerta();
        }
    }

    void terminaGioco() {
        delete livello_corrente;
        delete entita_corrente;
        std::cout << "\nGame Over\n";
    }
};

int main() {
    Gioco gioco;
    gioco.inizializzaGioco();
    gioco.loopGioco();
    return 0;
}
