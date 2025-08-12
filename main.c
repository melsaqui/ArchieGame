//use windows because of system("cls")
#include <stdio.h>
#include<time.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#define Row 20
#define Col 40
#include "mplib.c"
#define MAX_LEVEL 3
/*Description: Initializes the map for each level 
Parameters:
map Map: the array where the game is stored
int nLevel: The current level the player is playing on
Return Value: The array Map holds the values for the map
*/
void initLevels(map Map,int nLevel)
{
	int i;
	int j;
	FILE * file;
	if (nLevel == 1)
		file = fopen("maps/level1.txt","r");
	else if(nLevel == 2)
		file = fopen("maps/level2.txt","r");
	else if(nLevel == 3)
		file = fopen("maps/level3.txt","r");
	if (file != NULL)
	{	
		i = 0;
		while(!feof(file))
		{	
			fscanf(file,"%s",Map[i]);
			i++;
			j++;
		}
		fclose(file);
	}
	else
		printf("Level is unavailabe!");
}

/*Description: counts the item on the map
Parameters: 
map game: the main array of the game map
char items: the item being counted on the map
Return Value: The amount of the item on the game map
*/
int countItems(map game,char item)
{
	int i,j;
	int nCount=0;
	for (i=0;i<Row;i++)
	{
		for (j=0;j<Col; j++)
		{
			if (game[i][j]==item)
			{
				nCount+=1;
			}
		}
	}
	return nCount;
	
}
/*Description: Generates a randon number
Parameters:
int nLow: The lowest possible value generated
int nUp: The highest posiible value generated
Return Value: A random integer within the limits of nLow and nUp
*/
int Randomizer(int nLow,int nUp)
{
	int num;
	 num = (rand() % (nUp - nLow + 1)) + nLow;
    return num;
}
/*Description: Decides where all the power-ups and keys will be
Parameters:
map game: Array holding the game
int nLevel: The current level the game is on
Return Value: The items would be scattered on the map*/
void items (map game,int nLevel)
{
	char items[4]={'\\','/', '@','*'};
	srand(time(0));
	int i;
	int j;
	int z;
	int bValid;
	for( z = 0; z < 4; z++)
	{
		if(countItems(game,items[z]) == 0)
		{
			bValid = 0;
			while (bValid!=1)
			{
				i = (Randomizer(2,Row-1));
				j = (Randomizer(2,Col-1));
				if (game[i][j]=='_')
				{
					if(items[z]=='/' && i>15&&j<=5 && nLevel==1)
						bValid = 0;
					else if(items[z]=='@'&& i<=3 && j<=13 && nLevel==2)
						bValid = 0;
					else if(items[z]=='*'&& i>=16 && j>=23 && nLevel==2)
						bValid =0; 
					else if(items[z]=='/'&& i>=12 && j>=28 && nLevel==2)
						bValid = 0; 
					else if(items[z]=='\\'&& i>=6 && i<=9 &&j>=14&&j<=20 && nLevel==2)
						bValid = 0;
					else if(items[z]=='@' && i<=4 && nLevel==3 )
						bValid = 0 ;
					else if(items[z]=='/'&& i<=4 && j>=32 && nLevel==3)
						bValid = 0;
					else if (items[z]=='*' && i>=11 && i<=13 && j>=16 && j<=33 && nLevel==3)
						bValid = 0;
					else if (items[z]=='*' && i>=16 && j<=23 && nLevel==3)
						bValid = 0;
					else if (items[z]=='\\' && i>=15 && j<=6 && nLevel==3)
						bValid = 0;
					else
					{
						bValid = 1;
						game[i][j] = items[z];
					}
				}	
			}
		}
	}
}
/*Description: Displays the Players items
Parameters: 
Items Player: struct holding the amount of items player has
int reqChip: The amount of chips needed for the level
Return Value: The Inventory will be diplayed
*/
void displayItems(Items Player,int reqChip)
{
	printf("  ---------------------\n");
	printf(" | Inventory %11s\n","|");
	printf(" | Chips: %d/%d %10s\n",Player.chips,reqChip,"|");
	printf(" | Y-Key: %d %12s\n",Player.Keys.yellow,"|");
	printf(" | C-Key: %d %12s\n",Player.Keys.cyan,"|");	
	printf(" | Fire Protection: %d %2s\n", Player.Pro.fire,"|");
	printf(" | Water Protection: %d |\n",Player.Pro.water);
	printf("  --------------------- \n");

}

