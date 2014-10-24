/*
 * File:   	main.c
 * Author: 	kshitijkarthick
 * Program:	Basic Editor
 * Created on August 31, 2014, 4:49 PM
*/

#include<stdio.h>
#include<stdlib.h>
#include "conio.h"

// Double Linked List Implementation.
struct node
{
	char info[10];
	struct node *llink;
	struct node *rlink;
};

typedef struct node *Node;
Node root = NULL;  // Root node creation.
char* FILENAME;    // Filename given as cmd line arguments.

Node createNode(Node);
Node deleteNode(Node);
void print();
void save();
void input();
void lines(int);
void clearscr();

/*
	Receive the command line argument for filename and call the input function
*/
int main(int argc,char* argv[])
{
	root=(Node) malloc(sizeof(struct node));
	if(argc>1)
	{
		FILENAME=argv[1]; // Filename stored for creating and storing data.
		input();
	}
	else
		printf("Error! please give filename as command line argument\nThe program will exit now");
	return 0;
}

/*
	Creates a Node, links it to the previous Nodes and returns the address of the new node.
*/
Node createNode(Node parent)
{
	Node temp=(Node) malloc(sizeof(struct node)); // Node Creation and joining the Node with previous nodes.
	parent->rlink=temp;
	temp->llink=parent;
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
	Node temp=root;

	// Node traversal from the root node to all other nodes.
	while(temp!=NULL)
	{
		fprintf(fp,temp->info); // Store data of each node in the File.
		temp=temp->rlink;
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
	Node temp=root;

	// Node traversal from the root node to all other nodes.
	while(temp!=NULL)
	{
		for(i=0;i<10;i++)
			printf("%c",temp->info[i]); // Print the data of each node to the screen.
		temp=temp->rlink;
	}
}

/*
	Receives character by character input from the console , and exits the input mode on entry of ctr + c or ctrl + z
*/
void input()
{
	print();
	char ch;
	int noOfChar=0;       // No of Characters in the current Node.
	int totalNoOfLines=1;	// Total no of NewLine Characters.
	int totalNoOfChar=0;	// Total no of Characters.
	Node temp=root;
	ch=getche();

	// Receive input and check if input is not ctrl + c and ctrl + z
	while( ch != 3 && ch != 26 )
	{
		noOfChar++;
		//printf("\n%d->%c:%d\n",noOfChar,ch,ch);
		if(( ch == 8 || ch == 127 ) && noOfChar > 1) // Check Backspace character
		{
			noOfChar--;	// Remove the count of Backspace as character.
			(temp->info[noOfChar-1]=='\n')?(totalNoOfChar--,totalNoOfLines--):(totalNoOfChar--); // Reduce count of characters deleted.

			// if previous node character to be deleted then delete current node and delete previous node last character
			if(noOfChar == 1)
			{

				//Normal Node Deletion.
				if(temp!=root)
				{
					temp=deleteNode(temp);
					noOfChar=10;
				}

				// Root node not deleted, only last character made null.
				else
				{
							temp->info[0]='\0';
							noOfChar=0;
				}
			}

			// Delete Last character and append null in that position.
			else if(noOfChar < 11)
			{
				temp->info[noOfChar - 1]='\0';
				noOfChar--;
			}
			print();
		}

		// Node Creation for adding the Character.
		else if(noOfChar > 10)
		{
			(ch=='\n')?(totalNoOfChar++,totalNoOfLines++):(totalNoOfChar++); // Add Count of Character and NewLine.
			temp=createNode(temp);
			noOfChar=1;
			temp->info[noOfChar-1]=ch;
		}

		// Normal character addition in the same Node.
		else if(noOfChar < 11)
		{
			(ch=='\n')?(totalNoOfChar++,totalNoOfLines++):(totalNoOfChar++); // Add Count of Character and NewLine.

			temp->info[noOfChar - 1]=ch;
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
