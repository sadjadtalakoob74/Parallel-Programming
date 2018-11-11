/*
 ============================================================================
 Name        : test3.c
 Author      : sadjad
 Version     :
 Copyright   : Your copyright notice
 Description : Calculate Pi in MPI
 ============================================================================*/

#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

const int MAX_STRING = 100;

int main(void) {

	char greeting[MAX_STRING];

	int comm_sz = 4;
	int my_rank;

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	srand(time(NULL));
	int r = rand();

	for (int var = 0; var < 4; ++var) {

		static int number = 0;
		int average = 0;
		for (int var = 0; var < 4; ++var) {
			number = rand();
			/*	average = ((number / 100000000) / 4);
			 if (average <= 9) {
			 //for getting number between 10 to 20
			 average += 10;
			 } else if (average > 20) {
			 average -= 10;
			 }*/
		}

		if (my_rank != 0) {

			sprintf(greeting,
					"Receiving the computed average mark for student number :%d \n /*from Receiving-process %d of %d*/",
					var, my_rank, comm_sz);
			MPI_Send(greeting, strlen(greeting) + 1, MPI_CHAR, 0, 1,
			MPI_COMM_WORLD);
			MPI_Send(&number, 100, MPI_CHAR, 0, 0,
			MPI_COMM_WORLD);
		} else if (my_rank == 0) {
			printf("\n");
			printf(
					"Initializing 4 courses mark by Random number for Student %d\n /*from Sending-process %d of %d*/\n",
					var, my_rank, comm_sz);
			printf("\n");
			for (int q = 1; q < comm_sz; q++) {
				MPI_Recv(greeting, MAX_STRING, MPI_CHAR, q, 1, MPI_COMM_WORLD,
				MPI_STATUS_IGNORE);
				MPI_Recv(&number, 100, MPI_CHAR, q, 0, MPI_COMM_WORLD,
				MPI_STATUS_IGNORE);
				printf("\n");
				int result = ((number / 100000000) / 4);
				if (result <= 9) {
					//for getting number between 10 to 20
					result += 10;
				} else if (average > 20) {
					result -= 10;
				}
				printf("%s\n", greeting);
				printf(" the average of marks is %d\n", result);
				printf("***************\n");
			}
		}
	}

	MPI_Finalize();
	return 0;
}

