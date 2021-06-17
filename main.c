#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
const int MAX = 10000;
struct Product{
    char name[50];
    char id[10];
    int quantity;
    int price;
    char state[10];
    int sum;
};
void showMenu(){
    printf("\n");
    printf("\n\t\t\t========================Menu=========================");
    printf("\n\t\t\t====                                             ====");
    printf("\n\t\t\t===========1.Input Product Information===============");
    printf("\n\t\t\t====                                             ====");
    printf("\n\t\t\t==================2.Show Bills=======================");
    printf("\n\t\t\t====                                             ====");
    printf("\n\t\t\t================3.Remove Product=====================");
    printf("\n\t\t\t====                                             ====");
    printf("\n\t\t\t=================4.Find Product======================");
    printf("\n\t\t\t====                                             ====");
    printf("\n\t\t\t===================5.Save Data=======================");
    printf("\n\t\t\t====                                             ====");
    printf("\n\t\t\t===============6.Open Product Data===================");
    printf("\n\t\t\t====                                             ====");
    printf("\n\t\t\t=====================================================");
}
//File Function
void writeFile(struct Product productList[],int size);
void readFile(struct Product *list, int *size);
void openFile();
void outputDataFile(struct Product productList[], int size);

//Main Function
void inputProduct(struct Product productList[],int *size);
void solveDuplicate(struct Product productList[],int size,int pos);
void removeProduct(struct Product productList[], int *size, char key[]);
void checkState(struct Product productList[],int size, char key[]);
void findProductById_Name(struct Product productList[],int size, char key[]);
void outputProduct(struct Product productList[],int size);

//Another
int findIndexByID(struct Product productList[], int size, char key[]);
int checkValid(struct Product productList[],int size, char key[]);
void removePos(char str[],int pos);
void validSpace(char str[]);
void formatString(char str[]);
void validID(char str[]);
int main()
{
    struct Product productList[1000];
    int size=0;
    int choice;
    char buffer;
    char exit;
    readFile(productList,&size);
    do{
        outputDataFile(productList,size);
        showMenu();
        do{
            printf("\nEnter your choice: ");
            scanf("%d",&choice);
            scanf("%c",&buffer);
            if(buffer != 10) printf("nInvalid");
        }while(buffer!=10);
        switch(choice){
            case 1:{
                system("cls");
                inputProduct(productList,&size);
                printf("\nInput accepted");
                sleep(1);
                break;
            }
            case 2:{
                system("cls");
                outputProduct(productList,size);
                do{
                    printf("\nDo You Want To Accept This Bill? (Y/N)");
                    scanf("%c",&exit);
                    fflush(stdin);
                }while(exit!='Y' && exit!='N');
                if(exit=='Y'){
                    printf("\nYour Bill is Accepted!!");
                    sleep(2);
                    printf("\nThank you!!!");
                }
                break;
            }
            case 3:{
                system("cls");
                char name[50];
                outputDataFile(productList,size);
                printf("\n\nRemove Product: ");
                printf("\nEnter Product Name: ");
                gets(name);
                formatString(name);
                removeProduct(productList,&size,name);
                break;
            }
            case 4: {
                char tmp[50];
                printf("\nEnter Name or Id Product You Want To Find: ");
                gets(tmp);
                findProductById_Name(productList,size,tmp);
                break;
            }
            case 5:{
                writeFile(productList,size);
                printf("\nSaved successfully");
                break;
            }
            case 6:{
                printf("\nOpening file....");
                sleep(2);
                printf("\nOpen File Successfully!!!");
                openFile();
                break;
            }
            default:{
                printf("\nInvalid");
                break;
            }
        }
        if(choice!=5) printf("\nYou didn't save data!!!");
        if(exit!='Y'){
            char ans;
            do{
                printf("\n\nEnter Y or N");
                printf("\nDo you want to choose again ? \n");
                scanf("%c",&ans);
                fflush(stdin);
                if(ans!='Y' && ans!='y' && ans!='N' && ans!='n'){
                }
                system("cls");
                if(ans == 'N' || ans == 'n'){
                    exit = 'Y';
                    printf("\nEnd.");
                }
            }while(ans!='Y' && ans!='y' && ans!='N' && ans!='n');
        }
    }while(exit != 'Y');
    return 0;
}

void writeFile(struct Product productList[],int size){
    FILE *fOut;
    fOut = fopen("store.txt","w");
    if(fOut){
        for(int i=0; i<=size-1;i++){
        fprintf(fOut,"%-30s%-9d%-15d%-15d%-10s%-10s\n",productList[i].name,
                                       productList[i].quantity,productList[i].price,
                                       productList[i].sum,productList[i].state,productList[i].id);
        }
    }
    fclose(fOut);
}

