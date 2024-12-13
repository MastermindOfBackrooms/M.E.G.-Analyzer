#include "livelli.h"
#include <random>
#include <algorithm>
#include <iostream>

Livello::Livello(std::string n, std::string d, int diff) {
    nome = n;
    descrizione = d;
    difficolta = diff;
    generato = false;
    livello_anomalia = 0.0f;
    creaZone();
    setModificatori();
}

void Livello::creaZone() {
    if(nome == "Level 0") {
        // The Lobby - 20 zone
        mappa["Reception Principale"] = {"Reception Principale", "Grande sala con moquette umida e luci fluorescenti", false, 
            {"Corridoio Nord", "Corridoio Est", "Area Relax"}, {"Torcia", "Radio M.E.G."}, {"Impronte umide sul pavimento"}};
        
        mappa["Area Relax"] = {"Area Relax", "Zona con divani ammuffiti e distributori automatici", false,
            {"Reception Principale", "Bagni", "Corridoio Sud"}, {"Snack", "Monete"}, {"Macchie strane sui divani"}};
        
        mappa["Bagni"] = {"Bagni", "File di bagni con specchi incrinati", false,
            {"Area Relax", "Corridoio Manutenzione"}, {"Medicina", "Bende"}, {"Scritte sugli specchi"}};
        
        mappa["Open Space A"] = {"Open Space A", "Vasto spazio con cubicoli infiniti", false,
            {"Corridoio Nord", "Open Space B", "Sala Stampa"}, {"Documenti", "Penna USB"}, {"Computer accesi da soli"}};
        
        mappa["Open Space B"] = {"Open Space B", "Altra area cubicoli con PC spenti", false,
            {"Open Space A", "Sala Riunioni", "Archivio"}, {"Badge", "Caffè"}, {"Email misteriose"}};
        
        mappa["Sala Riunioni"] = {"Sala Riunioni", "Grande tavolo ovale con sedie vuote", false,
            {"Open Space B", "Corridoio Executive"}, {"Proiettore", "Appunti"}, {"Presentazione loop infinito"}};
        
        mappa["Archivio"] = {"Archivio", "File infinite di schedari metallici", false,
            {"Open Space B", "Deposito"}, {"Fascicoli", "Chiave"}, {"Documenti classificati M.E.G."}};
        
        mappa["Sala Server"] = {"Sala Server", "Stanza refrigerata con server ronzanti", false,
            {"Corridoio Tech", "Sala Controllo"}, {"Hard Disk", "Cavi"}, {"Log di sistema anomali"}};
        
        mappa["Sala Controllo"] = {"Sala Controllo", "Pannelli di controllo lampeggianti", false,
            {"Sala Server", "Corridoio Emergenza"}, {"Tablet", "Manuale"}, {"Registrazioni telecamere"}};
        
        mappa["Locale Tecnico"] = {"Locale Tecnico", "Stanza con macchinari elettrici", false,
            {"Corridoio Tech", "Sala UPS"}, {"Attrezzi", "Guanti"}, {"Letture energetiche impossibili"}};
            
        mappa["Corridoio Executive"] = {"Corridoio Executive", "Corridoio con pavimento in marmo e quadri", false,
            {"Sala Riunioni", "Uffici Dirigenziali", "Lounge VIP"}, {"Quadro", "Vaso"}, {"Ombre nei quadri"}};
            
        mappa["Uffici Dirigenziali"] = {"Uffici Dirigenziali", "Suite di uffici lussuosi", false,
            {"Corridoio Executive", "Terrazza Interna"}, {"Laptop", "Cassaforte"}, {"Rapporti sulle entità"}};
            
        mappa["Lounge VIP"] = {"Lounge VIP", "Area relax con mobili in pelle", false,
            {"Corridoio Executive", "Bar Privato"}, {"Bottiglia", "Sigari"}, {"Conversazioni registrate"}};
            
        mappa["Bar Privato"] = {"Bar Privato", "Bar abbandonato con bottiglie intatte", false,
            {"Lounge VIP", "Sala Fumo"}, {"Alcol", "Bicchieri"}, {"Impronte sul bancone"}};
            
        mappa["Mensa"] = {"Mensa", "Vasta sala con tavoli infiniti", false,
            {"Corridoio Sud", "Cucine", "Area Break"}, {"Cibo", "Posate"}, {"Piatti ancora caldi"}};
            
        mappa["Cucine"] = {"Cucine", "Cucine industriali abbandonate", false,
            {"Mensa", "Dispensa", "Celle Frigorifere"}, {"Coltello", "Pentole"}, {"Fornelli accesi"}};
            
        mappa["Celle Frigorifere"] = {"Celle Frigorifere", "Serie di celle frigorifere funzionanti", false,
            {"Cucine", "Corridoio Servizio"}, {"Carne", "Chiave"}, {"Temperature impossibili"}};
            
        mappa["Corridoio Servizio"] = {"Corridoio Servizio", "Corridoio di servizio con carrelli", false,
            {"Celle Frigorifere", "Magazzino"}, {"Carrello", "Scope"}, {"Rumori di passi"}};
            
        mappa["Magazzino"] = {"Magazzino", "Deposito forniture con scaffali alti", false,
            {"Corridoio Servizio", "Uscita Emergenza"}, {"Scatole", "Nastro"}, {"Scatole che si muovono"}};
            
        mappa["Uscita Emergenza"] = {"Uscita Emergenza", "Porta di emergenza con luce rossa", false,
            {"Magazzino", "???"}, {"Mappa", "Accendino"}, {"Simboli strani sulla porta"}};
    }
    else if(nome == "Level 1") {
        mappa["Hub Logistico"] = {"Hub Logistico", "Centro di smistamento con nastri trasportatori infiniti", false,
            {"Zona Carico A", "Magazzino Principale"}, {"Chiave magnetica", "Scanner"}, {"Documenti di spedizione anomali"}};
        
        mappa["Zona Carico A"] = {"Zona Carico A", "Area di carico con dock infiniti", false,
            {"Hub Logistico", "Zona Carico B", "Corridoio Stoccaggio"}, {"Muletto", "Casco"}, {"Container senza fondo"}};
        
        mappa["Zona Carico B"] = {"Zona Carico B", "Seconda area di carico", false,
            {"Zona Carico A", "Area Classificazione"}, {"Pallet", "Guanti"}, {"Impronte di olio animate"}};
        
        mappa["Magazzino Principale"] = {"Magazzino Principale", "Immenso magazzino con scaffali infiniti", false,
            {"Hub Logistico", "Zone Refrigerate", "Area Classificazione"}, {"Carrello elevatore", "Radio"}, {"Scatole che sussurrano"}};
        
        mappa["Area Classificazione"] = {"Area Classificazione", "Zone con sistemi di smistamento", false,
            {"Magazzino Principale", "Nastri Trasportatori"}, {"Scanner", "Etichette"}, {"Pacchi che cambiano peso"}};
        
        mappa["Nastri Trasportatori"] = {"Nastri Trasportatori", "Labirinto di nastri trasportatori", false,
            {"Area Classificazione", "Smistamento Automatico"}, {"Chiave inglese", "Olio"}, {"Nastri che si muovono da soli"}};
        
        mappa["Centro Controllo Logistica"] = {"Centro Controllo Logistica", "Sala controllo con monitor", false,
            {"Hub Logistico", "Uffici Spedizioni"}, {"Computer", "Documenti"}, {"Monitor con immagini impossibili"}};
        
        mappa["Magazzino Verticale"] = {"Magazzino Verticale", "Scaffalature che si estendono verso l'alto", false,
            {"Corridoio Stoccaggio", "Ascensori Merci"}, {"Imbracatura", "Corda"}, {"Oggetti che cadono verso l'alto"}};
        
        mappa["Zone Refrigerate"] = {"Zone Refrigerate", "Area di stoccaggio refrigerata", false,
            {"Magazzino Principale", "Celle Congelamento"}, {"Giacca termica", "Termometro"}, {"Ghiaccio che si muove"}};

        mappa["Celle Congelamento"] = {"Celle Congelamento", "File di celle a temperatura controllata", false,
            {"Zone Refrigerate", "Corridoio Freddo"}, {"Guanti termici", "Chiave cella"}, {"Temperature sotto lo zero assoluto"}};
        
        mappa["Corridoio Freddo"] = {"Corridoio Freddo", "Lungo corridoio refrigerato", false,
            {"Celle Congelamento", "Deposito Refrigerato"}, {"Maschera termica", "Batterie"}, {"Cristalli di ghiaccio viventi"}};
        
        mappa["Deposito Refrigerato"] = {"Deposito Refrigerato", "Grande area di stoccaggio freddo", false,
            {"Corridoio Freddo", "Uscita Emergenza Cold"}, {"Container isotermico", "Radio"}, {"Scatole congelate che vibrano"}};
        
        mappa["Area Spedizioni"] = {"Area Spedizioni", "Centro smistamento pacchi", false,
            {"Hub Logistico", "Uffici Spedizioni"}, {"Scanner codici", "Nastro"}, {"Pacchi che cambiano destinazione"}};
        
        mappa["Uffici Spedizioni"] = {"Uffici Spedizioni", "Uffici con scrivanie infinite", false,
            {"Area Spedizioni", "Archivio Spedizioni"}, {"Computer", "Timbri"}, {"Documenti che si riscrivono"}};
        
        mappa["Archivio Spedizioni"] = {"Archivio Spedizioni", "File infinite di documenti", false,
            {"Uffici Spedizioni", "Deposito Documenti"}, {"Carrello documenti", "Chiave archivio"}, {"Fascicoli che sussurrano"}};
        
        mappa["Zona Manutenzione"] = {"Zona Manutenzione", "Area riparazioni equipment", false,
            {"Hub Logistico", "Officina"}, {"Attrezzi", "Parti ricambio"}, {"Macchinari che si riparano da soli"}};
        
        mappa["Officina"] = {"Officina", "Officina con strumenti e banchi", false,
            {"Zona Manutenzione", "Deposito Attrezzi"}, {"Saldatore", "Chiavi inglesi"}, {"Attrezzi che lavorano autonomamente"}};
            }
    else if(nome == "Level 2") {
        mappa["Hub Tubazioni"] = {"Hub Tubazioni", "Intricato sistema di tubi e valvole", false,
            {"Sala Pressione", "Tunnel Vapore"}, {"Chiave inglese", "Manometro"}, {"Letture di pressione impossibili"}};
        
        mappa["Sala Pressione"] = {"Sala Pressione", "Stanza piena di indicatori e valvole", false,
            {"Hub Tubazioni", "Camera Compensazione"}, {"Guanti isolanti", "Cacciavite"}, {"Valvole che girano da sole"}};
        
        mappa["Tunnel Vapore"] = {"Tunnel Vapore", "Corridoio avvolto nel vapore caldo", false,
            {"Hub Tubazioni", "Centrale Termica"}, {"Maschera gas", "Termometro"}, {"Temperature che non hanno senso"}};
        
        mappa["Camera Compensazione"] = {"Camera Compensazione", "Stanza per equalizzazione pressione", false,
            {"Sala Pressione", "Tunnel Manutenzione A"}, {"Tuta protettiva", "Filtri"}, {"Pressione che cambia randomly"}};
        
        mappa["Centrale Termica"] = {"Centrale Termica", "Enorme sala con sistemi termici", false,
            {"Tunnel Vapore", "Sala Caldaie"}, {"Estintore", "Termostato"}, {"Caldaie che producono ghiaccio"}};
        
        mappa["Sala Caldaie"] = {"Sala Caldaie", "File infinite di caldaie industriali", false,
            {"Centrale Termica", "Tunnel Manutenzione B"}, {"Chiave valvole", "Guanti"}, {"Caldaie che cantano"}};
        
        mappa["Tunnel Manutenzione A"] = {"Tunnel Manutenzione A", "Stretto tunnel di servizio", false,
            {"Camera Compensazione", "Nodo Tubazioni"}, {"Torcia", "Attrezzi"}, {"Graffiti che cambiano"}};
        
        mappa["Tunnel Manutenzione B"] = {"Tunnel Manutenzione B", "Tunnel tecnico con tubi esposti", false,
            {"Sala Caldaie", "Deposito Strumenti"}, {"Multimetro", "Cavi"}, {"Tubi che pulsano"}};
        
        mappa["Nodo Tubazioni"] = {"Nodo Tubazioni", "Intersezione di tubi principali", false,
            {"Tunnel Manutenzione A", "Sala Controllo Flussi"}, {"Flussometro", "Valvola"}, {"Tubi che cambiano percorso"}};
        
        mappa["Sala Controllo Flussi"] = {"Sala Controllo Flussi", "Centro controllo flussi dei fluidi", false,
            {"Nodo Tubazioni", "Sala Monitor"}, {"Panel controllo", "Tablet"}, {"Display con numeri impossibili"}};
        
        mappa["Sala Monitor"] = {"Sala Monitor", "Stanza piena di schermi di monitoraggio", false,
            {"Sala Controllo Flussi", "Archivio Tecnico"}, {"Computer", "Logs"}, {"Monitor che mostrano altri livelli"}};
        
        mappa["Archivio Tecnico"] = {"Archivio Tecnico", "Deposito documentazione tecnica", false,
            {"Sala Monitor", "Ufficio Capo Tecnico"}, {"Manuali", "Chiave"}, {"Schemi che si ridisegnano"}};
        
        mappa["Camera Vapore"] = {"Camera Vapore", "Stanza piena di vapore denso", false,
            {"Tunnel Vapore", "Sala Turbine"}, {"Maschera", "Sensore"}, {"Forme nel vapore"}};
        
        mappa["Sala Turbine"] = {"Sala Turbine", "Enorme sala con turbine infinite", false,
            {"Camera Vapore", "Galleria Tecnica"}, {"Chiave turbina", "Olio"}, {"Turbine che girano al contrario"}};
        
        mappa["Galleria Tecnica"] = {"Galleria Tecnica", "Lungo corridoio con tubi esposti", false,
            {"Sala Turbine", "Deposito Ricambi"}, {"Torcia", "Attrezzi"}, {"Tubi che cambiano materiale"}};
        
        mappa["Deposito Ricambi"] = {"Deposito Ricambi", "Magazzino parti di ricambio", false,
            {"Galleria Tecnica", "Officina Riparazioni"}, {"Parti", "Inventario"}, {"Pezzi che si assemblano da soli"}};
        
        mappa["Officina Riparazioni"] = {"Officina Riparazioni", "Area manutenzione equipment", false,
            {"Deposito Ricambi", "Uscita Tecnica"}, {"Saldatore", "Strumenti"}, {"Macchinari che si riparano autonomamente"}};
    }
    generato = true;
}
void Livello::setModificatori() {
    if(nome == "Level 0") {
        modificatori_entita["Smiler"] = 1.5f;
        modificatori_entita["Hound"] = 0.7f;
        modificatori_entita["Bacteria"] = 1.2f;
    }
}

