#include <stdio.h>
#include <stdlib.h>

void manageCities();
void manageDistances();
void deliveryRequest();
void viewDeliveryRecords();
void generateReports();
void saveData();


int main() {

int choice;

    while (1) {

        printf("\n");
        printf("========================================================\n");
        printf("       LOGISTICS MANAGEMENT SYSTEM\n");
        printf("========================================================\n");
        printf("1. Manage Cities\n");
        printf("2. Manage Distances\n");
        printf("3. New Delivery Request\n");
        printf("4. View Delivery Records\n");
        printf("5. Generate Reports\n");
        printf("6. Save and Exit\n");
        printf("========================================================\n");
        printf("Enter your choice: ");

       scanf("%d", &choice);

         switch (choice) {
            case 1:
                manageCities();
                break;
            case 2:
                manageDistances();
                break;
            case 3:
                deliveryRequest();
                break;
            case 4:
                viewDeliveryRecords();
                break;
            case 5:
                generateReports();
                break;
            case 6:
                saveData();
                printf("Data saved. Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");

        }
    }
    return 0;
    }

