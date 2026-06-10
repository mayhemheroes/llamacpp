/* mayhem/asan_options.c
 * Disable LeakSanitizer so it does not try to ptrace its own threads at exit.
 * Mayhem's coverage collection already holds the ptrace lock; a second attach
 * fails, LSan exits 1, and the run records 0 edges.  Leaks are not useful
 * signals for short fuzzing iterations anyway (ASan + UBSan are still active).
 *
 * Strong symbols (no __attribute__((weak))) so they override the ASan runtime's
 * own weak defaults, which wins when the instrumented runtime is linked last.
 */
const char *__asan_default_options(void) {
    return "detect_leaks=0";
}
const char *__lsan_default_options(void) {
    return "detect_leaks=0";
}
