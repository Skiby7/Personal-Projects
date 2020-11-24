#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAXLEN 101

typedef struct _ingredients{
    char ingredient[MAXLEN];
    struct _ingredients *next;
}ingredients;

typedef struct _done{
    char **done;
    struct _done *next;
    
}done;

ingredients* insIngredients(ingredients *head, char *ingredient)
{
    ingredients *new = (ingredients *)malloc(sizeof(ingredients));
    strcpy(new->ingredient, ingredient);  
    new->next = head;

    return new;
}

done* insExtracted(done *head, char *a, char *b, char *c)
{
    done *new = (done *)malloc(sizeof(done));
    new->done = (char **)malloc(3*sizeof(char *));
    
    new->done[0] = (char *)malloc(MAXLEN*sizeof(char));
    strcpy(new->done[0], a);
    new->done[1] = (char *)malloc(MAXLEN*sizeof(char));
    strcpy(new->done[1], b);
    new->done[2] = (char *)malloc(MAXLEN*sizeof(char));
    strcpy(new->done[2], c);
    
      
    new->next = head;

    return new;
}

void from_list_to_array(char **array, ingredients *head, int elements)
{
    for (int i = 0; i < elements; i++){ 
        array[i] = (char *)malloc(MAXLEN*sizeof(char));
        strcpy(array[i], head->ingredient);
        head = head->next;
    }
}

int check(done *head, char *a, char *b, char *c)
{
    int count = 0;
    for (int i = 0; i < 3; i++)
        if (strcmp(head->done[i], a) == 0 || strcmp(head->done[i], b) == 0 || strcmp(head->done[i], c) == 0 )
            count++;
    if (count == 3)
        return 0;
    return 1;
}

int check_all(done *head, char *a, char *b, char *c)
{
    while(head != NULL){
        if (check(head, a, b, c) == 0)
            return 0;
        head = head->next;
    }
    return 1;
}

int main()
{
    int elements = 0;
    char ingredient[MAXLEN];
    memset(ingredient, 0, MAXLEN);
    ingredients *sfida = NULL;
    done *estratti = NULL;
    
    while (1){

        gets(ingredient);
        if (strcmp(ingredient, "basta") == 0)
            break;
        sfida = insIngredients(sfida, ingredient);
        elements++;
    }
    char **array = (char **)malloc(elements*sizeof(char *));
    from_list_to_array(array, sfida, elements);
    
    int choice = 0;
    int c , a, b;
    a = b = c = 0;
    char sep[] = {"-----------------------------------------------------------------------------------"};
    srand(time(0));
    while (choice != -1){
        puts("Inserisci 1 per estrarre la combinazione o -1 per fermarti");
        scanf("%d", &choice);
        if (choice == -1)
            break;
        while((a == b || b == c || a == c) || (a == 0 && b == 0 && c == 0) || (check_all(estratti, array[a], array[b], array[c]) == 0)){
            a = rand()%elements;
            b = rand()%elements;
            c = rand()%elements;
        }
        printf("%25s\n%25s%25s%25s\n%25s", sep, array[a], array[b], array[c], sep);
        printf("\n");
        estratti = insExtracted(estratti, array[a], array[b], array[c]);
        a = b = c = 0;
    }

    for (int l = 0; l < elements; l++)
            free(array[l]);
        free(array);

    while(sfida != NULL) {
        ingredients* tmp = sfida;
        sfida = sfida->next;
        free(tmp);
    }

    while(estratti != NULL) {
        for (int l = 0; l < 3; l++)
            free(estratti->done[l]);
        free(estratti->done);
        done* tmp = estratti;
        estratti = estratti->next;
        free(tmp);
    }    
    return 0;

}