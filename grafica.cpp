#include "grafica.h"

void SistemaGrafico::inizializzaMappe() {
    mappe["Level 0"] = R"(
╔════════════════ THE LOBBY - LEVEL 0 ════════════════╗
║                                                     ║
║   [Reception] ────── [Corridoio N] ── [Open Space] ║
║       │                    │               │        ║
║   [Area Relax] ─── [Sala Server] ── [Archivio]    ║
║       │                    │               │        ║
║    [Bagni] ────── [Magazzino] ── [Uscita Emerg]   ║
║                                                     ║
╚═════════════════════════════════════════════════════╝)";

    mappe["Level 1"] = R"(
╔════════════════ THE WAREHOUSE - LEVEL 1 ═══════════╗
║                                                    ║
║   [Hub] ────────── [Storage A] ──── [Storage B]   ║
║    │                    │               │         ║
║ [Control] ───── [Maintenance] ── [Power Room]     ║
║    │                    │               │         ║
║  [Exit] ────── [Loading Bay] ── [Security]       ║
║                                                    ║
╚════════════════════════════════════════════════════╝)";
}

std::string SistemaGrafico::coloraStringa(const std::string& testo, int colore) {
    if (!colori_attivi) return testo;
    return "\033[" + std::to_string(colore) + "m" + testo + "\033[0m";
}

void SistemaGrafico::mostraCaricamento(const std::string& messaggio) {
    std::string barra = "[";
    std::cout << "\n";
    for(int i = 0; i <= 100; i += 5) {
        barra = "[";
        for(int j = 0; j < i/5; j++) barra += "█";
        for(int j = i/5; j < 20; j++) barra += " ";
        barra += "]";
        std::cout << "\r" << coloraStringa(messaggio, 36) << " " 
                 << coloraStringa(std::to_string(i) + "%", 33) << " " 
                 << coloraStringa(barra, 32) << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    std::cout << "\n";
}

void SistemaGrafico::mostraMappa(const std::string& livello) {
    if(mappe.find(livello) != mappe.end()) {
        std::cout << coloraStringa(mappe[livello], 36) << "\n";
    }
}

void SistemaGrafico::animazioneAttacco() {
    std::vector<std::string> frames = {
        "⚔️ >>====>",
        "⚔️ >>>===>",
        "⚔️ >>>>==>"
    };
    
    for(int i = 0; i < 5; i++) {
        for(const auto& frame : frames) {
            std::cout << "\r" << coloraStringa(frame, 31) << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
    std::cout << "\n";
}

void SistemaGrafico::animazioneMovimento() {
    std::vector<std::string> frames = {
        "🚶    ",
        " 🚶   ",
        "  🚶  ",
        "   🚶 ",
        "    🚶"
    };
    
    for(const auto& frame : frames) {
        std::cout << "\r" << frame << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    std::cout << "\n";
}

void SistemaGrafico::animazioneRicerca() {
    std::vector<std::string> frames = {
        "🔍 .",
        "🔍 ..",
        "🔍 ...",
        "🔍 ...."
    };
    
    for(int i = 0; i < 3; i++) {
        for(const auto& frame : frames) {
            std::cout << "\r" << coloraStringa(frame, 33) << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    }
    std::cout << "\n";
}

void SistemaGrafico::pulisciSchermo() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void SistemaGrafico::mostraLogo() {
    std::string logo = R"(
███╗   ███╗ ███████╗  ██████╗ 
████╗ ████║ ██╔════╝ ██╔════╝ 
██╔████╔██║ █████╗   ██║  ███╗
██║╚██╔╝██║ ██╔══╝   ██║   ██║
██║ ╚═╝ ██║ ███████╗ ╚██████╔╝
╚═╝     ╚═╝ ╚══════╝  ╚═════╝ 
    )";
    std::cout << coloraStringa(logo, 35) << "\n";
}

void SistemaGrafico::mostraGameOver() {
    std::string gameover = R"(
 ██████╗  █████╗ ███╗   ███╗███████╗     ██████╗ ██╗   ██╗███████╗██████╗ 
██╔════╝ ██╔══██╗████╗ ████║██╔════╝    ██╔═══██╗██║   ██║██╔════╝██╔══██╗
██║  ███╗███████║██╔████╔██║█████╗      ██║   ██║██║   ██║█████╗  ██████╔╝
██║   ██║██╔══██║██║╚██╔╝██║██╔══╝      ██║   ██║╚██╗ ██╔╝██╔══╝  ██╔══██╗
╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗    ╚██████╔╝ ╚████╔╝ ███████╗██║  ██║
 ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝     ╚═════╝   ╚═══╝  ╚══════╝╚═╝  ╚═╝
    )";
    std::cout << coloraStringa(gameover, 31) << "\n";
}
