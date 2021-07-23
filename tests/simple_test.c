#include "logger.h"

int test_logger_write(void *priv, char *data, uint32_t len)
{
	fprintf(stdout, data);
	return 0;
}

const struct logger_ops test_logger_ops = {
	.init = NULL,
	.write = test_logger_write,
};

int main()
{
	struct logger *logger = logger_new(&test_logger_ops);

	logger_info(logger, "test 123\n");
	logger_debug(logger, "test 345\n");
	logger_warn(logger, "test 567\n");
	logger_error(logger, "test 789\n");

	logger_delete(logger);
	return 0;
}
