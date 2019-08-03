#include "gperftools/malloc_hook_c.h"
#include "gperftools/malloc_extension_c.h"
#include "gperftools/tcmalloc.h"

int main() {
	char *c = tc_malloc(1);
	(void)c;

	return 0;
}
