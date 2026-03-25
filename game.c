#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "words.h"

#define WORD_LEN 5
#define TRIES 6

#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define RESET "\x1b[0m"

char* generate_secret_word(char *words[], int size){
    int index = rand() % size;
    return words[index];
}

void to_uppercase_guess(char *guess){
    while (*guess){
        *guess = (char)toupper((unsigned char)*guess);
        guess++;
    }
}

int main(){
    srand(time(NULL));
    int word_bank_size = sizeof(word_bank) / sizeof(word_bank[0]);
    char *secret_word = generate_secret_word(word_bank, word_bank_size);
    char secret_word_upper[WORD_LEN + 1];
    strcpy(secret_word_upper, secret_word);
    to_uppercase_guess(secret_word_upper);
    secret_word = secret_word_upper;
    char guess[100];
    int won = 0;
    int i,j,k;
    
    for (i = 0; i < TRIES; i++){
        while(1){
            printf("\n Try %d/%d. Pls insert a 5 letter word: ", i + 1, TRIES);

            if (!fgets(guess, sizeof(guess), stdin)){
                printf("Error reading input\n");
                return 1;
            }

            guess[strcspn(guess, "\n")] = '\0';

            if (strlen(guess) != WORD_LEN){
                printf("Invalid Input! The guess must be exactly 5 letters\n");
                continue;
            }
            break;
        }

        to_uppercase_guess(guess);
    
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

    if (!won){
        printf("You lost! the secret word is: %s\n", secret_word);
    }

    return 0;
}