#include <stdio.h>
#include <math.h>

int main(){
	int i,j,y;
	double x,a,temp1;
	int k,n,temp;
	double temp3 = 1;
	double result = 0;
	scanf(" %lf %d %d",&x,&k,&n);
	int valueK = k;
	int valueN = n;
	
	for(i=valueN;i>=0;i--){
		temp = i;
		
		scanf(" %lf",&a);
		temp1 = a;
		for(j=0;j<k;j++){
			//temp1 = a*temp*pow(x,temp-1);
			temp1 *=  temp-j;
			
			
		}
		temp3 = 1;
		
		for(y=0;y<i-k;y++){
			temp3 *= x;
			
		}
		//printf("%lf\n",temp3); // = pow(x,i-k)
		temp1 *= temp3;
		result += temp1;		
		
	}
	printf("%.3lf",result);
	return 0;
}
