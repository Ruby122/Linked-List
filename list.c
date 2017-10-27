#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node {
    char last[30];
    char first [20];
    unsigned int id;
    struct node* link;
} ListNode;

int main(int argc, const char * argv[]) {
	//read the input file
	FILE* file;
	/* IMPORTANT: 
	   w+: clean the text file first and then read or write
	   r: read and write*/
	file = fopen("a.txt", "r");
	//declare the head and initialize the first node
	ListNode *afterMe, *temp, *head = malloc(sizeof(ListNode));;
	if(file == NULL){
		printf("Cannot open the data file.");
		perror("Error");
		return -1;
	}
	else{
		//declare a temp pointer pointing the the same node as head
		temp = head;
		//read the last name and the first name 
		char input[52];//last + first + , + \0 ????????????????
		//count the iteration of while loops
		int counter = 1;
		//" %s" ignore spaces before the last name
		while (fscanf(file, " %s", input) != EOF) {
			//separate first and last name
			int i;
			for (i = 0; i < strlen(input); i++){
				if(input[i] == ','){
					break;
				}
				temp->last[i] = input[i];
			}
			i++;//skip the comma and read the first name
			int j = 0;
			while(i < strlen(input)){
				temp->first[j] = input[i];
				i++;
				j++;
			}
			temp->first[j] =  '\0';//or there will be ? at the end of first name?????
			fscanf(file, " %u", &temp->id);
			//insert a new node
			if(counter > 1){
				//insert temp at the beginning (no duplicate)
				if(head->id > temp->id){
					//printf("insert at the beginning\n");
					temp->link = head;
					head = temp;	
				}
				//insert in the middle
				//find the pointer to a node after which the new node should be inserted 	
				else{
					afterMe = head;
					while (afterMe->link != NULL && afterMe->id <= temp->id){
						if(afterMe->link->id > temp->id){
							break;
						}
						afterMe = afterMe->link;
					}
					//check for duplicate ids
					if(afterMe->id != temp->id){
						temp->link = afterMe->link;
						afterMe->link = temp;
					}
					//report duplicate id items
					else{
						printf("Input: %d %s its id  =  %u already exists; Not added to the list!\n", counter, input, temp->id);
						//decrease the number of node since we do not add the node with duplicate id 
						counter--;
					}					
				}				
			}
			counter++;	
			//temp points to a new node 
			temp = malloc(sizeof(ListNode));
			//clear the char array inout?????
			memset(input,0, strlen(input));
		}
		//print number of nodes
		temp = head;
		counter = 0;
		do{
			counter++;
			temp = temp->link;
		}while(temp != NULL);
		printf("Number of nodes = %d\n\n", counter);
		//print, add, or delete node
		char response;
		int num;
		int count;
		while(1){
			printf("Enter p to print list, a to add node, d to delete node, e to exit: ");
			scanf(" %c", &response);
			printf("You entered = %c\n", response);
			//print the list
			if(response == 'p'){
				temp = head;
				do{
					printf("%s %s %d\n", temp->last, temp->first, temp->id);
					temp = temp->link;
				}while(temp != NULL);
				printf("\n");
			}
			//insert a node
			else if(response == 'a'){
				printf("Enter First, Last, and id: ");
				temp = malloc(sizeof(ListNode));
				scanf(" %s %s %u", temp->first, temp->last, &temp->id);
				printf("You entered = %s %s %u\n", temp->first, temp->last, temp->id);
				//insert temp at the beginning (no duplicate)
				if(head->id > temp->id){
					//printf("insert at the beginning\n");
					temp->link = head;
					head = temp;	
					counter++;	
					printf("Node added to the list; Number of nodes = %d\n", counter);
				}
				//insert in the middle
				//find the pointer to a node after which the new node should be inserted 	
				else{
					afterMe = head;
					while (afterMe->link != NULL && afterMe->id <= temp->id){
						if(afterMe->link->id > temp->id){
							break;
						}
						afterMe = afterMe->link;
					}
					//check for duplicate ids
					if(afterMe->id != temp->id){
						temp->link = afterMe->link;
						afterMe->link = temp;
						counter++;	
						printf("Node added to the list; Number of nodes = %d\n\n", counter);
					}
					//report duplicate id items
					else{
						printf("Input: %d %s its id = %u already exists; Not added to the list!\n\n", counter + 1, input, temp->id);
					}					
				}		
			}
			//delete a node
			else if(response == 'd'){
				//since each node has a unique id, we can locate a node according to its id
				printf("Enter Node number to delete: ");
				scanf(" %d", &num);				
				if(num > counter || num < 0){
					printf("illegal Node number!\n\n");
				}
				else{
					afterMe = head;
					//remove the first node
					if(num == 1){
						head = afterMe->link;
						free(afterMe);
					}
					//remove from the middle
					else{
						//find the node after which the node with corresponding number should be deleted
						for(int i = 1; i < num - 1; i++){
							afterMe = afterMe->link;
						}
						temp = afterMe->link;
						afterMe->link = temp->link;
					}
					counter--;
					printf("Node deleted from the list; Number of nodes = %d\n\n", counter);
				}
			}
			else if (response == 'e'){
				break;
			}
		}
	}
	fclose(file);
	free(temp);
	//free(afterMe);otherwise we have double free 
	return 0;
}
