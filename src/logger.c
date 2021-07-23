#include <stdio.h>

#ifndef CFG_LOGGER_PRODUCTION
#include <stdlib.h>
#endif /* CFG_LOGGER_PRODUCTION */

#include "logger.h"
#include "assert.h"

#if defined(CFG_LOGGER_ENABLED)

#if defined (CFG_LOGGER_MSG_POOL)
#include "cbuffer.h"

char *log_strings[CFG_LOGGER_MSG_POOL_SIZE];

#endif /* CFG_LOGGER_MSG_POOL */

#if defined(CFG_LOGGER_DEBUG_INTERNALS)
#define LOGGER_INTERNAL_ERR(fmt_, ...) fprintf(stdout, "logger: (error): "fmt_, ##__VA_ARGS__)
#define LOGGER_INTERNAL_DEBUG(fmt_, ...) fprintf(stdout, "logger: (debug): "fmt_, ##__VA_ARGS__)
#define LOGGER_INTERNAL_INFO(fmt_, ...) fprintf(stdout, "logger: (debug): "fmt_, ##__VA_ARGS__)
#else
#define LOGGER_INTERNAL_ERR(fmt, ...) while(0){}
#define LOGGER_INTERNAL_DEBUG(fmt, ...) while(0){}
#define LOGGER_INTERNAL_INFO(fmt, ...) while(0){}
#endif /* CFG_LOGGER_DEBUG_INTERNALS */

struct logger *logger_new(const struct logger_ops *ops)
{
	LOGGER_INTERNAL_INFO("Creating new logger\n");
	struct logger *logger = malloc(sizeof(*logger));
#ifdef CFG_LOGGER_MSG_POOL
	logger->cbuf = cbuffer_init_cbuffer(CFG_LOGGER_MSG_POOL_SIZE);
	for (int i = 0; i < CFG_LOGGER_MSG_POOL_SIZE; i++) {
		log_strings[i] = malloc((CFG_LOGGER_MSG_MAX_LEN + 1) * sizeof(char));
		cbuffer_set_element(logger->cbuf, i, log_strings[i]);
	}
#endif /* CFG_LOGGER_MSG_POOL */

	return logger;
}

void logger_delete(struct logger *logger)
{
	assert(logger);
	free(logger);
}

#endif /* CFG_LOGGER_ENABLED */
