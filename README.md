# 42_computor_v1

The aim of this project was to create a polynomial equation (to a maximum degree of 2) solver. A requirement was to implement your own Rationals class. I have added some functionality to the solver:
- Handling of complex solutions
- Keeping fractions and square roots in the answers when it preserves precision (i.e. 1/3 not 0.333333 and sqrt(5) instead of 2.23606...)
- Factoring of answers
- Square root class

I have made a solver that maintains precision of the answers by keeping square roots and fractions intact if they do not equate to an integer value. It also simplifies the answer as much as possible.

I have also created unit tests with Catch2, because there were quite a few operations that I needed to make sure worked and kept working, which was an interesting thing to learn more about.

Some example output:
<br>

![Capture_4](https://github.com/BlueUmbrella51/42_computor_v1/assets/28274612/4a916444-e168-4263-b600-31b00b235b56)

![Capture_3](https://github.com/BlueUmbrella51/42_computor_v1/assets/28274612/39125449-e478-427d-b00b-8206c6ceb844)

![Capture_2](https://github.com/BlueUmbrella51/42_computor_v1/assets/28274612/55c92dcf-70ec-447d-8503-6b6f80f9ce06)

![Capture_1](https://github.com/BlueUmbrella51/42_computor_v1/assets/28274612/243ed915-1cfe-4956-aac1-3006210cb2da)