/*Description: Initializes/resets the number of items the player currently has
Parameters: 
Items *Player: This where the values of the items are stored
Return Value: all items sghould be set to 0;*/
void initializeDefault(Items *Player)
{
	Player->chips = 0;
	(*Player).Keys.yellow = 0;
	(*Player).Keys.cyan = 0;	
	(*Player).Pro.fire = 0;
	(*Player).Pro.water = 0;
}
/*Description: checks if the player has died due to stepping on elemental tiles unprotected 
or they died attempting to exit without enough chips
Parameters:
char pos: the character value of the position of where the player goes
Items player: carries the values of the items player holds including the powerup and the chips they have
int reqChip: The required chips to exit for the current level
Return value: 1 if they died else 0 is returned
*/
int isDead(char pos, Items player,int reqChip)
{
	if ((pos=='~' && player.Pro.water <= 0)||(pos=='%' && player.Pro.fire<=0)||(pos=='X'&&player.chips<reqChip))
		return 1;
	else return 0;
}

/*Description: Updates the items the player is holding
Parameters: 
char pos: the character on the map the player has stepped on
Items *player: the struct holding the items of the player
Return Value: the item will be updated if player steps on tile with the item or loses it all if pos was '0'
*/
int characterItem(char pos, Items *player)
{
	if(pos=='/')
		(*player).Keys.yellow +=1;
	else if(pos =='\\')
		(*player).Keys.cyan +=1;
	else if (pos=='*')
		(*player).Pro.water+=1;
	else if(pos=='@')
		(*player).Pro.fire+=1;
	else if(pos=='H')
		player->chips+=1;
	else if (pos=='0')
	{
		initializeDefault(player);
		return 1;
	}
	return 0;	
}
/*Description: Displays the main menu*/
void displayLevelUpMenu()
{	
	printf("  ------------------- \n");
	printf(" |    1-Continue     |\n");
	printf(" |  2-Restart Level  |\n");
	printf(" |      3-Quit       |\n");
	printf("  ------------------- \n");

}

/*Descrription: Checks is if the value is a slide tile
Parameter:
char pos: The character on the board being checked
Return Value: returns 1 if pos is a slide tile, return 0 if it is not a slide tile*/
int isSlide(char pos)
{
	if (pos =='^'|| pos =='v'||pos=='>'|| pos=='<')
		return 1;
	else 
		return 0;
}
/*Description: Checks if the value on the board is a tile
char pos: The charcter value on the map that will be checked if it is a tile
Return Value: returns 1 if pos is a tile, return 0 if it is not a  tile*/
int isTile(char pos)
{
	if (pos =='~'|| pos =='%'|| pos=='0'||pos=='Y'||pos=='C'|| pos=='#')
		return 1;
	else 
		return 0;
}
/*Description: Displays the game
Parameters:
map game: the game to be displayed
int Level: the current level of the game
Return Value: The game map is displayed*/
void displayBoard (map game,int Level)
{
	int i, j;
	printf("%40s %d |\n\n","| LEVEL", Level);
	for(i = 0; i < Row; i++) 
  	{
		for(j = 0; j < Col; j++)
      	{
      		if (j!=0)
			{
				Colors(game[i][j]);
				if((isTile(game[i][j])==1 && game[i][j] == game[i][j+1] && game[i][j]!='#')
				||((isSlide(game[i][j])==1)&&(isSlide(game[i][j+1])==1)))
					printf("%c ", game[i][j]);
				else
				{	
      				printf("%c", game[i][j]);
      				printf("\x1b[0m|");
      			}
			}
      	else printf("|%c|", game[i][j]);
	  }
    printf("\n");
  }
}

