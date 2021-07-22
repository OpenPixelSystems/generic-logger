logger = executable('logger_test','simple_test.c', logger_srcs, cbuff_srcs,
			include_directories : [logger_includes, cbuff_includes],
			c_args : c_args,
			link_args : link_args)
test('Main test', logger)
