#include <stdio.h>
#include <string.h>

#define WORD_LEN 5
#define TRIES 6

#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define RESET "\x1b[0m"

int main(){
    char secret_word[] = "sigma";
    char guess[WORD_LEN + 1];
    int won = 0;
    int i,j,k;

    for (i = 0; i < TRIES; i++){
        printf("\n Try %d/%d. Pls insert a 5 letter word: ", i + 1, TRIES);
        if (scanf("%5s", guess) != 1) break;

        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        

        if (!strcmp(secret_word, guess)){
                printf("You guessed the secret word!!\n");
                won = 1;
                break;
        }

        int used_in_secret[WORD_LEN] = {0};
        int feedback[WORD_LEN] = {0};
        
        for (j = 0; j < WORD_LEN; j++){
            if (secret_word[j] == guess[j]){
                feedback[j] = 2;
                used_in_secret[j] = 1;
            }
        }

        for (j = 0; j < WORD_LEN; j++){
            if (feedback[j] == 2) continue;

            for (k = 0; k < WORD_LEN; k++){
                if (!used_in_secret[k] && guess[j] == secret_word[k]){
                    feedback[j] = 1;
                    used_in_secret[k] = 1;
                    break;
                }
            }
        }

        for (k = 0; k < WORD_LEN; k++){
            if (feedback[k] == 2){
                printf(GREEN "%c" RESET, guess[k]);
            }
            else if (feedback[k]){
                printf(YELLOW "%c" RESET, guess[k]);
            }
            else{
                printf("_");
            }
        }
        printf("\n");
    }

    
    return 0;
}