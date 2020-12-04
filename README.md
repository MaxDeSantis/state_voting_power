# state_voting_power
An easy to use application to compare and evaluate relative voting power between the 51 voting members of the U.S. Electoral College.

## The Algorithm
Power is calculated using the Banzhaf method. Simply put, it is the number of "swings" from losing to winning in which a state causes. This means any coalition of states comprising 263 - 269 electoral votes (excluding Oklahoma) can be swung by Oklahoma if it joins. Dividing a state's number of swings by the total number of swings provides the power index. This index describes how powerful a state is in relation to others.
