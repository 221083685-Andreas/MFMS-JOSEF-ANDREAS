#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "assets.h"

// Private array - demonstrates ARRAYS
static struct Asset assets[MAX_ASSETS];
static int assetCount = 0;

// Helper: Check empty string
int isEmptyString(char str[]) {
    if (strlen(str) == 0) return 1;
    for (int i = 0; i < (int)strlen(str); i++) {
        if (!isspace(str[i])) return 0;
    }
    return 1;
}

// Helper: Clear input buffer
void clearInput() {
    int c;
    while ((c = getchar())!= '\n' && c!= EOF);
}

void assetMenu() {
    int choice;
    do {
        printf("\n========================================\n");
        printf(" ASSET MANAGEMENT MODULE (Student 4)\n");
        printf("========================================\n");
        printf("1. Add Asset\n");
        printf("2. Display All Assets\n");
        printf("3. Search Asset\n");
        printf("4. Asset Report\n");
        printf("5. Back to Main Menu\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice)!= 1) {
            printf("Invalid input! Please enter a number.\n");
            clearInput();
            continue;
        }
        clearInput();

        switch(choice) {
            case 1: addAsset(); break;
            case 2: displayAssets(); break;
            case 3: searchAsset(); break;
            case 4: assetReport(); break;
            case 5: printf("Returning to Main Menu...\n"); break;
            default: printf("Invalid choice! Try 1-5.\n");
        }
    } while(choice!= 5);
}

void addAsset() {
    if (assetCount >= MAX_ASSETS) {
        printf("Asset register full! Cannot add more.\n");
        return;
    }

    struct Asset newAsset;
    printf("\n--- Add New Municipal Asset ---\n");

    printf("Enter Asset ID: ");
    if (scanf("%d", &newAsset.assetID)!= 1 || newAsset.assetID <= 0) {
        printf("Error: Asset ID must be a positive number!\n");
        clearInput();
        return;
    }
    clearInput();

    // Check duplicate ID
    for (int i = 0; i < assetCount; i++) {
        if (assets[i].assetID == newAsset.assetID) {
            printf("Error: Asset ID %d already exists!\n", newAsset.assetID);
            return;
        }
    }

    printf("Enter Asset Name: ");
    fgets(newAsset.assetName, sizeof(newAsset.assetName), stdin);
    newAsset.assetName[strcspn(newAsset.assetName, "\n")] = '\0';
    if (isEmptyString(newAsset.assetName)) {
        printf("Error: Asset name cannot be empty!\n");
        return;
    }

    printf("Enter Asset Type (Vehicle/Computer/Building/Equipment/Furniture): ");
    fgets(newAsset.assetType, sizeof(newAsset.assetType), stdin);
    newAsset.assetType[strcspn(newAsset.assetType, "\n")] = '\0';
    if (isEmptyString(newAsset.assetType)) {
        printf("Error: Asset type cannot be empty!\n");
        return;
    }

    printf("Enter Purchase Value (N$): ");
    if (scanf("%f", &newAsset.purchaseValue)!= 1 || newAsset.purchaseValue < 0) {
        printf("Error: Purchase value cannot be negative!\n");
        clearInput();
        return;
    }
    clearInput();

    printf("Enter Department: ");
    fgets(newAsset.department, sizeof(newAsset.department), stdin);
    newAsset.department[strcspn(newAsset.department, "\n")] = '\0';
    if (isEmptyString(newAsset.department)) {
        printf("Error: Department cannot be empty!\n");
        return;
    }

    printf("Enter Condition (New/Good/Fair/Poor): ");
    fgets(newAsset.condition, sizeof(newAsset.condition), stdin);
    newAsset.condition[strcspn(newAsset.condition, "\n")] = '\0';
    if (isEmptyString(newAsset.condition)) {
        strcpy(newAsset.condition, "Good");
    }

    assets[assetCount] = newAsset;
    assetCount++;
    printf("\nAsset added successfully! Total assets: %d\n", assetCount);
}

