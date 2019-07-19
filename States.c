/*
Program details:
Program references data.txt when user enters their desired capital city and state
to find the corresponding lattitude and longitude. If the incorrect city or
state or entered, for example city: Denver and state: Florida (Denver not being
the capital of Florida), the program will tell the user that the city/state are
not found. Regardless of error or the correct city/state being found, program
prompts user if they'd like to perform a second search. If not, program closes.
.*/

#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

struct CapitolInfo
{
    char State[100];
    char City[100];
    char lattitude[100], longitude[100];
};

void doSearch(char city[], char state[]);
FILE *openFile(char fileName[], char mode[]);
void readNextCity(struct CapitolInfo *ci, FILE *fptr);

FILE *openFile(char fileName[], char mode[])
{
    FILE *fptr;
    fptr = fopen(fileName, mode);
    if(fptr == NULL)
    {
        printf("File not found.\n");
        exit(0);
    }

    return fptr;
}

void readLine(char line[], int limit, FILE *fptr)
{
    fgets(line, limit, fptr);
    strtok(line, "\n");
}

void doSearch(char city[], char state[])
{
    struct CapitolInfo c;
    FILE *fptr = openFile("data.txt", "r");
    while(!feof(fptr))
    {
        readNextCity(&c, fptr);
        if(stricmp(city, c.City ) == 0 && stricmp(state, c.State) == 0)
        {
            printf("City: %s\n", c.City);
            printf("State: %s\n", c.State);
            printf("Lat: %s\n", c.lattitude);
            printf("Lon: %s\n", c.longitude);

        }
        else if(strcasecmp(city,c.City) == 0 || strcasecmp(state,c.State) == 0)
        {
            printf("City/State not found\n");
        }
    }
    fclose(fptr);
}

void readNextCity(struct CapitolInfo *ci, FILE *fptr)
{
    char temp[100];

    readLine(ci->State, 100, fptr);
    readLine(ci->City, 100, fptr);
    readLine(ci->lattitude, 100, fptr);
    readLine(ci->longitude, 100, fptr);
}

int main()
{
    char city[100], state[100], answer[10];
    struct CapitolInfo c;

    do {
        printf("What city? ");
        gets(city);
        printf("What State? ");
        gets(state);
        doSearch(city, state);
        printf("Do you want to search again (Y/N): ");
        gets(answer);
    } while(toupper(answer[0]) != 'N');

    printf("Thank you for using the program.\n");

    return 0;
}
