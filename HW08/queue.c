#include "queue.h"

/* creates a new queue with a given size */
queue_t* create_queue(int capacity) {
	queue_t * queue = malloc(sizeof(queue_t));

	if(queue == NULL){
		fprintf(stderr, "Memmory error!\n");
		exit(100);
	}

	queue->capacity_max = capacity;
	queue->capacity_current = 0;

	queue->data = (void**)malloc(capacity*sizeof(void*));

	if(queue->data == NULL){
		fprintf(stderr, "Memmory error!\n");
		exit(100);
	}

	for(int i = 0; i < capacity; i++) {
		queue->data[i] = NULL;
	}

	queue->head_index = 0;
	queue->tail_index = 0;

	return queue;
}
/* deletes the queue and all allocated memory */
void delete_queue(queue_t *queue) {
	free(queue->data);
	free(queue);
}

/* 
 * inserts a reference to the element into the queue
 * returns: true on success; false otherwise
 */
bool push_to_queue(queue_t *queue, void *data) {
	if(queue->capacity_current >= queue->capacity_max) {

		void ** tmp = (void**)malloc(queue->capacity_max*2*sizeof(void*));
		
		for(int i = 0; i < queue->capacity_current; i++) {
			tmp[i] = queue->data[ (queue->head_index + i)%queue->capacity_max ];
		}

		free(queue->data);
		
		queue->data = tmp;
		queue->capacity_max = 2*queue->capacity_max;
		queue->head_index = 0;
		queue->tail_index = queue->capacity_current - 1;
	}

	int capacity = queue->capacity_max;
	int current = queue->capacity_current;
	int head = queue->head_index;

	queue->tail_index = (head + current)%capacity;

	queue->data[ queue->tail_index ] = data;

	queue->capacity_current += 1;
	return true;
}

/* 
 * gets the first element from the queue and removes it from the queue
 * returns: the first element on success; NULL otherwise
 */
void* pop_from_queue(queue_t *queue) {

	if(queue->capacity_current < (queue->capacity_max / 3)) {


		void ** tmp = (void**)malloc((queue->capacity_max / 3)*sizeof(void*));
		
		for(int i = 0; i < queue->capacity_current; i++) {
			tmp[i] = queue->data[ (queue->head_index + i)%queue->capacity_max ];
		}

		free(queue->data);
		
		queue->data = tmp;
		queue->head_index = 0;
		queue->capacity_max = queue->capacity_max / 3;

		if(queue->capacity_current != 0) {
			queue->tail_index = queue->capacity_current - 1;
		}

	}

	if(queue->capacity_current == 0) {
		return NULL;
	}

	int start_index = queue->head_index;

	queue->head_index = (start_index + 1)%queue->capacity_max;

	queue->capacity_current -= 1;

	void* p = queue->data[start_index]; 
	return p;
}

/* 
 * gets idx-th element from the queue 
 * returns: the idx-th element on success; NULL otherwise
 */
void* get_from_queue(queue_t *queue, int idx) {
	if(idx >= queue->capacity_current || idx < 0 )
		return NULL;
	else {
		void * p;
		int head = queue->head_index;
		int capacity = queue->capacity_max;

		p = queue->data[((idx + head)%capacity)];

		return p;
	}
}

/* gets number of stored elements */
int get_queue_size(queue_t *q) {
	return q->capacity_current;
}