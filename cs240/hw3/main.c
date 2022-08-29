#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/wait.h> 
#include <signal.h>

/*As a general note, when reading through this code, almost all methods of
saving and running code is based up Linked List, which usually take the form
of First in First out (FIFO). Each of these linked lists have functions that
'copy' and 'paste' strings based upon what they are given by using numbers to
traverse through them, which is usually called the index. After working with this
system for a while, I understand that it is not very efficient and could be changed.
However, this system was set up during the early stages of this program and are
vital to its consistency*/

/*This definition will be used throughout the code to
determine the size of each mutable array to hold a string */
#define maxLen 1024

/*Files used in the program are declared 
here to suit the helper functions.
mshrc is used to read from 'mshrc'
pipecommand is used to read the command being piped
pipefile is used to write to a temporary 'pipe' file to pipe commands*/
FILE *mshrc,*pipecommand,*pipefile;

/*These following structs all define their own linked list
	history 	- stores all commands the user inputted into history.
							This is used when traversing the history using
							the arrow keys or !! or !3
	multiple 	- stores all commands that are inputted at once
							using the ';' operator between the multiple commands
	alias 		- stores all of the aliases the user creates. It's used
							also to find and replace the alias with the correct command
	path 			- stores all the paths the user creates//////////////////////////////CHANGE/////
*/

/*History Linked List
How this linked list works is whenever you input a string into the shell and enter it,
it gets sent to this list (This process is very arbitrary - it receives one character at
a time and places it into char history). After each string/command is inputted, the count
goes up, which is given to each node. The user is able to traverse through this list using the
arrow keys, this utilizes the 'scroll' variable, which traverses the history's list.
The user may also run '!!' to repeat the last command in history and !#' to repeat a certain
command based on the nodes number 'count'. If they match, run that command
*/
struct history {
  char history[maxLen];
	char count;
  struct history *next;
};

/*Multiple-Command Linked List
How this linked list works is whenever you run a ';' operator, theres at least one command
stored into the linked list. This means, for example, if 'ls;history' was executed, 'history'
would be stored into this linked list and 'ls' will run. Later you will see that if this 
linked list is not empty, as it is in this case, it will run again with the last command
added to this linked list, which is 'history'.
*/
struct multiple {
  char command[maxLen];
  struct multiple *next;
};

/*Alias Linked List
This linked list stores all of the aliases created by the 'alias' command 
(i.e. 'alias list='ls'). This struct contains two character arrays, one for 
the alias name (alias) and the next for the command the alias is performing (replace).
In this case, 'list' is the alias and 'ls' is the command that eventually replaces it.
*/
struct alias {
	int sizeAlias;
	int sizeReplace;
  char alias[maxLen];
	char replace[maxLen];
  struct alias *next;
};

/*Path Linked List////////////////////////////////////////////////////////////////CHANGE/////
This linked list stores paths inputted by the user. These paths are all tested when the user
inputs a command; basically, it cycles through this entire linked list to see if any of the
paths allow for the command the user inputted. If successful, it stops cycling.
*/
struct path {
  char exportpath[maxLen];
  struct path *next;
};

/*This global variable is used to 
determine the command number in history*/
int counter = 1;

/*This is the beginning command in history*/
struct history *head = NULL;
/*This is the beginning command in the ';' operator*/
struct multiple *first = NULL;
/*This is the first alias in the list of alias's*/
struct alias *start = NULL;
/*The first path in the list of paths*////////////////////////////////////////////CHANGE/////
struct path *origin = NULL;

/*This function adds a path to the list of paths*/////////////////////////////////CHANGE/////
void addPath(char *line) {
  struct path *n = (struct path*) malloc(sizeof(struct path));
	struct path *p = (struct path*) malloc(sizeof(struct path));
	p = origin;
  n->next = NULL;
	int i = 0;
  while(line[i] != '\0') {
    n->exportpath[i] = line[i];
    i++;
  }
	n->exportpath[i] = '\0';
	if(origin == NULL)
  {
    origin = n;
  }
  else
  {
    while(p->next != NULL) {
    	p = p->next;
  	}
  	p->next = n;
	}
}

