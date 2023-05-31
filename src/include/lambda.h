//
//  lambda.h
//  RSiCSv2
//
//  Created by Ruben Ticehurst-James on 01/05/2023.
//

#ifndef lambda_h
#define lambda_h

#include <stdlib.h>

#define lambda(ret_val, name, ...)                                   \
	struct name create_##name(void * context,                    \
				  __##name##_lambda_f_p function) {  \
		struct name ret = { context, function };             \
		return ret;                                          \
	}                                                            \
	struct name * alloc_##name(void * context,                   \
				   __##name##_lambda_f_p function) { \
		struct name * ret = malloc(sizeof(struct name));     \
		struct name _ret = { context, function };            \
		*ret = _ret;                                         \
		return ret;                                          \
	}                                                            \
	void delete_##name(struct name * lambda) {                   \
		free(lambda);                                        \
	}

#define lambda_defs(ret_val, name, ...)                                \
	typedef ret_val (*__##name##_lambda_f_p)(void *, __VA_ARGS__); \
	struct name {                                                  \
		void * context;                                        \
		__##name##_lambda_f_p function;                        \
	};                                                             \
	struct name create_##name(void * context,                      \
				  __##name##_lambda_f_p function);     \
	struct name * alloc_##name(void * context,                     \
				   __##name##_lambda_f_p function);    \
	void delete_##name(struct name *);

#endif /* lambda_h */
