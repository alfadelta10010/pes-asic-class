#include <stdio.h>
#include <math.h>

int main(){
	long long int max = (long long int) (pow(2,5) -1);
	long long int min = (long long int) (pow(2,5) *(-1));
	printf("lowest number represented by 64-bit integer is %lld\n",min);
	printf("highest number represented by 64-bit integer is %lld\n",max);
	return 0;
}

