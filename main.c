#include <stdio.h>
#include "assets.h"
void displayMainMenu();
int main() {
    int choice;
    printf("========================================\n");
    printf(" MUNICIPAL SYSTEM - Windhoek - Group 3\n");
    printf(" Member 4: 221083685 - Asset\n");
    printf("========================================\n");
    do {
        displayMainMenu();
        printf("Enter choice: ");
        if(scanf("%d",&choice)!=1){while(getchar()!='\n');continue;}
        switch(choice){
            case 1: printf("-> Employee (other)\n"); break;
            case 2: printf("-> Budget (other)\n"); break;
            case 3: printf("-> Supplier (other)\n"); break;
            case 4: manageAssets(); break;
            case 5: printf("-> Reports (other)\n"); break;
            case 6: printf("Exiting...\n"); break;
            default: printf("Choose 1-6\n");
        }
    } while(choice!=6);
    return 0;
}
void displayMainMenu(){
    printf("\n--- MAIN MENU ---\n1.Employee\n2.Budget\n3.Supplier\n4.Asset\n5.Reports\n6.Exit\n");
}