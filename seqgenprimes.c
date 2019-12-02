#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main( int argc, char *argv[] )  {
	printf(argv[1]);
	int n = atoi(argv[1]);
	int* numarr = malloc(sizeof(int)*n);
	int i;
	for (i = 0; i <= n; i++){
		numarr[i] = 0;
	} 
	
	for(i = 2; i<((n+1)/2); i++){
		if(!numarr[i]){
			int j;
			for(j = i*2; j<=n; j+=i){
				numarr[j] = 1;
			}
		}
	}
	
	char buffer [100];
	snprintf(buffer, 100, "%d.txt",n);
	
	FILE * fp;
	fp = fopen (buffer,"w");
	
	for(i = 2; i<n; i++){
		if(!numarr[i]){
			fprintf(fp, "%i ", i);
		}
	}
	
	fprintf(fp, "\n");
	fclose(fp);
}
	