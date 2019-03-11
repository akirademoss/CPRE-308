/**
 * @file      main.c
 * @author    Jeramie Vens
 * @date      2015-02-11: Created
 * @date      2015-02-15: Last updated
 * @date      2015-02-16: Complete re-write
 * @brief     Emulate a print server system
 * @copyright MIT License (c) 2015, 2016
 */
 
/*
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <semaphore.h>

#include <sys/time.h>
#include <errno.h>


#include "print_job.h"
#include "printer_driver.h"
#include "debug.h"

// -- GLOBAL VARIABLES -- //
int verbose_flag = 0;
int exit_flag = 0;

// -- STATIC VARIABLES -- //
static struct printer_group * printer_group_head;

// -- FUNCTION PROTOTYPES -- //
static void parse_command_line(int argc, char * argv[]);
static void parse_rc_file(FILE* fp);

// Extra Credit portion
//*****************************************************************************************
char* logname = NULL;
FILE* logfile = NULL;
//*****************************************************************************************




/**
 * A list of print jobs that must be kept thread safe
 */
struct print_job_list
{
	// the head of the list
	struct print_job * head;
	// the number of jobs in the list
	sem_t num_jobs;
	// a lock for the list
	pthread_mutex_t lock;
	// an event for the list
};

/**
 * A printer object with associated thread
 */
struct printer
{
	// the next printer in the group
	struct printer * next;
	// the driver for this printer
	struct printer_driver driver;
	// the list of jobs this printer can pull from
	struct print_job_list * job_queue;
	// the thread id for this printer thread
	pthread_t tid;
};

/**
 * A printer group.  A group represents a collection of printers that can pull
 * from the same job queue.
 */
struct printer_group
{
	// the next group in the system
	struct printer_group * next_group;
	// the name of this group
	char * name;
	// the list of printers in this group
	struct printer * printer_queue;
	// the list of jobs for this group
	struct print_job_list job_queue;
};



void *printer_thread(void* param)
{
	struct printer * this = param;
	struct print_job * job;
	struct print_job * prev;

// INDICATE CONSUMER THREAD START
//*****************************************************************************************
	fprintf(logfile, "Consumer thread\n");
//*****************************************************************************************

	
	while(1 && exit_flag == 0) // Modify original while loop consumer exits
	{	

// CONSUMER THREAD PRINTS JOBS FROM THE QUEUE
//*****************************************************************************************
		int err;
		
		// Log while waiting to be signaled
		if(verbose_flag)
			fprintf(logfile, "Consumer waiting for signal\n");

		long numJobs = (long) &this->job_queue->num_jobs;

		// Waits to be woken up by sem_post which provides # of jobs in queue
		// then starts poping from the print queue
		sem_wait(&this->job_queue->num_jobs);
		if(this->job_queue->head != NULL){
			job = this->job_queue->head;
			prev = job->next_job;
			this->job_queue->head = prev;
			numJobs--;
			// Send print job to driver
			err = printer_print(&this->driver, job);
			if(err != 0)
				fprintf(logfile, "Consumer printed job to driver\n");
				eprintf("ATTENTION:: Print job completed: %s\n", job->job_name);
			fprintf(logfile, "Consumed: %s\n", job->job_name);
		}		
		
		err = sem_post(&this->job_queue->num_jobs);
		if(err != 0){
			eprintf("Semaphore setting failed.\n");
			exit(err);
		}
//*****************************************************************************************
	}

// INDICATE CONSUMER THREAD EXIT
//*****************************************************************************************
	fprintf(logfile, "Consumer exiting\n");
//*****************************************************************************************


	return NULL;
}


