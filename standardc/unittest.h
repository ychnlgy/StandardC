#define ASSERT(expr) \
    expect(expr, #expr, __LINE__);

typedef const char* CStr;

void expect(int boolean, CStr expr, int line);


void setup();
int main() {
    
}
