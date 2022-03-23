#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "logger.h"
#include "assert.h"

struct logger *_logger;

#if defined(CFG_LOGGER_ENABLED)

#if defined (CFG_LOGGER_MSG_POOL)
#include "cbuffer.h"
char *log_strings[CFG_LOGGER_MSG_POOL_SIZE];
#else
char log_buffer[CFG_LOGGER_MSG_MAX_LEN + 1];
#endif /* CFG_LOGGER_MSG_POOL */

#if !defined(CFG_LOGGER_PRODUCTION) && defined(CFG_LOGGER_DEBUG_INTERNALS)
#warning("Logger build in none-production mode")
#define LOGGER_INTERNAL_ERR(fmt_, ...) fprintf(stdout, "logger: (error): "fmt_, ##__VA_ARGS__)
#define LOGGER_INTERNAL_DEBUG(fmt_, ...) fprintf(stdout, "logger: (debug): "fmt_, ##__VA_ARGS__)
#define LOGGER_INTERNAL_INFO(fmt_, ...) fprintf(stdout, "logger: (debug): "fmt_, ##__VA_ARGS__)
#else
#define LOGGER_INTERNAL_ERR(fmt, ...) while(0){}
#define LOGGER_INTERNAL_DEBUG(fmt, ...) while(0){}
#define LOGGER_INTERNAL_INFO(fmt, ...) while(0){}
#endif /* CFG_LOGGER_PRODUCTION */ /* CFG_LOGGER_DEBUG_INTERNALS */

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
	logger->ops = ops;

	return logger;
}

int _logger_log(struct logger *logger, const char *fmt,...)
{
	int retval = 0;
	va_list va;
	char *buf;

	struct logger *to = logger ? logger : _logger;
	if (!to) {
		LOGGER_INTERNAL_ERR("No logger provided\n");
		return -1;
	}

	va_start(va, fmt);
#ifdef CFG_LOGGER_MSG_POOL
	buf = cbuffer_get_write_pointer(to->cbuf);
#else
	buf = log_buffer;
#endif
	memset(buf, 0, CFG_LOGGER_MSG_MAX_LEN + 1);
	vsnprintf(buf, CFG_LOGGER_MSG_MAX_LEN, fmt, va);

#ifdef CFG_LOGGER_MSG_POOL
	retval = cbuffer_signal_element_written(to->cbuf);
#ifdef CFG_LOGGER_MSG_POOL_FLUSH_NOW
	logger_flush(to);
#endif /* CFG_LOGGER_MSG_POOL_FLUSH_NOW */
#else
	retval = logger_write(to, buf, CFG_LOGGER_MSG_MAX_LEN + 1);
#endif /* CFG_LOGGER_MSG_POOL */
	va_end(va);
	return retval;
}

void logger_flush(struct logger *logger)
{
	struct logger *to = logger ? logger : _logger;
	if (!to) {
		LOGGER_INTERNAL_ERR("No logger provided\n");
		return;
	}

#ifdef CFG_LOGGER_MSG_POOL
	while (1) {
		char *buf = cbuffer_get_read_pointer(to->cbuf);
		if (!buf) return;
		int retval = logger_write(to, buf, CFG_LOGGER_MSG_MAX_LEN +1);
		if (retval < 0) {
			LOGGER_INTERNAL_ERR("failed to write log string\n");
		}
		cbuffer_signal_element_read(to->cbuf);
	}
#endif
}

void logger_delete(struct logger *logger)
{
	assert(logger);
	free(logger);
}

#endif /* CFG_LOGGER_ENABLED */
