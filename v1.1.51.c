#include <stdio.h>
#include <string.h>
#include <time.h>//time_tt
#include <stdlib.h>

int seed;//randomizer seed;
int response=0;
char wynik[3][3]; /* Tabela dostępna globalnie, by funkcje wincond, ruch oraz
printer mogły jej używać*/
char p1[20]; /*Nazwa pierwszego gracza */
char p2[20];/*Nazwa drugiego gracza */
char buffer[20];
typedef enum bool {false=0, true=1} bool;
	bool ruc=false;


void printer(void);
int ruch(char, bool);
int wincond(void);
int pvp();
int ai();
int analyze();


int main()
{
	int choice;
printf("Chcesz zagrać przeciw komputerowi(1) czy przeciw człowiekowi(2)?(1/2)");
do{
	fgets(buffer, sizeof buffer, stdin);
	choice= strtol(buffer,NULL,10);
	if(choice==2){
		pvp();}
	if(choice==1){
		ai();
}}
while(choice!=1 || choice!=2);
return 0;
}
int ai(){
	time_t tt;//sprawdzamy czas od 01.01.1970
	int i,p;
	int new_game=0;

 /*Definiuje, kto aktualnie wykonuje ruch*/
	int input=0;
	while(new_game<1){
		seed = time(&tt);
		srand(seed); /* Zmienna bez określonej wartości przyjmuje losowe wartości*/
		for(i=0;i<3;i++){
			for(p=0;p<3;p++)
				wynik[i][p]='#';}
		printf("Cześć! Podaj swoje imię:\nImię:");
		fgets(p1, sizeof p1, stdin);
		p1[strcspn(p1, "\n")] = 0; /*Usuwa newline z stdin w p1*/
		printf("Oto plansza! Zapoznaj się z nią.\n\n");
		printer();/*Pokaz planszę na ekranie - plansza to zwykła tablica, którą będziemy modyfikować*/
		if(seed%2==0){
			printf("Zaczyna komputer!\n");
		}/*Januszowo zrobiona funkcja random-jeśli zmienna, której nie nadaliśmy wartości
		jest parzysta to zaczyna p2*/
		else{
			printf("Zaczyna %s!\n", p1);
			ruc=true;/*W przeciwnym wypadku zaczyna p1. Zmieniamy ruc na wartość przeciwną
			ponieważ ruc definiuje aktualnie działającego gracza*/
		}
		for(i=0;i<9;i++)/*Można wykonać maksymalnie 9 ruchów by zapełnić planszę, dlatego i<9*/
		{
			printf("%s, które pole chcesz zapełnić?\n", ruc==true?p1:p2);
			fgets(buffer, sizeof buffer, stdin);
			input= strtol(buffer,NULL,10);
			response = ruch(input, ruc);/*Przechowujemy odpowiedź funkcji ruch w zmiennej response*/
			while(response == 0) { /*Funkcja response zwraca 0 jeśli wprowadzono znak spoza dozwolonego zakresu.
				Prosimy wtedy zawodnika o powtórzenie jego ruchu.*/
				printf("Wprowadzono złą liczbę lub pole jest już zajęte!\n");
				fgets(buffer, sizeof buffer, stdin);
				input= strtol(buffer,NULL,10);
				response = ruch(input, ruc);}
			printer();/*Pokaż planszę*/
			ruc = !ruc;/*Zmiana wartości ruc pozwala przeciwnikowi na ruch w następnej turze(następnym obrocie pętli)*/
			if(wincond()==1 || wincond()==2){
				printf("Wygrywa %s!\n", wincond()==1?p1:p2);
				break;
			}/*Wincond sprawdza warunek wygranej - jeśli któryś z graczy go spełni,
			zwraca identyfikator gracza i przerywa pętlę*/
		}
		if(wincond()==0)
			printf("Remis!");/*Jeśli na końcu gry nikt nie wygrał, wyświetl odpowiedni komunikat*/

		printf("Czy chcesz zagrać jeszcze raz?(T/n)\n");
		fgets(buffer, sizeof buffer, stdin);
		buffer[strcspn(buffer, "\n")] = 0;
		if(buffer[0]=='T'||buffer[0]=='t'){
			continue;
		}
		else if(buffer[0]=='N'|| buffer[0]=='n'){
		new_game++;
	}
	else{
	return 0;}
	}
return 0;

}

