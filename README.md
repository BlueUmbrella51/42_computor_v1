# 42_computor_v1

The aim of this project was to create a polynomial equation (to a maximum degree of 2) solver. A requirement was to implement your own Rationals class. I have added some functionality to the solver:
- Handling of complex solutions
- Keeping fractions and square roots in the answers when it preserves precision (i.e. 1/3 not 0.333333 and sqrt(5) instead of 2.23606...)
- Factoring of answers
- Square root class

I have made a solver that maintains precision of the answers by keeping square roots and fractions intact if they do not equate to an integer value. It also simplifies the answer as much as possible.
