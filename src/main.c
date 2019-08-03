#include <assert.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

#include "gperftools/malloc_hook_c.h"
#include "gperftools/malloc_extension_c.h"
#include "gperftools/tcmalloc.h"


static pthread_t timeseries_thread;

static void *timeseries_main(__attribute__((unused)) void *arg)
{

	size_t current_allocated_bytes, heap_size, pageheap_free_bytes,
	       pageheap_unmapped_bytes, central_cache_free_bytes,
	       transfer_cache_free_bytes, aggressive_memory_decommit;

	fprintf(stdout, "time,current_allocated_bytes,heap_size,pageheap_free_bytes,"
			"pageheap_unmapped_bytes,central_cache_free_bytes,"
			"transfer_cache_free_bytes,aggressive_memory_decommit\n");


	while (1) {
		MallocExtension_GetNumericProperty("generic.current_allocated_bytes", &current_allocated_bytes);
		MallocExtension_GetNumericProperty("generic.heap_size", &heap_size);
		MallocExtension_GetNumericProperty("tcmalloc.pageheap_free_bytes", &pageheap_free_bytes);
		MallocExtension_GetNumericProperty("tcmalloc.pageheap_unmapped_bytes", &pageheap_unmapped_bytes);
		MallocExtension_GetNumericProperty("tcmalloc.central_cache_free_bytes", &central_cache_free_bytes);
		MallocExtension_GetNumericProperty("tcmalloc.transfer_cache_free_bytes", &transfer_cache_free_bytes);
		MallocExtension_GetNumericProperty("tcmalloc.aggressive_memory_decommit", &aggressive_memory_decommit);

		fprintf(stdout, "%lu,%zu,%zu,%zu,%zu,%zu,%zu,%zu\n",
				(unsigned long)time(NULL),
				current_allocated_bytes,
				heap_size,
				pageheap_free_bytes,
				pageheap_unmapped_bytes,
				central_cache_free_bytes,
				transfer_cache_free_bytes,
				aggressive_memory_decommit);

		sleep(1);
	}
	return NULL;
}

int main()
{
	assert(pthread_create(&timeseries_thread, NULL, timeseries_main, NULL) == 0);

	while (1) {
		sleep(1);
		char *c = tc_malloc(1);
		(void)c;

	}

	return 0;
}
