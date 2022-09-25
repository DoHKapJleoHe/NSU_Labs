#include<stdio.h>
#include<math.h>
#include<stdbool.h>
#include<mpi.h>
//#include<pthread.h>

#define TASKS_IN_LIST 1000
#define L 1500
#define REQUEST_TAG 1
#define ANSWER_TAG 2
#define SEND_TAG 3
#define EXIT_TAG -1

pthread_mutex_t mutex;

int numberOfLists = 3; // number of globaliterations
int* taskList;

int procNum,
	procRank;

double globalResult = 0;s
int tasksLeft = 0;
int curListLength;

void makeWeightOfTasks(int* taskList, int iteration, int procnum, int procrank) // takes task from taskList by index
{
	for (int i = 0; i < TASKS_IN_LIST; i++)
	{
		taskList[i] = abs(50 - i % 100) * abs(procrank - iteration % procnum) * L;
	}

	pthread_mutex_lock(&mutex);
	tasksLeft = TASKS_IN_LIST;
	pthread_mutex_unlock(&mutex);
}

/*  pthread_mutex_lock(&mutex);
	pthread_mutex_unlock(&mutex); */

void balance(double* time)
{
	double minTime = 10000;
	double maxTime = -1;

	for (int i = 0; i < procNum; i++)
	{
		if (time[i] < minTime)
			minTime = time[i];
		if (time[i] > maxTime)
			maxTime = time[i];
	}

	printf("Imbalance: %lf seconds, %lf%", maxTime - minTime, 100 * ((maxTime - minTime)/maxTime));
}

