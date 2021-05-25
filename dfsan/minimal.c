#include <sanitizer/dfsan_interface.h>
#include <assert.h>

int main(void) {

  int a[128];
  dfsan_label a_label = dfsan_create_label("a", 0);
  dfsan_set_label(a_label, a, sizeof(a));
  for (int i=0; i < 128; i++) {
    a[i] = i;
  }
  dfsan_label check = dfsan_read_label(a, sizeof(a));
  assert(dfsan_has_label(check, a_label));
  return 0;
}
