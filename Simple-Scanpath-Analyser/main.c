#include<stdio.h>        
#include<stdlib.h>          
#include<string.h>            

//I defined this structure to store the information in the Aois file.
struct areas{

    char name;
    int x;
    int weight;
    int y;
    int height;

};


//I defined this structure to store the information in the fixations file.
struct fix{

    int unique_id;
    int fix_id;
    int x;
    int y;
    int duration;

};


struct edge{

    int id;
    int weight;
    struct edge* next;

};


struct vertex{

    int id;
    char scanpath[100];
    struct edge *next;

};


struct vertex* createVertices(char file_aoi[30],char file_fixation[30],int *graph_size)
{
    int i=0,j,num_of_elements_area=0,num_of_elements_fix=0,scanpath_step=0,graph_step=0;

    struct areas *area_array = (struct areas*)calloc(1,sizeof(struct areas));
    struct fix *fix_array = (struct fix*)calloc(1,sizeof(struct fix));

    FILE *aoi,*fixation;

    aoi = fopen(file_aoi,"r");


            if(aoi == NULL)

                {
                    printf("file not found\n\n");
                }

             else
                {
                     while(!feof(aoi))
                     {

                       area_array = (struct areas*)realloc(area_array,(i+1)*sizeof(struct areas));

                       fscanf(aoi,"%c %d %d %d %d\n",&area_array[i].name,&area_array[i].x,&area_array[i].weight,&area_array[i].y,&area_array[i].height);

                       i++;
                     }
                }

                num_of_elements_area = i;
                fclose(aoi);



    i=0;
    int new_person=0;

    fixation = fopen(file_fixation,"r");


            if(fixation == NULL)

                {
                    printf("file not found\n\n");
                }

             else
                {
                     while( !feof(fixation) )
                     {

                       fix_array = (struct fix*)realloc(fix_array,(i+1)*sizeof(struct fix));

                       fscanf(aoi,"%d %d %d %d\n",&fix_array[i].fix_id,&fix_array[i].x,&fix_array[i].y,&fix_array[i].duration);


                                if(fix_array[i].fix_id == 0)

                                {
                                    new_person++;
                                }
                       fix_array[i].unique_id = new_person;
                       i++;

                     }
                }

                num_of_elements_fix = i;
                fclose(fixation);


    struct vertex *graph = (struct vertex*)calloc(1,sizeof(struct vertex));

        for(i=0;i<num_of_elements_fix;i++)
        {
            if(fix_array[i].fix_id == 0)
                {

                graph = (struct vertex*)realloc(graph,(graph_step+2)*sizeof(struct vertex));

                        if(i != 0)   {graph_step++;}

                graph[graph_step].id = fix_array[i].unique_id;

                scanpath_step = 0;

                graph[graph_step].next = NULL;


                }



                for(j=0;j<num_of_elements_area;j++)
                {

                      if( (fix_array[i].x >= area_array[j].x) && (fix_array[i].x <= (area_array[j].x + area_array[j].weight)) && (fix_array[i].y >= area_array[j].y) && (fix_array[i].y <= (area_array[j].y + area_array[j].height)) )

                            {
                            graph[graph_step].scanpath[scanpath_step] = area_array[j].name;
                            scanpath_step++;
                            graph[graph_step].scanpath[scanpath_step] = '\0';
                            }
                }
        }

            *graph_size = graph_step + 1;

return graph;
}


//This function returns the larger of two integers.
int bigger_int(int x, int y)
{
    return (x > y)? x : y;
}


//This function finds the length of the longest subsequence between two strings.
int lcs(char str1[100],char str2[100])
{
    int i,j,len_str1,len_str2;

        len_str1 = strlen(str1);
        len_str2 = strlen(str2);

    int L[len_str1+1][len_str2+1];


        for (i=0; i<=len_str1; i++)
        {
                for (j=0; j<=len_str2; j++)
                {
                    if (i == 0 || j == 0)
                        L[i][j] = 0;

                    else if (str1[i-1] == str2[j-1])
                        L[i][j] = L[i-1][j-1] + 1;

                    else
                        L[i][j] = bigger_int(L[i-1][j], L[i][j-1]);
                }
        }


return L[len_str1][len_str2];
}



void createEdges(struct vertex graph[],int size)
{
    int i,j,lcs_result;

    for(i=0;i<size;i++)
    {
            for(j=i+1;j<size;j++)
            {
                lcs_result = lcs(graph[i].scanpath,graph[j].scanpath);

                        if(lcs_result >= 5)
                        {
                            struct edge *new1,*new2,*temp1,*temp2;

                            new1 = (struct edge*)malloc(sizeof(struct edge));
                            new1->next = NULL;
                            new1->id = graph[j].id;
                            new1->weight = lcs_result;

                            new2 = (struct edge*)malloc(sizeof(struct edge));
                            new2->next = NULL;
                            new2->id = graph[i].id;
                            new2->weight = lcs_result;

                            temp1 = graph[i].next;
                            temp2 = graph[j].next;

                            graph[i].next = new1;
                            graph[j].next = new2;

                            new1->next = temp1;
                            new2->next = temp2;

                        }
            }
    }


}


void printGraph(struct vertex graph[],int size)
{
    int i,min,max,min_c,max_c;
    int neighbors[size];
        memset(neighbors,0,sizeof neighbors);

        for(i=0;i<size;i++)

        {
                if(graph[i].next != NULL)
                    printf("%d ",graph[i].id);

            while (graph[i].next != NULL)
            {
                neighbors[i]++;
                printf(" -> %d | %d ",graph[i].next->id,graph[i].next->weight);
                graph[i].next = graph[i].next->next;
            }
           if(neighbors[i] != 0)
            printf("\n");
        }

    min = neighbors[0];
    max = neighbors[0];

    for(i=1; i<size; i++)
    {
         if(min>neighbors[i]){
                min=neighbors[i];
                min_c = i;  }

         if(max<neighbors[i]){
                max=neighbors[i];
                max_c = i;   }
    }

    printf("\n\nVertex with maximum number of neighbors: %d has %d neighbors",max_c+1,neighbors[max_c]);
    printf("\nVertex with minimum number of neighbors: %d has %d neighbors\n\n",min_c+1,neighbors[min_c]);
}




int main()
{
    int graph_size;

    char file_aoi[30],file_fixation[30];

        printf("Enter AOIs file name > ");
        scanf("%s",&file_aoi);

        printf("Enter fixations file name > ");
        scanf("%s",&file_fixation);

    printf("\n\n");

    struct vertex *graph = createVertices(file_aoi,file_fixation,&graph_size);

    createEdges(graph,graph_size);

    printGraph(graph,graph_size);

return 0;
}
