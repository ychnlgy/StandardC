#ifndef STDC_UTIL_LIST_LIST
#define STDC_UTIL_LIST_LIST

#include "stdc/lib.h"

typedef struct List List;

Ptr new_List();

struct List {

	// === FIELDS ===
	long _size;
	long _capacity;
	Ptr* _data;
	
	// === METHODS ===

	long	(*size)		(List*);
	void	(*push)		(List*, Ptr);
	Ptr		(*pop)		(List*);

	/* NOTE: Accessors take long position rather than
	 * the unsigned size_t because there may be times
	 * where accidents happen and wierd things happen.
	 */

	// Fast but unsafe accessors (does not check range)
	Ptr		(*getitem)	(List*, long);
	void	(*setitem)	(List*, long, Ptr);

	// Slow but safe accessors (checks for range)
	Ptr		(*at)		(List*, long);
	bool	(*set)		(List*, long, Ptr);

	// Iteration
	// TODO: implement them!
	// iter
	// reverse
	// etc.
//	List*	(*map)		(List*, MapFunc);
//	List*	(*filter)	(List*, FilterFunc);
//	List*	(*reduce)	(List*, ReduceFunc);
};

#endif