/*This function determine how many paths possible the command can execute from*///CHANGE/////
int sizePath() {
	struct path *n = origin;
	int count = 0;
  while(n != NULL) {
    n = n->next;
		count++;
  }
	return count;
}

/*This function returns a path in the list based on the number given*/////////////CHANGE/////
char* checkPath(int index) {
	struct path *n = origin;
  while(--index > 0) {
    n = n->next;
  }
	return n->exportpath;
}

/*This function displays all of the paths*///////////////////////////////////////CHANGE/////
void printPath() {
	struct path *n = origin;
  while(n != NULL) {
		printf(":/usr%s",n->exportpath);
    n = n->next;
  }
}

/*This removes any command in history that exceeds the 20 history limit*/
void removeFirsthistory() 
{ 
	struct history *temp = (struct history*) malloc(sizeof(struct history));

  if (head != NULL)
	{
		temp = head;
    head = head->next;
	}
	free(temp);
}

/*This removes any commands that have been called by the ';' operator when used*/
void removeFirstCommand() 
{ 
	struct multiple *temp = (struct multiple*) malloc(sizeof(struct multiple));

  if (first != NULL)
	{
		temp = first;
    first = first->next;
	}
	free(temp);
}

/*This functions removes aliases with the 'unalias' command*/
void removeAlias(int index)
{
	struct alias *temp = (struct alias*) malloc(sizeof(struct alias));
	temp = start;
	struct alias *prev = (struct alias*) malloc(sizeof(struct alias));
	int header = 0;
	if(index == 1) header = 1;

	while(--index > 0) {
		prev = temp;
		temp = temp->next;
	}

	if (header == 1)
	{
  	temp = start;
  	start = start->next;
		free(temp);
	}
	else
	{
		free(prev->next);
		prev->next = temp->next;
	}
}

/*This function adds an alias with its name to the list of aliases*/
void addAlias(char line[]) {
  struct alias *n = (struct alias*) malloc(sizeof(struct alias));
	struct alias *p = (struct alias*) malloc(sizeof(struct alias));
	p = start;
  n->next = NULL;
	n->sizeAlias = 0;
	int i = 0;
	int j = 0;
  while(line[i] != '\0') {
		if(line[i] != ' ' && line[i] != '\'') {
			n->alias[j] = line[i];
			n->sizeAlias++;
			j++;
		}
		i++;
  }
	n->alias[i] = '\0';
	if(start == NULL)
  {
    start = n;
  }
  else
  {
    while(p->next != NULL) {
    	p = p->next;
  	}
  	p->next = n;
	}
}

/*This function adds a command to the same alias 
that was added the list of aliases*/
void replaceAlias(char line[]) {
	struct alias *n = start;
  while(n->next != NULL) {
    n = n->next;
  }
	n->sizeReplace = 0;
	int i = 0;
	int j = 0;
  while(line[i] != '\0') {
		if(line[i] != ' ' && line[i] != '\'') {
    	n->replace[j] = line[i];
			n->sizeReplace++;
			j++;
		}
		i++;
  }
	n->replace[i] = '\0';
}

/*This function returns the command for the alias name using the number given.
This function works alongside the next*/
char getAlias(int index, char character) {
	struct alias *n = start;
  while(--index > 0) {
    n = n->next;
  }
	return n->replace[character];
}

/*This function returns a number for a given alias when 
inputted by the user, if it exists*/
int findAlias(char line[]) {
	struct alias *n = start;
	int count = 0;
	int found = 0;
	while(n != NULL) {
		count++;
		if((strcmp(n->alias,line) == 0))
			{
				found = 1;
				break; break;
			}
    n = n->next;
  }
	if (!found) count = 0;
	return count;
}

/*This function determines the size of the alias name*/
int sizeAlias(int index) {
	struct alias *n = start;
	while(--index > 0) {
    n = n->next;
  }
  return n->sizeAlias;
}

/*This function determines the size of the alias command*/
int sizeReplace(int index) {
	struct alias *n = start;
	while(--index > 0) {
    n = n->next;
  }
  return n->sizeReplace;
}

