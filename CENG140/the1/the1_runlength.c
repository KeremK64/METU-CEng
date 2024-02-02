#include <stdio.h>

int main(){
	
	char a;
	char b = 'a';
	int count = 1;
	
	scanf("%c",&a);
	while(a != 10 && b != 10){
		scanf("%c",&b);
		if(a == b){
			count ++;
		}
		else{
			printf("%d%c",count,a);
			
			count = 1;
		}
		a = b;
		
	}
	
	
	return 0;
}
