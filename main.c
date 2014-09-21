/*
 * File:   main.c
 * Author: kshitijkarthick
 *
 * Created on August 31, 2014, 4:49 PM
 */

#include<stdio.h>
#include<stdlib.h>
#include "conio.h"
struct node																													//Double Linked List Implementation.
{
	char info[11];
	struct node *llink;
	struct node *rlink;
};
typedef struct node *Node;
Node root = NULL;																										//Root node creation
char* FILENAME;																											//Filename given as cmd line arguments

/*
	Creates a Node, links it to the previous Nodes and returns the address of the new node.
*/
Node createNode(Node parent)
{
	Node temp=(Node) malloc(sizeof(struct node));											//Node Creation and joining the Node with previous nodes.
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
	if(temp!=root)																										//Delete a Node if it is not the root node.
	{
		free(current);
		temp->rlink=NULL;
		return temp;
	}
	else
	{
		printf("\nError! cannot delete root node \nPress Enter key to continue");
		getchar();
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
	while(temp!=NULL)																									//Node traversal from the root node to all other nodes.
	{
		fprintf(fp,temp->info);																					//Store data of each node in the File.
		temp=temp->rlink;
	}
	fclose(fp);
	printf("\nFile Saved Successfully\nPress Enter key to Exit\n");
	getchar();
}

/*
	Print all the entered Characters on the console
*/
void print()
{
	//system("cls"); for dos operating system
	//system("clear"); for unix operating system
	Node temp=root;
	while(temp!=NULL)																									//Node traversal from the root node to all other nodes.
	{
		printf("%s",temp->info);																				//Print the data of each node to the screen.
		temp=temp->rlink;
	}
}

/*
	Receives character by character input from the console , and exits the input mode on entry of ctr + c or ctrl + z
*/
void input()
{
	char ch;
	int noOfChar=-1;
	Node temp=root;
	ch=getche();
																																		//receive input and check if input is not ctrl + c and ctrl + z
	while( ch != 3 && ch != 26 )
	{
		noOfChar++;
		if(ch == 8)																											//check Backspace character
		{
			if(noOfChar == 0)																							// if previous node character to be deleted then delete current node and delete previous node last character
			{
				temp=deleteNode(temp);
				noOfChar=9;
				temp->info[noOfChar--]='\0';
			}
			else if( noOfChar < 10 )
				temp->info[-- noOfChar ]='\0';															// last node traverses to previous node and delete last character
			print();
		}
		else if(noOfChar>10)
		{
			temp=createNode(temp);
			noOfChar=0;
		}
		temp->info[noOfChar]=ch;
		ch=getche();
	}
	save();
}

/*
	Receive the command line argument for filename and call the input function
*/
int main(int argc,char* argv[])
{
	root=(Node) malloc(sizeof(struct node));
	if(argc>1)
	{
		FILENAME=argv[1];																								//Filename stored for creating and storing data.
		input();
	}
	else
		printf("Error! please give filename as command line argument\nThe program will exit now");
	return 0;
}
