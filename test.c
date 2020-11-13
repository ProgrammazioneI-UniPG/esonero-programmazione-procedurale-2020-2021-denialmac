#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void randomkey(char arr[130], int pl){
  for(int i = 0; i < pl; i++){
    arr[i]= rand() % 128;
  }
  arr[pl]='\0';
}

int controlstringlenght(char c[130]){

  c[strcspn(c, "\n")] = '\0'; // sostituisco \n con \0 perchè \n viene contanto nella funzione strlen

  if(strlen(c)==0)
  printf("Nessun carattere inserito, riprovare\n");

  return strlen(c);
}

void printarr(char arr[130], int arr_lenght){
    for(int i = 0; i < arr_lenght; i++){
        if(arr[i]>31){
            printf("%c", arr[i]);
        }else{
            printf("{C%d}", arr[i]); // se sono caratteri speciali, stampa {C + valore in decimale}
        }
    }
    printf("\n");
}

void xor(char c[130], char p[130], char k[130], int pl){
  for(int i = 0; i < pl; i++){
        c[i] =  p[i] ^ k[i];
    }
}

void printcrypt_decrypt(char M[130], char k[130], char C[130], int pl, int kl){

  // M = plaintext , k = key , c = chipertext

  printf("Cifratura: Testo in chiaro ^ Chiave = Testo criptato\n");
  // M ^ k = C
  printf("Testo in chiaro: ");  printarr(M, pl);
  printf("Chiave: "); printarr(k, kl);
  printf("Testo criptato: ");
  xor(C, M, k, pl);
  printarr(C, pl);

  printf("Decifratura: Testo criptato ^ Chiave = Testo in chiaro\n");
  // C ^ k = M
  printf("Testo criptato: ");printarr(C, pl);
  printf("Chiave: ");printarr(k, kl);
  printf("Testo in chiaro: ");
  xor(M, C, k, pl);
  printarr(M, pl);
}

int main(){

time_t t;
srand (( unsigned ) time(&t));

char plaintext[130]; // maxlenght + \n + \0
char key[130];
char chipertext[130];
int plaintext_lenght, key_length, s,c;

do{
  printf("Inserire stringa da cifrare (max 128 caratteri, altrimenti verrà troncata):\n");
  fgets(plaintext, sizeof(plaintext)-1, stdin); // 129 = 128 char + \n

  plaintext_lenght=controlstringlenght(plaintext);

}while(!plaintext_lenght);

printf("Lunghezza stringa: %d Stringa: %s\n", plaintext_lenght, plaintext);

printf("Selezionare:\n1. Inserire manualmente la chiave\n2. Generare randomicamente la chiave\n");

do {
  scanf("%d", &s);
  while ((c = getchar()) != '\n' && c != EOF) { } // svuoto buffer stdin

  switch(s){
    case 1:
      do{
        printf("Inserire una chiave di lunghezza compresa tra %d e 128:\n", plaintext_lenght);
        fgets(key, sizeof(key)-1, stdin);
        key_length = controlstringlenght(key);

        if((key_length != 0) && (key_length < plaintext_lenght))
        printf("Chiave troppo corta, riprovare\n");

      }while(key_length<plaintext_lenght);

      printcrypt_decrypt(plaintext, key, chipertext, plaintext_lenght, key_length);
      break;

    case 2:
      randomkey(key, plaintext_lenght);
      key_length = strlen(key);
      printarr(key, key_length);
      //printf("pl = %d kl = %d\n", plaintext_lenght, key_length);

      if(key_length >= plaintext_lenght && key_length <= 128)
      printcrypt_decrypt(plaintext, key, chipertext, plaintext_lenght, key_length);
      break;

    default:
      printf("Selezionare una scelta valida\n");
    break;
  }

} while(s!=1 && s!=2);

printf("Grazie per aver usato il programma!\n");
return 0;
}
