#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
    #include <windows.h>
    #define CLEAR "cls"
    #define SLEEP(ms) Sleep(ms)
#else
    #include <unistd.h>
    #define CLEAR "clear"
    #define SLEEP(ms) usleep((ms) * 1000)
#endif

// Couleurs ANSI (uniquement bleu et rouge)
#define RESET "\033[0m"
#define RED   "\033[31m"
#define BLUE  "\033[34m"

// Variables globales pour le score et les noms
int score1 = 0, score2 = 0, draws = 0;
char player1[50], player2[50];
bool namesInitialized = false;

// Variable globale pour la langue (1 = Français, 2 = English)
int language = 1;

// Prototypes
void clearScreen();
void pauseScreen();
void showLanguageSelection();
void showSplashScreen();
void displayMenu();
void playGame();
void resetBoard(char board[]);
void printBoard(char board[]);
bool checkWin(char board[], char player);
bool checkDraw(char board[]);
void saveHistory(const char *result);

int main() {
    int choice;
    
    clearScreen();
    showLanguageSelection();   // Choix de la langue
    clearScreen();
    showSplashScreen();        // Écran d'accueil ASCII
    pauseScreen();
    
    while (1) {
        displayMenu();
        
        // Prompt du menu
        if (language == 1) {
            printf(BLUE "Choisissez une option : " RESET);
        } else {
            printf(BLUE "Choose an option: " RESET);
        }
        
        if (scanf("%d", &choice) != 1) {
            while(getchar() != '\n'); // vider le buffer
            printf(RED "Entrée invalide.\n" RESET);
            pauseScreen();
            continue;
        }
        
        // Gestion du menu
        if (choice == 1) {
            // Jouer / Rejouer
            if (!namesInitialized) {
                // Saisie des noms (une seule fois)
                if (language == 1) {
                    printf(BLUE "Entrez le nom du Joueur 1 (X) : " RESET);
                    scanf("%s", player1);
                    printf(RED "Entrez le nom du Joueur 2 (O) : " RESET);
                    scanf("%s", player2);
                } else {
                    printf(BLUE "Enter Player 1's name (X): " RESET);
                    scanf("%s", player1);
                    printf(RED "Enter Player 2's name (O): " RESET);
                    scanf("%s", player2);
                }
                namesInitialized = true;
            }
            playGame();
        }
        else if (choice == 2) {
            // Historique / History
            clearScreen();
            if (language == 1) {
                printf(BLUE "========== Historique de la session ==========\n" RESET);
                printf("%s : %d victoire(s)\n", player1, score1);
                printf("%s : %d victoire(s)\n", player2, score2);
                printf("Matchs nuls : %d\n", draws);
                printf(BLUE "==============================================\n" RESET);
            } else {
                printf(BLUE "========== Session History ==========\n" RESET);
                printf("%s : %d win(s)\n", player1, score1);
                printf("%s : %d win(s)\n", player2, score2);
                printf("Draws : %d\n", draws);
                printf(BLUE "=====================================\n" RESET);
            }
            pauseScreen();
        }
        else if (choice == 3) {
            // Quitter / Quit
            clearScreen();
            if (language == 1) {
                printf(BLUE "\nMerci d'avoir joué ! Au revoir.\n" RESET);
            } else {
                printf(BLUE "\nThanks for playing! Goodbye.\n" RESET);
            }
            break;
        }
        else {
            // Entrée invalide
            printf(RED "Option invalide.\n" RESET);
            pauseScreen();
        }
    }
    
    return 0;
}

//------------------------------------
//        Sélection de la langue
//------------------------------------
void showLanguageSelection() {
    printf(BLUE "1. Français\n" RESET);
    printf(BLUE "2. English\n\n" RESET);
    printf(BLUE "Choisissez votre langue / Choose your language: " RESET);
    
    if (scanf("%d", &language) != 1) {
        // Par défaut : Français
        language = 1;
    }
    while(getchar() != '\n'); // vider le buffer
}

