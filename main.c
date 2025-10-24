#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CITIES 30
#define MAX_NAME_LENGTH 50

char cities[MAX_CITIES][MAX_NAME_LENGTH];
int distances[MAX_CITIES][MAX_CITIES];
int cityCount = 0;

void initializeSystem();
void manageCities();
void manageDistances();
void deliveryRequest();
void viewDeliveryRecords();
void generateReports();
void saveData();

void addCity();
void renameCity();
void removeCity();
void displayCities();
int findCity(char *name);

void inputDistance();
void editDistance();
void displayDistanceTable();

void clearInputBuffer();

int main()
{
    initializeSystem();
    int choice;

    while (1)
    {

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

        switch (choice)
        {
        case 1:
            manageCities();
            break;
        case 2:
            manageDistances();
            break;
        case 3:
            //deliveryRequest();
            break;
        case 4:
            //viewDeliveryRecords();
            break;
        case 5:
            //generateReports();
            break;
        case 6:
           // saveData();
            printf("Data saved. Exiting...\n");
            exit(0);
        default:
            printf("Invalid choice! Please try again.\n");

        }
    }
    return 0;
}

void initializeSystem()
{
    int i, j;

    for (i = 0; i < MAX_CITIES; i++)
    {
        for (j = 0; j < MAX_CITIES; j++)
        {
            distances[i][j] = 0;
        }
    }

    for (i = 0; i < MAX_CITIES; i++)
    {
        strcpy(cities[i], "");
    }
}



void manageCities()
{
    int choice;

    while (1)
    {
        printf("\n");
        printf("========================================================\n");
        printf("       CITY MANAGEMENT\n");
        printf("========================================================\n");
        printf("1. Add New City\n");
        printf("2. Rename City\n");
        printf("3. Remove City\n");
        printf("4. Display All Cities\n");
        printf("5. Back to Main Menu\n");
        printf("========================================================\n");
        printf("Enter your choice: ");
        scanf(" %d", &choice);

        switch (choice)
        {
        case 1:
            addCity();
            break;
        case 2:
             renameCity();
            break;
        case 3:
            removeCity();
            break;
        case 4:
            displayCities();
            break;
        case 5:
            return ;
        default:
            printf("Invalid choice!\n");

        }
    }
}

void addCity()
{
    char newCity[MAX_NAME_LENGTH];

    if (cityCount >= MAX_CITIES)
    {
        printf("Maximum city limit reached!\n");

        return;
    }
    clearInputBuffer();
    printf("\nEnter city name: ");
    fgets( newCity, MAX_NAME_LENGTH, stdin);

    if (strlen(newCity) == 0)
    {
        printf("City name cannot be empty!\n");

        return;
    }

    if (findCity(newCity) != -1)
    {
        printf("City already exists!\n");

        return;
    }



    strcpy(cities[cityCount], newCity);
    cityCount++;
    printf("City '%s' added successfully!\n", newCity);

}

void renameCity()
{
    char oldName[MAX_NAME_LENGTH], newName[MAX_NAME_LENGTH];
    int index;

    if (cityCount == 0)
    {
        printf("No cities available!\n");

        return;
    }

    displayCities();

    clearInputBuffer();
    printf("\nEnter city name to rename: ");
    fgets(oldName, MAX_NAME_LENGTH, stdin);

    index = findCity(oldName);
    if (index == -1)
    {
        printf("City not found!\n");

        return;
    }

    printf("Enter new name: ");
    fgets(newName, MAX_NAME_LENGTH, stdin);

    if (strlen(newName) == 0)
    {
        printf("City name cannot be empty!\n");

        return;
    }

    if (findCity(newName) != -1)
    {
        printf("City with this name already exists!\n");

        return;
    }

    strcpy(cities[index], newName);
    printf("City renamed successfully!\n");

}



