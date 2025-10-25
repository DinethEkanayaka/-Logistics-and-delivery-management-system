
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CITIES 30
#define MAX_NAME_LENGTH 50
#define MAX_DELIVERIES 50
#define FUEL_PRICE 310.0

char cities[MAX_CITIES][MAX_NAME_LENGTH];
int distances[MAX_CITIES][MAX_CITIES];
int cityCount = 0;
int deliveryCount = 0;

char vehicleTypes[3][20] = {"Van", "Truck", "Lorry"};
int vehicleCapacity[3] = {1000, 5000, 10000};
float vehicleRate[3] = {30.0, 40.0, 80.0};
float vehicleSpeed[3] = {60.0, 50.0, 45.0};
float vehicleEfficiency[3] = {12.0, 6.0, 4.0};

int deliverySource[MAX_DELIVERIES];
int deliveryDest[MAX_DELIVERIES];
int deliveryWeight[MAX_DELIVERIES];
int deliveryVehicle[MAX_DELIVERIES];
float deliveryDistance[MAX_DELIVERIES];
float deliveryCost[MAX_DELIVERIES];
float deliveryTime[MAX_DELIVERIES];
float deliveryRevenue[MAX_DELIVERIES];
float deliveryProfit[MAX_DELIVERIES];

void initializeSystem();
void manageCities();
void manageDistances();
void handleDeliveryRequest();
void viewDeliveryRecords();
void generateReports();
void saveData();
void loadData();

void addCity();
void renameCity();
void removeCity();
void displayCities();
int findCity(const char *name);

void inputDistance();
void editDistance();
void displayDistanceTable();
void clearInputBuffer();
void trimNewline(char *str);

void swap(int *a, int *b);
int calculateDistance(int path[], int pathLen);
void generatePermutations(int arr[], int start, int end, int source, int dest, int *minDist, int bestPath[]);
int findLeastCostRoute(int source, int dest, int resultPath[]);