/*Description: Checks if user input is the passsword for the next level
Parameters:
string pw: The password for the next level
Return Value: -1 is returned when player has already used three attempts at entering the password, 1 if the passwrod was successfully entered*/
int isValidPass(string pw)
{
	int i;
	int nAttempt=0;
	char pass[strlen(pw)+1];
	while (strcmp(pass,pw)!=0 && nAttempt!=3)
	{

		printf("\nEnter Password:");
		for(i=0;i<strlen(pw);i++)
		{
			pass[i]=(char)getch();
			printf("*"); 
		}
		pass[strlen(pw)] ='\0';
		if(strcmp(pass,pw)!=0)
			nAttempt++;	
	}
	if (nAttempt==3)
		return -1;
	else
		return 1;
}
/*Description: What happens when player levels up
Parameters:
char pos: The tile player steps on
int *nLevel: current level in the game
Items *player: Holds the player items
int *reqChip: The required chips to exit level
map game: The main array holding the game
Return Value:  if player wanted to quit game, 3 is returned and game exits, 
if player wants to restart the level, 2 is returned and all values and map for the current level is initialized
if player wants to continue the game they are propmted to input the password in order to continue otherwise they can die*/
int isLevelUp(char pos, int *nLevel, Items *player, int *reqChip, map game)
{
	string pw[2]={"4rchi3", "f137pr0g2"};
	char choice ='z';
	int next;
	if (pos =='X' && (isDead(pos,*player,*reqChip) == 0))
	{
		if(*nLevel==MAX_LEVEL)
		{
			system("cls");
			printf(" Congrats! You finished the Game! \n");
			printf("Press any key to continue!");
			getch();
			next =3;
		}
		else
		{
			printf("Congrats! You finished level %d!\n", *nLevel);
			printf("Remember The password for level %d is: %s  or else you die!! \n", *nLevel+1, pw[*nLevel-1]);
			printf("Press any key to continue!");
			getch();
			system("cls");
			displayLevelUpMenu();
			
			while(choice!='3'&& choice!='1'&& choice!='2'){
				scanf(" %c",&choice);
				if(choice!='3'&& choice!='1'&& choice!='2'){
					printf("Invalid Choice!");
				}
			}
			
			if (choice =='3'){
				next = 3; 
			}
			else if(choice =='1')//continue
			{
				system("cls");
				if(isValidPass(pw[*nLevel-1])==-1)
					next=-1;
				else if	(isValidPass(pw[*nLevel-1])==1)
				{
					*nLevel += 1;
					initLevels(game,*nLevel);
					*reqChip = countItems(game, 'H');
					initializeDefault(player);
					displayBoard(game,*nLevel);
					next=1;
				}
			}
			else if(choice =='2') //restart level
			{
				initLevels(game, *nLevel);
        		items(game, *nLevel);
        		next = 2;
			}
		}
	}else
		next= 0;

	return next;
}
/*Description: Does what happens when a player stepped on a slide tile
int *x: The player's current x position 
int *y: The player's current y position 
char pos: tile the player is stepping on
int nLevel: Current level of the game
map game: The main array of the game displayed
Return Value: x or y gets updated depending on the tile the player stepped on*/
void slideTile(int *x, int *y, char pos, int nLevel,map game)
{
	while(isSlide(pos)==1)
	{
		if (pos=='>')
		{
			while (game[*y][*x+1]=='>'||game[*y+1][*x]=='>'||game[*y-1][*x]=='>')
			{
				*x+=1;
				game[*y][*x] ='A';
				game[*y][*x-1] ='>';
				system("cls");
				displayBoard(game,nLevel);
			}		
			*x += 1;
			game[*y][*x-1] = '>';
			pos = game[*y][*x];	
		}
		else if (pos=='<')
		{
			while (game[*y][*x-1]=='<'||game[*y+1][*x]=='<'||game[*y-1][*x]=='<')
			{	
				*x-=1;
				game[*y][*x]='A';
				game[*y][*x+1]='<';
				system("cls");
				displayBoard(game,nLevel);	
			}
			*x-=1;
			game[*y][*x+1]='<';
			pos=game[*y][*x];
		}
		else if (pos=='^')
		{
			while (game[*y][*x+1]=='^'||game[*y][*x-1]=='^'||game[*y-1][*x]=='^')
			{
				*y-=1;
				game[*y][*x]='A';
				game[*y+1][*x]='^';
				system("cls");
				displayBoard(game,nLevel);
			}
			*y-=1;
			game[*y+1][*x]='^';
			pos=game[*y][*x];
		}
		else if (pos=='v')
		{
			while (game[*y][*x+1]=='v'||game[*y][*x-1]=='v'||game[*y+1][*x]=='v')
			{
				*y+=1;
				game[*y][*x]='A';
				game[*y-1][*x]='v';
				system("cls");
				displayBoard(game,nLevel);
			}
			*y+=1;
			game[*y-1][*x]='v';
			pos = game[*y][*x];
		}
	}
}
/*Desscription: Finds the initial place of the player on the map
Parameters: 
map game: the array of the map where we are looking for the player
int *x: the x value or the column value of the player
int *y: the y value or the row value of the player
Return value: the initial x and y value of the player or indexes on the array where player is*/
void findPlayer(map game, int *x, int *y)
{
	int i;
	int j;
	for (i=0;i<Row; i++)
	{
		for(j=0;j<Col; j++)
		if (game[i][j]=='A')
		{
			*x=j;
			*y=i;
		}
	}
}
/*Description:What happens whenever player moves
Parameters:
map game: The set array of the game's map 
int *nLevel: The current level of the game is here in order to call displayBoard
int *x: the x coordinate the player will move to (horizontal)
int *y: the y coordinate the player will move to (Vertical)
Items * player: The items the player currently has is stored here
int *reqChip: The required chips needed to exit level
return value: Calls appropriate functions needed,returns 1 is the player died, 2 if they quit, otherwise 0;
*/
int characterMove(map game, int *nLevel, int *x, int *y, Items* player,int *reqChip)
{	
	int nEnd;
	slideTile(x,  y, game[*y][*x],*nLevel, game);

	int nLevelUp = isLevelUp(game[*y][*x],nLevel,  player,  reqChip, game);
	if (nLevelUp == -1) //died because of too many failed attempts at password
		nEnd = 1;
	else if(nLevelUp == 3)//quit game after level
	{
		system("cls"); 
		nEnd = 2;
	}	
	else 
	{
		if(nLevelUp == 2) //restart level 
		{

			initializeDefault(player);
      		findPlayer(game, x, y);
		}
			
		else if(isDead(game[*y][*x], *player,*reqChip) == 1)//died by elemental
			return 1;

		else if(characterItem(game[*y][*x], player)==1)
		{
			if (*nLevel == 1)
			{
				game[17][2] ='H';
				game[13][34] ='H';
			}	
			else if(*nLevel == 2)
			{
				game[18][2]='H';
				game[1][1]='H';
				game[12][33]='H';
			}
			else if(*nLevel == 3)
			{
				game[2][36] ='H';
				game[17][4]='H';
				game[1][1]='H';
				game[18][36]='H';
				game[12][31]='H';
			}
			items(game,*nLevel);
		}	
		
			game[*y][*x]= 'A';
			system("cls");
			displayBoard(game,*nLevel);
			displayItems(*player,*reqChip);
			nEnd = 0;
	
	}
	return nEnd;
}
/*Description: Check if the tile is locked
char pos: the tile being checked
Items player: The items the player holding that could unlock the tile
Rerturn value: returns 1 if tile is locked, otherwise it returns 0*/
int isLocked(char pos, Items player)
{
	if(pos =='Y' && player.Keys.yellow>=1)
		return 0;
	else if (pos=='C'&& player.Keys.cyan>=1)
		return 0;
	else if (pos!='Y'&& pos!='C')
		return 0;
	else return 1;		
}
/*Description: Main gameplay through moving the characters
Parameters
map game: the game map in order to put the player on the game
int *nLevel: the current level of the game needed to know which map to load
Items *player: The items player is holding is stored here
int reqChip: The required chips needed to level up or end the game
return value: updated values of the x and y of the player, returns 1 if player died, 2 if player quit 
or 0 if the game is not yet ending*/
int gamePlay(map game, int *nLevel, Items *player,int reqChip)
{
	int x;
	int y;
	findPlayer(game, &x,&y);
	char control;
	char temp ='_';
	int bEnd = 0;
	
	int charMoved ;
	while (bEnd == 0)
	{ 	
		if(control!='d'&&control!='D'&&control!='a'&&control!='A'&& control!='s'&&control!='S'&&control!='w'&&control!='W')
			control=(char)getch();
		while ((control == 'd'||control== 'D' ) && bEnd==0)
		{
			if((game[y][x+1]!='#'&& x+1<=Col-1)&& isLocked(game[y][x+1],*player)==0)
			{
				x++;
				game[y][x-1] = temp;
				if (isTile(game[y][x]) == 1)
					temp = game[y][x];
				else if(isTile(game[y][x]==1))
					temp = game[y][x+1];
				else temp = '_';	
			}	
			charMoved = characterMove(game, nLevel,&x,&y, player,&reqChip);
			if(charMoved==1)
				bEnd=1;
			else if(charMoved==2) //quit after level
				bEnd =2;
			else 
				control = (char)getch();
		}
		while ((control== 'a'||control == 'A') && bEnd==0)
		{
			if((game[y][x-1]!='#'&& x-1>=0)&& isLocked(game[y][x-1],*player)==0)
			{
				x--;
				game[y][x+1] = temp;
				if (isTile(game[y][x]) == 1)
					temp = game[y][x]; 
				else temp = '_';
			}
			charMoved = characterMove(game, nLevel,&x,&y, player,&reqChip);

			if(charMoved==1)
				bEnd=1;
			else if(charMoved==2)
			{
				bEnd=2;
			}
			else
				control=(char)getch();
		}
		while ((control== 's'||control== 'S') && bEnd==0)
		{
 			if ((game[y+1][x]!= '#' && y+1 <= Row-1) && isLocked(game[y+1][x],*player)==0)
			{		
				y++;
				game[y-1][x] = temp;
				if (isTile(game[y][x]) == 1)
					temp = game[y][x];
				else 
					temp = '_';
			}	
			charMoved = characterMove(game, nLevel,&x,&y, player,&reqChip);

			if(charMoved==1)
				bEnd=1;
			else if(charMoved==2)
			{
				bEnd=2;
			}
			else
				control = (char)getch();
		}
		while ((control=='w'||control=='W')&&bEnd==0)
		{
 			if ((game[y-1][x]!= '#' && y-1>=0)&&isLocked(game[y-1][x],*player)==0)
 			{
 				y--;
 				game[y+1][x]= temp;
 				if (isTile(game[y][x])== 1)
					temp = game[y][x];
				else 
					temp = '_';
 			}
			charMoved = characterMove(game, nLevel,&x,&y, player,&reqChip);

			if(charMoved==1)
				bEnd=1;
			else if(charMoved==2)
			{
				bEnd = 2;
			}
			else	
				control = (char)getch();
		}
	}

	if (bEnd==1)
	{
		system("cls"); 
		*nLevel=1;
		return 1;
	}
	else if(bEnd==2)
		return 2;
	else return 0;
	}
