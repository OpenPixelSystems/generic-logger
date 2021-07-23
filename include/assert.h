#ifndef _LOGGER_ASSERT_H_
#define _LOGGER_ASSERT_H_

#define assert(x) { \
	if (!(x)) { \
		while (1) {}; \
	} }

#endif /* _LOGGER_ASSERT_H_ */
