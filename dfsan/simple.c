#include <sanitizer/dfsan_interface.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {

  int a[128];
  int b[128];
//  memset(a, 7, 128 * sizeof(int));
  dfsan_label a_label = dfsan_create_label("a", 0);
  dfsan_set_label(a_label, a, sizeof(a));
  dfsan_label b_label = dfsan_create_label("b", 0);
  dfsan_set_label(b_label, b, 128 * sizeof(int));
  int tmp = 0;
  // init b
  dfsan_label i_label = dfsan_create_label("i",0);
  int i = 0;
  dfsan_set_label(i_label, &i, sizeof(i));
  for (int i=0; i < 128; i++) {
    dfsan_set_label(i_label, &i, sizeof(i));
    b[i] = i;
  }
  int idx = b[0];
  dfsan_label check_idx = dfsan_read_label(b, sizeof(b));
  assert(dfsan_has_label(check_idx,b_label));
  tmp = a[b[4]];
  dfsan_label check = dfsan_read_label(&tmp, sizeof(tmp));
  assert(dfsan_has_label(check,a_label));
  assert(dfsan_has_label(check,b_label));
  
  printf("tmp is %d\n", tmp);

  return 0;
}