void removeCity()
{
    char cityName[MAX_NAME_LENGTH];
    int index, i;

    if (cityCount == 0)
    {
        printf("No cities available!\n");

        return;
    }

    displayCities();

    clearInputBuffer();
    printf("\nEnter city name to remove: ");
    fgets(cityName, MAX_NAME_LENGTH, stdin);

    index = findCity(cityName);
    if (index == -1)
    {
        printf("City not found!\n");

        return;
    }

    for (i = index; i < cityCount - 1; i++)
    {
        strcpy(cities[i], cities[i + 1]);
    }

    for (i = index; i < cityCount - 1; i++)
    {
        int j;
        for (j = 0; j < cityCount; j++)
        {
            distances[i][j] = distances[i + 1][j];
        }
    }

    for (i = index; i < cityCount - 1; i++)
    {
        int j;
        for (j = 0; j < cityCount; j++)
        {
            distances[j][i] = distances[j][i + 1];
        }
    }

    cityCount--;
    printf("City removed successfully!\n");

}


void displayCities()
{
    int i;

    printf("\n");
    printf("========================================================\n");
    printf("       AVAILABLE CITIES (%d)\n", cityCount);
    printf("========================================================\n");

    if (cityCount == 0)
    {
        printf("No cities available.\n");
        return;
    }

    for (i = 0; i < cityCount; i++)
    {
        printf("%d. %s\n", i + 1, cities[i]);
    }
    printf("========================================================\n");
}

int findCity(char *name)
{
    int i;
    char searchName[MAX_NAME_LENGTH], cityName[MAX_NAME_LENGTH];

    strcpy(searchName, name);

    for (i = 0; i < cityCount; i++)
    {
        strcpy(cityName, cities[i]);
        if (strcmp(cityName, searchName) == 0)
        {
            return i;
        }
    }
    return -1;
}

void manageDistances()
{
    int choice;
    while (1)
    {

        printf("\n");
        printf("========================================================\n");
        printf(" DISTANCE MANAGEMENT\n");
        printf("========================================================\n");
        printf("1. Input/Edit Distance\n");
        printf("2. Display Distance Table\n");
        printf("3. Back to Main Menu\n");
        printf("========================================================\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1)
        {

            printf("Invalid input!\n");

            continue;
        }

        switch (choice)
        {
        case 1:
            inputDistance();
            break;
        case 2:
            displayDistanceTable();

            break;
        case 3:
            return;
        default:
            printf("Invalid choice!\n");

        }
    }
}

void inputDistance()
{
    int city1, city2, distance;
    if (cityCount < 2)
    {
        printf("Need at least 2 cities to set distances!\n");

        return;
    }
    displayCities();
    printf("\nEnter first city number: ");
    if (scanf("%d", &city1) != 1 || city1 < 1 || city1 > cityCount)
    {

        printf("Invalid city number!\n");
clearInputBuffer();
        return;
    }
    printf("Enter second city number: ");
    if (scanf("%d", &city2) != 1 || city2 < 1 || city2 > cityCount)
    {

        printf("Invalid city number!\n");
clearInputBuffer();
        return;
    }

    city1--;
    city2--;
    if (city1 == city2)
    {
        printf("Cannot set distance from a city to itself!\n");

        return;
    }
    printf("Enter distance in km: ");
    if (scanf("%d", &distance) != 1 || distance < 0)
    {

        printf("Invalid distance!\n");
clearInputBuffer();
        return;
    }

    distances[city1][city2] = distance;
    distances[city2][city1] = distance;
    printf("Distance set successfully!\n");

}

void displayDistanceTable()
{
    int i, j;
    if (cityCount == 0)
    {
        printf("No cities available!\n");
        return;
    }
    printf("\n");
    printf("========================================================\n");
    printf(" DISTANCE MATRIX (km)\n");
    printf("========================================================\n");
    printf("%-15s", "");
    for (i = 0; i < cityCount; i++)
    {
        printf("%-8s", cities[i]);
    }
    printf("\n");
    for (i = 0; i < cityCount; i++)
    {
        printf("%-15s", cities[i]);
        for (j = 0; j < cityCount; j++)
        {
            printf("%-8d", distances[i][j]);
        }
        printf("\n");
    }
    printf("========================================================\n");
}


















void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
