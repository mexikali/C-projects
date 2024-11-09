#include<stdio.h>               
#include<stdlib.h>   
#include<string.h>           

struct student{

    char ID[4];
    char name[41];
    char department[4];

};



int quadratic(struct student table[],int table_size,char ID[],char name[],char dep[],int h1){


    int result,i=0,counter=0;

            if (strlen(table[h1].ID) == 0){
                strcpy(table[h1].ID,ID);
                strcpy(table[h1].name,name);
                strcpy(table[h1].department,dep);

                return h1;}

            else{

                    do{

                        result = ( h1 + ((i*i)%table_size) ) %table_size;

                                if (strlen(table[result].ID) == 0){

                                    strcpy(table[result].ID,ID);
                                    strcpy(table[result].name,name);
                                    strcpy(table[result].department,dep);
                                    counter = 1;   }
                         i++;

                      }while(counter == 0);

                return result;
                }

}



int double_h(struct student table[],int table_size,char ID[],char name[],char dep[],int h1,int key){


    int result,i=0,counter=0;

            if (strlen(table[h1].ID) == 0){

                strcpy(table[h1].ID,ID);
                strcpy(table[h1].name,name);
                strcpy(table[h1].department,dep);

                return h1;}

            else{

                    do{

                        result = ( h1 + ( i*(7-(key%7)) ) %table_size ) %table_size;


                                if (strlen(table[result].ID) == 0){

                                    strcpy(table[result].ID,ID);
                                    strcpy(table[result].name,name);
                                    strcpy(table[result].department,dep);
                                    counter++;   }
                        i++;

                      }while(counter == 0);

                return result;
                }

}



int h1(int table_size,char S_ID[],int *key)
{
    char ID[4];

    strcpy(ID,S_ID);

        *key = (ID[0] - 65) + (atoi(&ID[1]) / 10) + atoi(&ID[2]);

    strcpy(S_ID,ID);
return (2 * (*key)) % (table_size);
}


/*this function checks that x is prime number or not*/
int check_prime(int x)
{
     int i,counter=0;

     for(i=2;i<x;i++){

            if( x % i == 0){
                counter++;} }

     if(counter == 0)
        return 0;/*return 0 means that x is prime number*/
     else
        return 1;
}



struct student* rehashing(struct student table[],int *table_size,int hashing_type){

    int check_result,stop=0,i,old_size,h_1,key,index;

    old_size = *table_size;

    *table_size = (*table_size) * 2;


    do{
    check_result = check_prime(*table_size);

            if( check_result != 0)
            {   *table_size = *table_size + 1; }

            else if( check_result == 0 )
            {   stop = 1; }

    }while(stop == 0);

    struct student *hash_table_new = ((struct student*)calloc(*table_size,sizeof(struct student)));

    for(i=0;i<old_size;i++){

            if(hashing_type == 1)
            {

                    if(strlen(table[i].ID) != 0)
                    {

                        h_1 = h1(*table_size,table[i].ID,&key);

                        index = double_h(hash_table_new,*table_size,table[i].ID,table[i].name,table[i].department,h_1,key);
                    }

            }

            else if(hashing_type == 2)
            {

                    if(strlen(table[i].ID) != 0)
                    {

                        h_1 = h1(*table_size,table[i].ID,&key);

                        index = quadratic(hash_table_new,*table_size,table[i].ID,table[i].name,table[i].department,h_1);
                    }

            }
    }
return hash_table_new;
}


int search_double(struct student table[],int table_size,char id[4],int h1,int key)
{
    int result,i=0,counter=0;

    if(strlen(table[h1].ID) == 0)
        {   return 0;   }

    else
        {
                        do{

                        result = ( h1 + ( i*(7-(key%7)) ) %table_size ) %table_size;


                                if (strcmp(table[result].ID,id) == 0)

                                    {  counter++;   }

                                else if (strlen(table[result].ID) == 0)

                                    {   return 0;   }


                        i++;

                      }while(counter == 0);

        }

return result;
}