/*This function prints all of the aliases*/
void printAlias() {
	struct alias *n = start;
	while(n != NULL) {
		printf("\n\ralias %s=%s",n->alias,n->replace);
    n = n->next;
  }
}

/*This function add commands to the list of functions created by the ';' operator*/
void addCommand(char line[]) {
  struct multiple *n = (struct multiple*) malloc(sizeof(struct multiple));
	struct multiple *p = (struct multiple*) malloc(sizeof(struct multiple));
	p = first;
  n->next = NULL;
	int i = 0;
  while(line[i] != '\0') {
    n->command[i] = line[i];
    i++;
  }
	n->command[i] = '\0';
	if(first == NULL)
  {
    first = n;
  }
  else
  {
    while(p->next != NULL) {
    	p = p->next;
  	}
  	p->next = n;
	}
}

/*This function adds commands or strings to the history list*/
void addHistory(char line[]) {
  struct history *n = (struct history*) malloc(sizeof(struct history));
  struct history *p = (struct history*) malloc(sizeof(struct history));
  p = head;
  n->next = NULL;
	n->count = counter++;
  int i = 0;
  while(line[i] != '\0') {
    n->history[i] = line[i];
    i++;
  }
  n->history[i] = '\0';
  if(head == NULL)
  {
    head = n;
  }
  else
  {
    while(p->next != NULL) {
    	p = p->next;
  	}
  	p->next = n;
	}
	if (n->count > 20)
		removeFirsthistory();
}

/*This function prints all the elements in the history list*/
void printHistory(condition) {
	struct history *n = head;
	if (!condition) {
  	while(n != NULL) {
    	printf("	 %d %s\n",n->count,n->history);
    	n = n->next;
  	}
	}
	else if (condition) {
		pipefile = fopen("pipe", "a");
  	while (n != NULL)
    {
  		fprintf(pipefile,"	 %d %s\n",n->count,n->history);
			n = n->next;
    }
		fclose(pipefile);
	}
}

/*This function returns the number of the last command used in history*/
int lastCommand(index) {
	struct history *n = head;
	int count = 0;
	while(n != NULL) {
    count++;
		n = n->next;
  }
	return (count-index);
}

/*This function returns the size of a string in the history list*/
int sizeList (index) {
	struct history *n = head;
	int count = 0;
  while(n != NULL) {
		if(n->count == index)
			{
				break; break;
			}
    n = n->next;
  }
	if (n != NULL) {
		while(n->history[count] != '\0') {
    	count++;
  	}
	}
	return count;
}

/*This function returns the size of the command used in the ';' operator*/
int sizeCommand () {
	struct multiple *n = first;
	int count = 0;
	if(n != NULL)
	{
		while(n->command[count] != '\0') {
    	count++;
  	}
	}
	return count;
}

/*This function returns the actual command used in the ';' operator*/
char executeCommand (index,character) {
	struct history *n = head;
	int find = 0;
  while(n != NULL) {
		if(n->count == index)
		{
			find = 1;
			break; break;
		}
    n = n->next;
  }
	if (find == 1) return n->history[character];

	return ' ';
}

/*This function returns the first command used in the ';' operator*/
char executeNewCommand (character) {
	return first->command[character];
}

