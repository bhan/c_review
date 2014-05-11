#include <stdarg.h>
#include <stdio.h>

double average(int count, ...)
{
  printf("count:%d\n", count);
  va_list ap;
  va_start(ap, count);
  printf("ap:%p\n", ap);
  double tot = 0;
  for (int j = 0; j < count; ++j) {
    double cur_arg = va_arg(ap, double);
    printf("cur_arg:%g\n", cur_arg);
    tot += cur_arg;
  }
  va_end(ap);
  return tot/count;
}

int main(void) {
  printf("average:%g\n", average(2, 1.0, 2.0));
  double (*average_func) (int, ...) = &average;
  printf("average:%g\n", average_func(2, 1.0, 2.0));
}
