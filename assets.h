#ifndef ASSETS_H
#define ASSETS_H
#define MAX_ASSETS 100
typedef struct {
    int assetId;
    char assetName[50];
    char category[30];
    char location[30];
    double value;
    char purchaseDate[15];
    char status[20];
} Asset;
void manageAssets();
#endif