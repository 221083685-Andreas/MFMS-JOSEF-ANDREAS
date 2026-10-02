#ifndef ASSETS_H
#define ASSETS_H

#define MAX_ASSETS 100

struct Asset {
    int assetID;
    char assetName[50];
    char assetType[30];
    float purchaseValue;
    char department[30];
    char condition[20];
};

// Main functions - Student 4
void assetMenu();
void addAsset();
void displayAssets();
void searchAsset();
void assetReport();

// For Student 5 Reports module
int getAssetCount();
float getTotalAssetValue();
struct Asset* getAssetsArray();

#endif