#ifndef _OPS_LOGGER_H_
#define _OPS_LOGGER_H_

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#include "assert.h"

/******************************************************************************/
//!< Completly disable the logger
#define CFG_LOGGER_ENABLED

//!< Enable compile time optimizations
// This configuration option will disable DEBUG and TRACE log levels at
// compile time
#define CFG_LOGGER_OPTIMIZE_SIZE

//!< Enabled logging for the logger
#define CFG_LOGGER_DEBUG_INTERNALS

//!< The number of message that can be stored in the internal CBUFFER
//#define CFG_LOGGER_MSG_POOL
//#define CFG_LOGGER_MSG_POOL_SIZE 25
#define CFG_LOGGER_MSG_MAX_LEN 512
//
//#define CFG_LOGGER_MSG_POOL_FLUSH_NOW

#define CFG_LOGGER_PRODUCTION

/******************************************************************************/

#if defined(CFG_LOGGER_ENABLED)

extern struct logger *_logger;

#if defined (CFG_LOGGER_MSG_POOL)
struct cbuffer_t;
#endif

struct logger_ops {
	int (*init)(void *priv);
	int (*write)(void *priv, char *data, uint32_t len);
};

struct logger {
#if defined(CFG_LOGGER_MSG_POOL)
	struct cbuffer_t *cbuf;
#endif

	const struct logger_ops *ops;
};

struct logger *logger_new(const struct logger_ops *ops);

int _logger_log(struct logger *logger, const char *fmt,...);

#define logger_info(lgr_, fmt_, ...)  _logger_log(lgr_, "(INFO) : "__FILE__": "fmt_, ##__VA_ARGS__)
#define logger_debug(lgr_, fmt_, ...) _logger_log(lgr_, "(DEBUG): "__FILE__": "fmt_, ##__VA_ARGS__)
#define logger_warn(lgr_, fmt_, ...)  _logger_log(lgr_, "(WARN) : "__FILE__": "fmt_, ##__VA_ARGS__)
#define logger_error(lgr_, fmt_, ...) _logger_log(lgr_, "(ERROR): "__FILE__": "fmt_, ##__VA_ARGS__)
#define logger_raw_print(lgr_, fmt_, ...) _logger_log(lgr_, fmt_, ##__VA_ARGS__)

#define log_info(fmt_, ...)  _logger_log(NULL, "(INFO) : "__FILE__": "fmt_, ##__VA_ARGS__)
#define log_debug(fmt_, ...) _logger_log(NULL, "(DEBUG): "__FILE__": "fmt_, ##__VA_ARGS__)
#define log_warn(fmt_, ...)  _logger_log(NULL, "(WARN) : "__FILE__": "fmt_, ##__VA_ARGS__)
#define log_error(fmt_, ...) _logger_log(NULL, "(ERROR): "__FILE__": "fmt_, ##__VA_ARGS__)
#define log_raw_print(fmt_, ...) _logger_log(NULL, fmt_, ##__VA_ARGS__)

static inline int logger_write(struct logger *logger, char *data, uint32_t len)
{
	assert(logger);
	assert(logger->ops);
	assert(logger->ops->write);

	return logger->ops->write((void*)logger, data, len);
}

static inline void logger_set_default_logger(struct logger *logger)
{
	_logger = logger;
}

void logger_flush(struct logger *logger);

void logger_delete(struct logger *logger);

#endif /* CFG_LOGGER_ENABLED */

#endif /* _OPS_LOGGER_H_ */
