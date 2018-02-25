/*
rcd audit

The function \texttt{rcd_prefs_get_mid()} is not thread-safe and may be
called while another thread uses it. A NULL value may be returned which
will cause a segmentation fault in function \texttt{strcmp()}.

*/


#include <sys/types.h>
#include <stdio.h>
#include <pthread.h>
#include <err.h>


const char *
rcd_prefs_get_mid(void)
{
    static char mid[20];


    strcpy(mid, "thomas\0");

    return mid;
}

void *my_thread(void *arg)
{
	pthread_t	tid = pthread_self();


	pthread_detach(tid);

	if(rcd_prefs_get_mid() == NULL)
		fprintf(stderr, "%u: NULL\n", tid);


	pthread_exit(NULL);
}


int main(int argc, char **argv)
{
	int		i, nr_of_threads;
	pthread_t	tid;


	if(argc != 2)
		errx(-1, "usage: %s <nr. of threads>\n", argv[0]);

	nr_of_threads = atoi(argv[1]);

	for(i = 0; i < nr_of_threads; i++)
		pthread_create(&tid, NULL, my_thread, NULL);	

	return 0;
}