float Livello::getModificatoreEntita(std::string nome_entita) {
    return modificatori_entita[nome_entita];
}

Zona& Livello::getZona(std::string nome_zona) {
    return mappa[nome_zona];
}

std::vector<std::string> Livello::getZoneAdiacenti(std::string zona_attuale) {
    return mappa[zona_attuale].uscite;
}

float Livello::getModificatoreAmbientale() const {
    return 1.0f + (livello_anomalia * 0.1f);
}

std::vector<std::string> Livello::getIndiziZona(const std::string& zona) {
    return mappa[zona].indizi;
}

bool Livello::isZonaSicura(const std::string& zona) {
    return mappa[zona].sicura;
}

void Livello::aggiornaStatoZona(const std::string& zona, bool sicura) {
    mappa[zona].sicura = sicura;
}

float Livello::getLivelloAnomalia() const {
    return livello_anomalia;
}

void Livello::aumentaAnomalia(float amount) {
    livello_anomalia = std::min(livello_anomalia + amount, 10.0f);
}

void Livello::diminuisciAnomalia(float amount) {
    livello_anomalia = std::max(livello_anomalia - amount, 0.0f);
}

bool Livello::isGenerato() const {
    return generato;
}

void Livello::rigeneraZone() {
    mappa.clear();
    generato = false;
    creaZone();
}
