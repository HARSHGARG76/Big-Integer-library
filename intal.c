//intal.c is a library of integers of arbitrary length.
//intal stands for "int"eger of "a"rbitrary "l"ength.

// intal is an integer of arbitrary length. It has two fields; s and n.
// Field s stores a null-terminated string of decimal digits preceded by
// a + or sign indicating positive and negative integers.
// Field n represents the number of decimal digits excluding the sign.
// n is always greater than zero.
// Eg: Zero is represented with s as "+0" and n == 1.
// Eg: 2017 is represented with s as "+2017" and n == 4.
// Eg: -272 is represented with s as "-272" and n == 3.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "intal.h"
#include <math.h>

// Creates and returns a pointer to a new intal initialized to zero.
// Initial values of i would be "+0" and n == 1.
intal* create_intal(){
	intal* i;

	i =  malloc(sizeof(intal));
	if(i == NULL) {
		return NULL; //malloc failed
	}

	//alloc 3 chars for a null-terminated string "+0".
	i->s = malloc(25 * sizeof(char));
	if(i->s == NULL) {
		free(i);
		return NULL; //malloc failed
	}

	strcpy(i->s, "+0"); 
	i->n = 1;

	return i;
}

// Deletes an intal, especially the memory allocated to it.
// i is a pointer to an intal to be deleted. It also resets *i to null.
void delete_intal(intal** i){

	if (i == NULL) {
		return;
	}

	if (*i == NULL) {
		return;
	}

	if( (*i)->s != NULL ) {
		free( (*i)->s );
	 }

	free(*i);
	*i = NULL;
	return;
}

// Reads an intal from str into intal struct.
// str should be a null-terminated string just like s inside intal except that
// a postive integer could start without a + sign.
// str is unmodified.
void read_intal(intal* i, char* str){
	int n;

	if(i == NULL) {
		return; //use create_intal before calling read_intal
	}
	if(str == NULL) {
		return; //invalid str
	}

	n = strlen(str);

	if( (str[0] == '+') || (str[0] == '-') ) {
		//it has a sign
	 	i->s = realloc(i->s,(n + 1)*sizeof(char)); //one extra char for null termination
	 	strcpy(i->s, str);
	} else {
		//it doesn't have a sign and hence it's positive
		n++; //one extra for the + sign
	 	i->s = realloc(i->s,(n + 1)*sizeof(char)); //one extra char for null termination
	 	i->s[0] = '+';
	 	strcpy(i->s + 1, str);
	}
    i->s[n]='\0';
    i->n=n-1;
	return;
}

// Prints the integer into stdout.
// It's just printf of s in intal (with format specifier %s) except that 
// it doesn't print the sign in case of positive integer.
void print_intal(intal* i){
	if(i == NULL) {
		return; //no intal to print
	}

	if(i->s != NULL) {
		if(i->s[0] == '+') {
			printf("%s", i->s + 1);
		} else {
			printf("%s", i->s);
		}
	}
	return;
}

int Intal_pad(intal* bi, int newNod)
{
    
    char* newData = (char *)malloc(sizeof(char)*(newNod+1));
    for(int i=0;i<newNod-(bi->n);i++)
    {
        newData[i]=0+'0';
    } //add padding zeros
    
    for(int i=0;i<(bi->n);i++)
    {
        newData[i+(newNod-(bi->n))]=bi->s[i+1];
    }
    newData[0]=bi->s[0];
    newData[newNod] = '\0';
    
    bi->s=newData;
    bi->n=newNod-1;
    return 1;
    }
