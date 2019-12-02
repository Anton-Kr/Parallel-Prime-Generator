#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>
#include <string.h> 
#include <unistd.h> 

int main( int argc, char *argv[] )  {

	MPI_Init(NULL, NULL);
	// Find out rank, size
	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	int n = atoi(argv[1]);
	int numarr[n] ;
	int resultarr[n];
	memset( numarr, 0, n*sizeof(int) );
	memset( resultarr, 0, n*sizeof(int) );
	
	int i;
	for (i = 0; i <= n; i++){
		numarr[i] = 0;
		resultarr[i] = 0;
	} 
	

	
	for(i = 2+world_rank; i<((n+1)/2); i+=world_size){
		if(!numarr[i]){
			int j;
			for(j = i*2; j<=n; j+=i){
				numarr[j] = 1;
			}
		}
	}
	
	
	
	MPI_Reduce(&numarr, &resultarr, n, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	
	char buffer [100];
	snprintf(buffer, 100, "%d.txt",n);
	
	FILE * fp;
	fp = fopen (buffer,"w");
	if(world_rank == 0){
		for(i = 2; i<n; i++){
			if(!resultarr[i]){
				fprintf(fp, "%i ", i);
			}
		}
	}
	fprintf(fp, "\n");
	fclose(fp);
	MPI_Finalize();
}
	