int search_quadratic(struct student table[],int table_size,char id[4],int h1)
{
    int result,i=0,counter=0;

    if(strlen(table[h1].ID) == 0)
        {   return 0;   }

    else
        {
                        do{

                        result = ( h1 + ((i*i)%table_size) ) %table_size;


                                if (strcmp(table[result].ID,id) == 0)

                                    {  counter++;   }

                                else if (strlen(table[result].ID) == 0)

                                    {   return 0;   }


                        i++;

                      }while(counter == 0);

        }

return result;
}



void print_table(struct student table[],int table_size)
{
    int i;

        printf("\n\n");

    for(i=0;i<table_size;i++)
        {printf("%d. %s %s %s\n",i,table[i].ID,table[i].name,table[i].department);}

    printf("\n\n");
}



int main(){

    int table_size = 11,hashing_type,menu_choice,num_of_elements=0;


    printf("1. double hashing\n");
    printf("2. quadratic probing\n");

    do{
        printf("Enter your choice: ");
        scanf("%d",&hashing_type);

            if(hashing_type != 1 && hashing_type != 2){
                printf("Please enter one of the available options...\n");}

    }while(hashing_type != 1 && hashing_type != 2);
    printf("\n\n\n");


        struct student *hash_table = ((struct student*)calloc(table_size,sizeof(struct student)));

    do{

    int key,h_1,i,index;
    char name[41],dep[4];
    float load_factor;


                    printf("1. Add a student\n");
                    printf("2. Search a student\n");
                    printf("3. Print table\n");
                    printf("4. Exit\n");


        printf("Enter your choice: ");
        scanf("%d",&menu_choice);

        int ID_check=0;


        if(menu_choice == 1){

            char ID[4];

            printf("Enter unique identifier: ");
            fflush(stdin);
            scanf("%s",&ID);

                h_1 = h1(table_size,ID,&key);

                            if(hashing_type == 1)
                                {ID_check = search_double(hash_table,table_size,ID,h_1,key);}

                            else if(hashing_type == 2)
                                {ID_check = search_quadratic(hash_table,table_size,ID,h_1);}


                if(ID_check == 0){

                        printf("Name: ");
                        fflush(stdin);
                        gets(name);

                        printf("Department: ");
                        fflush(stdin);
                        gets(dep);


                                      if(hashing_type == 1){

                                            index = double_h(hash_table,table_size,ID,name,dep,h_1,key);
                                            num_of_elements++;
                                            printf("%s has been registered.",name);
                                      }

                                      else if(hashing_type == 2){

                                            index = quadratic(hash_table,table_size,ID,name,dep,h_1);
                                            num_of_elements++;
                                            printf("%s has been registered.",hash_table[index].name);
                                      }


                        load_factor = (float)num_of_elements / (float)table_size;


                                        if(load_factor > 0.5)
                                            { hash_table = rehashing(hash_table,&table_size,hashing_type); }

                                }



                else{
                    printf("Id should be unique!");}


        }



        else if(menu_choice == 2)
            {
                char searched_id[4];

                printf("Enter unique identifier: ");
                scanf("%s",&searched_id);


                h_1 = h1(table_size,searched_id,&key);

                            if(hashing_type == 1)
                                {ID_check = search_double(hash_table,table_size,searched_id,h_1,key);}

                            else if(hashing_type == 2)
                                {ID_check = search_quadratic(hash_table,table_size,searched_id,h_1);}


                if(ID_check != 0)
                {
                    printf("Name: %s\n",hash_table[ID_check].name);
                    printf("Department: %s",hash_table[ID_check].department);
                }

                else {printf("Student is not found!");}
            }



        else if(menu_choice == 3)
            {print_table(hash_table,table_size);}

        else if(menu_choice == 4)
            {return 0;}

        else
            {printf("Please enter one of the available options...\n");  fflush(stdin);}

    printf("\n\n");
    }while(menu_choice != 4);

return 0;
}