// Adds two intals a and b, and returns the sum.
// Parameters a and b are not modified. Sum is a new intal.
// intal* add_intal(intal* a, intal* b)
intal* add_intal(intal* a, intal* b)
{
    intal* sum=NULL;
    intal *c;
    sum=create_intal();
    int size;
    int n1 = (a->n) + 1;
    int n2 = (b->n) + 1;
    if(a->s[0]!=(b->s[0]))
    {
        if(a->s[0]=='+')
        {
            if(strcmp((a->s)+1,(b->s)+1)>0)
            {
                b->s[0]='+';
                c=subtract_intal(a,b);
                c->s[0]='+';
            }
            else
            {
                b->s[0]='+';
                c=subtract_intal(b,a);
                c->s[0]='-';
            }
            
        }
        else
        {
            if(strcmp((a->s)+1,(b->s)+1)>0)
            {
                b->s[0]='-';
                c=subtract_intal(a,b);
                c->s[0]='-';
            }
            else
            {
                b->s[0]='-';
                c=subtract_intal(b,a);
                c->s[0]='+';
            }
         }
        return c;
    }
    if(n1 > n2)
    {
        size = n1;
        Intal_pad(b,size);
    }
    else
    {
        size = n2;
        Intal_pad(a,size);
    }
    char * s1=(char *)malloc(sizeof(char)*(size+1));
    char * s2;
    int carry = 0;
    int val = 0;
    for (int i = size-1; i >=1; i--)
    {
        val = ((a->s[i]-'0') + (b->s[i]-'0') + carry);
        carry = val/10;
        s1[i] = val%10 + '0';
    }
    s1[0]= a->s[0];
    s1[size] = '\0';
    read_intal(sum,s1);
    if(carry>0){
        s2 = malloc(sizeof(char)*size+2);
        s2[0] = a->s[0];
        s2[1] = carry +'0';
        strcpy(s2+2,s1+1);
        read_intal(sum,s2);

    }
    //TODO it's a stub function. Fill in the details and delete this comment.
    return sum;
}
// Subtracts intal b from intal a. That is, finds a-b and returns the answer.
// Parameters a and b are not modified. a-b is a new intal.
intal * subtract_intal(intal *a, intal *b)
{
    intal *c;
    intal* diff=NULL;
    diff = create_intal();
    int size;
    int n1 = a->n + 1;
    int n2 = b->n + 1;
    if(a->s[0]!=(b->s[0]))
    {
        
        if(a->s[0]=='+')
        {
            b->s[0]='+';
            c=add_intal(a,b);
            c->s[0]='+';
            
        }
        else
        {
            a->s[0]='+';
            c=add_intal(a,b);
            c->s[0]='-';
        }
        
        return c;
    }
    
    if(n1 > n2)
    {
        size = n1;
        Intal_pad(b,size);
    }
    else{
        size = n2;
        Intal_pad(a,size);
    }
    char * s1=(char *)malloc(sizeof(char)*size);
    int swap=0;
    if(strcmp(a->s,b->s)<0)
    {
        intal *c=NULL;
        c=a;
        a=b;
        b=c;
        swap=1;
    }
    int val=0;
    for(int i=size-1;i>0;i--)
    {
        a->s[i] = ((a->s[i]-'0') - (b->s[i]-'0'))+'0';
        if((a->s[i]-'0')<0)
        {
            int j=i;
            while((a->s[j]-'0')<0)
            {
                a->s[j] = (a->s[j])-'0' + 10 +'0';
                a->s[j-1]=((a->s[j-1])-'0')-1+'0';
                j--;
                if(j==-1)
                    printf("subtraction error\n");
            }
        }
    }
    
    if(a->s[0]=='-' && b->s[0]=='-')
    {
        if(swap==0)
        {
            a->s[0]='-';
        }
        else
        {
            a->s[0]='+';
        }
        diff=a;
        return diff;
        
    }
    
    if(swap==1)
        a->s[0]='-';
    else
        a->s[0]='+';
    diff = a;
    return diff;
}

int Intal_pow10 (intal** a, int m) {

    intal *temp=create_intal();
    int newNod = m + (*a)->n + 2;
   // printf("m is %d\n",newNod);
    char *str = (char*)malloc(sizeof(char)*(newNod));
    //a->s = realloc(a->s, newNod * sizeof(char));
    for(int i= (*a)->n+1; i < newNod-1; i++)
      str[i] = 0+'0';
    for (int i = 1; i <= (*a)->n; ++i)
    {
      str[i] = (*a)->s[i];
    }
    str[0] = (*a)->s[0];
    str[newNod-1]='\0';
    temp->n = newNod -2;
    read_intal(temp,str);
    *a = temp;
    return 0;
}
// Divides intal a from intal b and returns the quotient. 
// That is, finds floor(a/b), which is aka integer division.
// Parameters a and b are not modified. Floor(a/b) is a new intal.

long int divide_intal(intal* a, intal* b)
{
    if(b->s[1]=='0')
    {
        printf("Unsuccessful -- divide by zero\n");
        return -999;  //spcified divide by zero
    }
    int n1 = (a->n) + 1;
    int n2 = (b->n) + 1;
    int size;
    long int quotient=0;
    intal *divisor1=NULL;
    intal *dividend=NULL;
    divisor1=create_intal();
    dividend=create_intal();
    if(n1 > n2)
    {
        size = n1;
        Intal_pad(b,size);
    }
    else
    {
        size = n2;
        Intal_pad(a,size);
    }
    read_intal(divisor1,b->s);   // divisor is 6
    read_intal(dividend,a->s); // dividend is 24
    dividend->s[0]='+';
    divisor1->s[0]='+';
    while(strcmp(dividend->s+1,divisor1->s+1)>=0)
    {
        dividend = subtract_intal(dividend,divisor1);
        ++quotient;
    }
    if(a->s[0]!=b->s[0])
    {
        quotient=-quotient;
    }
    return quotient;
}

// split function for splitting the number in the middle

