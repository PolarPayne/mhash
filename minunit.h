#ifndef MINUNIT_H
#define MINUNIT_H

/* 
 * LICENSE:
 * You may use the code in this tech note for any purpose,
 * with the understanding that it comes with NO WARRANTY.
 *
 * From http://www.jera.com/techinfo/jtns/jtn002.html
 */

#define mu_assert(message, test) do { if (!(test)) return message; } while (0)
#define mu_run_test(test) do { char *message = test(); mu_tests_run++; \
			  if (message) return message; } while (0)
extern int mu_tests_run;

#endif // MINUNIT_H
