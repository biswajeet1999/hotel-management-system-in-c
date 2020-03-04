#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
typedef struct ITEM
{
    int cost;
    char item[30];
    struct ITEM *next;
}ITEM;
int returncost(ITEM **l,char order[])
{
    ITEM *temp=*l;
    while(temp!=NULL){
        if(strcmp(temp->item,order)==0)
            return(temp->cost);
        temp=temp->next;
        }
    return 0;
}

void showlist(ITEM **l)
{
    if(*l==NULL)
        printf("List is empty\n");
    else{
        ITEM *temp=*l;
        printf("ITEM\t\t\t\tprice\n");
        while(temp!=NULL){
            printf("%s\t\t\t\t%d\n",temp->item,temp->cost);
            temp=temp->next;
        }
    }
}
void insertnode(ITEM **l,int cost,char item[])
{
    ITEM *temp=(ITEM *)malloc(sizeof(ITEM));
    strcpy(temp->item,item);
    temp->cost=cost;
    if(*l==NULL){
        *l=temp;
    }else{
        ITEM *t=*l;
        while(t->next!=NULL)
            t=t->next;
        t->next=temp;
    }
    temp->next=NULL;
}
void main()
{
    ITEM *START=NULL;
    int choise1,total,price1,i=0;
    char item1[30],c,order[30],name[30];
    FILE *item,*price,*store;
    item=fopen("item.txt","r");
    price=fopen("price.txt","r");
    store=fopen("record.txt","a+");
    if(item==NULL || price==NULL || store==NULL){
        printf("Error opening of files\n");
        exit(0);
    }
    while(!feof(item)){
        c=fgetc(item);
        if(c!='\n'){
            item1[i]=c;i++;
        }else{
            item1[i]='\0';
            fscanf(price,"%d",&price1);
            insertnode(&START,price1,item1);
            i=0;
        }
    }
    printf("  ***************** HOTEL TAJ *****************\n");
    while(1){
        system("cls");
        total=0;
        printf("PRESS\n 1-SEE ITEM\t 2-GET PREVIOUS RECORD\t 3-EXIT\n");
        scanf("%d",&choise1);
        switch(choise1){
        case 1:
            system("cls");
            showlist(&START);
            printf("\n1-Place order\t2-back\n");
            scanf("%d",&choise1);
            switch(choise1)
            {
            case 1:
                system("cls");
                showlist(&START);
                printf("Press * to stop order\n      ENTER ITEM\n");
                printf("Enter your name\n");
                fflush(stdin);
                scanf("%[^\n]s",name);
                fprintf(store,"%s\n",name);
                while(1){
                    fflush(stdin);
                    scanf("%[^\n]s",order);
                    if(strcmp(order,"*")==0)
                        break;
                    price1=returncost(&START,order);
                    if(price1==0)
                        printf("%s not found in the list\n",order);
                    else{
                        total=total+price1;
                        fprintf(store,"%s\t",order);
                        fprintf(store,"%d\n",price1);
                    }
                }
                printf("\n\n TOTAL  %d/- only\n",total);
                fprintf(store,"TOTAL %d/-\n\n",total);
                fprintf(store,"-----------------------------------------------------------------------\n");
                printf("  THANKS  VISIT AGAIN\npress any key to continue");
                getch();
                continue;
            case 2:
                continue;
            default:
                printf("Invalid choice\nPress any key to continue\n");
                getch();
                continue;
            }
            continue;
        case 2:
            system("cls");
            fclose(store);
            store=fopen("record.txt","r");
            while(!feof(store)){
                c=fgetc(store);
                if(!feof(store))
                   printf("%c",c);
            }
            printf("Press any key to continue\n");
            getch();
            continue;
        case 3:
            exit(0);
        }
    }
    fclose(item);
    fclose(price);
    fclose(store);
}
