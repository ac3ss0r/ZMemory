#ifdef DEBUG
#define LOG(s, ...) printf(s, __VA_ARGS__)
#else
#define LOG(s, ...) do {} while (0)
#endif