#include <stdio.h>
#include "logger.h"

#if defined(CFG_LOGGER_ENABLED)

#if defined (CFG_LOGGER_MSG_POOL)
#include "cbuffer.h"
#endif

struct logger *logger_new(const struct logger_ops *ops)
{
	LOGGER_INFO("Creating new logger\n");
}

void logger_delete(struct logger *logger)
{
	/* assert(logger); */
	free(logger);
}

#endif /* CFG_LOGGER_ENABLED */
