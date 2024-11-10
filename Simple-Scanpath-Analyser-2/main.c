#include<stdio.h>                       
#include<stdlib.h>                     
#include<string.h>                     
#include<math.h>

struct scanpath
{
    int id;

    char str[100];

    struct scanpath *next;

};


//This function converts the character it receives into an integer.
int char_to_int(char x)
{
    int y;

    y = (int)x - (int)'0';

return y;
}




struct scanpath* createScanpathList(char file_name[50])
{
    int i=0;

    struct scanpath *list,*list_next;

    FILE *file;

    file = fopen(file_name,"r");

        if (file == NULL)

        {   printf("file not found\n\n");    }


        else
        {
                while(!feof(file))
                {
                    struct scanpath *temp = (struct scanpath*)calloc(1,sizeof(struct scanpath));

                    temp->next = NULL;

                    fscanf(file,"%s\n",&temp->str);

                    temp->id = i+1;

                            if(i == 0)
                            {
                                list = temp;
                            }

                            else if(i == 1)
                            {
                                list_next = temp;
                                list->next = list_next;
                            }

                            else
                            {
                                list_next->next = temp;
                                list_next = list_next->next;
                            }

                    i++;


                }
        }

fclose(file);

return list;
}



//This function does the hashing. Since the pow function returns a double value, it converts the result to integer.
//We add '1e-9' to avoid errors when converting double to integer.
int hash(int m)
{
    int result;
    result = pow(10,m-1)+1e-9;

    return result % 11;
}


//This function takes two strings and returns 1 if they are equal.
int compare_str(char str1[100], char str2[100], int digit)
{
    int i,counter=0;

            for(i=0;i<strlen(str2);i++)
            {
                if(str1[digit+i] == str2[i])
                {
                    counter++;
                }
            }

      if(counter == strlen(str2))

          { return 1; }


      else

          { return 0; }

}



/*This function takes a string, one-stop point, and the array containing the most repeated numbers as input.
Then it finds the most repeated numbers in the string up to the stop point and puts them into the array.
If it has repeated in other numbers as much as the most repeated number, it puts them in the array.*/
void  most_frequent_AOI(char str[100],int stop,int most_array[])
{
    int i,j,array[10]={0},max=0,check_same_counter;

            for(i=0;i<stop;i++)
            {
                array[char_to_int(str[i])]++;
            }

    for(i=0;i<10;i++)
    {
        if(array[i]>max)
        {
            max = array[i];
        }
    }



    for(i=0;i<10;i++)
    {
        check_same_counter = 0;

        for(j=0;j<10;j++)
        {
                if(most_array[j] == i)
                {
                    check_same_counter++;
                }


                if( (array[i] == max) && (most_array[j] == 0) && (check_same_counter == 0) )
                {
                    most_array[j] = i;
                    check_same_counter++;
                }
        }
    }

}



//This function prints strings. Specify the patterns' parts using '[' and ']'.
void print_patterns(int pattern_locations[],char str[100],int lenght,int *counter)
{
    int i,j,k=0;

    printf("%d. ",*counter);

    for(i=0;i<strlen(str);i++)
    {

            if(pattern_locations[k] == i)
            {
                printf("[");

                j=i+lenght;

                for(;i<j;i++)
                {
                    printf("%c",str[i]);
                }

                printf("]");
                k++;
                i--;
            }

            else
            {
                printf("%c",str[i]);
            }
    }

    printf("\n");
}