void readFile(struct Product *list, int *size){
    FILE *fOut =fopen("store.txt","r");
    int i=0;
    struct Product pr;
    if(fOut == NULL){
    printf("\nNo Data");
    }else{
        while(fscanf(fOut,"%30[^\n]%9d%15d%15d%10s%10s\n",
        pr.name,&pr.quantity,&pr.price,&pr.sum,pr.state,pr.id)==6){
            list[i++]=pr;
        }
    }
        fclose(fOut);
        (*size)=i;
    }

void openFile(){
    FILE *fp = fopen("store.txt", "a+");
    if (fp == NULL){
        printf("Error!");
    }
    system("start notepad \"store.txt\"");
    fclose(fp);
}

void outputDataFile(struct Product productList[], int size){
    printf("\n========================================Product List Data======================================");
    printf("\n%-30s%9s%15s%15s%10s%10s","Product","Quantity","Price","Sum","Status","ID");
    for(int i=0; i<=size-1;i++){
        printf("\n%-30s%9d%15d%15d%10s%10s",productList[i].name,
               productList[i].quantity,productList[i].price,
               productList[i].sum,productList[i].state,productList[i].id);
    }
    printf("\n===============================================================================================");
}


void inputProduct(struct Product productList[],int *size){
    char buffer;
    char name[50];
    char id[10];
    printf("\nEnter Product Name: ");
    gets(name);
    formatString(name);

    printf("\nEnter ID: ");
    gets(id);
    validID(id);

    int isFoundID = checkValid(productList,*size,id);
    int isFoundName = checkValid(productList,*size,name);
    if(isFoundID==1||isFoundName==2){
        if(isFoundID==1&&isFoundName==2){
            printf("\nProduct's Name and ID is both duplicated!!");
            checkState(productList,*size,id);
        }else if(isFoundID==1&&isFoundName!=2){
            printf("\nProduct's ID is duplicated!!");
            checkState(productList,*size,id);
        }else if(isFoundID!=1&&isFoundName==2){
            printf("\nProduct's Name is duplicated!!");
            checkState(productList,*size,name);
        }
    (*size)--;
    }else{
        strcpy(productList[*size].name,name);
        strcpy(productList[*size].id,id);
        do{
            printf("\nEnter Quantity of Products: ");
            scanf("%d",&productList[*size].quantity);
            scanf("%c",&buffer);
        }while(buffer!=10||productList[*size].quantity<0);
        do{
            printf("\nEnter Price each Product: ");
            scanf("%d",&productList[*size].price);
            scanf("%c",&buffer);
        }while(buffer!=10||productList[*size].price<0);

        while(1){
            printf("\nEnter Status of Product: ");
            printf("\n\t-Active\n\t-Inactive\n\t-Deleted\n");
            gets(productList[*size].state);
            formatString(productList[*size].state);
            if(strcmp(productList[*size].state,"Active")==0
               ||strcmp(productList[*size].state,"Inactive")==0
               ||strcmp(productList[*size].state,"Deleted")==0){
            break;
            }else{
                printf("\nWrong format!!");
            }
        }

        productList[*size].sum = productList[*size].quantity*productList[*size].price;
    }
    (*size)++;
}

void solveDuplicate(struct Product productList[],int size,int pos){

    int amount;
    printf("\nEnter Quantity of Products: ");
    scanf("%d",&amount);

    productList[pos].quantity+=amount;

    char answer;
    printf("\nWould You Like To Update Price? (Y/N) ");
    fflush(stdin);
    scanf("%c",&answer);
    switch(answer){
        case 'y':
        case 'Y':{
            int newPrice;
            printf("\nEnter New Price: ");
            scanf("%d",&newPrice);
            productList[pos].price = newPrice;
            break;
        }
        case 'n':
        case 'N':{
            break;
        }
        default:{
            printf("\nInput Invalid");
        }
    }
    productList[pos].sum = productList[pos].quantity*productList[pos].price;
}

void removeProduct(struct Product productList[], int *size, char key[]){
    int pos = findIndexByID_Name(productList,*size,key);
    if(pos==-1){
        printf("\nNot Found!!!!");
    }else{
        for(int i=pos; i<=*size-1;i++){
            strcpy(productList[i].id,productList[i+1].id);
            strcpy(productList[i].name,productList[i+1].name);
            productList[i].quantity = productList[i+1].quantity;
            productList[i].price = productList[i+1].price;
            productList[i].sum = productList[i+1].sum;
        }
    printf("\nRemove Successfully!");
    (*size)--;
    }
}

