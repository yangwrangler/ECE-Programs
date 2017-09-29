/*******************************************************************
 
 ECE 437: Operating Systems PA03
 Professor: Dr. Shu
 Created by: Panayioti Kitsos, Ryan Vacek
 Date: 9/28/17

*******************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int extern x;

int fib_seq(int x) { 
    
     srand(time(NULL));
     int i, rint = (rand() % 30); 
     double dummy; 

     for (i = 0; i<rint*100; i++) { 
       dummy = 2.3458*i*8.7651/1.234;
     }
     
     if (x == 0) 
     	return(0);
     else if (x == 1) 
     	return(1); 
     else 
     	return (fib_seq(x-1)+fib_seq(x-2));
}
