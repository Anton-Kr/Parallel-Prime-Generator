#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int main( int argc, char *argv[] )  {

        MPI_Init(NULL, NULL);
        // Find out rank, size
        int world_rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
        int world_size;
        MPI_Comm_size(MPI_COMM_WORLD, &world_size);
        printf("World rank is: %i\n", world_rank);
        int n = atoi(argv[1]);
        int* numarr;
        int* resultarr;
        numarr = (int *)calloc(n, sizeof(int));
        resultarr = (int *)calloc(n, sizeof(int));
        if(numarr == NULL || resultarr == NULL){
                printf("Malloc fail");
        }
        int i;


        for(i = 2+world_rank; i<((n+1)/2); i+=world_size){
                if(!numarr[i]){
                        int j;
                        for(j = i*2; j<=n; j+=i){
                                numarr[j] = 1;
                        }
                }
        }



        MPI_Reduce(&numarr, &resultarr, n, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

        printf("World rank is NOW: %i\n", world_rank);

        if(world_rank == 0){
                for(i = 0; i<n; i++){
                        printf("%i ", i);
                }
        }
        printf("\n");
}