void * producer_thread(void * param)
{
	struct printer_group * g;
	struct print_job * job;
	char * line = NULL;
	size_t n = 0;
	long long job_number = 0;

// INDICATE START OF PRODUCER THREAD
//*****************************************************************************************
	fprintf(logfile, "Started producer!\n");
//*****************************************************************************************

	
	while(getline(&line, &n, stdin) > 0)
	{
		if(strncmp(line, "NEW", 3) == 0)
		{
			fprintf(logfile, "Producer read NEW!\n");
			job = calloc(1, sizeof(struct print_job));
			job->job_number = job_number++;
		}
		else if(job && strncmp(line, "FILE", 4) == 0)
		{
			fprintf(logfile, "Producer read FILE!\n");
			strtok(line, ": ");
			job->file_name = malloc(n);
			strncpy(job->file_name, strtok(NULL, "\n"), n);
		}
		else if(job && strncmp(line, "NAME", 4) == 0)
		{
			fprintf(logfile, "Producer read NAME!\n");
			strtok(line, ": ");
			job->job_name = malloc(n);
			strncpy(job->job_name, strtok(NULL, "\n"), n);
		}
		else if(job && strncmp(line, "DESCRIPTION", 11) == 0)
		{
			fprintf(logfile, "Producer read DESCRIPTION!\n");
			strtok(line, ": ");
			job->description = malloc(n);
			strncpy(job->description, strtok(NULL, "\n"), n);
		}
		else if(job && strncmp(line, "PRINTER", 7) == 0)
		{
			fprintf(logfile, "Producer read PRINTER!\n");
			strtok(line, ": ");
			job->group_name = malloc(n);	
			strncpy(job->group_name, strtok(NULL, "\n"), n);
		}
		else if(job && strncmp(line, "PRINT", 5) == 0)
		{
			fprintf(logfile, "Producer read PRINT!\n");
			if(!job->group_name)
			{
				eprintf("Trying to print without setting printer\n");
				continue;
			}
			if(!job->file_name)
			{
				eprintf("Trying to print without providing input file\n");
				continue;
			}
			for(g = printer_group_head; g; g=g->next_group)
			{
				if(strcmp(job->group_name, g->name) == 0)
				{	

// PRODUCER THREAD ADDS ITEMS TO PRINT QUEUE
//*****************************************************************************************
					int err;
					fprintf(logfile, "Producer group found, locking mutex!\n");

					pthread_mutex_lock(&g->job_queue.lock);
					fprintf(logfile, "Producer locked mutex!\n");

					// If the print job is empty, add dummy to print queue, otherwise add new print job to end of queue
					struct print_job* j = g->job_queue.head;
					if(j == NULL){
						// Empty queue
						g->job_queue.head = job;
						job->next_job = NULL;
					}else{
						while(j->next_job != NULL)
							j = j->next_job;
						j->next_job = job;
						job->next_job = NULL;
					}

					// increment the lock and wake up printer_thread
					err = sem_post(&g->job_queue.num_jobs);
					if(err != 0){
						eprintf("Failed to post semaphore.\n");
						exit(err);
					}
					fprintf(logfile, "Producer unlocked sem\n");
					pthread_mutex_unlock(&g->job_queue.lock);

					fprintf(logfile, "Signal ready for consumption\n");
				}
			}
//*****************************************************************************************


			if(job)
			{
				fprintf(logfile, "Producer looped over extra printer group name given: %s\n", job->group_name);
				continue;
			}
		}
		else if(strncmp(line, "EXIT", 4) == 0)
		{
			exit_flag = 1;

// INDICATE PRODUCER THREAD EXITING
//*****************************************************************************************
			fprintf(logfile, "Producer exiting\n");
			fprintf(logfile, "Waiting on all consumers to exit…\n");
			eprintf("ATTENTION:: Producer exiting\n");
//*****************************************************************************************
			
			return NULL;
		}
	}
	return NULL;
}


