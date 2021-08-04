#define _CRT_SECURE_NO_WARNINGS
#define NAME_LENGTH 200
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define max_name 256
#define table_size 15
#define phone_number_size 11

/*define people struct*/
typedef struct {
	char* name;
	char phone_number[phone_number_size];
}people;


people* hash_table[table_size];

/*this function is use to build the hash table*/
void init_hash_table() {
	for (int i = 0; i < table_size; i++) {
		hash_table[i] = NULL;
	}
}
/*this function return the key index of the person in our data struct this is the strength of the hash table
that later on insted of iterate over our entire data struct we can just use the key index of the item we are
looking for*/
unsigned int hash_key(const char* name, int length) {
	unsigned int key = 0;
	for (int i = 0; i < length; i++) {
		key += name[i];
		key = key % table_size;
	}

	return key;
}


void hash_table_insert() {
	int name_length = 0;
	int i;
	int result;
	char temp_name[max_name];
	/*dynamically allocated  memory for a people type pointer*/
	people*person = malloc(sizeof(people));

	/*if dynamically allocated memory fail we deal with it*/
	if (person == NULL) {
		exit(1);
	}
	printf("\nplease enter the name of the person that you want to add to the phonebook:\n");
	fgets(temp_name, max_name, stdin);
	/*this for loop is checking if the name that the user gave us is valid*/
	for (i = 0; temp_name[i] != NULL; i++) {
		if (isalpha(temp_name[i]) == 0 && isspace(temp_name[i]) == 0) {
			/*if not we return a text message*/
			printf("it seems you enterd an invalid name\n");
			return 0;
		}
		if (temp_name[i] == '\n') {
			temp_name[i] = NULL;
		}
	}
	/*then we dynamic allocated memory for entire len of our person name */
	person->name = malloc(i * sizeof(char));

	/*if fail we deal with it*/
	if (person->name == NULL) {
		exit(1);
	}
	printf("\nwhat is the current phone number of the person you want to add?\n");

	fgets(person->phone_number, phone_number_size, stdin);

	/*use strcpy to copy the address of the name to our name pointer*/
	strcpy(person->name, temp_name);

	unsigned int Key = 0;
	/*then we get our index using our hash key maping function*/
	Key = hash_key(temp_name, i);
	/*if this place is full we deal with it*/
	if (hash_table[Key] != NULL) {
		if (strcmp(hash_table[Key]->name, temp_name) == 0) {
			printf("\nthis person is already in the phonebook!\n");
			return 0;
		}
		else {
			printf("\noops it seems that this spot in the phonebook is already taken by %s\n",hash_table[Key]->name);
			printf("if you still want to add a person you need to delet %s\n", hash_table[Key]->name);
			return 0;
		}
	}
	else {
		printf("%s has add successfuly to the phonebook\n", temp_name);
		hash_table[Key] = person;
		return 1;
	}

}


 void print_table() {
	 printf("\n----Ofek Sharabi online phonebook------\n");
	 for (int i = 0; i < table_size; i++) {
		 if (hash_table[i] == NULL) {
			 printf("\t%i\t_____\n", i);
		 }
		 else {
			 printf("\t%i\t%s--->number:%s\n", i, hash_table[i]->name,hash_table[i]->phone_number);
		 }
	 }
 }


 /*our search func that we will use alot*/
 int lookup() {
	 char name[max_name];
	 int i = 0;
	 printf("please enter the name of the person you want to find\n");
	 fgets(name, max_name, stdin);
	 /*we check if the name is valid*/
	 for (i = 0; name[i] != NULL; i++) {
		 if (isalpha(name[i]) == 0 && isspace(name[i]) == 0) {
			 /*if not we return a text message*/
			 printf("it seems you enterd an invalid name\n");
			 return 0;
		 }
		 if (name[i] == '\n') {
			 name[i] = NULL;
		 }
	 }
	 /*geting the place of our item in our hash table using hash maping algorithm*/
	 int index = hash_key(name, i);
	 /*if we found a match we return the key value*/
	 if (hash_table[index] != NULL && strcmp(hash_table[index]->name, name) == 0) {
		 return index;
	 }
	 else {
		 printf("\ndidnt find the person you where looking for, sorry!\n");
		 return NULL;
	 }
	
 }

 void search_number() {
	 /*use lookup to get the key*/
	 int index = lookup();
	 if (index != NULL) {
		 printf("\nthe number of the person you where looking for is %s\n\n", hash_table[index]->phone_number);
	 }
	
 }


 void remove_person (){
	 /*use lookup to get the key*/
	 int index = lookup();
	 if (index != NULL) {
		 /*if we got a match then we free the memory slot*/
		 printf("\n%s was deleted form the phone book\n", hash_table[index]->name);
		 /*creating a temp pointer that points to the memory loction of our item*/
		 people* temp = hash_table[index];
		 /*free this memory space*/
		 free(temp->name);
		 free(temp);
		 /*rest this spot to null*/
		 hash_table[index] = NULL;

	 }


}

 
void update_phone_number(){
	int index = lookup();
	if (index != NULL) {
		char new_phone_number[phone_number_size];
		printf("please enter the new phone number: ");
		fgets(new_phone_number, phone_number_size, stdin);
		strcpy(hash_table[index]->phone_number, new_phone_number);
	}

}
int main() {
	/*starting our hash table*/

	init_hash_table();

	int buffer = 0;
	/*main menu*/
	printf("------welcome to the first online phonebook-------\n");
	printf("---To add a person to the phonebook please press 1----\n");
	printf("---To update a phonenumber please press 2-------------\n");
	printf("---To remove a person form the phonebook please press 3----\n");
	printf("---To print the current phonebook please enter 4-----\n");
	printf("----To search a number please enter 5--------\n");
	printf("------------for exite please press 0-------\n");
	scanf("%d", &buffer);
	/*fgetc is to deal with the \n at the end of our user input*/

	fgetc(stdin);

	/*check if our user input is valid if not, we give the user a chance to fix it*/

	while (buffer>5||buffer<0) {
		printf("invalid input please try again!\n");
		printf("---To add a person to the phonebook please press 1----\n");
		printf("---To update a phonenumber please press 2-------------\n");
		printf("---To remove a person form the phonebook please press 3----\n");
		printf("---To print the current phonebook please enter 4-----\n");
		printf("----To search a number please enter 5--------\n");
		printf("------------for exite please press 0-------\n");
		scanf("%d", &buffer);
		fgetc(stdin);
		if (buffer == 0 || buffer == 1 || buffer == 2 || buffer == 3 || buffer == 4||buffer==5) {
			break;
			 }
	}


	while (buffer == 0 || buffer == 1 || buffer == 2 || buffer == 3 || buffer == 4||buffer==5) {
		if (buffer == 1) {
			hash_table_insert();
		}

		if (buffer == 2) {
			update_phone_number();
		}

		if (buffer == 3) {
			remove_person();
		}

		if (buffer == 4) {
			print_table();
		}

		if (buffer == 5) {
			search_number();
		}

		if (buffer == 0) {
			exit(1);
		}
		buffer = 0;
		printf("\n---To add a person to the phonebook please press 1----\n");
		printf("---To update a phonenumber please press 2-------------\n");
		printf("---To remove a person form the phonebook please press 3----\n");
		printf("---To print the current phonebook please enter 4-----\n");
		printf("----To search a number please enter 5--------\n");
		printf("------------for exite please press 0-------\n");
		scanf("%d", &buffer);
		fgetc(stdin);
		while (buffer > 5 || buffer < 0) {
			printf("invalid input please try again!\n");
			printf("---To add a person to the phonebook please press 1----\n");
			printf("---To update a phonenumber please press 2-------------\n");
			printf("---To remove a person form the phonebook please press 3----\n");
			printf("---To print the current phonebook please enter 4-----\n");
			printf("----To search a number please enter 5--------\n");
			printf("------------for exite please press 0-------\n");
			scanf("%d", &buffer);
			fgetc(stdin);
			if (buffer == 0 || buffer == 1 || buffer == 2 || buffer == 3 || buffer == 4 || buffer == 5) {
				break;
			}
		}
	}

	return 0;
}