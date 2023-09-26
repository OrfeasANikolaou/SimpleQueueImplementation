#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
int64_t *mkqueue(int64_t *queue_size);
bool is_queue_empty();
bool is_queue_full(int64_t const queue_size);
void enqueue(int64_t const queue_size, int64_t queue[queue_size], int64_t const x);
void dequeue(int64_t const queue_size, int64_t queue[queue_size]);
int64_t get_select(void);
int64_t get_val(void);
int64_t q_head = 0;
int64_t q_tail = 0;

int main(void){
	int64_t queue_size;
	int64_t *queue = NULL;
	int64_t select;
	int64_t x;
	queue = mkqueue(&queue_size);
	do{
		select = get_select();
		switch (select){
			case 1:
				x = get_val();
				enqueue(queue_size, &queue[0], x);	
				break;
			case 2:
				dequeue(queue_size, &queue[0]);
				break;
			case 3:
				if ( is_queue_empty() ) printf("The queue is empty\n");
				else printf("The queue is not empty\n");
				break;
			case 4:
				if ( is_queue_full(queue_size) ) printf("The queue is full\n");
				else printf("The queue is not full\n");
				break;
			case 5:
				printf ("Head: %ld\n", q_head);
				printf ("Tail: %ld\n", q_tail);
				break;
			case 6:
				if ( is_queue_empty() ) fprintf(stderr, "Cannot print an empty queue\n");
				else {
					int64_t i = q_head;
					int64_t cnt = 0;
					while (i != q_tail && cnt < queue_size) {
						printf("q[%ld] = %ld\n", i, queue[i]);
						i = (i + 1) % queue_size;
						++cnt;
					}
				}
				break;
		}
	}while (select == 6 ||
					select == 5 ||
					select == 4 ||
					select == 3 ||
					select == 2 ||
					select == 1);
	free(queue);
return EXIT_SUCCESS;
}

int64_t *mkqueue(int64_t *queue_size){
	int clear_buffer;
	do{
		printf("Enter valid queue length size (between 1 and 1000): ");
		scanf("%ld", queue_size);
	}while (*queue_size < 1 || *queue_size > 1000);
	while( (clear_buffer = getchar() != '\n' && clear_buffer != EOF) );
	return malloc(sizeof(int64_t) * *queue_size); 
}
bool is_queue_empty(){
	if ( q_tail == q_head ) return true;
	return false;
}
bool is_queue_full(int64_t const queue_size){
	if ( (q_head == 0 && q_tail == queue_size) 
			|| (q_head == q_tail+1) ) return true;
	return false;
}
void enqueue(int64_t const queue_size, int64_t queue[queue_size], int64_t const x){
	if ( is_queue_full(queue_size) ) {
		fprintf(stderr, "Cannot add object to queue (queue overflow)\n");
	}
	else {
		queue[q_tail] = x;
		printf("Element added to queue\n");
		if (q_tail == queue_size) q_tail = 0;
		else ++q_tail;
	}
}
void dequeue(int64_t const queue_size, int64_t queue[queue_size]){
	if ( is_queue_empty() ) {
		fprintf(stderr, "Cannot dequeue object to queue (queue underflow)\n");
	}
	else {
		if (q_head ==  queue_size) q_head = 0;
		else ++q_head;
	}
}
int64_t get_select(void){
	int64_t select, clear_buffer;
	puts("--------------------------------------");
	printf ("Press 1 to enqueue\n"
					"Press 2 to dequeue\n"
					"Press 3 to check if queue is empty\n"
					"Press 4 to check if queue is full\n"
					"Press 5 to print indexes\n"
					"Press 6 to print queue\n");
	puts("--------------------------------------");
	scanf("%ld", &select);
	while ( (clear_buffer = getchar()) != '\n' && clear_buffer != EOF );
	return select;
}
int64_t get_val(void){
	int64_t x;
	int64_t clear_buffer;
	printf("Enter value to add to queue: ");
	scanf("%ld", &x);
	while ( (clear_buffer = getchar()) != '\n' && clear_buffer != EOF);
	return x;
}
