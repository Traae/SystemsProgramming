#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

struct Stuff {
	int id;
	int somethingElse;
	char buf[50];
};

void *doStuff(void * arg) {
	struct Stuff *myStuff = (struct Stuff*) arg;
//	if (id == 0)
//			sleep(10);
	printf("I am thread %d\n", myStuff->id);
	printf(myStuff->buf);
	return 0;
}

int main() {
	printf("Hello world\n");
	pthread_t thread_id[10];
	for (int i = 0; i < 10; i++) {
		struct Stuff *myStuff = malloc(sizeof(struct Stuff));
		myStuff->id = i;
		myStuff->somethingElse = i*37;
		sprintf(myStuff->buf, "This is thread %d\n", i);
		pthread_create(&thread_id[i], NULL, (void *)doStuff, (void *) myStuff);
	}
	for (int i = 0; i < 10; i++) {
		pthread_join(thread_id[i], NULL);
	}
//	sleep(10);
	return 0;
}