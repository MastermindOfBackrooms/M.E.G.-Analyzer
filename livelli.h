#ifndef LIVELLI_H
#define LIVELLI_H

#include <string>
#include <vector>
#include <map>
#include "entita.h"

class Zona {
public:
    std::string nome;
    std::string descrizione;
    bool esplorata;
    std::vector<std::string> uscite;
    std::vector<std::string> oggetti;
    std::vector<std::string> indizi;
    float pericolo;
    bool illuminata;
    bool sicura;
};

class Livello {
private:
    std::string nome;
    std::string descrizione;
    int difficolta;
    std::map<std::string, Zona> mappa;
    std::map<std::string, float> modificatori_entita;
    std::vector<std::string> caratteristiche_ambientali;
    bool generato;
    float livello_anomalia;

public:
    Livello(std::string n, std::string d, int diff);
    void creaZone();
    void setModificatori();
    float getModificatoreEntita(std::string nome_entita);
    Zona& getZona(std::string nome_zona);
    std::vector<std::string> getZoneAdiacenti(std::string zona_attuale);
    float getModificatoreAmbientale() const;
    std::vector<std::string> getIndiziZona(const std::string& zona);
    bool isZonaSicura(const std::string& zona);
    void aggiornaStatoZona(const std::string& zona, bool sicura);
    float getLivelloAnomalia() const;
    void aumentaAnomalia(float amount);
    void diminuisciAnomalia(float amount);
    bool isGenerato() const;
    void rigeneraZone();
};

#endif
