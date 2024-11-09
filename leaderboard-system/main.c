#include<stdio.h>                       
#include<math.h>                     
#include<stdlib.h>                     
#include<string.h>

//  awr is actual win rate
//  ewr is expected win rate
//  wrr is win rate ratio
struct Champions
{
    char name[50];
	int  num_of_battle,num_of_win;
	float awr,ewr,wrr,skew;

};

struct Champions* initalizeChampions(char file_name[20],int *size)
{

	int i=0;

	struct Champions *champ_array = (struct Champions*)calloc(1,sizeof(struct Champions));

    FILE *char_file;

    char_file = fopen(file_name,"r");


            if(char_file==NULL){
                    printf("file not found\n\n");}

            else{

                    while(!feof(char_file)){


                            champ_array = (struct Champions*)realloc(champ_array,(i+1)*sizeof(struct Champions));
		                            champ_array[i].awr = 0.0;
		                            champ_array[i].ewr = 0.0;
		                            champ_array[i].wrr = 0.0;
		                            champ_array[i].skew = 0.0;
		                            champ_array[i].num_of_win = 0;
		                            champ_array[i].num_of_battle = 0;

                            fscanf(char_file,"%s %f\n",&champ_array[i].name,&champ_array[i].ewr);

                            *size = *size + 1;

                            i++;}   }

    fclose(char_file);

return &champ_array[0];
}



struct Champions* getBattleData(char file_name[20],int size,struct Champions champ_array[size])
{

	int i=0,char1,char2,winner;

	char temp_read1[50],temp_read2[50],temp_read3[50];


    FILE *battle_file;

    battle_file = fopen(file_name,"r");


            if(battle_file==NULL){
                    printf("file not found\n\n");}

            else{

                    while(!feof(battle_file)){


							fscanf(battle_file,"%s %s %s %s\n",&temp_read1,&temp_read1,temp_read2,temp_read3);

                            for(i=0;i<size;i++){

                            	if(strcmp(temp_read1,champ_array[i].name) == 0){

                            		char1 = i;}

                            	if(strcmp(temp_read2,champ_array[i].name) == 0){
                                    char2 = i;}

                                if(strcmp(temp_read3,champ_array[i].name) == 0){
                                    winner = i;}

                            		}


                    if(char1 == winner && char1 != char2){

                        champ_array[char1].num_of_battle += 1;
                        champ_array[char1].num_of_win += 1;
                        champ_array[char2].num_of_battle += 1;      }


                    else if(char2 == winner && char1 != char2){

                        champ_array[char2].num_of_battle += 1;
                        champ_array[char2].num_of_win += 1;
                        champ_array[char1].num_of_battle += 1;      }


                            }   }

    fclose(battle_file);

return &champ_array[0];
}



struct Champions* computeWinRate(int size,struct Champions champ_array[size])
{
	int i;

	for(i=0;i<size;i++){

		champ_array[i].awr = (float)champ_array[i].num_of_win / (float)champ_array[i].num_of_battle;
		champ_array[i].wrr = (float)champ_array[i].awr / (float)champ_array[i].ewr;
		champ_array[i].skew = fabsf((champ_array[i].wrr-1));

	}


return &champ_array[0];
}



void heapify(struct Champions champ_array[],int size,int i,int criteria)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;


		if(criteria == 1)
		{


			    if (left < size && champ_array[left].awr < champ_array[largest].awr)
			        largest = left;

			    if (right < size && champ_array[right].awr < champ_array[largest].awr)
			        largest = right;

			    if (largest != i) {

			       struct Champions temp;

			       			temp = champ_array[i];
			       			champ_array[i] = champ_array[largest];
			       			champ_array[largest] = temp;


			         heapify(champ_array, size, largest,criteria);
			    }
		}





		else if(criteria == 2)
		{


			    if (left < size && champ_array[left].ewr < champ_array[largest].ewr)
			        largest = left;

			    if (right < size && champ_array[right].ewr < champ_array[largest].ewr)
			        largest = right;

			    if (largest != i) {

			       struct Champions temp;

			       			temp = champ_array[i];
			       			champ_array[i] = champ_array[largest];
			       			champ_array[largest] = temp;


			         heapify(champ_array, size, largest,criteria);
			    }
		}





		else if(criteria == 3)
		{


			    if (left < size && champ_array[left].skew < champ_array[largest].skew)
			        largest = left;

			    if (right < size && champ_array[right].skew < champ_array[largest].skew)
			        largest = right;

			    if (largest != i) {

			       struct Champions temp;

			       			temp = champ_array[i];
			       			champ_array[i] = champ_array[largest];
			       			champ_array[largest] = temp;


			         heapify(champ_array, size, largest,criteria);
			    }
		}

}


void heapSort(int size,struct Champions champ_array[],int criteria)
{
    int i;
	for (i = size / 2 - 1; i >= 0; i--){
        heapify(champ_array, size, i,criteria);}


    for (i = size - 1; i >= 0; i--) {

		    struct Champions temp;

       			temp = champ_array[0];
       			champ_array[0] = champ_array[i];
       			champ_array[i] = temp;

        heapify(champ_array, i, 0,criteria);

    }


}

void printLeaderBoard(struct Champions champ_array[],int size)
{
	printf("Champion \tBattles \tWin \tAWR \tEWR \tSkew\n");

	int i;

	for(i=0;i<size;i++){

	printf("%s \t\t%d \t\t%d \t%.2f \t%.2f  \t%.2f\n",champ_array[i].name,champ_array[i].num_of_battle,champ_array[i].num_of_win,champ_array[i].awr,champ_array[i].ewr,champ_array[i].skew);}

}


int main(int argc,char* argv[]){

// if there is no comment line argument, the program will be stopped
if(argc == 1)
{
	printf("Enter the command line arguments and re-compile...");
	return 0;
}


	int num_of_elements_in_array=0;

	struct Champions *champ_array;

	champ_array = initalizeChampions(argv[3],&num_of_elements_in_array);
	//The array is created, and the character file is read. The piece of information on the file is written to the array.

	champ_array = getBattleData(argv[4],num_of_elements_in_array,champ_array);
	//The battle file is read. The piece of information on the file is written to the array.

	champ_array = computeWinRate(num_of_elements_in_array,champ_array);
    //the actual win rate, win rate ratio and, expectation skew are calculated.

	heapSort(num_of_elements_in_array,champ_array,atoi(argv[2])); // Atoi function is used for the string to an integer.
	/*The created array is sorted according to criteria.
    "1" is for the actual win rate
    "2" is for the expected win rate
    "3" is for expectation skew*/

	printLeaderBoard(champ_array,num_of_elements_in_array);

			if(atoi(argv[2]) == 1)
				printf("\n\nThis table sorted according to actual win rate\n\n");
			else if(atoi(argv[2]) == 2)
				printf("\n\nThis table sorted according to expected win rate\n\n");
			else if(atoi(argv[2]) == 3)
				printf("\n\nThis table sorted according to expectation skew\n\n");


return 0;
}
