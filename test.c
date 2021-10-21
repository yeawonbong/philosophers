# include "philo.h"

int fun(int *restrict a, int *restrict b)
{
	printf("a = %d, b = %d\n", *a, *b);
	return(0);
}

int main ()
{
	// char c = 'a';
	// char *restrict ptr1 = &c;
	// char *ptr2 = &c;

	// (*ptr2)++;
	// printf("string is : %c\n", *ptr2);
	// printf("adrress.. \nptr1: %p\nptr2: %p\n", ptr1, ptr2);

	int ia=1, ib=2;
	int *a=&ia;
	int *b=&ib;

// printf("a=%d\n", *a);
	fun(a,b);
	return(0);
}