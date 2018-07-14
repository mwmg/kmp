// Author: Miguel Guse, miguel.guse@tum.de
#include <stdio.h>
#include <string.h>

//Farben für Ausgabe
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define LENGTH  100

//Funktionen um Arrays auszugeben
void printIntArr(int arr[], int length){
  for (int i = 0; i < length; i++) {
    printf("%2d", arr[i]);
  }
  printf("\n");
}

void printCharArr(char arr[], int length){
  for (int i = 0; i < length && arr[i] != '\0'; i++) {
    printf("%2c", arr[i]);
  }
  printf("\n");
}

// Parameter m ist die Länge von pat[]/shift[]
void initShift(char pat[], int shift[], int m){
  shift[0] = -1;
  shift[1] = 0;
  int i = 0;
  for(int j = 2;j < m; j++){
    while(i >= 0 && pat[i] != pat[j-1]){
      i = shift[i];
    }
    i = i+1;
    shift[j] = i;
  }
}

// Parameter n ist die Länge von text[]
// m ist Länge von pat[]/shift[]
int kmpSearch(char text[], char pat[], int shift[], int n, int m){
  //Init Shift table and print it
  printf("\nInitShift:\n");
  printCharArr(pat,m);
  initShift(pat, shift, m);
  printIntArr(shift,m);

  //Search
  printf("\nSearch:\n");
  printCharArr(text, n);
  int i=0; int j=0;
  while(i <= (n-m)){
    // i Leerzeichen ausgeben, um pat visuell zu verschieben
    printf("%*s", i*2, "");

    // Bereits verglichene Zeichen ausgeben (immer grün)
    for(int c = 0; c < j; c++){
      printf(ANSI_COLOR_GREEN "%2c" ANSI_COLOR_RESET, pat[c]);
    }

    // j ausgeben, notwendig für Fall, dass while-Schleife nicht eintritt
    if(text[i+j] != pat[j]){
      printf(ANSI_COLOR_RED "%2c" ANSI_COLOR_RESET, pat[j]);
    } else{
      printf(ANSI_COLOR_GREEN "%2c" ANSI_COLOR_RESET, pat[j]);
    }

    while(text[i+j] == pat[j]){
      j++;

      // if-else für Farbenzuordnung
      if(text[i+j] != pat[j]){
        printf(ANSI_COLOR_RED "%2c" ANSI_COLOR_RESET, pat[j]);
      } else{
        printf(ANSI_COLOR_GREEN "%2c" ANSI_COLOR_RESET, pat[j]);
      }

      if(j==m){
        return i;
      }
    }
    i += j - shift[j];
    j = (shift[j] > 0) ? shift[j] : 0;  // j = max(0,shift[j])
    printf("\n");
  }
  return -1;  //no match found
}

int main(int argc, char const *argv[]) {
  char text[100] = "";
  char pat[100] = "";
  int shift[100];

  // Text einlesen
  printf("Text: ");
  // fgets eignet sich für ganze Zeilen besser als scanf
  fgets(text, 100, stdin);
  int n = (int)strlen(text) - 1;  // fgets will also read the '\n'

  // Pattern einlesen
  printf("Pattern: ");
  fgets(pat, 100, stdin);
  int m = (int)strlen(pat) - 1;

  int status = kmpSearch(text, pat, shift, n, m);
  printf("\n");
  if(status >= 0){
    printf("String match at index %d.\n", status);
  }else{
    printf("String not found.\n");
  }
  return 0;
}
