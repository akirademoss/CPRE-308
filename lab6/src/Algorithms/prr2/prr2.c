#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "debug.h"
#include "task.h"
#include "scheduler_algorithm.h"

#define SCHEDULER_NAME "prr2"
#define nil ((void*)0)

const struct scheduler_operations sops;

int verbose_flag = 1;

static int handle;

static struct task *head0 = nil, *head1 = nil, *head2 = nil, *head3 = nil;

/*
	prr2 is a randomized prr
*/

int init_module(void)
{
	handle = register_scheduler(SCHEDULER_NAME, &sops);
	if(handle < 0){
		eprintf("Failed registering scheduler prr2 with error %d\n", handle);
		return handle;
	}
	else{
		dprintf("Registered scheduler prr2\n");
	}
	
	srand(time(NULL));
	
	return 0;
}

void cleanup_module(void)
{
	int rv = unregister_scheduler(handle);
	if(rv < 0) eprintf("Error in unregister_scheduler: %d\n", rv);
}

struct task* 
prr2_enqueue(struct task* r, struct task* t)
{
	struct task** h;
	if(t->task_info->priority == 0)
		h = &head0;
	else if(t->task_info->priority == 1)
		h = &head1;
	else if(t->task_info->priority == 2)
		h = &head2;
	else
		h = &head3;

	if(*h == NULL){
		*h = t;
		t->next = *h;
		t->prev = *h;
	}else{
		(*h)->prev->next = t;
		t->prev = (*h)->prev;
		(*h)->prev = t;
		t->next = (*h);
	}
	return *h;
}

struct task*
prr2_dequeue(struct task* r)
{
	// select head to use
	struct task** h;
	if(r->task_info->priority == 0)
		h = &head0;
	else if(r->task_info->priority == 1)
		h = &head1;
	else if(r->task_info->priority == 2)
		h = &head2;
	else
		h = &head3;

	if(r->next == r)
		*h = NULL;
	else{
		r->prev->next = r->next;
		r->next->prev = r->prev;
		*h = r->next;
	}
	return *h;
}

struct task*
prr2_periodic_timer(struct task* r)
{
	int s = rand() % 4;
	
	if(3 == s && head3){
		head3 = head3->next;
		return head3;
	}
	if(2 == s && head2){
		head2 = head2->next;
		return head2;
	}
	if(1 == s && head1){
		head1 = head1->next;
		return head1;
	}
	if(0 == s && head0){
		head0 = head0->next;
		return head0;
	}

	if(head3){
		head3 = head3->next;
		return head3;
	}else if(head2){
		head2 = head2->next;
		return head2;
	}else if(head1){
		head1 = head1->next;
		return head1;
	}else if(head0){
		head0 = head0->next;
		return head0;
	}
	
	return nil;
}

const struct scheduler_operations sops =
{
	.task_enqueue = prr2_enqueue,
	.task_dequeue = prr2_dequeue,
	.periodic_timer = prr2_periodic_timer,
	.period = 1
};