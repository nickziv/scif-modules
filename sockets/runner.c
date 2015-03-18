#include "gemtc_api.h"

#define QUE_SZ  10
#define WORKERS  2

int main(int argc, char *argv[])
{
	gemtc_setup(QUE_SZ, WORKERS);
	gemtc_cleanup();

	return(0);
}
