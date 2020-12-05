# state_voting_power
An easy to use application to compare and evaluate relative voting power between the 51 voting members of the U.S. Electoral College.

## The Algorithm
Power is calculated using the Banzhaf method. Simply put, it is the number of "swings" from losing to winning in which a state causes, divided by the total number of swings that can occur. As an example, we can look at Oklahoma, which has 7 electoral votes. This means any coalition of states comprising 263 - 269 electoral votes (excluding Oklahoma) can be swung by Oklahoma if it joins. Dividing a state's number of swings by the total number of swings provides the power index, which describes the relative power of a state in the college.

This poses an interesting combinatorics problem - Banzhaf power can be simply (and tediously) calculated for small voting groups. However, for a group as large as the electoral college, computing each individual winning coalition and its power takes too long.

Even utilizing the power of a computer might prove inadequate if the Banzhaf power is being computed traditionally. The traditional algorithm has a Big O complexity of 2^n - with n being the number of voting members. Given large voting groups, this is simply incomputable in a reasonable time frame.

An alternative method would be to use a Monte Carlo simulation to find estimations of the values. This isn't entirely dependable, however, because the sample size of outcomes is excessively large (2^51) so no meaningful dataset can be generated. Additionally, a uniform density cannot be guaranteed.

The method utilized in my algorithm involves generating functions that compute the swings in which each state is involved. If you're unaware of how generating functions work, here is an example:

1) Think of how many ways 8 points can be scored in a game of basketball. Points are earned in 1's (free throws), 2's (dunks), and 3's (3-pointers).
2) Now use Wolfram Alpha or a similar online calculator to compute the power series of 1/((1-x)(1-x^2)(1-x^3)).
3) Compare the coefficients and exponents of the power series and of your initial calculation for 8 points.
4) You should notice that the x term with exponent 8 has the same coefficient as number of ways 8 points can be earned. This is not a coincidence (go ahead and find it for different points, or use football scoring if you'd like).

This combinatorial trick can be utilized in our situation to simplify the math involved. By multiplying (1+x^55)(1+x^38)(1+x^29)... and so on, where every exponent is the number of electoral votes of a college member. Multiplying 51 binomials is obviously somewhat computationally intensive, but it can be done quickly within a program. If a select member is left out of the multiplication, then it's number of swings is the coefficients of the terms with exponents equal to 270 minus the member's weight (look at the Oklahoma example in the first paragraph). This can be computed for every member, then Banzhaf power can be easily calculated.

In fact, an interesting challenge within this problem is the size of values being used. 128 bit integers are necessary, as well as very high precision floating point numbers. The Boost multiprecision library was used to provide this cabability.