void displayAssets() {
    if (assetCount == 0) {
        printf("\nNo assets registered yet.\n");
        return;
    }

    printf("\n================================================================================\n");
    printf("MUNICIPAL ASSET REGISTER - Total: %d\n", assetCount);
    printf("================================================================================\n");
    printf("%-8s %-20s %-15s %-12s %-15s %-10s\n", "ID", "Name", "Type", "Value(N$)", "Department", "Condition");
    printf("--------------------------------------------------------------------------------\n");

    for (int i = 0; i < assetCount; i++) {
        printf("%-8d %-20s %-15s %-12.2f %-15s %-10s\n",
               assets[i].assetID,
               assets[i].assetName,
               assets[i].assetType,
               assets[i].purchaseValue,
               assets[i].department,
               assets[i].condition);
    }
    printf("================================================================================\n");
}

void searchAsset() {
    if (assetCount == 0) {
        printf("\nNo assets to search.\n");
        return;
    }

    int option;
    printf("\n--- Search Asset ---\n");
    printf("1. Search by Asset ID\n");
    printf("2. Search by Department\n");
    printf("3. Search by Asset Type\n");
    printf("Enter search option: ");
    scanf("%d", &option);
    clearInput();

    int found = 0;

    if (option == 1) {
        int searchID;
        printf("Enter Asset ID to search: ");
        scanf("%d", &searchID);
        clearInput();
        for (int i = 0; i < assetCount; i++) {
            if (assets[i].assetID == searchID) {
                printf("\nAsset Found:\n");
                printf("ID: %d | Name: %s | Type: %s | Value: N$%.2f | Dept: %s | Condition: %s\n",
                       assets[i].assetID, assets[i].assetName, assets[i].assetType,
                       assets[i].purchaseValue, assets[i].department, assets[i].condition);
                found = 1;
                break;
            }
        }
    } else if (option == 2) {
        char searchDept[30];
        printf("Enter Department to search: ");
        fgets(searchDept, sizeof(searchDept), stdin);
        searchDept[strcspn(searchDept, "\n")] = '\0';

        printf("\nAssets in Department '%s':\n", searchDept);
        for (int i = 0; i < assetCount; i++) {
            if (strcmp(assets[i].department, searchDept) == 0) {
                printf("ID: %d | Name: %s | Type: %s | Value: N$%.2f | Condition: %s\n",
                       assets[i].assetID, assets[i].assetName, assets[i].assetType,
                       assets[i].purchaseValue, assets[i].condition);
                found = 1;
            }
        }
    } else if (option == 3) {
        char searchType[30];
        printf("Enter Asset Type to search: ");
        fgets(searchType, sizeof(searchType), stdin);
        searchType[strcspn(searchType, "\n")] = '\0';

        printf("\nAssets of Type '%s':\n", searchType);
        for (int i = 0; i < assetCount; i++) {
            if (strcmp(assets[i].assetType, searchType) == 0) {
                printf("ID: %d | Name: %s | Dept: %s | Value: N$%.2f | Condition: %s\n",
                       assets[i].assetID, assets[i].assetName, assets[i].department,
                       assets[i].purchaseValue, assets[i].condition);
                found = 1;
            }
        }
    } else {
        printf("Invalid search option!\n");
        return;
    }

    if (!found) {
        printf("No matching asset found!\n");
    }
}

void assetReport() {
    if (assetCount == 0) {
        printf("\nAsset Report: No assets registered.\n");
        return;
    }
    printf("\n========== ASSET REPORT ==========\n");
    printf("Total Assets: %d\n", assetCount);
    printf("Total Asset Value: N$%.2f\n", getTotalAssetValue());

    int newCount = 0, goodCount = 0, fairCount = 0, poorCount = 0;
    for (int i = 0; i < assetCount; i++) {
        if (strcmp(assets[i].condition, "New") == 0) newCount++;
        else if (strcmp(assets[i].condition, "Good") == 0) goodCount++;
        else if (strcmp(assets[i].condition, "Fair") == 0) fairCount++;
        else if (strcmp(assets[i].condition, "Poor") == 0) poorCount++;
    }
    printf("Condition: New:%d, Good:%d, Fair:%d, Poor:%d\n", newCount, goodCount, fairCount, poorCount);
    printf("===================================\n");
    displayAssets();
}

int getAssetCount() {
    return assetCount;
}

float getTotalAssetValue() {
    float total = 0;
    for (int i = 0; i < assetCount; i++) {
        total += assets[i].purchaseValue;
    }
    return total;
}

struct Asset* getAssetsArray() {
    return assets;
}