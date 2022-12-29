#ifndef DEBUG_H
#define DEBUG_H

#ifdef ENABLE_DEBUG
#define _DEBUG(...) printf(__VA_ARGS__)
#else
#define _DEBUG(...)                                                            \
  {}
#endif

#endif /* DEBUG_H */
