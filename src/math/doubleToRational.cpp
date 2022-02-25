#include "headers/math_helpers.hpp"

// Seek for the upper bound where the number we're looking for is no longer
// below the value we're looking for
// void			SeekH(long int n, double err, long int *hn, long int *hd, long int ln, long int ld) {
// 	*hn += ln;
// 	*hd += ld;
// // (lower_d + ud) * (value + maxError) < (lower_n + un)
// 	if (((ld + *hd) * (n + err)) < (ln + *hn)) {
// 		int weight = 1;
//         do
//         {
//             weight *= 2;
//             *hn += ln * weight;
//             *hd += ld * weight;
// 			printf("SEEK H : %ld/%ld\n%f\n%ld\n\n", *hn, *hd, ((ld + *hd) * (n + err)),
// 			(ln + *hn));
//         }
//         while (((ld + *hd) * (n + err)) < (ln + *hn));
//         do
//         {
//             weight /= 2;

//             long int adec = ln * weight;
//             long int bdec = ld * weight;

//             if (!(((ld + (*hd - bdec)) * (n + err)) < (ln + (*hn - adec))))// (!f(a - adec, b - bdec))
//             {
//                 *hn -= adec;
//                 *hd -= bdec;
//             }
// 			printf("SEEK H : %ld/%ld\n%f\n%ld\n\n", *hn, *hd, ((ld + *hd) * (n + err)),
// 			(ln + *hn));
//         }
//         while (weight > 1);
// 		printf("SEEK H : %ld/%ld\n%f\n%ld\n\n", *hn, *hd, ((ld + *hd) * (n + err)),
// 			(ln + *hn));
// 		exit(0);
// 	}
// }


// Stern-brocot algorithm for continued fractions


//TODO: handle inf/nan
Rational        doubleToRational(double num, double accuracy) {
	if (accuracy <= 0.0 || accuracy >= 1.0) {
        throw new std::invalid_argument("Accuracy must be > 0 and < 1.");
    }
	int sign = num > 0 ? 1: -1;
	num = abs(num);
	double error = sign == -1 ? accuracy : num * accuracy;
	long int n = long(floor(num));
	num -= n;
	printf("ERROR %.25lf\nNUM %.25lf\n", error, num);
	if (num < error) {
		printf("NUM < ERROR\n");
		return (Rational(sign * n, 1));
	}
	else if (1 - error < num) {
        printf("1 - ERR < NUM");
		return (Rational(sign * (n + 1), 1));
	}
	printf("HERE\n");
	// lower bound is 0/1
	long int lower_n = 0;
	long int lower_d = 1;
	// higher bound is 1/0
	long int	higher_n = 1;
	long int 	higher_d = 0;
	while (true) {
		long int middle_n = lower_n + higher_n;
		long int middle_d = lower_d + higher_d;
		printf("upper: %ld/%ld\nlower: %ld/%ld\nmiddle: %lu/%ld\n\n\n", 
		higher_n, higher_d, lower_n, lower_d, middle_n, middle_d);
		// If x + error < middle
		//Seek(ref upper_n, ref upper_d, lower_n, lower_d, (un, ud) => (lower_d + ud) * (value + maxError) < (lower_n + un));
        if ((middle_d * (num + error)) < middle_n) {
			printf("LOWER THAN MIDDLE\n");
			if (((lower_d + higher_d) * (num + error)) < (lower_n + higher_n)) {
				int weight = 1;
				do
				{
					weight *= 2;
					higher_n += lower_n * weight;
					higher_d += lower_d * weight;
					printf("SEEK H :hn  %ld hd %ld\nld + hd  * (num * error)%f\n%ld\n\n", higher_n, higher_d, ((lower_d + higher_d) * (num + error)),
					(lower_n + higher_n));
				}
				while (((lower_d + higher_d) * (num + error)) < (lower_n + higher_n));
				do {
					weight /= 2;
					long int n_off = lower_n * weight;
					long int d_off = lower_d * weight;

					if (!(((lower_d + (higher_d - d_off)) * (num + error)) < (lower_n + (higher_n - n_off))))
					{
						higher_n -= n_off;
						higher_d -= d_off;
					}
				}
				while (weight > 1);
				printf("RESULT: %ld/%ld", higher_n, higher_d);
				// exit(0);
			}
		}
            // middle is new upper limit
            // higher_n = middle_n;
            // higher_d = middle_d;
			// Traverse down one side of the tree until we approach closer
			// values
			// SeekH(num, error, &higher_n, &higher_d, lower_n, lower_d);
        // Else If middle < x - error
        else if (middle_n < ((num - error) * middle_d)) {
			printf("HIGHER THAN MIDDLE\n");
            // middle is our new lower limit
			//(ln + upper_n) < (value - maxError) * (ld + upper_d));
			if ((lower_n + higher_n) < ((num - error) * (lower_d + higher_d))) {
				int weight = 1;
				do
				{
					weight *= 2;
					lower_n += higher_n * weight;
					lower_d += higher_d * weight;
					// printf("SEEK H : %ld/%ld\n%f\n%ld\n\n", higher_n, higher_d, ((lower_d + higher_d) * (num + error)),
					// (lower_n + higher_n));
				}
				while ((lower_n + higher_n) < ((num - error) * (lower_d + higher_d)));
				do {
					weight /= 2;
					long int n_off = higher_n * weight;
					long int d_off = higher_d * weight;

					if (!(((lower_n - n_off) + higher_n) < ((num - error) * ((lower_d - d_off) + higher_d))))
					{
						lower_n -= n_off;
						lower_d -= d_off;
					}
				}
				while (weight > 1);
				printf("RESULT: %ld/%ld", higher_n, higher_d);
				// exit(0);
			}
            // lower_n = middle_n;
            // lower_d = middle_d;
		}
        // Else middle is our best fraction
        else {
            return (Rational((n * middle_d + middle_n) * sign, middle_d));
		}
	}
}