#include "logger.h"

int main()
{
	struct logger *logger = logger_new(NULL);
	logger_delete(logger);
}
