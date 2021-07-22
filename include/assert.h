#ifndef _LOGGER_ASSERT_H_
#define _LOGGER_ASSERT_H_

#ifdef CFG_LOGGER_PRODUCTION
#define assert(x) { \
	if (!(x)) { \
		while (1) {}; \
	} }
#else 
#define assert(x) { \
	if (!(x)) { \
		printf("logger: (error): (%s:%s:%d): assert triggerd!\n",\
			__FILE__,__FUNCTION__, __LINE__);\
		exit(-1); \
	} }

#endif

#endif /* _LOGGER_ASSERT_H_ */
