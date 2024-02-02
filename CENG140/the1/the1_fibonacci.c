#include <stdio.h>

int main(){
	
	int a,b,c,d,n;
	int i;
	char oper;
	int result ;
		
	scanf(" %d %d %d %d ",&a,&b,&c,&d);
	scanf(" %c",&oper);
	scanf(" %d",&n);
	
	if(oper == 43){
		if (i <= 1){
		 	result = a;
		}
		for(i = 0;i < n-2 ; i++){
			result = a*c + b*d;
			a = b;
			b = result;
		}
			printf("%d",b);
	}
	
	if(oper == 45){
		if (i <= 1){
		 	result = a;
		}
		for(i = 0;i < n-2 ; i++){
			result = a*c - b*d;
			a = b;
			b = result;
		}
			printf("%d",b);
	}
	

	
	
	
	return 0;
}