/*This is the function that searches for the pattern in the string. If found,
it returns how many it has found. Other integer values taken as inputs are used to create statistical data.*/
int rabin_karp(char str[100],char pattern[100],int *counter_scanpath,int *counter_pattern,int print_counter,int *first_pattern_location)
{
        int i,j=0,n,m,h,p=0,t=0,round_counter=0,*pattern_location;

        n = strlen(str);
        m = strlen(pattern);
        h = hash(m);

                for(i=0;i<m;i++)
                {
                    p = ((10*p) + char_to_int(pattern[i]))%11;
                    t = ((10*t) + char_to_int(str[i]))%11;
                }

       for(i=0;i<=n-m;i++)
       {


            if(p == t)
            {
                    if(compare_str(str,pattern,i) == 1)
                    {

                        *counter_pattern = *counter_pattern + 1;

                                if(round_counter == 0)
                                    {*counter_scanpath = *counter_scanpath +1;
                                      pattern_location = (int *)malloc(1*sizeof(int));
                                      pattern_location[j] = i;
                                      j++;
                                    }
                                else
                                    {
                                      pattern_location = (int *)realloc(pattern_location,(j+1)*sizeof(int));
                                      pattern_location[j] = i;
                                      j++;
                                    }

                        round_counter++;

                    }
            }


            if(i <= (n-m))
            {
                t =( 10 * (t - char_to_int(str[i])*h) + char_to_int(str[i+m]) ) % 11;

                    if(t<0)
                    {
                        t = t + 11;
                    }
            }
       }

   if(round_counter != 0)
        {

          print_patterns(pattern_location,str,m,&print_counter);

          *first_pattern_location = pattern_location[0];

          }

return round_counter;
}




void searchPattern(struct scanpath *with,struct scanpath *without,char pattern[100])
{
    int counter_scanpath=0,counter_pattern=0,print_counter=1,result,first_pattern_location,frequents_with[10]={0},frequents_without[10]={0};
    int i;

        printf("Detected patterns for people with autism:\n");

        while(with != NULL)
            {
                first_pattern_location = -1;

                result = rabin_karp(with->str,pattern,&counter_scanpath,&counter_pattern,print_counter,&first_pattern_location);

                       if(result != 0)
                           {

                             print_counter++;

                             most_frequent_AOI(with->str,first_pattern_location,frequents_with);
                           }

                 with = with->next;


            }

      if(counter_pattern != 0)
            {

            printf("%d patterns detected in %d scanpaths\nThe most frequent AOI before the pattern is/are",counter_pattern,counter_scanpath);


                        for(i=0;i<10;i++)
                        {
                            if(frequents_with[i] != 0)
                            {
                                printf("   %d",frequents_with[i]);
                            }
                        }
            printf("\n\n");
            }
      else
            { printf("None\n\n\n"); }


    counter_pattern=0;
    counter_scanpath=0;
    print_counter=1;

        printf("Detected patterns for people without autism:\n");

        while(without != NULL)
            {
                first_pattern_location = -1;

                result = rabin_karp(without->str,pattern,&counter_scanpath,&counter_pattern,print_counter,&first_pattern_location);

                       if(result != 0)
                           {

                            print_counter++;

                            most_frequent_AOI(without->str,first_pattern_location,frequents_without);
                           }


                without = without->next;


            }

      if(counter_pattern != 0)
            {
                printf("%d patterns detected in %d scanpaths\nThe most frequent AOI before the pattern is/are",counter_pattern,counter_scanpath);

                        for(i=0;i<10;i++)
                        {
                            if(frequents_without[i] != 0)
                            {
                                printf("   %d",frequents_without[i]);
                            }
                        }
                printf("\n\n");
                }
      else
            { printf("None\n\n"); }

}



int main()
{
    char with_autism[50],without_autism[50],pattern[100];


            printf("Enter the file name for people with autism: ");
            scanf("%s",&with_autism);

            printf("Enter the file name for people without autism: ");
            scanf("%s",&without_autism);

            printf("Enter the pattern: ");
            scanf("%s",&pattern);

        printf("\n\n");

    struct scanpath *list_with_autism,*list_without_autism,*temp;

            list_with_autism = createScanpathList(with_autism);
            list_without_autism = createScanpathList(without_autism);



    searchPattern(list_with_autism,list_without_autism,pattern);
return 0;
}
