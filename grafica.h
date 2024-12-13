#ifndef GRAFICA_H
#define GRAFICA_H

#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <iostream>
#include <map>

class SistemaGrafico {
private:
    std::map<std::string, std::string> mappe;
    bool colori_attivi;
    
    void inizializzaMappe();
    std::string coloraStringa(const std::string& testo, int colore);

public:
    SistemaGrafico() : colori_attivi(true) {
        inizializzaMappe();
    }
    
    void mostraCaricamento(const std::string& messaggio);
    void mostraMappa(const std::string& livello);
    void animazioneAttacco();
    void animazioneMovimento();
    void animazioneRicerca();
    void animazioneNascondino();
    void animazioneEntita();
    void pulisciSchermo();
    void mostraLogo();
    void mostraInterfaccia();
    void mostraMenu();
    void mostraGameOver();
    void mostraVittoria();
    void setColori(bool attivo) { colori_attivi = attivo; }
};

#endif