void* worker(void* me)
{
	bool iterationFinished = false;
	double res = 0;
	int taskWeight = 0;
	int taskNum = 0;
	int tasksDone = 0;
	int exit_msg = -1;
	double start,
		   end,
		   time;
	int answer;

	int* tasksDoneByAllProcesses = (int*)malloc(procNum * sizeof(int));
	int* timeOfAllProcesses = (int*)malloc(procNum * sizeof(int));
	double* globalResults = (double*)malloc(procNum * sizeof(double));

	for (int i = 0; i < numberOfLists; i++)
	{
		iterationFinished = false;
		res = 0;
		taskWeight = 0;
		taskNum = 0;
		curListLength = TASKS_IN_LIST;
		start = 0;
		end = 0; 
		time = 0;
		answer = 0;

		makeWeightOfTasks(taskList, i, procNum, procRank);

		start = MPI_Wtime();
		while (iterationFinished != true)
		{
			pthread_mutex_lock(&mutex);
			if (tasksLeft > 0)
			{
				taskWeight = taskList[taskNum];
				tasksLeft--;
				pthread_mutex_unlock(&mutex);

				for (int j = 0; j < taskWeight; j++)
				{
					res += sin(j);
				}

				taskNum++;
				tasksDone++;
			}
			else
			{
				pthread_mutex_unlock(&mutex);

				for (int k = 0; k < procNum; k++)
				{
					if (k != procRank)
					{
						MPI_Send(&procRank, 1, MPI_INT, k, REQUEST_TAG, MPI_COMM_WORLD);
						MPI_Recv(&answer, 1, MPI_INT, k, ANSWER_TAG, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);

						if (answer > 0) // answer is the amount of extra tasks to do from anothre process
						{
							pthread_mutex_lock(&mutex);
							MPI_Recv(taskList, answer, MPI_INT, k, SEND_TAG, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);

							tasksLeft = answer;
							curListLength = answer;
							pthread_mutex_unlock(&mutex);
							taskNum = 0;

							break;
						}
					}
				}

				pthread_mutex_lock(&mutex);
				if (tasksLeft == 0)
					iterationFinished = true;
				pthread_mutex_unlock(&mutex);
			}
		}
		end = MPI_Wtime();
		time = end - start;


		MPI_Gather(&tasksDone, 1, MPI_INT, tasksDoneByAllProcesses, 1, MPI_INT, 0, MPI_COMM_WORLD);
		MPI_Gather(&res, 1, MPI_DOUBLE, globalResults, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
		MPI_Gather(&time, 1, MPI_DOUBLE, timeOfAllProcesses, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

		if (procRank == 0)
		{
			printf("Iteration %d: \n", i);
			for (int x = 0; x < procNum; x++)
			{
				printf("Process %d: did %d tasks in %lf seconds; global result = %lf\n", x, tasksDoneByAllProcesses[x], timeOfAllProcesses[x], globalResults[x]);
			}

			balance(timeOfAllProcesses);
		}

		MPI_Barrier(MPI_COMM_WORLD);
	}

	MPI_Send(&exit_msg, 1, MPI_INT, procRank, EXIT_TAG, MPI_COMM_WORLD);
	pthread_exit(0);
}

void* receiver(void* me)
{
	int messg;
	int sendTasksNumber = 0;
	int* bufToSendTasks;

	while (true)
	{
		MPI_Recv(&messg, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
		
		if (messg < 0)
		{
			break;
		}
		else
		{
			pthread_mutex_lock(&mutex);
			if (tasksLeft > TASKS_IN_LIST * 0.2)
			{
				sendTasksNumber = tasksLeft * 0.2;
				pthread_mutex_unlock(&mutex);
				MPI_Send(&sendTasksNumber, 1, MPI_INT, messg, ANSWER_TAG, MPI_COMM_WORLD);

				bufToSendTasks = (int*)malloc(sendTasksNumber * sizeof(int));

				pthread_mutex_lock(&mutex);
				for (int i = 0; i < sendTasksNumber; i++)
				{
					bufToSendTasks[i] = taskList[curListLength - sendTasksNumber + i];
				}
				pthread_mutex_unlock(&mutex);
				MPI_Send(bufToSendTasks, sendTasksNumber, MPI_INT, messg, SEND_TAG, MPI_COMM_WORLD);

				//MPI_Send(&taskList[curListLength - sendTasksNumber], sendTasksNumber, MPI_INT, messg, SEND_TAG, MPI_COMM_WORLD);

				free(bufToSendTasks);
			}
			// mb i need one more scenario
			else
			{
				MPI_Send(0, 1, MPI_INT, messg, ANSWER_TAG, MPI_COMM_WORLD);
			}
		}
	}

	pthread_exit(0);
}

int main(int argc, char* argv[])
{
	double startProg = MPI_Wtime();

	int provided;
	MPI_Init_thread(&argc, &argv, MPI_THREAD_MULTIPLE, &provided); 

	if (provided != MPI_THREAD_MULTIPLE)
	{
		printf("Couldn't init thread!");
		MPI_Finalize();

		return -1;
	}

	MPI_Comm_size(MPI_COMM_WORLD, procNum);
	MPI_Comm_rank(MPI_COMM_WORLD, procRank);

	taskList = (int*)malloc(TASKS_IN_LIST * sizeof(int));

	pthread_mutex_init(&mutex, NULL); // initialising mutex

	pthread_attr_t attrs;
	if (pthread_attrs_init(&attrs) != 0) // initializing attributes
	{
		printf("Couldn't initialize attributes!");
		MPI_Finalize();

		return -1;
	}

	if (0 != pthread_attr_setdetachstate(&attrs, PTHREAD_CREATE_JOINABLE)) // setting attribute "joinable"
	{
		printf("Error in setting attributes");
		abort();
	}

	pthread_t threads[2];

	//creating 2 threads...
	if (pthread_create(&threads[0], &attrs, receiver, NULL) != 0)
	{
		printf("Couldn't create thread!");
		MPI_Finalize();

		return -1;
	}

	if (pthread_create(&threads[1], &attrs, worker, NULL) != 0)
	{
		printf("Couldn't create thread!");
		MPI_Finalize();

		return -1;
	}

	for (int i = 0; i < 2; i++)
	{
		if (pthread_join(threads[i], NULL) != 0)
		{
			printf("Couldn't join thread");
			MPI_Finalize();

			return -1;
		}
	}

	pthread_attr_destroy(&attrs);
	pthread_mutex_destroy(&mutex);
double endProg = MPI_Wtime();
if (rank == 0)
{
printf("Time: %lf\n", end - start); 
} 	

	MPI_Finalize();

	return 0;
}