int main() {
    const char *RESET = "\033[0m";
    const char *CYAN = "\033[1;36m";

    initializeSystem();
    loadData();
    int choice;

    while (1) {
        printf("\n");
        printf("%s========================================================%s\n", CYAN, RESET);
        printf("   LOGISTICS MANAGEMENT SYSTEM  %s \n", CYAN);
        printf("========================================================\n");
        printf("1. Manage Cities\n");
        printf("2. Manage Distances\n");
        printf("3. New Delivery Request\n");
        printf("4. View Delivery Records\n");
        printf("5. Generate Reports\n");
        printf("6. Save and Exit\n");
        printf("========================================================\n");
        printf("Enter your choice: %s", RESET);

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1: manageCities(); break;
            case 2: manageDistances(); break;
            case 3: handleDeliveryRequest(); break;
            case 4: viewDeliveryRecords(); break;
            case 5: generateReports(); break;
            case 6:
                saveData();
                printf("Data saved. Exiting...\n");
                exit(0);
            default: printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

void initializeSystem() {
    int i, j;
    for (i = 0; i < MAX_CITIES; i++) {
        for (j = 0; j < MAX_CITIES; j++) {
            distances[i][j] = 0;
        }
        strcpy(cities[i], "");
    }
}

void manageCities() {
    int choice;
    while (1) {
        printf("\n\n\n");
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

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1: addCity(); break;
            case 2: renameCity(); break;
            case 3: removeCity(); break;
            case 4: displayCities(); break;
            case 5: return;
            default: printf("Invalid choice!\n");
        }
    }
}



void addCity() {
    char newCity[MAX_NAME_LENGTH];
    if (cityCount >= MAX_CITIES) {
        printf("Maximum city limit reached!\n");
        return;
    }

    printf("\nEnter city name: ");
    fgets(newCity, MAX_NAME_LENGTH, stdin);
    trimNewline(newCity);

    if (strlen(newCity) == 0) {
        printf("City name cannot be empty!\n");
        return;
    }

    if (findCity(newCity) != -1) {
        printf("City already exists!\n");
        return;
    }

    strcpy(cities[cityCount], newCity);
    cityCount++;
    printf("City added successfully!\n");
}

void renameCity() {
    char oldName[MAX_NAME_LENGTH], newName[MAX_NAME_LENGTH];
    int index;

    if (cityCount == 0) {
        printf("No cities available!\n");
        return;
    }

    displayCities();

    printf("\nEnter city name to rename: ");
    fgets(oldName, MAX_NAME_LENGTH, stdin);
    trimNewline(oldName);

    index = findCity(oldName);
    if (index == -1) {
        printf("City not found!\n");
        return;
    }

    printf("Enter new name: ");
    fgets(newName, MAX_NAME_LENGTH, stdin);
    trimNewline(newName);

    if (strlen(newName) == 0) {
        printf("City name cannot be empty!\n");
        return;
    }

    if (findCity(newName) != -1) {
        printf("City with this name already exists!\n");
        return;
    }

    strcpy(cities[index], newName);
    printf("City renamed successfully!\n");
}

void removeCity() {
    char cityName[MAX_NAME_LENGTH];
    int index, i, j;

    if (cityCount == 0) {
        printf("No cities available!\n");
        return;
    }

    displayCities();

    printf("\nEnter city name to remove: ");
    fgets(cityName, MAX_NAME_LENGTH, stdin);
    trimNewline(cityName);

    index = findCity(cityName);
    if (index == -1) {
        printf("City not found!\n");
        return;
    }


    for (i = index; i < cityCount - 1; i++) {
        strcpy(cities[i], cities[i + 1]);
    }
    strcpy(cities[cityCount - 1], "");


    for (i = index; i < cityCount - 1; i++) {
        for (j = 0; j < cityCount; j++) {
            distances[i][j] = distances[i + 1][j];
        }
    }


    for (i = 0; i < cityCount; i++) {
        for (j = index; j < cityCount - 1; j++) {
            distances[i][j] = distances[i][j + 1];
        }
    }


    for (i = 0; i < cityCount; i++) {
        distances[cityCount - 1][i] = 0;
        distances[i][cityCount - 1] = 0;
    }

    cityCount--;
    printf("City removed successfully!\n");
}

void displayCities() {
    int i;
    printf("\n");
    printf("========================================================\n");
    printf("       AVAILABLE CITIES (%d)\n", cityCount);
    printf("========================================================\n");

    if (cityCount == 0) {
        printf("No cities available.\n");
        return;
    }

    for (i = 0; i < cityCount; i++) {
        printf("%d. %s\n", i + 1, cities[i]);
    }
    printf("========================================================\n");
}

int findCity(const char *name) {
    int i;
    for (i = 0; i < cityCount; i++) {
        if (strcmp(cities[i], name) == 0) {
            return i;
        }
    }
    return -1;
}

void manageDistances() {
    int choice;
    while (1) {
        printf("\n");
        printf("========================================================\n");
        printf(" DISTANCE MANAGEMENT\n");
        printf("========================================================\n");
        printf("1. Input/Edit Distance\n");
        printf("2. Display Distance Table\n");
        printf("3. Back to Main Menu\n");
        printf("========================================================\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1: inputDistance(); break;
            case 2: displayDistanceTable(); break;
            case 3: return;
            default: printf("Invalid choice!\n");
        }
    }
}

void inputDistance() {
    int city1, city2, distance;
    if (cityCount < 2) {
        printf("Need at least 2 cities to set distances!\n");
        return;
    }
    displayCities();
    printf("\nEnter first city number: ");
    if (scanf("%d", &city1) != 1 || city1 < 1 || city1 > cityCount) {
        printf("Invalid city number!\n");
        clearInputBuffer();
        return;
    }
    printf("Enter second city number: ");
    if (scanf("%d", &city2) != 1 || city2 < 1 || city2 > cityCount) {
        printf("Invalid city number!\n");
        clearInputBuffer();
        return;
    }

    city1--;
    city2--;
    if (city1 == city2) {
        printf("Cannot set distance from a city to itself!\n");
        return;
    }
    printf("Enter distance in km: ");
    if (scanf("%d", &distance) != 1 || distance < 0) {
        printf("Invalid distance!\n");
        clearInputBuffer();
        return;
    }

    distances[city1][city2] = distance;
    distances[city2][city1] = distance;
    printf("Distance set successfully!\n");
}

void displayDistanceTable() {
    int i, j;
    if (cityCount == 0) {
        printf("No cities available!\n");
        return;
    }

    int maxLen = 0;
    for (i = 0; i < cityCount; i++) {
        int len = strlen(cities[i]);
        if (len > maxLen) maxLen = len;
    }
    maxLen += 2;

    printf("\n");
    printf("============================================================\n");
    printf("                   DISTANCE MATRIX (km)\n");
    printf("============================================================\n");

    printf("%-*s", maxLen, "");
    for (i = 0; i < cityCount; i++) {
        printf("%-*s", maxLen, cities[i]);
    }
    printf("\n");

    for (i = 0; i < cityCount; i++) {
        printf("%-*s", maxLen, cities[i]);
        for (j = 0; j < cityCount; j++) {
            printf("%-*d", maxLen, distances[i][j]);
        }
        printf("\n");
    }

    printf("============================================================\n\n");
}

void handleDeliveryRequest() {
    int source, dest, weight, vehicleType;
    float cost, time, fuelUsed, fuelCost, totalCost, profit, customerCharge;
    int minDistance;
    int resultPath[MAX_CITIES];

    if (cityCount < 2) {
        printf("Need at least 2 cities for delivery!\n");
        return;
    }

    if (deliveryCount >= MAX_DELIVERIES) {
        printf("Maximum delivery limit reached!\n");
        return;
    }

    printf("\n");
    printf("========================================================\n");
    printf("       NEW DELIVERY REQUEST\n");
    printf("========================================================\n");

    displayCities();

    printf("\nEnter source city number: ");
    if (scanf("%d", &source) != 1 || source < 1 || source > cityCount) {
        clearInputBuffer();
        printf("Invalid city number!\n");
        return;
    }

    printf("Enter destination city number: ");
    if (scanf("%d", &dest) != 1 || dest < 1 || dest > cityCount) {
        clearInputBuffer();
        printf("Invalid city number!\n");
        return;
    }
    clearInputBuffer();

    source--;
    dest--;

    if (source == dest) {
        printf("Source and destination cannot be the same!\n");
        return;
    }

    printf("\nAvailable Vehicles:\n");
    printf("\n");
    printf("+----------+--------------+-----------------+\n");
    printf("| Vehicle  | Capacity(kg) | Rate (LKR/km)   |\n");
    printf("+----------+--------------+-----------------+\n");
    printf("| 1. Van   | 1000         | 30              |\n");
    printf("| 2. Truck | 5000         | 40              |\n");
    printf("| 3. Lorry | 10000        | 80              |\n");
    printf("+----------+--------------+-----------------+\n");
    printf("\nSelect vehicle type (1-3): ");
    if (scanf("%d", &vehicleType) != 1 || vehicleType < 1 || vehicleType > 3) {
        clearInputBuffer();
        printf("Invalid vehicle type!\n");
        return;
    }
    vehicleType--;

    printf("Enter weight in kg: ");
    if (scanf("%d", &weight) != 1 || weight <= 0) {
        clearInputBuffer();
        printf("Invalid weight!\n");
        return;
    }
    clearInputBuffer();

    if (weight > vehicleCapacity[vehicleType]) {
        printf("Weight exceeds vehicle capacity!\n");
        return;
    }

    minDistance = findLeastCostRoute(source, dest, resultPath);

    if (minDistance == 0) {
        printf("No route found between these cities!\n");
        return;
    }

    printf("\nOptimal Route: ");
    int i = 0;
    while (resultPath[i] != -1) {
        printf("%s", cities[resultPath[i]]);
        if (resultPath[i + 1] != -1) {
            printf(" -> ");
        }
        i++;
    }

    cost = minDistance * vehicleRate[vehicleType] * (1 + (weight / 10000.0));
    time = minDistance / vehicleSpeed[vehicleType];
    fuelUsed = minDistance / vehicleEfficiency[vehicleType];
    fuelCost = fuelUsed * FUEL_PRICE;
    totalCost = cost + fuelCost;
    profit = cost * 0.25;
    customerCharge = totalCost + profit;

    printf("\n");
    printf("======================================================\n");
    printf("       DELIVERY COST ESTIMATION\n");
    printf("------------------------------------------------------\n");
    printf("From: %s\n", cities[source]);
    printf("To: %s\n", cities[dest]);
    printf("Minimum Distance: %d km\n", minDistance);
    printf("Vehicle: %s\n", vehicleTypes[vehicleType]);
    printf("Weight: %d kg\n", weight);
    printf("\n");
    printf("Base Cost: %.2f LKR\n", cost);
    printf("Fuel Used: %.2f L\n", fuelUsed);
    printf("Fuel Cost: %.2f LKR\n", fuelCost);
    printf("Operational Cost: %.2f LKR\n", totalCost);
    printf("Profit: %.2f LKR\n", profit);
    printf("Customer Charge: %.2f LKR\n", customerCharge);
    printf("Estimated Time: %.2f hours\n", time);
    printf("======================================================\n");

    deliverySource[deliveryCount] = source;
    deliveryDest[deliveryCount] = dest;
    deliveryWeight[deliveryCount] = weight;
    deliveryVehicle[deliveryCount] = vehicleType;
    deliveryDistance[deliveryCount] = minDistance;
    deliveryCost[deliveryCount] = cost;
    deliveryTime[deliveryCount] = time;
    deliveryRevenue[deliveryCount] = customerCharge;
    deliveryProfit[deliveryCount] = profit;
    deliveryCount++;

    printf("\nDelivery request saved successfully!\n");
}

void viewDeliveryRecords() {
    int i;
    printf("\n");
    printf("========================================================\n");
    printf(" DELIVERY RECORDS\n");
    printf("========================================================\n");
    if (deliveryCount == 0) {
        printf("No delivery records available.\n");
    } else {
        printf("Total Deliveries: %d\n\n", deliveryCount);
        for (i = 0; i < deliveryCount; i++) {
            printf("Delivery #%d\n", i + 1);
            printf(" From: %s -> To: %s\n", cities[deliverySource[i]], cities[deliveryDest[i]]);
            printf(" Distance: %.2f km\n", deliveryDistance[i]);
            printf(" Vehicle: %s\n", vehicleTypes[deliveryVehicle[i]]);
            printf(" Weight: %d kg\n", deliveryWeight[i]);
            printf(" Revenue: %.2f LKR\n", deliveryRevenue[i]);
            printf(" Profit: %.2f LKR\n", deliveryProfit[i]);
            printf(" Time: %.2f hours\n", deliveryTime[i]);
            printf("------------------------------------------------------\n");
        }
    }
}

void generateReports() {
    int i;
    float totalDistance = 0, totalRevenue = 0, totalProfit = 0, avgTime = 0;
    float longestRoute = 0, shortestRoute = 10000;

    printf("\n");
    printf("========================================================\n");
    printf(" PERFORMANCE REPORT\n");
    printf("========================================================\n");
    if (deliveryCount == 0) {
        printf("No delivery data available for reports.\n");
        return;
    }
    for (i = 0; i < deliveryCount; i++) {
        totalDistance += deliveryDistance[i];
        totalRevenue += deliveryRevenue[i];
        totalProfit += deliveryProfit[i];
        avgTime += deliveryTime[i];
        if (deliveryDistance[i] > longestRoute) {
            longestRoute = deliveryDistance[i];
        }
        if (deliveryDistance[i] < shortestRoute) {
            shortestRoute = deliveryDistance[i];
        }
    }
    avgTime /= deliveryCount;
    printf("Total Deliveries Completed: %d\n", deliveryCount);
    printf("Total Distance Covered: %.2f km\n", totalDistance);
    printf("Average Delivery Time: %.2f hours\n", avgTime);
    printf("Total Revenue: %.2f LKR\n", totalRevenue);
    printf("Total Profit: %.2f LKR\n", totalProfit);
    printf("Longest Route: %.2f km\n", longestRoute);
    printf("Shortest Route: %.2f km\n", shortestRoute);
    printf("========================================================\n");
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int calculateDistance(int path[], int pathLen) {
    int total = 0;
    int i;
    for (i = 0; i < pathLen - 1; i++) {
        if (distances[path[i]][path[i + 1]] == 0) {
            return 999999;
        }
        total += distances[path[i]][path[i + 1]];
    }
    return total;
}

void generatePermutations(int arr[], int start, int end, int source, int dest, int *minDist, int bestPath[]) {
    int i;
    if (start == end) {
        int path[MAX_CITIES];
        int len = 0;
        path[len++] = source;
        for (i = 0; i <= end; i++) {
            path[len++] = arr[i];
        }
        path[len++] = dest;
        int dist = calculateDistance(path, len);
        if (dist < *minDist) {
            *minDist = dist;
            for (i = 0; i < len; i++) {
                bestPath[i] = path[i];
            }
            bestPath[len] = -1;
        }
        return;
    }
    for (i = start; i <= end; i++) {
        swap(&arr[start], &arr[i]);
        generatePermutations(arr, start + 1, end, source, dest, minDist, bestPath);
        swap(&arr[start], &arr[i]);
    }
}

int findLeastCostRoute(int source, int dest, int resultPath[]) {
    int minDist = 999999;
    int i, len;
    if (distances[source][dest] != 0) {
        minDist = distances[source][dest];
        resultPath[0] = source;
        resultPath[1] = dest;
        resultPath[2] = -1;
    }
    int intermediate[MAX_CITIES];
    int count = 0;
    for (i = 0; i < cityCount; i++) {
        if (i != source && i != dest) {
            intermediate[count++] = i;
        }
    }
    if (count > 4) count = 4;
    for (len = 1; len <= count; len++) {
        int subset[MAX_CITIES];
        for (i = 0; i < len; i++) {
            subset[i] = intermediate[i];
        }
        generatePermutations(subset, 0, len - 1, source, dest, &minDist, resultPath);
    }
    if (minDist == 999999) {
        return 0;
    }
    return minDist;
}

void loadData() {
    FILE *routesFile, *deliveriesFile;
    int i, j;
    routesFile = fopen("routes.txt", "r");
    if (routesFile != NULL) {
        fscanf(routesFile, "%d", &cityCount);
        for (i = 0; i < cityCount; i++) {
            fscanf(routesFile, " %[^\n]", cities[i]);
        }
        for (i = 0; i < cityCount; i++) {
            for (j = 0; j < cityCount; j++) {
                fscanf(routesFile, "%d", &distances[i][j]);
            }
        }
        fclose(routesFile);
        printf("Routes data loaded successfully!\n");
    } else {
        printf("No previous routes data found.\n");
    }
    deliveriesFile = fopen("deliveries.txt", "r");
    if (deliveriesFile != NULL) {
        fscanf(deliveriesFile, "%d", &deliveryCount);
        for (i = 0; i < deliveryCount; i++) {
            fscanf(deliveriesFile, "%d %d %d %d %f %f %f %f %f",
                   &deliverySource[i],
                   &deliveryDest[i],
                   &deliveryWeight[i],
                   &deliveryVehicle[i],
                   &deliveryDistance[i],
                   &deliveryCost[i],
                   &deliveryTime[i],
                   &deliveryRevenue[i],
                   &deliveryProfit[i]);
        }
        fclose(deliveriesFile);
        printf("Delivery records loaded successfully!\n");
    } else {
        printf("No previous delivery records found.\n");
    }
}

void saveData() {
    FILE *routesFile, *deliveriesFile;
    int i, j;
    routesFile = fopen("routes.txt", "w");
    if (routesFile != NULL) {
        fprintf(routesFile, "%d\n", cityCount);
        for (i = 0; i < cityCount; i++) {
            fprintf(routesFile, "%s\n", cities[i]);
        }
        for (i = 0; i < cityCount; i++) {
            for (j = 0; j < cityCount; j++) {
                fprintf(routesFile, "%d ", distances[i][j]);
            }
            fprintf(routesFile, "\n");
        }
        fclose(routesFile);
    } else {
        printf("Error: Could not save routes data!\n");
    }
    deliveriesFile = fopen("deliveries.txt", "w");
    if (deliveriesFile != NULL) {
        fprintf(deliveriesFile, "%d\n", deliveryCount);
        for (i = 0; i < deliveryCount; i++) {
            fprintf(deliveriesFile, "%d %d %d %d %.2f %.2f %.2f %.2f %.2f\n",
                    deliverySource[i],
                    deliveryDest[i],
                    deliveryWeight[i],
                    deliveryVehicle[i],
                    deliveryDistance[i],
                    deliveryCost[i],
                    deliveryTime[i],
                    deliveryRevenue[i],
                    deliveryProfit[i]);
        }
        fclose(deliveriesFile);
    } else {
        printf("Error: Could not save delivery records!\n");
    }
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void trimNewline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}
