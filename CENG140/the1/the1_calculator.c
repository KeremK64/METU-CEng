#include <stdio.h>

int main(){
	
	double num1,num2;
	char operator1;
	
	scanf(" %lf", &num1);
	scanf(" %c", &operator1);
	scanf(" %lf", &num2);
	
	
	if(operator1 == 43){ //Sum
		if( num1 > 2147483647 - num2  ){
			printf("Overflow.\n");
		}
		else{
			printf("%.3lf\n",num1+num2);
		}
	}
	
	if(operator1 == 45){ //Subtract
		if( (num1 - num2) > 2147483647  ){
			printf("Overflow.\n");
		}
		else{			
			printf("%.3lf\n",num1-num2);
		}
	}
	
	if(operator1 == 42){ //Multiply
		if( num1 > 2147483647 / num2  ){
			printf("Overflow.\n");
		}
		else{
			printf("%.3lf\n",num1*num2);
		}
	}
	
	if(operator1 == 47){ //Division
		if( (num1 / num2) > 2147483647 ){
			printf("Overflow.\n");
		}	
		else{
			printf("%.3lf\n",(num1/num2));
		}
	}
	
	
	return 0;
}
