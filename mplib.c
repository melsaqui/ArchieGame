typedef char map[Row][Col];
typedef char string[30];

typedef struct
{
	int water;
	int fire; 
}powerUp;
typedef struct 
{
	int yellow; // '/'
	int cyan;//	'\'
}keys;
struct items
{
	keys Keys;
	int chips;
	powerUp Pro;
};
typedef struct items Items;

/*Description: Sets the colors of the tiles, items, and character
char pos: is the character within the map to be colored*/
void Colors(char pos)
{
    if(pos =='*')
    	printf("\x1b[34;1m"); //blue text
    else if(pos =='~')
      	printf("\x1b[44;1m"); //blue background
    else if(pos =='%')
      	printf("\x1b[41;1m"); //red background
    else if (pos=='@')
    	printf("\x1b[31;1m"); //red text
    else if (pos =='\\')
    	printf("\x1b[36;1m"); //cyan text
    else if (pos=='/' )
		printf("\x1b[33;1m"); //yellow text
	else if(pos=='Y')
		printf("\x1b[30;103;1m"); //yellow background
	else if(pos=='C')
		printf("\x1b[30;106;1m"); //Cyan background
	else if(pos=='0')
		printf("\x1b[47m\x1b[31;1m"); //white background; red foreground
	else if(pos=='X')
		printf("\x1b[45;1m"); //magenta background
	else if(pos=='>'||pos=='^'||pos=='v'||pos=='<')
		printf("\x1b[42;1m");// green background
	else if(pos =='H')
		printf("\x1b[95;1m"); //magenta text
	else if(pos =='A') //Player
		printf("\x1b[38;5;209;1;5m"); //orange ; bold; blinking
	else 
		printf("\x1b[40m");
	
}
//Source ANSII Codes: https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797 