//------------------------------------
//       Écran d'accueil ASCII
//------------------------------------
void showSplashScreen() {
    // "TIC" en bleu
    printf(BLUE "  TTTTTTT   IIIIIII   CCCCCCC \n" RESET);
    printf(BLUE "     T         I      C       \n" RESET);
    printf(BLUE "     T         I      C       \n" RESET);
    printf(BLUE "     T         I      C       \n" RESET);
    printf(BLUE "     T      IIIIIII   CCCCCCC \n\n" RESET);

    // "TOE" en rouge
    printf(RED  "  TTTTTTT   OOOOOOO   EEEEEEE \n" RESET);
    printf(RED  "     T      O     O   E       \n" RESET);
    printf(RED  "     T      O     O   EEEEEE  \n" RESET);
    printf(RED  "     T      O     O   E       \n" RESET);
    printf(RED  "     T      OOOOOOO   EEEEEEE \n\n" RESET);

    // Message de bienvenue (en bleu)
    if (language == 1) {
        printf(BLUE "Bienvenue dans le Tic Tac Toe !\n\n" RESET);
    } else {
        printf(BLUE "Welcome to Tic Tac Toe!\n\n" RESET);
    }
}

//------------------------------------
//           Menu principal
//------------------------------------
void displayMenu() {
    clearScreen();
    // En-tête simplifié (sans "TIC TOE")
    printf(BLUE "========================================\n" RESET);
    printf(BLUE "│                                      │\n" RESET);
    printf(BLUE "│          TICTACTOE CONSOLE           │\n" RESET);
    printf(BLUE "│                                      │\n" RESET);
    printf(BLUE "========================================\n" RESET);
    printf("\n");

    printf(BLUE "┌────────────────────────────────────────┐\n" RESET);

    // Option 1 : Jouer ou Rejouer
    if (!namesInitialized) {
        if (language == 1)
            printf(BLUE "│ 1. Jouer                               │\n" RESET);
        else
            printf(BLUE "│ 1. Play                                │\n" RESET);
    } else {
        if (language == 1)
            printf(BLUE "│ 1. Rejouer                             │\n" RESET);
        else
            printf(BLUE "│ 1. Replay                              │\n" RESET);
    }

    // Option 2 : Historique
    if (language == 1)
        printf(BLUE "│ 2. Afficher l'historique               │\n" RESET);
    else
        printf(BLUE "│ 2. View history                        │\n" RESET);

    // Option 3 : Quitter
    if (language == 1)
        printf(BLUE "│ 3. Quitter                             │\n" RESET);
    else
        printf(BLUE "│ 3. Quit                                │\n" RESET);

    printf(BLUE "└────────────────────────────────────────┘\n" RESET);
    printf("\n");
}

