#include <stdio.h>

  
int main () {
        char str1[11];
	int i;
	
	int x = scanf("%d %s", &i, str1);

	while(x != EOF){
	

       if(i == 0){
		printf("%s\n",str1);


        }
       else {
               printf("%c\n",str1[i]);
		

       }

	x = scanf("%d %s", &i, str1);

    }

	return 0;


}
