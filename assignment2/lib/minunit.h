 #define mu_assert(message, test) do { if (!(test)) return message; } while (0)
 #define mu_run_test(test) do { char *message = test(); testsRun++; \
                                if (message) return message; } while (0)
 extern int testsRun;