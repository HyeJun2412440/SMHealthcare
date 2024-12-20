//
//  main.c
//  Calorie Diary
//
//  Created by Eunju Cha
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"

#define HEALTH_FILE_PATH "health_data.txt"
#define EXERCISEFILEPATH "exercises.txt"
#define DIETFILEPATH "diets.txt"

void saveData(const char* HEALTHFILEPATH, const HealthData* health_data);
void printHealthData(const HealthData* health_data);

static int choice;

int main() {
	// To initialize the health data object
    HealthData health_data = {0};
    health_data.remaining_calories = DAILY_CALORIE_GOAL;
    
    // Tocode: to read the list of the exercises and diets
    loadExercises(EXERCISEFILEPATH);
    loadDiets(DIETFILEPATH);

    // ToCode: to run the "Healthcare Management Systems" until all calories are used up or the user wants to exit the system
    do {
    	if ( health_data.remaining_calories <= 0){
            printf("You have consumed all your calories for today! \n");
    
		} else {

			printf("\n=======================================================================\n");
        	printf("[Healthcare Management Systems] \n");
        	printf("1. Exercise \n");
        	printf("2. Diet \n");
        	printf("3. Show logged information \n");
        	printf("4. Exit \n");
        	printf("Select the desired number: ");
        	scanf("%d", &choice);
        	printf("=======================================================================\n");
        
    }
		// ToCode: to run the sysmtem based on the user's choice
        switch (choice) {
            case 1:
            	inputExercise(&health_data);
                break;
                
            case 2:
            	inputDiet(&health_data);
                break;
                
            case 3:
            	printHealthData(&health_data);
            	break;
                
            case 4:
            	saveData(HEALTH_FILE_PATH, &health_data);
    			printf("Exit the system.\n");
    			printf("=======================================================================\n");
                break;
                
            default:
                printf("[Error] Invalid option. \n");
                printf("Please try again! \n");
        }
    } while (choice != 4);

    return 0;
}

void saveData(const char* filepath, const HealthData* health_data) {
    FILE* file = fopen(HEALTH_FILE_PATH, "w");
    if (file == NULL) {
        printf("There is no file for health data.\n");
        return;
    }

    // ToCode: save the chosen exercises and total calories burned
    fprintf(file, "[Exercises]\n");
    for (int i = 0; i < health_data->exercise_count; i++) {
        fprintf(file, "%s: %d calories burned\n", 
                health_data->exercises[i].exercise_name, 
                health_data->exercises[i].calories_burned_per_minute);
    }

    // ToCode: save the chosen diets and total calories intake
    fprintf(file, "\n[Diets]\n");
    for (int i = 0; i < health_data->diet_count; i++) {
        fprintf(file, "%s: %d calories intake\n", 
                health_data->diet[i].food_name, 
                health_data->diet[i].calories_intake);
    }

    // ToCode: save the total remaining calories
    fprintf(file, "\n[Total]\n");
    fprintf(file, "Total Calories Burned: %d\n", health_data->total_calories_burned);
    fprintf(file, "Total Calories Intake: %d\n", health_data->total_calories_intake);
    fprintf(file, "Remaining Calories: %d\n", health_data->remaining_calories);

    fclose(file);
}
void printHealthData(const HealthData* health_data) {
    printf("=========================== History of Exercise =======================\n");
    for (int i = 0; i < health_data->exercise_count; i++) {
        printf("%s: %d calories burned\n", 
               health_data->exercises[i].exercise_name, 
               health_data->exercises[i].calories_burned_per_minute);
    }
    printf("=======================================================================\n");

    printf("============================= History of Diet =========================\n");
    for (int i = 0; i < health_data->diet_count; i++) {
        printf("%s: %d calories intake\n", 
               health_data->diet[i].food_name, 
               health_data->diet[i].calories_intake);
    }
    printf("=======================================================================\n");

    printf("============================== Total Calories =========================\n");
    printf("Total Calories Burned: %d\n", health_data->total_calories_burned);
    printf("Total Calories Intake: %d\n", health_data->total_calories_intake);
    printf("Remaining Calories: %d\n", health_data->remaining_calories);
    printf("=======================================================================\n\n");
}

