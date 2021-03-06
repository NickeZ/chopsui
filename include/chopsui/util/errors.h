#ifndef _SUI_ERRORS_H
#define _SUI_ERRORS_H
#include <stdarg.h>
#include <chopsui/util/list.h>

typedef sui_list_t errors_t;

const char *append_error(errors_t **errs, const char *fmt, ...);
void errors_free(errors_t *errs);

#endif