void checkState(struct Product productList[],int size, char key[]){
    int pos = findIndexByID_Name(productList,size,key);
    char ans;
    if(strcmp(productList[pos].state,"Inactive")==0){
        printf("\nProduct is inactive. \nDo you want to active it? (Y/N)");
        scanf("%c",&ans);
        switch(ans){
            case 'y':
            case 'Y':{
                solveDuplicate(productList,size,pos);
                strcpy(productList[pos].state,"Active");
                break;
            }
            case 'n':
            case 'N':{
                solveDuplicate(productList,size,pos);
                break;
            }
            default:{
                printf("\nInput Invalid");
            }
        }
    }else
    if(strcmp(productList[pos].state,"Deleted")==0){
        printf("\nProduct is deleted. \nDo you want to active it? (Y/N)");
        scanf("%c",&ans);
        switch(ans){
            case 'y':
            case 'Y':{
                solveDuplicate(productList,size,pos);
                strcpy(productList[pos].state,"Active");
                break;
            }
            case 'n':
            case 'N':{
                break;
            }
            default:{
                printf("\nInput Invalid");
            }
        }
    }else
        solveDuplicate(productList,size,pos);
}

void findProductById_Name(struct Product productList[],int size, char key[]){
    int pos = findIndexByID_Name(productList,size,key);
    if(pos==-1){
        printf("\nNot found!!!");
    }else{
        printf("\n===============================================================================================");
        printf("\n  %-10s%-30s%9s%15s%15s%10s","ID","Product","Quantity","Price","Sum","State");
        printf("\n-----------------------------------------------------------------------------------------------");
        printf("\n  %-10s%-30s%9d%15d%15d%10s",productList[pos].id,productList[pos].name,
               productList[pos].quantity,productList[pos].price,
               productList[pos].sum,productList[pos].state);
        printf("\n===============================================================================================");
    }
}

void outputProduct(struct Product productList[],int size){
    printf("\n%-30s%9s%15s%15s","Product","Quantity","Price","Sum");
    printf("\n-------                        --------      ---------        -------");
    for(int i=0; i<=size-1;i++){
        printf("\n%-30s%9d%15d%15d",productList[i].name,
               productList[i].quantity,productList[i].price,
               productList[i].sum);
    }
    //total chua VAT
    int total=0;
    for(int i=0; i<=size-1;i++){
        total+=productList[i].sum;
    }
    //vat
    int vat=total/10;
    //total VAT
    int totalVat=vat+total;
    printf("\n                                                              -------");
    printf("\nTotal%49s%15d"," ",total);
    printf("\nVAT%51s%15d"," ",vat);
    printf("\nTotal(VAT)%44s%15d"," ",totalVat);
}


int findIndexByID_Name(struct Product productList[], int size, char key[]){
    char nameTmp[50];
    for(int i = 0; i <= size - 1;i++){
        formatString(productList[i].name);
        strcpy(nameTmp,productList[i].name);
        if(strcmp(nameTmp,key) == 0){
            return i;
        }
    }
    for(int i = 0; i <= size - 1;i++){
        if(strcmp(productList[i].id,key) == 0){
            return i;
        }
    }
    return -1;
}

int checkValid(struct Product productList[],int size, char key[]){
    for(int i=0; i<=size-1;i++){
        if(strcmp(key,productList[i].id)==0){
            return 1;
        }
        formatString(productList[i].name);// when fscanf -> scan spaces -> formatString to remove spaces
        if(strcmp(key,productList[i].name)==0){
            return 2;
        }
    }
    return 0;
}

void removePos(char str[],int pos){
    for(int i = pos; i <= strlen(str) - 1;i++){
        str[i] = str[i + 1];
    }
}

void validSpace(char str[]){
    int pos = 0;
    while(str[pos] != 0){
        for(int i = pos; i <= strlen(str) - 1;i++){
            if(str[0] == 32){
            removePos(str,0);
            break;
        }
        if(str[i] == 32 && str[i + 1] == 32){
            removePos(str,i+1);
            break;
        }
        if(str[i] == 32 && str[i+1] == 0){
            removePos(str,i);
        }
        pos++;
    }
}
}

void formatString(char str[]){
    validSpace(str);
    strlwr(str);
    for(int i = 0;i <= strlen(str) - 1;i++){
        if(str[i] == 32){
            if(str[i+1] >= 97 && str[i+1] <= 122){
            str[i+1] -=32;
            }
        }
    }
        if(str[0] != 32){
            if(str[0] >= 97 && str[0] <= 122){
            str[0] -= 32;
            }
        }
}

void validID(char str[]){
    int i=0;
    validSpace(str);
    while(str[i]!='\0'){
        if(str[i]==32){
            str[i] = '_';
        }
        i++;
    }
    strlwr(str);
}

















