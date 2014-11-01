/*
 * File:   	main.c
 * Author: 	kshitijkarthick
 * Program:	Basic Editor
 * Created on August 31, 2014, 4:49 PM
*/

#include<stdio.h>
#include<stdlib.h>
#include "conio.h"

#define WORD_SIZE 10
// Double Linked List Implementation.
struct node
{
	char info[WORD_SIZE];
	struct node *llink;
	struct node *rlink;
};

typedef struct node *Node;
Node root = NULL;  // Root node creation.

// Function Declarations.
Node createNode(Node);
Node deleteNode(Node);
void print();
void save();
void keyboardInput();
void lines(int);
void clearscr();
void fileInput(char*);

int noOfChar=0;       // No of Characters in the current Node.
int totalNoOfLines=1;	// Total no of NewLine Characters.
int totalNoOfChar=0;	// Total no of Characters.
char* FILENAME;    // Filename given as cmd line arguments.

/*
	Receive the command line argument for filename and call the input function
*/
int main(int argc,char* argv[])
{
	root=(Node) malloc(sizeof(struct node));
	if(argc>1)
	{
		FILENAME=argv[1]; // Filename stored for creating and storing data.
		fileInput(FILENAME);
		keyboardInput();
	}
	else
		printf("Error! please give filename as command line argument\nThe program will exit now");
	return 0;
}

/*
	Reads a file and loads it into all Nodes.
 */
void fileInput(char *FILENAME)
{
	FILE *fp;
	if(fp=fopen(FILENAME,"r"))
		{
			char ch;
			Node temp=root;
			while( ( ch = fgetc(fp) ) != EOF )
      		{
      			//printf("\n%c->",ch);
      			noOfChar++;
      			(ch=='\n')?(totalNoOfChar++,totalNoOfLines++):(totalNoOfChar++); // Add Count of Character and NewLine.
      			// Normal character storage in the Node.
      			if(noOfChar <= WORD_SIZE)
					temp->info[noOfChar - 1]=ch;
      			// Node Creation for adding the Character.
				else
				{
					temp=createNode(temp);
					noOfChar=1;
					temp->info[noOfChar-1]=ch;
				}
      		}
      		fclose(fp);
		}
}

/*
	Creates a Node, links it to the previous Nodes and returns the address of the new node.
*/
Node createNode(Node parent)
{
	int i;
	Node temp=(Node) malloc(sizeof(struct node)); // Node Creation and joining the Node with previous nodes.
	parent->rlink=temp;
	temp->llink=parent;
	for(i=0;i<WORD_SIZE;i++)
		temp->info[i]='\0';
	return temp;
}

/*
	Deletes a node and returns the previous Node , edge case: does not delete if it is the root node
*/
Node deleteNode(Node current)
{
	Node temp=current->llink;

	// Delete a Node if it is not the root node.
	if(current!=root)
	{
		free(current);
		temp->rlink=NULL;
		return temp;
	}

	// Warning message if explicit Root node deletion.
	else
	{
		printf("\n\nError! cannot delete root node \nPress Enter key to continue");
		getchar();
		print();
		return current;
	}
}

/*
	Save the Entered data onto the File specified in command line arguments of the program. Edge Case:No append option only used to create new files.
*/
void save()
{
	FILE *fp=fopen(FILENAME,"w");
	Node temp;
	int i;
	// Node traversal from the root node to all other nodes.
	for(temp=root;temp!=NULL;temp=temp->rlink)
	{
		for(i=0;i<WORD_SIZE && temp->info[i]!='\0';i++)
			fputc(temp->info[i],fp); // Store data of each node in the File.
		
	}
	fclose(fp); // Close File Stream.
	printf("\n\t\t\tFile Saved Successfully\n");
}

/*
	Print all the entered Characters on the console
*/
void print()
{
	int i;
	clearscr();
	lines(2);
	printf("\n\t\t\tBasic Editor\n");
	printf("\t\t\tSave Option : ctrl + c or ctrl + z\n");
	lines(2);
	lines(0);
	printf("\t\t\tInput Field:\n\n");
	Node temp;
	// Node traversal from the root node to all other nodes.
	for(temp=root;temp!=NULL;temp=temp->rlink)
	{
		for(i=0;i<WORD_SIZE && temp->info[i] != '\0';i++)
			printf("%c",temp->info[i]); // Print the data of each node to the screen.
	}
}

/*
	Receives character by character input from the console , and exits the input mode on entry of ctr + c or ctrl + z
*/
void keyboardInput()
{
	
	char ch;
	print();
	Node temp=root;
	while(temp->rlink!=NULL)
		temp=temp->rlink;
	ch=getche();

	// Receive input and check if input is not ctrl + c and ctrl + z
	while( ch != 3 && ch != 26 )
	{
		noOfChar++;
		//printf("\n%d\t->\t%c:\t%d\n",noOfChar,ch,(int)ch);
		if(( ch == 8 || ch == 127 )) // Check Backspace character
		{
			if(noOfChar>1)
				noOfChar--;	// Remove the count of Backspace as character.				
			(temp->info[noOfChar-1]=='\n')?(totalNoOfChar--,totalNoOfLines--):(totalNoOfChar--); // Reduce count of characters deleted.

			// if previous node character to be deleted then delete current node and delete previous node last character
			if(noOfChar == 1)
			{

				//Normal Node Deletion.
				if(temp!=root)
				{
					temp=deleteNode(temp);
					noOfChar=WORD_SIZE;
				}

				// Root node not deleted, only last character made null.
				else
				{
					temp->info[noOfChar-1]='\0';
					noOfChar=0;
				}
			}

			// Delete Last character and append null in that position.
			if(noOfChar <= WORD_SIZE && noOfChar > 0)
			{
				temp->info[noOfChar - 1]='\0';
				noOfChar--;
			}
			print();
		}
		else
		{
			(ch=='\n')?(totalNoOfChar++,totalNoOfLines++):(totalNoOfChar++); // Add Count of Character and NewLine.
			
			// Normal character addition in the same Node.
			if(noOfChar <= WORD_SIZE)
				temp->info[noOfChar - 1]=ch;
		
			// Node Creation for adding the Character.
			else
			{
				temp=createNode(temp);
				noOfChar=1;
				temp->info[noOfChar-1]=ch;
				fflush(stdin);
			}
		}
		ch=getche(); // Character input from conio.h.
	}
	print();
	lines(0);
	lines(1);
	save();
	printf("\n\t\t\tNo Of Characters:%d\n\t\t\tNo of Lines:%d\n",totalNoOfChar,totalNoOfLines);
	lines(1);
}

/*
	Printing the required type of Lines.
*/
void lines(int option)
{
	switch(option)
	{
		case 1:
			printf("\n************************************************************************\n");
			break;
		case 2:
			printf("\n+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+\n");
			break;
		default:
			printf("\n------------------------------------------------------------------------\n");
	}
}

/*
	OS Independent clear screen functionality.
*/
void clearscr()
{
	#if defined(__CYGWIN__) && !defined(_WIN32)
	/* Cygwin POSIX under Microsoft Windows. -------------------- */
  		system("cls");
	#elif !defined(_WIN32) && (defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__)))
	/* UNIX-style OS. ------------------------------------------- */
		system("clear");
	#else
		printf("\n\n\t\tSorry the OS is not supported,the editor cannot function properly in this target OS\n\t\t\tPress Enter key to Exit.");
		getchar();
		exit(-1);
	#endif
}
