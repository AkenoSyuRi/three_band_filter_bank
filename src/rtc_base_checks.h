//
// Created by wedo on 2023/9/5.
//

#ifndef CPP_TEST_RTC_BASE_CHECKS_H
#define CPP_TEST_RTC_BASE_CHECKS_H

#include <cstdio>

#define RTC_DCHECK(condition)                                                 \
  do {                                                                       \
    if (!(condition)) {                                                      \
        fprintf(stderr, "%s:%d: assertion failed: %s", __FILE__, __LINE__, #condition); \
        abort();                                                                         \
    }                                                                        \
  } while (0)

#define RTC_DCHECK_EQ(a, b) RTC_DCHECK((a) == (b))
#define RTC_DCHECK_NE(a, b) RTC_DCHECK((a) != (b))
#define RTC_DCHECK_LE(a, b) RTC_DCHECK((a) <= (b))
#define RTC_DCHECK_LT(a, b) RTC_DCHECK((a) < (b))
#define RTC_DCHECK_GE(a, b) RTC_DCHECK((a) >= (b))
#define RTC_DCHECK_GT(a, b) RTC_DCHECK((a) > (b))

#endif //CPP_TEST_RTC_BASE_CHECKS_H