//------------------------------------
//     Lancer / Rejouer une partie
//------------------------------------
void playGame() {
    char board[9];
    int move;
    char currentPlayer = 'X';  // Joueur 1 = X (BLEU), Joueur 2 = O (ROUGE)
    bool gameOver = false;
    
    resetBoard(board);
    
    while (!gameOver) {
        clearScreen();
        
        // Affichage du score
        if (language == 1) {
            printf(BLUE "Score : %s = %d, %s = %d, Nuls = %d\n\n" RESET,
                   player1, score1, player2, score2, draws);
        } else {
            printf(BLUE "Score: %s = %d, %s = %d, Draws = %d\n\n" RESET,
                   player1, score1, player2, score2, draws);
        }
        
        // Affiche le plateau
        printBoard(board);
        
        // Demande le coup du joueur courant
        if (currentPlayer == 'X') {
            if (language == 1)
                printf(BLUE "%s (X), entrez votre coup (1-9) : " RESET, player1);
            else
                printf(BLUE "%s (X), enter your move (1-9): " RESET, player1);
        } else {
            if (language == 1)
                printf(RED "%s (O), entrez votre coup (1-9) : " RESET, player2);
            else
                printf(RED "%s (O), enter your move (1-9): " RESET, player2);
        }
        
        // Lecture de la saisie
        if (scanf("%d", &move) != 1) {
            while(getchar() != '\n');
            printf(RED "\nEntrée invalide.\n" RESET);
            pauseScreen();
            continue;
        }
        
        // Vérification de la validité du coup
        if (move < 1 || move > 9 || board[move - 1] == 'X' || board[move - 1] == 'O') {
            if (language == 1)
                printf(RED "\nCoup invalide. Essayez à nouveau.\n" RESET);
            else
                printf(RED "\nInvalid move. Try again.\n" RESET);
            pauseScreen();
            continue;
        }
        
        // Place le symbole sur le plateau
        board[move - 1] = currentPlayer;
        
        // Vérifie la victoire
        if (checkWin(board, currentPlayer)) {
            clearScreen();
            printBoard(board);
            if (currentPlayer == 'X') {
                if (language == 1) {
                    printf(BLUE "Félicitations, %s gagne !\n" RESET, player1);
                } else {
                    printf(BLUE "Congratulations, %s wins!\n" RESET, player1);
                }
                score1++;
                saveHistory(player1);
            } else {
                if (language == 1) {
                    printf(RED "Félicitations, %s gagne !\n" RESET, player2);
                } else {
                    printf(RED "Congratulations, %s wins!\n" RESET, player2);
                }
                score2++;
                saveHistory(player2);
            }
            gameOver = true;
        }
        // Vérifie le match nul
        else if (checkDraw(board)) {
            clearScreen();
            printBoard(board);
            if (language == 1)
                printf(BLUE "Match nul !\n" RESET);
            else
                printf(BLUE "It's a draw!\n" RESET);
            draws++;
            saveHistory("Match nul / Draw");
            gameOver = true;
        }
        // Sinon, passe au joueur suivant
        else {
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }
    pauseScreen();
}

//------------------------------------
//   Réinitialise le plateau
//------------------------------------
void resetBoard(char board[]) {
    for (int i = 0; i < 9; i++) {
        board[i] = '1' + i;
    }
}

//------------------------------------
//  Affiche le plateau de jeu
//------------------------------------
void printBoard(char board[]) {
    // Grille simplifiée pour éviter des soucis d'affichage
    printf("         -------------\n");
    for (int i = 0; i < 3; i++) {
        printf("         | ");
        for (int j = 0; j < 3; j++) {
            int index = i * 3 + j;
            char cell = board[index];
            // Joueur 1 (X) = Bleu, Joueur 2 (O) = Rouge
            if (cell == 'X')
                printf(BLUE "%c" RESET, cell);
            else if (cell == 'O')
                printf(RED "%c" RESET, cell);
            else
                printf("%c", cell);
            
            printf(" | ");
        }
        printf("\n");
        printf("         -------------\n");
    }
    printf("\n");
}

//------------------------------------
//   Vérifie la victoire
//------------------------------------
bool checkWin(char board[], char player) {
    // Lignes
    if (board[0] == player && board[1] == player && board[2] == player) return true;
    if (board[3] == player && board[4] == player && board[5] == player) return true;
    if (board[6] == player && board[7] == player && board[8] == player) return true;
    // Colonnes
    if (board[0] == player && board[3] == player && board[6] == player) return true;
    if (board[1] == player && board[4] == player && board[7] == player) return true;
    if (board[2] == player && board[5] == player && board[8] == player) return true;
    // Diagonales
    if (board[0] == player && board[4] == player && board[8] == player) return true;
    if (board[2] == player && board[4] == player && board[6] == player) return true;
    return false;
}

//------------------------------------
//   Vérifie le match nul
//------------------------------------
bool checkDraw(char board[]) {
    for (int i = 0; i < 9; i++) {
        if (board[i] != 'X' && board[i] != 'O') {
            return false;
        }
    }
    return true;
}

//------------------------------------
//   Sauvegarde le résultat
//------------------------------------
void saveHistory(const char *result) {
    FILE *fp = fopen("historique.txt", "a");
    if (fp == NULL) {
        printf(RED "Erreur d'ouverture du fichier historique.\n" RESET);
        return;
    }
    time_t now = time(NULL);
    fprintf(fp, "%s won on %s", result, ctime(&now));
    fclose(fp);
}

//------------------------------------
//     Fonctions utilitaires
//------------------------------------
void clearScreen() {
    system(CLEAR);
}

void pauseScreen() {
    // Petit message en bleu
    printf(BLUE "\nAppuyez sur Entrée pour continuer..." RESET);
    while(getchar() != '\n'); 
    getchar();
}
