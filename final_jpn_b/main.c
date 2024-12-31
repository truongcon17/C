#include <stdio.h>
#include <stdlib.h>
#include "Function.h" 

int main(int argc, char *argv[]) {
	int choose;
	
	do{
		displayMenu();
		scanf("%d", &choose);
		getchar();
		switch (choose) {
			case 1:{
				addStudent();
				break;
			}
			case 2:{
				displayStudents();
				break;
			}
			case 3:{
				updateStudents();
				break;
			}
			case 4:{
				
				break;
			}
			case 5:{
				
				break;
			}
			case 6:{
				
				break;
			} 
			case 0:{
				printf("Exit the program");
				break;
			}
			default:
                printf("Invalid selection. Please try again.\n");
			
		}
	}while(choose !=0);

	return 0;
}
