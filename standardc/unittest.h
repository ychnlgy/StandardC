#ifndef STANDARD_UNITTEST
#define STANDARD_UNITTEST

#ifndef SYSTEM_EXIT
#define SYSTEM_EXIT 1
#endif

// === INTERFACE ===

#define ASSERT(expr) \
    _expect(_testCase, expr, #expr, __LINE__);

#define SETUP \
    void _SETUP()

#define TEARDOWN \
    void _TEARDOWN()

#define RUN \
    int main() { \
        _TestSuite* _testSuite = _initTestSuite(__FILE__, SYSTEM_EXIT);

#define STOP \
       return  _free_testSuite(_testSuite); \
    }

#define CASE(casename) \
    { \
        _SETUP(); \
        _TestCase* _testCase = _initTestCase(_testSuite, casename);

#define END \
        _free_testCase(_testCase); \
        _TEARDOWN(); \
    }

// === PRIVATE ===

typedef const char* CStr;
typedef struct _TestSuite _TestSuite;
typedef struct _TestCase _TestCase;

_TestSuite* _initTestSuite(CStr, int);
int _free_testSuite(_TestSuite*);

_TestCase* _initTestCase(_TestSuite*, CStr);
void _free_testCase(_TestCase*);

void _expect(_TestCase*, int, CStr, int);

#endif
