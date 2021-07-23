#ifndef _OPS_LOGGER_H_
#define _OPS_LOGGER_H_

#include <stddef.h>
#include <stdint.h>

/******************************************************************************/
//!< Completly disable the logger
#define CFG_LOGGER_ENABLED 1

//!< Enable compile time optimizations
// This configuration option will disable DEBUG and TRACE log levels at
// compile time
#define CFG_LOGGER_OPTIMIZE_SIZE 0

//!< Enabled logging for the logger
#define CFG_LOGGER_DEBUG_INTERNALS 1

//!< The number of message that can be stored in the internal CBUFFER
#define CFG_LOGGER_MSG_POOL
#define CFG_LOGGER_MSG_POOL_SIZE 25
#define CFG_LOGGER_MSG_MAX_LEN 256

/******************************************************************************/

#if defined(CFG_LOGGER_ENABLED)

#if defined (CFG_LOGGER_MSG_POOL)
struct cbuffer_t;
#endif

typedef int (*init_fn)(void *priv);
typedef int (*write_fn)(void *priv, uint8_t *data, uint32_t len);

struct logger_ops {
	init_fn init;
	write_fn write;
};

struct logger {
#if defined(CFG_LOGGER_MSG_POOL)
	struct cbuffer_t *cbuf;
#endif

	struct logger_ops *ops;
};

struct logger *logger_new(const struct logger_ops *ops);
void logger_delete(struct logger *logger);

#endif /* CFG_LOGGER_ENABLED */

#endif /* _OPS_LOGGER_H_ */
