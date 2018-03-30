#ifndef STDC_UTIL_STRING_STRING
#define STDC_UTIL_STRING_STRING

#include "stdc/lib.h"

typedef struct String String;

Ptr new_String();

struct String {

	// === FIELDS ===
	long _size;
	char* _cstr;

	// === METHODS ===
	void		(*set)		(String*, CStr);
	String*		(*copy)		(String*);
	bool		(*equals)	(String*, String*);
	
	// Getters
	long		(*size)		(String*);
	CStr		(*cstr)		(String*);
};

#endif