void displayInstructions(){
	FILE *fptr;

	printf("  --------------------------------------------------------------------------------\n");
	printf(" | %51s%37s\n"," \x1b[1mObjectives \x1b[0m","|");

	fptr = fopen("instructions.txt", "r");
	char instructions[100];
	int i= 0;
	if (fptr != NULL){
		while(fgets(instructions, 100, fptr)) {	
			i=0;
			while (instructions[i]!=NULL){
				if (i!=0 && instructions[i-1]=='(' && instructions[i+1]==')'){
					Colors(instructions[i]);
				}else if (i!=0 && instructions[i-1]=='(' && instructions[i+1]==',' && instructions[i+3]==')'){
					Colors(instructions[i]);
				}
				else if(instructions[i-3]=='(' && instructions[i-1]==',' && instructions[i+1]==')')
					Colors(instructions[i]);

				printf("%c", instructions[i]);
				printf("\x1b[0m");
				i++;
			}
  		
			
		}
		fclose(fptr);
	}
	
	printf("\n  -----------\n");
	printf(" | \x1b[1mControls\x1b[0m  |\n");
	printf(" |     W     |\n");
	printf(" |  A     D  |\n");
	printf(" |     S     |\n");
	printf("  -----------\n");
	

}
void displayMenu()
{
	printf("  --------------------");
	printf("\n |%18s |\n"," \x1b[1;4mArcher's Adventure\x1b[0m");
	printf(" |%17s   |\n"," 1-Start Game ");
	printf(" |%17s   |\n","  2-Instructions");
	printf(" |%17s   |\n", " 3-Exit Game ");
	printf("  --------------------\n");

}
/*Description: Manages the general flow of the game*/
int main()
{
	
	int nLevel = 1;
	char choice;
	int ReqChip;
	displayMenu();
	Items player;
	map game;
	do
	{
		scanf(" %c",&choice);
		if (choice !='2'  && choice !='1' && choice!='3')
		{
			printf(" Invalid! Enter 1 or 2! \n");
		}
		if (choice == '1')
		{ 
			initializeDefault(&player);
			initLevels(game,nLevel);
			ReqChip = countItems(game,'H');
			items(game,nLevel);
			system("cls"); 
			displayBoard(game,nLevel);
			displayItems(player,ReqChip);
			int nGame;
			nGame=gamePlay(game, &nLevel, &player,ReqChip);
			if (nGame==1){
				printf(" | %14s%6s\n","You died!","|");
				
			}
			displayMenu();
			
		}else if (choice=='2'){
			system("cls");
			displayInstructions();
			displayMenu();
		}
	 		
	}while (choice!='3');
return 0;

}


	