int pvp(){
	time_t tt;//sprawdzamy czas od 01.01.1970
	int i,p;
int new_game=0;
 /*Definiuje, kto aktualnie wykonuje ruch*/
	int input=0;
	while(new_game<1){
		seed = time(&tt);
		srand(seed); /* Zmienna bez określonej wartości przyjmuje losowe wartości*/
		for(i=0;i<3;i++){
			for(p=0;p<3;p++)
				wynik[i][p]='#';}
		printf("Cześć! Podaj swoje imię:\nImię:");
		fgets(p1, sizeof p1, stdin);
		p1[strcspn(p1, "\n")] = 0; /*Usuwa newline z stdin w p1*/
		printf("%s, jak ma na imię Twój przeciwnik?\nImię:", p1);
		fgets(p2, sizeof p2, stdin);
		p2[strcspn(p2, "\n")] = 0;/*Usuwa newline z stdin w p2*/
		printf("Oto plansza! Zapoznajcie się z nią.\n\n");
		printer();/*Pokaz planszę na ekranie - plansza to zwykła tablica, którą będziemy modyfikować*/
		if(seed%2==0){
			printf("Zaczyna %s!\n", p2);
		}/*Januszowo zrobiona funkcja random-jeśli zmienna, której nie nadaliśmy wartości
		jest parzysta to zaczyna p2*/
		else{
			printf("Zaczyna %s!\n", p1);
			ruc=true;/*W przeciwnym wypadku zaczyna p1. Zmieniamy ruc na wartość przeciwną
			ponieważ ruc definiuje aktualnie działającego gracza*/
		}
		for(i=0;i<9;i++)/*Można wykonać maksymalnie 9 ruchów by zapełnić planszę, dlatego i<9*/
		{
			printf("%s, które pole chcesz zapełnić?\n", ruc==true?p1:p2);
			fgets(buffer, sizeof buffer, stdin);
			input= strtol(buffer,NULL,10);
			response = ruch(input, ruc);/*Przechowujemy odpowiedź funkcji ruch w zmiennej response*/
			while(response == 0) { /*Funkcja response zwraca 0 jeśli wprowadzono znak spoza dozwolonego zakresu.
				Prosimy wtedy zawodnika o powtórzenie jego ruchu.*/
				printf("Wprowadzono złą liczbę lub pole jest już zajęte!\n");
				fgets(buffer, sizeof buffer, stdin);
				input= strtol(buffer,NULL,10);
				response = ruch(input, ruc);}
			printer();/*Pokaż planszę*/
			ruc = !ruc;/*Zmiana wartości ruc pozwala przeciwnikowi na ruch w następnej turze(następnym obrocie pętli)*/
			if(wincond()==1 || wincond()==2){
				printf("Wygrywa %s!\n", wincond()==1?p1:p2);
				break;
			}/*Wincond sprawdza warunek wygranej - jeśli któryś z graczy go spełni,
			zwraca identyfikator gracza i przerywa pętlę*/
		}
		if(wincond()==0)
			printf("Remis!");/*Jeśli na końcu gry nikt nie wygrał, wyświetl odpowiedni komunikat*/

		printf("Czy chcesz zagrać jeszcze raz?(T/n)\n");
		fgets(buffer, sizeof buffer, stdin);
		buffer[strcspn(buffer, "\n")] = 0;
		if(buffer[0]=='T'||buffer[0]=='t'){
			continue;
		}
		else if(buffer[0]=='N'|| buffer[0]=='n'){
		new_game++;
	}
	else
	return 0;
	}
return 0;

}

int ruch(char pole, bool gracz){
	int i,p;
	for(i=0;i<3;i++){
		for(p=0;p<3;p++){
			if(pole-1==i*3+p)
				if (wynik[i][p] == '#') {wynik[i][p] = (gracz) ? 'X' : 'O'; return 3; }
	/*Jeśli pole jest wolne(wartość elementu tablicy to "#"), to wstaw znak. W przeciwnym wypadku zwróć komunikat błędu.*/
}}
 return 0;
}

void printer(void)
{
	printf("%c %c %c\n%c %c %c\n%c %c %c \n \n", wynik[0][0], wynik[0][1], wynik[0][2],wynik[1][0], wynik[1][1], wynik[1][2], wynik[2][0], wynik[2][1], wynik[2][2]);
	/*Pokaż na ekranie wszystkie elementy tablicy w odpowiedniej kolejności*/
}
int wincond(){
	int i,p;
	for(i=0;i<3;i++){
		for(p=0;p<3;p++){
			if((wynik[i][p]=='X' && wynik[i][p+1]=='X' && wynik[i][p+2]=='X') || (wynik[i][p]=='X' && wynik[i+1][p]=='X' && wynik[i+2][p]=='X') ||
			(wynik[i][i]=='X' && wynik[i+1][i+1]=='X' && wynik[i+2][i+2]=='X') || (wynik[i][2-i]=='X' && wynik[i+1][1-i]=='X' && wynik[i+2][0-i]=='X')){
				return 1;
			}
			else if((wynik[i][p]=='O' && wynik[i][p+1]=='O' && wynik[i][p+2]=='O') || (wynik[i][p]=='O' && wynik[i+1][p]=='O' && wynik[i+2][p]=='O') ||
						(wynik[i][i]=='O' && wynik[i+1][i+1]=='O' && wynik[i+2][i+2]=='O') || (wynik[i][2-i]=='O' && wynik[i+1][1-i]=='O' && wynik[i+2][0-i]=='O')){
							return 2;
						}
		}			/*Sprawdza, czy odpowiednie pola są zajęte. Jeśli któryś z graczy zapełni
					3 pola wymagane do wygranej to funkcja zwróci odpowiednią wartość, W przeciwnym wypadku
					zwraca wartość 0, świadczącą o remisie.*/
	}
				return 0;
}
