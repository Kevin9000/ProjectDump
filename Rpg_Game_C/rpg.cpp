/*
Esercizio 3:
Progettare un rpg con le seguenti funzionalità minime:

- creazione di un personaggio con le seguenti caratteristiche.
    nome
    razza
    difesa 
    attacco
    vita
    livello (iniziale = 1)
    (min 3 caratteristiche a vostra scelta)
    la somma delle caratteristiche è costante per ciascun livello
- generare un vettore di 5 nemici con valori casuali
  la somma delle caratteristiche è costante per ciascun livello
- in base alla scelta fatta  da un personaggio in un quesito (caricare    quesito da file) selezionare un nemico
- combattimento (termina con decesso di uno dei due):
  se muore il personaggio muore il gioco termina
  se il nemico muore il personaggio aumenta di livello e il gioco si   riavvia
  */
  
/* indice:
   -livello 1: 20-30
*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<windows.h>
#include<conio.h>

//numero massimo caratteri in un vettore
#define DIM 40         

//dopo la generazione dei stats base, l'utente deve aggiungere altri punti stats a sua scelta con punti massimo assegnabili.....
#define MAX_PUNTI_ASSEGNABILI 10

//numero massimo di stats generato all'inizio (per creazione pg)
#define RANGE_STATS 10
#define RANGE_EVENTI 2              

//le stats/informazioni principali che ogni personaggio possiede
struct stats              
{
	char nome[DIM];
	char razza[DIM];
	int vita;
	int attacco;
	int difesa;
	int livello;
	//segna quanti mostri il pg ha ucciso
	int mostri_uccisi;
	//un character appena creato è "vivo"
	bool alive;             
};

//il pg dell'utente
stats pg;    
                   
//pg nemici
stats nemico;                   

//variabile per scelta del tipo di generatore
char tipo_generatore[DIM];      

//puntatore a file dove sono situati tutte le informazione sui pg
FILE * p_character;             

//**************************************************************************FUNZIONI*********************************************************************

//generatore di valori casuali, che in tipo di generatore richiesto (dipende al valore della variabile globale "tipo_generatore) seleziona che tipo di valore specifico dare in uscita
int roll()   
{
	int numero;           
	
	if(strcmp(tipo_generatore,"creazione_stats")==0)
	{
		//7-10 range dei stats iniziali
		numero=rand()%(RANGE_STATS-7)+7;  
	}
	
	if(strcmp(tipo_generatore,"creazione_nemico_normale")==0)
	{
		//range minimo 7 massimo dipende dalla progressione nel gioco(scala sui mostri uccisi)
		numero=rand()%(RANGE_STATS-7+pg.mostri_uccisi)+7;  
	}
	
	if(strcmp(tipo_generatore,"creazione_nemico_difficile")==0)
	{
		numero=rand()%(RANGE_STATS+(pg.mostri_uccisi*2))+7;
	}
	
	
	if(strcmp(tipo_generatore,"selezione_eventi")==0)
	{
		numero=rand()%RANGE_EVENTI+1;
	}
	
	//restituisco il valore casuale
	return numero;                  
}

//---------------------------------------------------------------------------------------Crezione Personaggio e Assegnazione Stats--------------------------------------------------------------------------------------------------

//grafica durante l'assegnazione dei punti extra (oltre a qualli basi) a un character appena creato
int assegnazione_punti_grafica()
{
	//variabile d'appoggio dove metto il valore input da tastiera
	int KeyStatus;
	
	//opzioni
	char text[2][DIM]={"Attacco","Vita"};
	
	//puntatore alla variabile text, punta su che opzione è attualmente l'utente
	int pointer=0;
	
	//dopo la crezione pg, indica quanti punti l'utente ha assegnato
	int punti_assegnati=0;
	
	//indica quanti punti sono stati assegnati nei seguenti campi
	int punti_attacco=0;
	int punti_vita=0;
	
	while(1)
	{
		system("cls");
		
		printf("queste solo le tue stats:\n-livello:%d\n\nSTATS      |   Punti Assegnati\n-attacco:%d   +%d\n-vita: %d     +%d\n-difesa: %d\n\n",pg.livello,pg.attacco,punti_attacco,pg.vita,punti_vita,pg.difesa);
		printf("per assegnare punti freccetta destra; per togliere punti freccetta sinistra\n\n");
		printf("Punti Assegnati:%d (Max: %d)\n\n",punti_assegnati,MAX_PUNTI_ASSEGNABILI);
		
		//stampa le opzioni
		for(int cont=0;cont<2;cont++)
		{
			//se l'opzione da stampare è dove il puntatore è attualmente, cambia il colore del testo e stampa una freccia (scopo puramente visivo)
			if(pointer==cont)
			{
				//modifica il colore per evidenziare dove sta attualmente l'utente
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
				printf("---> %s\n",text[cont]);
				
				//ritorna al colore normale
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
				printf("   %s\n",text[cont]);
			}
		}
		
		printf("\n\n\nSi prega di assegnare tutti i punti possibili e premere enter per continuare\n");
		
		//prende in ingresso il tasto premuto (Prima Chiamata)
		KeyStatus=getch();
		
		//quando si legge una freccetta, ogni funzione deve essere chiamata 2 volte; la prima chiamata ritorna 0 o  0xE0, e la seconda chiamata ritorna il valore del tasto
		if (KeyStatus == 0xE0)       
		{
			//Seconda Chiamata e in base al valore.......
			switch(getch())
			{
				//Arrow Key: Up
				case 72:
					//scala il puntatore, nella realta la posizione nella selezione delle opzioni dove è attualmente l'utente va "sopra"	    
					pointer--;
					//controllo che il puntatore non vada sotto allo 0
					if(pointer<0)
					{
						pointer=1;
					}
					break;
				
				//Arrow Key: Down
				case 80:				
				    //aumenta il puntatore, nella realta la posizione nella selezione delle opzioni dove è attualmente l'utente va "sotto"	    
					pointer++;
					//controllo che il puntatore non vada sopra al numero delle opzioni
				    if(pointer>1)
					{
						pointer=0;
					}
					break;
				
				//Arrow Key: Right
				case 77:
					//controllo che non vengano piu punti di quelli del massimo punti assegnati
				    if(punti_assegnati<MAX_PUNTI_ASSEGNABILI)
				    {
					    if(pointer==0)
						{
							pg.attacco++;
							
							punti_attacco++;
						}				
					    if(pointer==1)
						{
							pg.vita++;
							
							punti_vita++;
						}
						punti_assegnati++;
					}
					break;
					
				//Arrow Key: Left
				case 75:
					//controllo per evitare di togliere punti alle stats base 
					if(punti_assegnati>0)
				    {
					    if(pointer==0 && punti_attacco!=0)
						{
							pg.attacco--;
							
							punti_attacco--;
							punti_assegnati--;
						}				
					    if(pointer==1 && punti_vita!=0)
						{
							pg.vita--;
							
							punti_vita--;
							punti_assegnati--;
						}
					}
					break;
			}
		}
		//se invece viene premuto l'Enter Key, controllo che siano assegnati TUTTI i punti ed esci dal ciclo
		else if(KeyStatus == 13 && punti_assegnati==MAX_PUNTI_ASSEGNABILI)       
		{
			break;
		}
	}
}

void creazione_personaggio()  
{
    //sposta il cursore del file alla fine in modo da evitare la sovrascrittura
	while(1)                   
    {
    	fread(&pg,sizeof(stats),1,p_character);
    	if(feof(p_character))
    	{
    		break;
		}
	}
	//stats dell'utente iniziali (creati casualmente
	printf("dammi il nome del personaggio\n");
	gets(pg.nome);
	
	//il livello iniziale è 1
	pg.livello=1;   
	
	//il pg non ha ancora ucciso nessuno (ovviamente)            
	pg.mostri_uccisi=0;  
	
	//il pg appena creato è vivo (ancora più ovvio)          
	pg.alive=true;             
		
	strcpy(tipo_generatore,"creazione_stats");
	
	//generazione stats base
	pg.vita=roll();
	pg.attacco=roll();
	pg.difesa=roll();
	
	//variabile supporto
	int scelta;
	
	//dopo che vengono generati dei stats base, l'utente deve aggiungere 10 punti a sua scelta alle diverse stats
	assegnazione_punti_grafica();
	
	//trascrive i dati sul file dove sono salvati tutti i dati dei personaggi
	fwrite(&pg,sizeof(stats),1,p_character);
}

//----------------------------------------------------------------------------------------------MENU-------------------------------------------------------------------------------------------------------------------

int menu_grafica()
{
	//variabile d'appoggio dove metto il valore input da tastiera
	int KeyStatus;
	
	//opzioni
	char text[3][DIM]={"Crea Personaggio","Carica Personaggio","Exit"};
	
	//puntatore alla variabile text, punta su che opzione è attualmente l'utente
	int pointer=0;
	
	while(1)
	{
		system("cls");
		
		printf("MENU:\n\n");
		
		//stampa le opzioni
		for(int cont=0;cont<3;cont++)
		{
			//se l'opzione da stampare è dove il puntatore è attualmente, cambia il colore del testo e stampa una freccia (scopo puramente visivo)
			if(pointer==cont)
			{
				//modifica il colore per evidenziare dove sta attualmente l'utente
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
				printf("---> %s\n",text[cont]);
				
				//ritorna al colore normale
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
				printf("   %s\n",text[cont]);
			}
		}
		
		//prende in ingresso il tasto premuto (Prima Chiamata)
		KeyStatus=getch();
		
		//quando si legge una freccetta, ogni funzione deve essere chiamata 2 volte; la prima chiamata ritorna 0 o  0xE0, e la seconda chiamata ritorna il valore del tasto
		if (KeyStatus == 0xE0)       
		{
			//Seconda Chiamata e in base al valore.......
			switch(getch())
			{
				//Arrow Key: Up
				case 72:
					//scala il puntatore, nella realta la posizione nella selezione delle opzioni dove è attualmente l'utente va "sopra"	    
					pointer--;
					//controllo che il puntatore non vada sotto allo 0
					if(pointer<0)
					{
						pointer=2;
					}
					break;
				
				//Arrow Key: Down
				case 80:				
				    //aumenta il puntatore, nella realta la posizione nella selezione delle opzioni dove è attualmente l'utente va "sotto"	    
					pointer++;
					//controllo che il puntatore non vada sopra al numero delle opzioni
				    if(pointer>2)
					{
						pointer=0;
					}
					break;
			}
		}
		//se invece viene premuto l'Enter Key, in base alla posizione del pointer (opzione su dove è attualmente l'utente) ritorna un valore o esce dal programma
		else if(KeyStatus == 13)       
		{
			printf("\n--------------------------------------------\n\n");
			if(pointer==0)
			{
				return 1;
			}
			if(pointer==1)
			{
				return 2;
			}
			if(pointer==2)
			{
				exit(1);
			}
		}
		
	}
}

 //ha il compito di fare da schermato e caricare un personaggio
void menu()                      
{
	char supp[DIM];                     
	bool personaggio_caricato=false;
	while(personaggio_caricato==false)              //caricamento di un character
	{
		
		rewind(p_character);               //riporta indicatore a file all'inizio
		
    	switch(menu_grafica())
    	{
    		case 1:
    			creazione_personaggio();
    			printf("\npersonaggio creato!!\n");
    			system("pause");
    			break;
    			
    		case 2:
    			printf("elenco salvataggi:\n");
    			while(1)
    			{
    				fread(&pg,sizeof(stats),1,p_character);
    				if(feof(p_character))
    				{
    					break;
					}
					if(pg.alive==true)             //mostra l'elenco SOLO dei personaggi vivi
					{
						printf("-%s\n",&pg.nome);
					}
				}
				printf("\nscrivi il nome del personaggio che vuoi caricare\n");
				gets(supp);
				rewind(p_character);
				//ciclo per verificare se il nome del pg inserito corrisponde nei salvataggi, e se si caricarlo
				while(1)
    			{
    				fread(&pg,sizeof(stats),1,p_character);
    				if(feof(p_character))
    				{
    					break;
					}
					if(strcmp(supp,pg.nome)==0)
					{
						if(pg.alive==true)             //controllo se è vivo il personaggio selezionato........
						{
							printf("hai caricato il personaggio :%s !!!!! \n",pg.nome);
	    					printf("queste solo le tue stats \n-livello:%d\n-vita: %d\n-attacco: %d\n-difesa: %d\n\n",pg.livello,pg.vita,pg.attacco,pg.difesa);
	    					personaggio_caricato=true;
		    				break;
						}
					}
				}
				system("pause");
    			break;
				                
    		default:
    			printf("hai selezionato un'opzione non valida\n");
    			system("pause");
    			break;
		}
	}
}

//------------------------------------------------------------------------------Creazione Nemico e Meccaniche di combattimento-------------------------------------------------------------------------------------------------------

//generazione nemico, che riceve in ingresso che tipo di nemico creare (difficile,normale)
void creazione_nemico(char tipo_nemico[DIM])        
{
	strcpy(nemico.nome,"goblin");
	
	if(strcmp(tipo_nemico,"generazione_normale")==0)
	{
		strcpy(tipo_generatore,"creazione_nemico_normale");
	}
	if(strcmp(tipo_nemico,"generazione_forte")==0)
	{
		strcpy(tipo_generatore,"creazione_nemico_difficile");
	}
	
	nemico.vita=roll();
	nemico.attacco=roll();
	nemico.difesa=roll();
	printf("queste le stats del nemico iniziali:\n-livello:%d\n-vita: %d\n-attacco: %d\n-difesa: %d\n\n",nemico.livello,nemico.vita,nemico.attacco,nemico.difesa);
}

void grafica_fight()
{
	system("cls");
	printf("    %s                           %s\n",pg.nome,nemico.nome);
	printf("    %d                             \n",pg.livello);
	printf("HP: %d                       HP: %d\n",pg.vita,nemico.vita);
	printf("Df: %d                       Df: %d\n",pg.difesa,nemico.difesa);
	printf("Atk:%d                      Atk: %d\n\n",pg.difesa);
}

void fight()
{
    //fight
	while(pg.vita>0 && nemico.vita>0)
	{
		grafica_fight();
		nemico.vita-=pg.attacco;
		printf("%s ha attaccato %s: infliggendo %d danni con salute rimanente %d\n",pg.nome,nemico.nome,pg.attacco,nemico.vita);
		system("pause");
		if(nemico.vita<=0)        //se il nemico è gia morto esci dal ciclo
		{
			break;
		}
		pg.vita-=nemico.attacco;
		printf("%s ha attaccato %s: infliggendo %d danni con salute rimanente %d\n",nemico.nome,pg.nome,nemico.attacco,pg.vita);
		system("pause");
	}
	//se durante il combattimento il pg muore ......
	if(pg.vita<=0)
    {
    	pg.alive=false;
    	fseek(p_character,-sizeof(stats),SEEK_CUR);           //sposto il cursore al file di un "blocco"precedente in modo da permettere la sovrascrittura
    	fwrite(&pg,sizeof(stats),1,p_character);              //sovrascrivo il salvataggio
	}
	else if(nemico.vita<=0)
	{
    	pg.mostri_uccisi++;
	}
}



void eventi()
{
	int evento;
	char tipo_nemico[DIM];
	
	while(pg.vita>0)
	{
		strcpy(tipo_generatore,"selezione_eventi");
	    
	    //"lancio un dado" per selezionare tipo di evento (evento casuale)
		evento=roll();                              
		
		printf("eventi possibili:\n1-nemico normale\n2-nemico GROSSO (ti fa il fondo nella maggior parte delle volte)\n");
		system("pause");
	
		switch(evento)
		{
            case 1:
            	strcpy(tipo_nemico,"generazione_normale");
			    creazione_nemico(tipo_nemico);
		    	fight();
		    	break;
		    	
    		case 2:
    			strcpy(tipo_nemico,"generazione_forte");
	    		creazione_nemico(tipo_nemico);
	    		fight();
	    		break;
    	}
	}
}

//-------------------------------------------------------------------------------Programma Principale---------------------------------------------------------------------------------------------------------------

int main()
{
	srand((unsigned)time(NULL));         //inizializzazione seed
	system("color 0f");
	
	p_character=fopen("character.txt","r+");
	if(p_character==NULL)                    //verifica apertura fallita
	{
		printf("errore\n");
		exit(1);
	}
	
	//schermata iniziale
	menu();          
	
	//"avventura"
	eventi();
	
	fclose(p_character);
	
	return 0;
}
