#include <sanitizer/dfsan_interface.h>
#include <assert.h>

int main(void) {

  int a = 5;
  dfsan_label a_label = dfsan_create_label("a", 0);
  dfsan_set_label(a_label, &a, sizeof(a));
  a = 6;
  dfsan_label check = dfsan_read_label(&a, sizeof(a));
  assert(dfsan_has_label(check, a_label));
  return 0;
}