int Intal_split (intal** a, intal** a1, intal** a2) {
     intal* p1 = create_intal();
     intal* p2 = create_intal();
    int n=0;
    n = ((*a)->n)/2; 
    char *s1= (char *)malloc(sizeof(char)*(n+2));
    char *s2= (char *)malloc(sizeof(char)*(n+2));
    memcpy(s1+1, (*a)->s+1, n * sizeof(char));
    memcpy(s2+1, (*a)->s+1 + n, n * sizeof(char));
    s1[0]= (*a)->s[0];
    s2[0]= (*a)->s[0];
    s1[n+1] = '\0';
    s2[n+1] = '\0';

    read_intal(p1,s1);
    read_intal(p2,s2);
    *a1 = p1;
    *a2 = p2;
    return 0;
}


intal* stripzeros(intal* a){
    intal *res3=create_intal();
    int num_digits = a->n;
    int index=0;
    char ch;
    while((ch=a->s[index+1])=='0'){
      index++;
    }
    int new_size= (a->n) - index +2;
    char *str = (char *)malloc(sizeof(char)*(new_size));
    str[0]= a->s[0];
    memcpy(str+1,a->s + index+1, new_size-2);
    str[new_size-1] = '\0';
    read_intal(res3,str);
    free(str);

    return res3;


}

intal *karat(intal **a, intal **b){
	intal *res=create_intal();
	if((*a)->n == 1){
	int product = ((*a)->s[1]-'0')*((*b)->s[1]-'0');
  int size1=0;
  int val = product;
  int val1= product;
  int prod=product;
  if(val<10)
    size1 = 1;
  else
    size1=2;
  char *s1 = malloc(sizeof(char) * (size1+2));
  int k = size1;
  if(prod==0)
    s1[k--]=0+'0';
  while(prod>0){
    int temp= prod%10;
    s1[k]=temp +'0';
    k--;
    prod=prod/10;
  }
  if(((*a)->s[0])!=((*b)->s[0]))
    s1[0]='-';
  else
    s1[0]= '+';
  s1[size1+1] = '\0';
	  read_intal(res,s1);                           
		free(s1);
		return res;
	}

    intal *a1 = NULL;
    intal *a2 = NULL;
    intal *b1 = NULL;
    intal *b2 = NULL;
    intal *p1 = NULL;
    intal *p2 = NULL;
    intal *p3 = NULL;
    intal *a1pa2 = NULL;
    intal *b1pb2 = NULL;

    if(((*a)->n)%2 !=0){
        Intal_pad((*b),((*a)->n) + 2);
        Intal_pad((*a),((*a)->n) + 2);
    }
    int n1 = ((*a)->n);
    int m = ((*a)->n)/2;
    Intal_split(a,&a1,&a2);
    Intal_split(b,&b1,&b2);
    a1pa2 = add_intal(a1,a2);
    b1pb2 = add_intal(b1,b2);
    p1 = karat(&a1,&b1);
    p2 = karat(&a2,&b2);
    if(a1pa2->n < b1pb2->n){
        Intal_pad(a1pa2, b1pb2->n+1);
        a1pa2->n = (b1pb2->n);
    }
    else if(a1pa2->n > b1pb2->n){
        Intal_pad(b1pb2,a1pa2->n+1);
        b1pb2->n = (a1pa2->n);
    }

    p3= karat(&a1pa2,&b1pb2);
    a1 = subtract_intal(p3,p1);
    a2 = subtract_intal(a1,p2);   //p3-p1-p2
    Intal_pow10(&p1,n1);
    Intal_pow10(&a2,m);
    a1 = add_intal(p1,a2);
    delete_intal(&p1);
    delete_intal(&a2);
    a2 = add_intal(a1,p2);
    delete_intal(&a1);
    delete_intal(&p2);
    res = a2;
    return res;
}

intal* multiply_intal(intal* a, intal* b)
{   

    int n1 = (a->n) + 1;
    int n2 = (b->n) + 1;
    int size;

    
    if(n1 > n2)
    {
        size = n1;
        Intal_pad(b,size);
    }
    else{
        size = n2;
        Intal_pad(a,size);
    }
    intal *res,*res2;
    res=karat(&a,&b);
    res2=stripzeros(res);
    

    return res2;
}

intal* pow_intal(intal* a, intal* b) {

  intal *res=NULL;
  intal *testa = create_intal();
  read_intal(testa,a->s);
  intal *one=create_intal();
  char *str = malloc(sizeof(char)*3);
  str[0]='+';
  str[1]='1';
  str[2]='\0';
  read_intal(one,str);
  printf("one->s :%s\n",one->s );
  if(b->s[1] == '0')
    return one; 

  intal *count1=create_intal();
  read_intal(count1,b->s);
  count1=subtract_intal(b,one);
  intal *count;
  count = count1;
  count = subtract_intal(b,one);
  int check=0;
 
  while((count->s[0])!='-'){
    res = multiply_intal(testa,a);
    testa=res;
    count=subtract_intal(b,one);
  }
  //TODO it's a stub function. Fill in the details and delete this comment.
  return res;
}
