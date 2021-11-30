#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

//*****************************************************************************************************
//												STRUCT
//*****************************************************************************************************

struct StrDetails
{
	int ID;
	int PairedNumber;
	char PlayerName[20];
	char PartnerName[20];
	
	void reset()	// METHOD FOR CLEAR PartnerName AND PAIREDNUMBER
	{
		strcpy(PartnerName, "");
		PairedNumber = -1;	
	}
	
	StrDetails()	// CONSTRUCTOR
	{
		strcpy(PlayerName, "");
		ID = -1;
		strcpy(PartnerName, "");
		PairedNumber = -1;	
	}
	
};

//*****************************************************************************************************
//											GLOBAL VARIABLES
//*****************************************************************************************************

#define MAX_NUMBER_OF_PLAYERS 100

StrDetails Person[MAX_NUMBER_OF_PLAYERS];
int NumOfPlayers = 0;	

//*****************************************************************************************************
//										GLOBAL FUNC PROTOTYPES
//*****************************************************************************************************
	
void SetNumOfPlayers();	// GET NUMBER OF THE PLAYERS FROM EXT. INPUT
void SetPlayerName(StrDetails *a);	// GET PLAYERS' NAMES FROM EXT. INPUT
void Coupling();	// CREATE RANDOM COUPLES BETWEEN PLAYERS
void PrintResults(); // PRINT CUPLING RESULTS

//*****************************************************************************************************
//										LOCAL FUNC PROTOTYPES
//*****************************************************************************************************

static void reset(int numofplayers, StrDetails *a);	// RESET DATAS COLLECTED IN THE STRUCT
static void SetNameToLowerCase(char a[]); // CONVERT NAMES IN LOWERCASE

//*****************************************************************************************************
//												MAIN
//*****************************************************************************************************

int main()
{
	SetNumOfPlayers();
	SetPlayerName(Person);
	Coupling();
	PrintResults();
		
	return 0;
}

//*****************************************************************************************************
//												METHODS
//*****************************************************************************************************

static void reset(int numofplayers, StrDetails *a)	// METHOD FOR RECALL RESET IN THE STRUCT
{
	for (int i = 0; i < numofplayers; i++)
	{
		a[i].reset();	
	}	
}

//*****************************************************************************************************
//*****************************************************************************************************
//*****************************************************************************************************

void SetNumOfPlayers()
{
	do
	{
		printf ("Inserire un numero di giocatori PARI: ");	// INSERT AN EVEN PLAYERS NUMBER
		scanf("%d", &NumOfPlayers);
	} 
	while (NumOfPlayers % 2 != 0);	// IF IS ODD REDO
	
}

//*****************************************************************************************************
//*****************************************************************************************************
//*****************************************************************************************************

void SetPlayerName(StrDetails *a)
{	
	for (int i = 0; i < NumOfPlayers; i++)	// COLLECTING NAMES AND SAVING THEM IN A STRUCT
	{
		a[i].ID = i;
		printf ("\nInserire il nome numero %d: ", i + 1);
		scanf("%s", a[i].PlayerName);
	}	
}

//*****************************************************************************************************
//*****************************************************************************************************
//*****************************************************************************************************

static void SetNameToLowerCase(char a[])	// TRANSFORM CHARACTERS IN LOWERCASES
{	
	for (int i = 0; i < 20; i++)
	{
		if (a[i] >= 'A' && a[i] <= 'Z') a[i] = a[i] + 32;
		else                            a[i] = a[i];								
	}		
}
	
//*****************************************************************************************************
//*****************************************************************************************************
//*****************************************************************************************************	

//TO_DO: it should work with odd numbers too..
void Coupling()
{	
	srand (time(NULL));
	
	bool flag = true;
	
	while (flag)
	{
		flag = false;
		int err = 0;
		
		for (int i = 0; i < NumOfPlayers; i++)	
		{	
			int nrandom = rand() % NumOfPlayers;	// GENERATE RANDOM NUMBERS
			
			if (nrandom == i)	// CHECK THAT A PlayerName IS NOT EXTRACTED WITH ITSELF
			{
				i--;
				flag = true;
				break;	
			}
				
			Person[i].PairedNumber = nrandom;	// NUMBER ASSIGNMENT
			strcpy (Person[i].PartnerName, Person[nrandom].PlayerName);	// NAME ASSIGNMENT

			for (int j = 0; j < i; j++)	// CHECK THAT A NAME IS NOT ALREADY EXTRACTED
			{
				if (Person[i].PairedNumber == Person[j].PairedNumber)
				{
					reset(NumOfPlayers, Person); // CLEAN ALL
					err = 1;
					flag = true;
					break;
				}
			}		
		
			if (err == 1) break;	
		}		
	}		
}

//*****************************************************************************************************
//*****************************************************************************************************
//*****************************************************************************************************

void PrintResults()
{
	int cnt = 0;
	bool tamp = true;
	
	while(tamp)
	{
		char user_name[20] = {""};
		
		printf("\n\n");
		system("pause");
		system("cls");	// CLEAR THE SCREEN
		
		printf("\tBenvenuto all'estrazione dei regali di Natale!\n\n\tPer favore inserisci il tuo nome: ");
		scanf("%s", user_name);
		
		SetNameToLowerCase(user_name);	// TRANSFORM CHARACTERS IN LOWERCASES
		
		for (int i = 0; i < NumOfPlayers; i++)
		{	
			if(strcmp (user_name, Person[i].PlayerName) == 0)
			{
				printf("\n\tDovrai fare un regalo a: %s", Person[i].PartnerName);
				printf("\n\n");
				cnt ++;
				break;
			}
		}
		
	    // IF I HAVE PRINTED ALL THE CASES -> EXIT
		if(cnt == NumOfPlayers)	tamp = false;
	}
	
	printf ("\n************ESTRAZIONE TERMINATA, BUON NATALE**************");
}
