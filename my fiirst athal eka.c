#include<stdio.h>

int main(void)
{
	int  n,count, L,multi,x , z , y ,t;
	
	printf("enter your number:");
	scanf("%d",&n);
	
	L = n;
	z = 0;
	multi = 1;
	 
	  
	while(n > 0)
	{
		n = n / 10;
		count++;
	}
	n = L;//after the while loop n = 0 zero , therefore im saying n = l , so again n get the input value
	z = count;
	y = count;
	t = count;
	
	printf("\n Number of Digits in a Given Number = %d \n", count);
	
	while( y >= 1) 
	 {
	 	t = t - 1;
	 	x = t;
	 
        while (x > 0 )
	    {
		   multi = 10*multi;
		   x--;		
	    }
	    
	    z = n / multi;
	    n = n % multi;
	    
	    printf ("%d\t",z);
	    
	    multi = 1;
	    
	  y = y - 1;	
    }
  return 0;
}
