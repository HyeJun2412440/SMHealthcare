//
//  cal_exercise.c
//  Excercise for Calorie Diary
//
//  Created by Eunju Cha
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"

#define MAX_EXERCISES 100  			// Maximum number of exercises
#define MAX_EXERCISE_NAME_LEN 50	// Maximum length of the name of exercise


// To declare the structure of the exercises
static Exercise exercise_list[MAX_EXERCISES];
int exercise_list_size = 0;


/*
    description : read the information in "excercises.txt"
*/

void loadExercises(const char* EXERCISEFILEPATH) {
    FILE *file = fopen(EXERCISEFILEPATH, "r");
    if (file == NULL) {
        printf("There is no file for exercises! \n");
        return;
    }

    // ToCode: to read a list of the exercises from the given file
    while (fscanf(file, "%49s %d", exercise_list[exercise_list_size].exercise_name,
                  &exercise_list[exercise_list_size].calories_burned_per_minute) == 2) {
    	exercise_list_size++;
        if (exercise_list_size >= MAX_EXERCISES){
        	
        	break;
        	
		}
    }

    fclose(file);
}


/*
    description : to enter the selected exercise and the total calories burned in the health data
    input parameters : health_data - data object to which the selected exercise and its calories are added 
    return value : No
    
    operation : 1. provide the options for the exercises to be selected
    			2. enter the duration of the exercise
    			3. enter the selected exercise and the total calories burned in the health data
*/

void inputExercise(HealthData* health_data) {
	
	printf("Enter exercise name: ");
    scanf("%s", health_data->exercises[health_data->exercise_count].exercise_name);

    printf("Enter calories burned per minute: ");
    scanf("%d", &health_data->exercises[health_data->exercise_count].calories_burned_per_minute);

    health_data->total_calories_burned += health_data->exercises[health_data->exercise_count].calories_burned_per_minute;
    health_data->exercise_count++;
}
