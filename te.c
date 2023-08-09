#include <stdio.h>
#include <signal.h>

// Gestionnaire de signal personnalisé pour SIGINT
void handle_sigint(int sig) {
    printf("Signal SIGINT (Ctrl+C) reçu. Sortie du programme.\n");
    // Insérer ici le code de nettoyage ou d'autres actions avant de quitter
    return;
}

int main() {
    // Associer le signal SIGINT au gestionnaire handle_sigint
    signal(SIGINT, handle_sigint);

    // Le programme continue son exécution ici
    while (1) {
        // Boucle infinie ou d'autres actions
    }

    return 0;
}
