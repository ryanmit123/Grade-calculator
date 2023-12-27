/* Ryan Mitchell 
   UID: 118522210
   Dir ID: rymit9 */

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

double calc_mean(int score[], int days[], int points_per_day_late, int num_assignments);
double standard_deviation(int scores[], int days[],int num_assignments, double mean, int points_per_day_late);

int main(){

  double numeric_score = 0, mean = 0, stand_deviation = 0, weight_total = 0;

  int num_assignments, points_per_day_late, num_drop_assignments, count1, count2, points_off;
  int assignment_number, assignment_score, assignment_weight, days_late, index, current, lowest_val;

  int scores[51], weights[51], days[51];

  char stat_info;

  bool assignment_dropped[51], display_stats = false;

  /* gets input for late points per day, number of dropped assignments, stats
     and number of assignments*/
  scanf("%d %d %c", &points_per_day_late, &num_drop_assignments, &stat_info);
  scanf("%d", &num_assignments);
  
  for(count1 = 0; count1 < num_assignments; count1++){

    /* input for assignment number, score, weight, and days late */
    scanf("%d, %d, %d, %d", &assignment_number, &assignment_score, &assignment_weight, &days_late);

    /* assigns assignment details to correct arrays */
    scores[assignment_number - 1] = assignment_score;
    weights[assignment_number - 1] = assignment_weight;
    days[assignment_number - 1] = days_late;
  }

    /* adds up all weights and initializing bool array */
  for(count1 = 0; count1 < num_assignments; count1++){

    weight_total = weight_total + weights[count1];

    assignment_dropped[count1] = false;

  }

  /* confirms weights add up to 100% */
  if(weight_total != 100){

    printf("ERROR: Invalid values provided \n");
    return;

  }


  /* Finding and dropping the lowest valued assignment */
  for(count1 = 0; count1 < num_drop_assignments; count1++){

    lowest_val = 10000;

    for(count2 = 0; count2 < num_assignments; count2++){

      current = scores[count2] * weights[count2];

      if(current < lowest_val && assignment_dropped[count2] == false){

	lowest_val = current;
	index = count2;

      }

    }
    /* index of assignment number is set to true, meaning it is dropped */
    assignment_dropped[index] = true;

  }

  /* IF the user requests statistical information, calls mean and SD functions*/
  if(stat_info == 'y' || stat_info == 'Y'){

    mean = calc_mean(scores, days, points_per_day_late, num_assignments);

    stand_deviation = standard_deviation(scores, days, num_assignments, mean, points_per_day_late);

    display_stats = true;
  }

  /* Calculating numeric score */
  
  weight_total = 0;

  for(count1 = 0; count1 < num_assignments; count1++){

    if(scores[count1] - (points_per_day_late * days[count1]) < 0){

      numeric_score += 0;

    } else if(assignment_dropped[count1] == true){

      weight_total += weights[count1];

    } else {
      
      numeric_score += (scores[count1] - (points_per_day_late * days[count1])) * (weights[count1]);

    }
  }

  numeric_score = numeric_score / (1 - (weight_total / 100));
  numeric_score /= 100;


  /* Displaying calculations */
  printf("Numeric Score: %0.4lf\n", numeric_score);
  printf("Points Penalty Per Day Late: %d\n", points_per_day_late);
  printf("Number of Assignments Dropped: %d\n", num_drop_assignments);
  printf("Values Provided: \n");
  printf("Assignment, Score, Weight, Days Late\n");


  /* Printing each assignment */
  for(count1 = 0; count1 < num_assignments; count1++){

    printf("%d, %d, %d, %d\n", count1 + 1, scores[count1], weights[count1], days[count1]);

  }


  /* Stat info */					    
  if(display_stats == true){
    printf("Mean: %0.4lf, Standard Deviation: %0.4lf\n", mean, stand_deviation);
  }

    return 1;

}


/* Calculates the mean average of the scores provided. 
   The parameters include scores, days late, pointers off per day late, 
   and the number of assignments. The function returns the mean as a double.*/

double calc_mean(int score[], int days[], int points_per_day_late, int num_assignments){

  double total = 0;
  int index;

  for(index = 0; index < num_assignments; index++){
    if(score[index] - (days[index] * points_per_day_late) < 0){
      total += 0;
    } else {
      total += (score[index] - (days[index] * points_per_day_late));
    }
  }

  total = total / num_assignments;

  return total;

}
/* Calculates the standard deviations of the scores provided.
   The parameters include the scores, days late, number of assignments, 
   the mean of the scores, and the points off per day late.
   The functions returns the standard deviation as a double.
*/
double standard_deviation(int scores[], int days[], int num_assignments, double mean, int points_per_day_late){

  int index;
  double stand_dev = 0;

  for(index = 0; index < num_assignments; index++){
    stand_dev += pow((scores[index] - (points_per_day_late * days[index])) - mean , 2);
  }

  stand_dev = stand_dev / num_assignments;

  stand_dev = sqrt(stand_dev);

  return stand_dev;

}
