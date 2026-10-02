#include <stdio.h>
#include <string.h>
#include "assets.h"

Asset assets[100];
int assetCount = 0;

void saveAssetsToFile() {
    FILE *fp = fopen("assets.txt", "w");
    if(fp == NULL) return;
    for(int i=0; i<assetCount; i++) {
        fprintf(fp, "%d,%s,%s,%s,%.2f,%s,%s\n",
            assets[i].assetId, assets[i].assetName, assets[i].category,
            assets[i].location, assets[i].value, assets[i].purchaseDate, assets[i].status);
    }
    fclose(fp);
}

void loadAssetsFromFile() {
    FILE *fp = fopen("assets.txt", "r");
    if(fp == NULL) return;
    assetCount = 0;
    while(fscanf(fp, "%d,%49[^,],%29[^,],%29[^,],%lf,%14[^,],%19[^\n]\n",
        &assets[assetCount].assetId, assets[assetCount].assetName, assets[assetCount].category,
        assets[assetCount].location, &assets[assetCount].value, assets[assetCount].purchaseDate, assets[assetCount].status) == 7) {
        assetCount++;
    }
    fclose(fp);
}

void addAsset() {
    if(assetCount >= 100) {
        printf("Storage full!\n");
        return;
    }
    Asset a;
    printf("\nEnter Asset ID: ");
    scanf("%d", &a.assetId);
    getchar();
    printf("Enter Asset Name: ");
    fgets(a.assetName, 50, stdin);
    a.assetName[strcspn(a.assetName, "\n")] = 0;
    printf("Enter Category (Vehicle/Equipment/Building/IT): ");
    fgets(a.category, 30, stdin);
    a.category[strcspn(a.category, "\n")] = 0;
    printf("Enter Location (Windhoek Central, Katutura, etc): ");
    fgets(a.location, 30, stdin);
    a.location[strcspn(a.location, "\n")] = 0;
    printf("Enter Value (N$): ");
    scanf("%lf", &a.value);
    getchar();
    printf("Enter Purchase Date (DD/MM/YYYY): ");
    fgets(a.purchaseDate, 15, stdin);
    a.purchaseDate[strcspn(a.purchaseDate, "\n")] = 0;
    strcpy(a.status, "Active");
    assets[assetCount++] = a;
    saveAssetsToFile();
    printf("Asset added! Total: %d\n", assetCount);
}

void viewAssets() {
    if(assetCount == 0) {
        printf("\nNo assets found!\n");
        return;
    }
    printf("\n%-5s %-20s %-15s %-15s %-10s %-12s\n", "ID", "Name", "Category", "Location", "Value", "Status");
    printf("--------------------------------------------------------------------------------\n");
    for(int i=0; i<assetCount; i++) {
        printf("%-5d %-20s %-15s %-15s N$%-8.2f %-12s\n",
            assets[i].assetId, assets[i].assetName, assets[i].category,
            assets[i].location, assets[i].value, assets[i].status);
    }
}

void searchAsset() {
    int id;
    printf("Enter Asset ID to search: ");
    scanf("%d", &id);
    for(int i=0; i<assetCount; i++) {
        if(assets[i].assetId == id) {
            printf("\nFound: %s | %s | %s | N$%.2f | %s\n",
                assets[i].assetName, assets[i].category, assets[i].location,
                assets[i].value, assets[i].status);
            return;
        }
    }
    printf("Asset ID %d not found!\n", id);
}

void updateAssetStatus() {
    int id;
    printf("Enter Asset ID to update: ");
    scanf("%d", &id);
    getchar();
    for(int i=0; i<assetCount; i++) {
        if(assets[i].assetId == id) {
            printf("Current Status: %s\n", assets[i].status);
            printf("Enter New Status (Active/Maintenance/Disposed): ");
            fgets(assets[i].status, 20, stdin);
            assets[i].status[strcspn(assets[i].status, "\n")] = 0;
            saveAssetsToFile();
            printf("Status updated!\n");
            return;
        }
    }
    printf("Asset not found!\n");
}

void manageAssets() {
    int choice;
    loadAssetsFromFile();
    do {
        printf("\n--- ASSET MANAGEMENT - Windhoek ---\n");
        printf("1. Add New Asset\n");
        printf("2. View All Assets\n");
        printf("3. Search Asset\n");
        printf("4. Update Asset Status\n");
        printf("5. Back to Main Menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();
        switch(choice) {
            case 1: addAsset(); break;
            case 2: viewAssets(); break;
            case 3: searchAsset(); break;
            case 4: updateAssetStatus(); break;
            case 5: printf("Returning...\n"); break;
            default: printf("Invalid!\n");
        }
    } while(choice!= 5);
}