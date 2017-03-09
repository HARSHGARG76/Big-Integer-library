//Demo program for the "intal" library of integers of arbitrary length.
//intal stands for "int"eger of "a"rbitrary "l"ength.

#include <stdio.h>
#include "intal.h"

int main() {
    
	intal* i1 = create_intal();
	intal* i2 = create_intal();
	intal* i3 = create_intal();
	intal* i4 = create_intal();
    intal *k=NULL;
    long int k1=0;

	read_intal(i1, "12");
	read_intal(i2, "10");
	// read_intal(i3, "-1234");
	// read_intal(i4, "+0");
	// Intal_split(&i1,&i3,&i4);
	// printf("%s\n", i3->s);
	//  printf("%s\n", i4->s);
	//  Intal_pow10(&i1,6);
	// printf("%s\n", i1->s);
	// printf("i1 = ");
	//print_intal(i1);
	//printf("\n");

	// printf("i2 = ");
	//print_intal(i2);
	//printf("\n");
	
	// printf("i3 = ");
	// print_intal(i3);
	// printf("\n");
	
	// printf("i4 = ");
	// print_intal(i4);
	// printf("\n");
    
 	// k1=divide_intal(i1,i2);
  //   printf("div is %ld\n",k1);
    k=pow_intal(i1,i2);
     printf("the number of digits is :%d\n",k->n);
     printf("multiply is %s\n",k->s);
    
    
    delete_intal(&i1);
    delete_intal(&i2);
    delete_intal(&i3);
    delete_intal(&i4);

    

	// delete_intal(&i1);
	// delete_intal(&i2);
	// delete_intal(&i3);
	

	return 0;
}
