# St Id:1705098 , so problem 1-2
# the tm writes X at the position (n+2) if ww^r string of length 2n is found.If w is an empty string ,it writes X and goes to qf

# the following 3 lines are commands
#! start q0
#! end qf
#! fill B

# Now we specify some rules
q0 1 B R [q1,1]
q0 0 B R [q1,0]

[q1,1] 1 1 R [q1,1]
[q1,1] 0 0 R [q1,1]
[q1,0] 1 1 R [q1,0]
[q1,0] 0 0 R [q1,0]

[q1,1] B B L [q3,1]
[q1,0] B B L [q3,0]

[q3,1] 1 B L q4
[q3,1] 0 0 L q5
[q3,0] 0 B L q4
[q3,0] 1 1 L q5

q4 1 1 L q4
q4 0 0 L q4
q4 B B R q0

q0 B B R q5

q5 B X R qf
q5 0 0 L qf
q5 1 1 L qf




 
 
