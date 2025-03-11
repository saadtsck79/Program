#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_RECORD_LENGTH 100 
#define MAX_RECORDS 100
typedef struct {
    char data [MAX_RECORD_LENGTH] ;    
} Record ;
void addRecordToFile (Record records[], int numRecords);
void searchRecordInFile (char *record) ;
void displayAllRecords() ;
int main () {
    Record records [MAX_RECORDS] ;
    int numRecords = 0 ;
    strcpy (records[0].data , "JOHN , 25") ;
    strcpy (records[1].data , "ALICE , 22") ;
    strcpy (records[2].data , "BOB , 45") ;
    numRecords = 3 ;
    addRecordToFile(records , numRecords) ;
    char searchRecord [MAX_RECORD_LENGTH] = "ALICE , 22" ;
    searchRecordInFile (searchRecord) ;
    displayAllRecords () ;
    return 0 ;
}
void addRecordToFile (Record records[] , int numRecords) {
    FILE * file = fopen("fileorg.txt" , "w") ;
    if (file == NULL) {
        printf("could not open file .\n") ;
        return ;
    }
    for (int i = 0 ; i < numRecords ; i++) {
        fprintf(file , "%s\n" , records[i].data) ;
    }
    fclose (file) ;
}
void searchRecordInFile (char *record) {
    FILE * file = fopen ("fileorg.txt" , "r") ;
    if (file == NULL) {
        printf ("could not open file \n") ;
        return ;
    }
    char line [MAX_RECORD_LENGTH] ;
    int found = 0 ;
    while (fgets(line,sizeof(line),file)) {
        line [strcspn(line,"\n")] = 0 ;
        if (strcmp (line , record) == 0) {
            printf ("Record found : %s \n" , line) ;
            found = 1; 
            break ;
        }
    }
    if (!found) {
        printf ("Record not found \n") ;
    }
     fclose (file) ;
}
void displayAllRecords () {
    FILE * file = fopen ("fileorg.txt" , "r") ;
    if (file == NULL) {
        printf ("Could not open the file \n") ;
        return ;
    }
    char line [MAX_RECORD_LENGTH] ;
    printf ("All Records \n") ;
    while (fgets(line,sizeof(line),file)) {
        line [strcspn(line , "\n")] = 0 ;
        printf ("%s \n" , line) ;
    }
    fclose (file) ;
}