/*
 * Functions for reading runtime configuration files
 *
 * $Id: lib.config.h 3316 2010-08-14 10:13:37Z eldering $
 */

#ifndef LIB_CONFIG_H
#define LIB_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

void  config_init(void);
int   config_isset(const char *);
const char *config_getvalue(const char *);
void  config_setvalue(const char *, const char *);
int   config_readfile(const char *);

#ifdef __cplusplus
}
#endif

#endif /* LIB_CONFIG_H */
