#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>
#define MAX_LEN 969
#define CHOSEN_LEN 20
#define WORD 50
#define QUOTES 391
#define QUOTES_LEN 140

int compare(const void *a, const void *b)
{
    char **a1= (char **)a;    
    char **b1= (char **)b;     
    return strcmp(*a1,*b1);
}

void orderNames(char** all_names, FILE* out){
    qsort(all_names, MAX_LEN, sizeof(char *), compare);
    int j = 0;
    for (int i = 0; i < MAX_LEN; i++)
       for (j = 0; j < strlen(all_names[i]); j++){
           if(j != 0)
                all_names[i][j] = tolower(all_names[i][j]);
       }
    for (int i = 0; i < MAX_LEN; i++)
        fprintf(out, "%s\n", all_names[i]);
}

void randomizeNames(char** all_names, char** chosen_names){
    int r = 0;
    for (int i = 0; i < CHOSEN_LEN; i++){
        r = rand()%MAX_LEN;
        strcpy(chosen_names[i], all_names[r]);
    }    
}

void randomizeQuotes(char** all_quotes, char** chosen_quotes){
    int r = 0;
    for (int i = 0; i < CHOSEN_LEN; i++){
        r = rand()%QUOTES;
        if (strcmp(all_quotes[r], "") != 0)
            strcpy(chosen_quotes[i], all_quotes[r]);
        else
            i--;
    }    
}

int main(){
    srand(time(NULL));
    // 4 array di stringhe
    char **chosen_names = (char **)malloc(CHOSEN_LEN*sizeof(char *));
    char **all_names = (char **)malloc(MAX_LEN*sizeof(char *));
    char **all_quotes = (char **)malloc(QUOTES*sizeof(char *));
    char **chosen_quotes = (char **)malloc(CHOSEN_LEN*sizeof(char *));

    // Alloco la memoria per le stringhe
    for (int mem = 0; mem < MAX_LEN; mem++){
        all_names[mem] = (char *)malloc(WORD*sizeof(char));
        memset(all_names[mem], 0, WORD);
    }

    for (int mem = 0; mem < QUOTES; mem++){
        all_quotes[mem] = (char *)malloc(QUOTES_LEN*sizeof(char));
        memset(all_quotes[mem], 0, QUOTES_LEN);
    }
    
    for (int mem = 0; mem < CHOSEN_LEN; mem++){
        chosen_names[mem] = (char *)malloc(WORD*sizeof(char));
        chosen_quotes[mem] = (char *)malloc(QUOTES_LEN*sizeof(char));
        memset(chosen_names[mem], 0, WORD);
        memset(chosen_quotes[mem], 0, QUOTES_LEN);
    }
    FILE *names = fopen("nomi_italiani.txt", "rw");
    FILE *out = fopen("nomi_out.txt", "w");
    FILE *quotes = fopen("quotes.txt", "r");
    FILE *quotes_out = fopen("quotes_out.txt", "w");
    if(names == NULL || out == NULL || quotes == NULL || quotes_out == NULL){
        perror("Il file non esiste");
        exit(1);
    }
    int i = 0;
    int j = 0;
    while (i < MAX_LEN){
        j = 0;
        fgets(all_names[i], WORD, names);
        while(all_names[i][j] !='\n')
            j++;
        all_names[i][j] = 0;
        i++;
        
    }
    i = 0;
    j = 0;
    while (i < QUOTES){
        j = 0;
        char *tmp = (char *)malloc(3*QUOTES_LEN*sizeof(char));
        fgets(tmp, 3*QUOTES_LEN, quotes);
        tmp[strcspn(tmp, "\n")] = 0;
        realloc(tmp, QUOTES_LEN*sizeof(char));
        if (strlen(tmp) > QUOTES_LEN)
            continue;
        strcpy(all_quotes[i], tmp);
        i++;
    }

    // orderNames(all_names, sorted);
    randomizeNames(all_names, chosen_names);
    randomizeQuotes(all_quotes, chosen_quotes);


    for (int i = 0; i < CHOSEN_LEN; i++)
        fprintf(out, "\"%s\", ", chosen_names[i]);

    
    for (int i = 0; i < CHOSEN_LEN; i++)
        fprintf(quotes_out, "\"%s\", ", chosen_quotes[i]);
    
    for(int i = 0; i < CHOSEN_LEN; i++)
        puts(chosen_names[i]);


    for (int i = 0; i < CHOSEN_LEN; i++){
        free(chosen_names[i]);
        free(chosen_quotes[i]);
    }

    for (int i = 0; i < MAX_LEN; i++)
        free(all_names[i]);

       for (int i = 0; i < QUOTES; i++)
        free(all_quotes[i]);

    free(all_names);
    free(chosen_names);
    free(chosen_quotes);
    free(all_quotes);
    return 0;
}