int main()
{
	/*This character array holds the path string to run the command on
	This value is received from the 'checkPath' Linked List to simulate multiple paths.
	This means that, if a new path is exported, it will be able to run commands in
	that environment*/
	char progpath[20];

	/*Here, we see '/bin' being added as a path, and char pointer 'path' receiving it*/
	addPath("/bin/");
  char* path = checkPath(1); //1 being the head of the list, /bin/ in this case

	/*This character array holds the command string to run in the environment
	This is the string that does,in the end, get used to run the given command
	which is given by the 'line' character array*/
  char* argv[100];

	/*This variable determines whether or not the file 'mshrc' is to be read.
	This is done by inputting 'readfile' as a command. Once executed, this is set to 1
	and the file is read in through getc*/
	int readfile = 0;

	/*This sequence finally opens the 'mshrc' file and stores it to mshrc.
	If it is not found, the program exits*/
	mshrc = fopen("mshrc", "r");

	if(mshrc == NULL){
    printf("Couldn't find mshrc. \n");
    exit(0);
	}
	
	/*This while loop will continue until the user or mshrc exits*/
  while(1)
  {
		
		/*This character array receives the users input but
		manipulates it ro run an actual command in the shell*/
		char line[maxLen] = "";
		/*This character array receives the users raw input.
		This is what the user sees when inputting a string*/
		char temp[maxLen] = "";

		/*These next values determine small changes in display mostly*/

		/*This variable determines if any of the paths in the list contain the given command*/
		int goodpath = 0;
		/*This variable determines if it is the first time reading msrhc*/
		int firstread = 0;
		/*This variable determines if a carriage return is necessary*/
		int carriage = 0;
		/*This variable determines if their is a command on the ';' operator.
		If so, it does not read another carriage return when exitting (i.e. 'ls;exit'*/
		int readline = 0;

		//
		int readpath = 0;

		/*This removes the first command in the 'multiple' linked list, which uses the ';'
		operator if the list contains more than 0 commands. This is necessary when
		running commands through the path later on with the 'exectueCommand' function.
		Basically, if a command is found in the 'mulitple' linked list, it will be executed
		then deleted when it gets here until there are no more commands left in the list*/
		if (sizeCommand() != 0) removeFirstCommand();

		/*This simply prints the '?:' before reading in any user input. It only occurs when
		the 'multiple' list is complete, as to not display when multiple commands are being
		run through the path*/
    if (sizeCommand() == 0) printf("\r?: ");

		/*If there are no more commands, a carriage return is required, hence carriage being
		set to 1 in this case*/
		if (sizeCommand() == 0) carriage = 1;

		/*This variable is used in EVERY array manipulation, whether it be copying or pasting*/
		int index = 0;

		/*This variable is used later to determine the output of a command to pipe into another
		command, pr or more*/
  	char var[40];


    int historyn = 0;
		int exitn = 0;
		int repeat = 0;
		int space = 0;

		int backspaces = 0;
		int enter = 0;
		int semicolon = 0;
		int incomplete = 0;
		int empty = 0;
		char nospace[maxLen];

		int printalias = 0;
		int alias = 0;
		int aliasing = 0;
		int unalias = 0;
		int unaliasing = 0;
		int exportpath = 0;
		int arrow = 0;
		int size = 0;
		int pipe = 0;

		int findA = 0;

    int ch;
    int j = 0;
		int k = 0;
		system("stty raw -echo");
		int scroll = -1;
		if (sizeCommand() != 0) {
			size = sizeCommand();
			index = 0;
			while(index < size) {
				line[index] = executeNewCommand(index);
    		index++;
			}
			readline = 1;
				if (strncmp(line,"unalias",7) == 0) unalias = 1;
				else if (strncmp(line,"alias",5) == 0) alias = 1;

				if (strncmp(line,"!!",2) == 0) repeat = 1;
				else if (strncmp(line,"!",1) == 0) repeat = 2;
      	else repeat = 0;

				if (strchr(line,';') != NULL) semicolon = 1;

				if (strchr(line,'|') != NULL) pipe = 1;

				if (strncmp(line,"export PATH",7) == 0) exportpath = 1;

				if (repeat == 1) {
				index = 0;
				while(line[index] != '\0') {
					line[index] = '\0';
    			index++;
  			}
				index = 0;
				while(temp[index] != '\0') {
					temp[index] = '\0';
    			index++;
  			}
				int lineNumber = lastCommand(0);
				size = sizeList(lineNumber);
				if (size == 0) {break;break;}
				index = 0;
				while(index < size) {
					line[index] = executeCommand(lineNumber,index);
					temp[index] = line[index];
    			index++;
				}
				printf("\n\r%s",line);
      	if (strncmp(line,"exit",4) == 0) exitn = 1;
      	if (strncmp(line,"history",7) == 0) historyn = 1;
      	else historyn = 0;
				if (strncmp(line,"readfile",9) == 0) readfile = 1;
				if (strchr(line,';') != NULL) semicolon = 1;
			}
			if (repeat == 2) {
				index = 1;
				char lineNumber[maxLen];
				while(line[index] != '\0') {
					lineNumber[index-1] = line[index];
    			index++;
  			}
				while(line[index] != '\0') {
					line[index] = '\0';
    			index++;
  			}
				index = 0;
				while(temp[index] != '\0') {
					temp[index] = '\0';
    			index++;
  			}
				lineNumber[index] = '\n';
				if (atoi(lineNumber) <= 0) {break;break;}
				size = sizeList(atoi(lineNumber));
				if (size == 0) {break;break;}
				index = 0;
				while(index < size) {
					line[index] = executeCommand(atoi(lineNumber),index);
					temp[index] = line[index];
    			index++;
				}
				printf("\n\r%s",line);
				if (strncmp(line,"exit",4) == 0) exitn = 1;
      	if (strncmp(line,"history",7) == 0) historyn = 1;
      	else historyn = 0;
				if (strncmp(line,"readfile",9) == 0) readfile = 1;
				if (strchr(line,';') != NULL) semicolon = 1;
			}

				if (semicolon == 1) {
					char element[maxLen];
					index = 0;
					while(line[index] != '\0')
					{
						k = 0;
						while(line[index] != ';' && line[index] != '\0') {
							element[k] = line[index];
							k++;
							index++;
						}
						index++;
						element[k] = '\0';
						addCommand(element);
						k = 0;
						while(element[k] != '\0') {
							element[k] = '\0';
    					k++;
  					}
					}
					alias = 0;
					unalias = 0;
				}

				if (alias == 1) {
					char aliasLine[maxLen];
					char replaceLine[maxLen];
					index = 6;
					k = 0;
					if (line[index] == '\0') {
						printf("\r?: %s",temp);
						printf("\n\rIncomplete 'alias' - syntax is 'alias name=command'");
						incomplete = 1;
						break;break;
					}
					while(line[index] != '=') {
						aliasLine[k] = line[index];
						k++;
						index++;
					}
					aliasLine[k] = '\0';
					addAlias(aliasLine);
					k = 0;
					index++;
					if (line[index] == '\0') {
						printf("\r?: %s",temp);
						printf("\n\rIncomplete 'alias' - syntax is 'alias name=command'");
						incomplete = 1;
						break;break;
					}
					while(line[index] != '\0') {
						replaceLine[k] = line[index];
						k++;
						index++;
					}
					replaceLine[k] = '\0';
					replaceAlias(replaceLine);
				}
				if (unalias == 1) {
					char unaliasLine[maxLen];
					index = 8;
					k = 0;
					if (line[index] == '\0') {
						printf("\r?: %s",temp);
						printf("\n\rIncomplete 'unalias' - syntax is 'unalias name'");
						incomplete = 1;
						break;break;
					}
					while(line[index] != '\0') {
						unaliasLine[k] = line[index];
						k++;
						index++;
					}
					unaliasLine[k] = '\0';
					findA = 0;
					if ((findA = findAlias(unaliasLine)) > 0) {
						removeAlias(findA);
					}
				}
				if (exportpath == 1)
				{
					char* pathing = line + 18;
					addPath(pathing);
				}
				if (pipe == 1) {
					char tempLine[maxLen];
					char commandLine[maxLen];
					index = 0;
					while(line[index] != '|') {
						tempLine[index] = line[index];
						index++;
					}
					tempLine[k] = '\0';
					index++;
					k = 0;
					while(line[index] != '\0') {
						commandLine[k] = line[index];
						k++;
						index++;
					}
					commandLine[k] = '\0';
					index = 0;
      		if (strncmp(line,"history",7) == 0) {
						historyn = 1;
						printHistory(1);
					}
      		else {
						pipecommand = popen(tempLine, "r");
						pipefile = fopen("pipe", "a");
  					while (fgets(var, sizeof(var), pipecommand) != NULL)
    				{
  						fprintf(pipefile,"%s",var);
    				}
						fclose(pipefile);
						pclose(pipecommand);
					}
					index = 0;
					while(line[index] != '\0') {
						line[index] = '\0';
    				index++;
  				}
					index = 0;
					while(commandLine[index] != '\0') {
						line[index] = commandLine[index];
    				index++;
  				}
					line[index++] = ' ';
					line[index++] = 'p';
					line[index++] = 'i';
					line[index++] = 'p';
					line[index++] = 'e';
					
					addCommand(line);

					index = 0;
					while(line[index] != '\0') {
						line[index] = '\0';
    				index++;
  				}

      		historyn = 0;
				}

				index = 0;
				while(line[index] != '\0') {
					line[index] = '\0';
    			index++;
  			}
				j = 0;
				int size = sizeCommand();
				while(j < size) {
					line[j] = executeNewCommand(j);
    			j++;
				}
      	if (strncmp(line,"exit",4) == 0) exitn = 1;
      	if (strncmp(line,"history",7) == 0) historyn = 1;
      	else historyn = 0;
				if (strncmp(line,"readfile",9) == 0) readfile = 1;
		}
		else
		{
		while(1)
    {
			if (readfile == 1) ch = getc(mshrc);
			else ch = getchar();
			if (ch == EOF) {
				printf("\r\n\r");
				kill(0,1);
			}
			if (ch == 27) {
				printf("\r                                                    ");
				enter = 0;
				arrow = 1;
				while (ch == 27)
				{
					if (readfile == 1) ch = getc(mshrc);
					else ch = getchar();
					if (readfile == 1) ch = getc(mshrc);
					else ch = getchar();
					
					if(ch == 65 && scroll < counter-2 ) {
						backspaces = 0;
						int lineNumber;
						lineNumber = lastCommand(++scroll);
						int size = sizeList(lineNumber);
						j = 0;
						k = 0;
						index = 0;
						while(temp[index] != '\0') {
							temp[index] = '\0';
    					index++;
  					}
						index = 0;
						while(line[index] != '\0') {
							line[index] = '\0';
    					index++;
  					}
						while(j < size) {
							line[j] = executeCommand(lineNumber,j);
							temp[j] = line[j];
							backspaces++;
							k++;
    					j++;
						}
					}
					if(ch == 66 && scroll > -1) {
						backspaces = 0;
						int lineNumber = lastCommand(--scroll);
						int size = sizeList(lineNumber);
						j = 0;
						k = 0;
						index = 0;
						while(temp[index] != '\0') {
							temp[index] = '\0';
    					index++;
  					}
						index = 0;
						while(line[index] != '\0') {
							line[index] = '\0';
							backspaces++;
    					index++;
  					}
						while(j < size) {
							line[j] = executeCommand(lineNumber,j);
							temp[j] = line[j];
    					j++;
						}
					}
				}
			}
			else {
				if (enter == 0) {
					printf("\r                                                    ");
					printf("\r?: ");
				}
				enter = 1;
				arrow = 0;
			}
			if ((ch == '\n' || ch == 13)) {

				if (line[0] == '\0') {empty = 1;break;break;}

				if (strncmp(line,"unalias ",8) == 0) unalias = 1;
				else if (strncmp(line,"alias ",6) == 0) alias = 1;

				if (strncmp(line,"!!",2) == 0) repeat = 1;
				else if (strncmp(line,"!",1) == 0) repeat = 2;
      	else repeat = 0;

				if (strchr(line,';') != NULL) semicolon = 1;

				if (strchr(line,'|') != NULL) pipe = 1;

				if (strncmp(line,"export PATH=$PATH:",18) == 0) exportpath = 1;

				if (repeat == 1) {
				index = 0;
				while(line[index] != '\0') {
					line[index] = '\0';
    			index++;
  			}
				index = 0;
				while(temp[index] != '\0') {
					temp[index] = '\0';
    			index++;
  			}
				int lineNumber = lastCommand(0);
				int size = sizeList(lineNumber);
				if (size == 0) {break;break;}
				index = 0;
				while(index < size) {
					line[index] = executeCommand(lineNumber,index);
					temp[index] = line[index];
    			index++;
				}
				printf("\n\r%s",line);
				if (strchr(line,';') != NULL) semicolon = 1;
			}
			if (repeat == 2) {
				index = 1;
				char lineNumber[maxLen];
				while(line[index] != '\0') {
					lineNumber[index-1] = line[index];
    			index++;
  			}
				while(line[index] != '\0') {
					line[index] = '\0';
    			index++;
  			}
				index = 0;
				while(temp[index] != '\0') {
					temp[index] = '\0';
    			index++;
  			}
				lineNumber[index] = '\n';
				if (atoi(lineNumber) <= 0) {break;break;}
				int size = sizeList(atoi(lineNumber));
				if (size == 0) {break;break;}
				index = 0;
				while(index < size) {
					line[index] = executeCommand(atoi(lineNumber),index);
					temp[index] = line[index];
    			index++;
				}
				printf("\n\r%s",line);
				if (strchr(line,';') != NULL) semicolon = 1;
			}

				if (semicolon == 1) {
					char element[maxLen];
					index = 0;
					while(line[index] != '\0')
					{
						k = 0;
						while(line[index] != ';' && line[index] != '\0') {
							element[k] = line[index];
							k++;
							index++;
						}
						index++;
						element[k] = '\0';
						addCommand(element);
						k = 0;
						while(element[k] != '\0') {
							element[k] = '\0';
    					k++;
  					}
					}
				}

				if (alias == 1) {
					char aliasLine[maxLen];
					char replaceLine[maxLen];
					index = 6;
					k = 0;
					if (line[index] == '\0') {
						printf("\r?: %s",temp);
						printf("\n\rIncomplete 'alias' - syntax is 'alias name=command'");
						incomplete = 1;
						break;break;
					}
					while(line[index] != '=') {
						aliasLine[k] = line[index];
						k++;
						index++;
					}
					aliasLine[k] = '\0';
					addAlias(aliasLine);
					k = 0;
					index++;
					if (line[index] == '\0') {
						printf("\r?: %s",temp);
						printf("\n\rIncomplete 'alias' - syntax is 'alias name=command'");
						incomplete = 1;
						break;break;
					}
					while(line[index] != '\0' && line[index] != ';') {
						replaceLine[k] = line[index];
						k++;
						index++;
					}
					replaceLine[k] = '\0';
					replaceAlias(replaceLine);
				}
				if (unalias == 1) {
					char unaliasLine[maxLen];
					index = 8;
					k = 0;
					if (line[index] == '\0') {
						printf("\r?: %s",temp);
						printf("\n\rIncomplete 'unalias' - syntax is 'unalias name'");
						incomplete = 1;
						break;break;
					}
					while(line[index] != '\0' && line[index] != ';') {
						unaliasLine[k] = line[index];
						k++;
						index++;
					}
					unaliasLine[k] = '\0';
					findA = 0;
					if ((findA = findAlias(unaliasLine)) > 0) {
						removeAlias(findA);
					}
				}

				if (exportpath == 1)
				{
					char* pathing = line + 18;
					addPath(pathing);
				}
				if (pipe == 1) {
					char tempLine[maxLen];
					char commandLine[maxLen];
					index = 0;
					while(line[index] != '|') {
						tempLine[index] = line[index];
						index++;
					}
					tempLine[k] = '\0';
					index++;
					k = 0;
					while(line[index] != '\0') {
						commandLine[k] = line[index];
						k++;
						index++;
					}
					commandLine[k] = '\0';
					index = 0;
      		if (strncmp(line,"history",7) == 0) {
						historyn = 1;
						printHistory(1);
					}
      		else {
						pipecommand = popen(tempLine, "r");
						pipefile = fopen("pipe", "a");
  					while (fgets(var, sizeof(var), pipecommand) != NULL)
    				{
  						fprintf(pipefile,"%s",var);
    				}
						fclose(pipefile);
						pclose(pipecommand);
					}
					index = 0;
					while(line[index] != '\0') {
						line[index] = '\0';
    				index++;
  				}
					index = 0;
					while(commandLine[index] != '\0') {
						line[index] = commandLine[index];
    				index++;
  				}
					line[index++] = ' ';
					line[index++] = 'p';
					line[index++] = 'i';
					line[index++] = 'p';
					line[index++] = 'e';
					
      		historyn = 0;
				}

				if((alias == 0 && unalias == 0 && semicolon == 0 && exportpath == 0) ||
						pipe == 1)
					addCommand(line);

				index = 0;
				while(line[index] != '\0') {
					line[index] = '\0';
    			index++;
  			}
				j = 0;
				int size = sizeCommand();
				while(j < size) {
					line[j] = executeNewCommand(j);
    			j++;
				}
				if (strncmp(line,"alias",5) == 0) {
					printalias = 1; 
					printAlias();
				}
      	if (strncmp(line,"exit",4) == 0) exitn = 1;
      	if (strncmp(line,"history",7) == 0) historyn = 1;
      	else historyn = 0;
				if (strncmp(line,"readfile",9) == 0) readfile = 1;
				if (strncmp(line,"path",4) == 0) readpath = 1;

				break; break;
			}

			if ((ch == 127 || ch == 8) && backspaces > 0) {
					printf("\b");printf(" ");printf("\b");
					line[--j] = '\0';
					temp[--k] = '\0';
					backspaces--;
				}
			else if (ch != 127 && arrow == 0)
			{
				if (ch == ' ' && (line[0] == '\0' || line[j-1] == ';' || line[j-1] == '=' || line[j-1] == '|' ))
				{
					
				}
				else
				{
					temp[k++] = ch;
					line[j++] = ch;
					backspaces++;
				}
			}
			printf("\r                                                    ");
			printf("\r?: %s",temp);
    }
			line[j] = '\0';
		}

		if (empty == 0) {

    system("stty cooked sane");

		if ((strncmp(temp,"!",1) != 0) && temp[0] != '\0') {
			addHistory(temp);
		}

		if ((findA = findAlias(line)) > 0)
		{
			int sizeA = sizeReplace(findA);
			index = 0;
			while(line[index] != '\0') {
				line[index] = '\0';
    		index++;
  		}
				index = 0;
			while(index < sizeA) {
				line[index] = getAlias(findA,index);
				index++;
			}
		}
		if (incomplete == 0 && repeat == 0 && arrow == 0 && readline == 0 && printalias == 0) printf("\r?: %s",temp);

		if (repeat == 0 && sizeCommand() == 0) line[j] = '\n';

		if (strncmp(line,"exit",4) == 0) exitn = 1;
    if (strncmp(line,"history",7) == 0) historyn = 1;
      else historyn = 0;
		if (strncmp(line,"readfile",9) == 0) {
			firstread = 1;
			readfile = 1;
		}

    if (exitn == 1) {
			if (readline == 0)
				printf("\r\n\r");
			kill(0,1);
		}
    if (historyn == 1) {
			if (carriage == 1) printf("\n");
			printHistory(0);
		}
		if (readpath == 1) {
			if (carriage == 1) printf("\n");
			printPath();
		}

		j = 0;

		if (historyn == 0 && carriage == 1) printf("\n");

    if(historyn == 0 && alias == 0 && unalias == 0 && firstread == 0 && exportpath == 0 && readpath == 0 && printalias == 0) {

		int pathsize = sizePath();
		int i = 0;

		while(i < pathsize && goodpath == 0) {
		i++;

		path = checkPath(i);

    size_t length = strlen(line);

    if (line[length - 1] == '\n')
    line[length - 1] = '\0';

    char *token;
    token = strtok(line," ");
    int i = 0;

    while(token!=NULL){
        argv[i]=token;
        token = strtok(NULL," ");
        i++;
    }

    argv[i]= NULL;

    strcpy(progpath, path);
    strcat(progpath, argv[0]);

    for(i=0; i<strlen(progpath); i++){
      if(progpath[i]=='\n'){
        progpath[i]='\0';
      }
    }

    pid_t pid = fork();


    if(pid == 0)
    {
      execvp(progpath,argv);
    }
    else
    {
			goodpath = 1;
      wait(NULL);
    }
		if(pipe == 1)
		system("rm pipe");
	}
	if (!goodpath)
		fprintf(stderr, "Cannot execute: %s: command not found\n",line);
	}
}
else
{
	printf("\n");
}
}

	if (getc(mshrc) == EOF)
  exit(0);
	
	return 0;
}