int main(int argc, char* argv[])
{
	struct printer_group * g;
	struct printer * p;

	// parse the command line arguments
	parse_command_line(argc, argv);


// LOGFILE
//*****************************************************************************************
	if(logname != NULL){
		logfile = fopen(logname, "w+");
		if(logfile != NULL){
			setbuf(logfile, NULL);
		}else{
			eprintf("Error. Failed to open logfile.\n");
			logfile = stdout;
		}
	}else{
		logfile = stdout;
	}
//*****************************************************************************************


	// open the runtime config file
	FILE* config = fopen("config.rc", "r");
	// parse the config file
	parse_rc_file(config);
	// close the config file
	fclose(config);

	//-- Create the consumer threads
	// for each printer group
	for(g = printer_group_head; g; g = g->next_group) 
	{
		sem_init(&g->job_queue.num_jobs, 0, 0);
		pthread_mutex_init(&g->job_queue.lock, NULL);
		
		// for each printer in the group
		for(p = g->printer_queue; p; p = p->next)
		{
			// spawn the printer thread
			pthread_create(&p->tid, NULL, printer_thread, (void*)p);
		}
	}
	
	
	//-- Create the prducer thread
	pthread_t producer_tid;
	pthread_create(&producer_tid, NULL, producer_thread, NULL);
	

// JOIN AND DESTROY THREADS
//*****************************************************************************************
	//-- Initialize events
	int err = pthread_join(producer_tid, NULL);
	if(err != 0){
		eprintf("pthread join error - producer.\n");
		exit(err);
	}
	
	//-- Join the consumer threads
	// for each printer group
	for(g = printer_group_head; g; g = g->next_group)
	{
		// for each printer in the group
		for(p = g->printer_queue; p; p = p->next)
		{
			// spawn the printer thread
			err = pthread_join(p->tid, NULL);
			err = 0;
			if(err != 0){
				eprintf("pthread join error - consumer.\n");
				exit(err);
			}
		}
	}
	
	
	// Tear down
	// for each printer group
	for(g = printer_group_head; g; g = g->next_group)
	{
		//destroy
		pthread_mutex_destroy(&g->job_queue.lock);
		sem_destroy(&g->job_queue.num_jobs);
	}
		
	fflush(logfile);
	fclose(logfile);
//*****************************************************************************************


	return 0;
}

/**
 * Parse the command line arguments and set the appropriate flags and variables
 * 
 * Recognized arguments:
 *   - `-v`: Turn on Verbose mode
 *   - '-l':  Log to a given file provided as an argument to l
 *   - '-t':  Set the Consumer thread timeout in ms. Larger values can reduce CPU load (default: 100).
 *   - `-?`: Print help information
 */
static void parse_command_line(int argc, char * argv[])
{
	int c;
	while((c = getopt(argc, argv, "l:t:v?")) != -1)
	{
		switch(c)
		{


// LOGGING
//*****************************************************************************************
			case 'l': 
				logname = optarg;
				break;
//*****************************************************************************************


			case 'v': // turn on verbose mode
				verbose_flag = 1;
				break;
			case '?': // print help information
				fprintf(stdout, "Usage: %s [options]\n", argv[0]);
				exit(0);
				break;
		}
	}
}

static void parse_rc_file(FILE* fp)
{
	char * line = NULL;
	char * ptr;
	size_t n = 0;
	struct printer_group * group = NULL;
	struct printer_group * g;
	struct printer * printer = NULL;
	struct printer * p;

	// get each line of text from the config file
	while(getline(&line, &n, fp) > 0)
	{
		// if the line is a comment
		if(line[0] == '#')
				continue;

		// If the line is defining a new printer group
		if(strncmp(line, "PRINTER_GROUP", 13) == 0)
		{
			strtok(line, " ");
			ptr = strtok(NULL, "\n");
			group = calloc(1, sizeof(struct printer_group));
			group->name = malloc(strlen(ptr)+1);
			strcpy(group->name, ptr);

			if(printer_group_head)
			{
				for(g = printer_group_head; g->next_group; g=g->next_group);
				g->next_group = group;
			}
			else
			{
				printer_group_head = group;
			}
		}
		// If the line is defining a new printer
		else if(strncmp(line, "PRINTER", 7) == 0)
		{
			strtok(line, " ");
			ptr = strtok(NULL, "\n");
			printer = calloc(1, sizeof(struct printer));
			printer_install(&printer->driver, ptr);
			printer->job_queue =  &(group->job_queue);
			if(group->printer_queue)
			{
				for(p = group->printer_queue; p->next; p = p->next);
				p->next = printer;
			}
			else
			{
					group->printer_queue = printer;

			}
		}
	}

	// print out the printer groups
	dprintf("\n--- Printers ---\n"); 
	for(g = printer_group_head; g; g = g->next_group)
	{
		dprintf("Printer Group %s\n", g->name);
		for(p = g->printer_queue; p; p = p->next)
		{
			dprintf("\tPrinter %s\n", p->driver.name);
		}
	}
	dprintf("----------------\n\n");

}
