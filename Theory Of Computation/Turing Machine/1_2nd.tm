# St Id:1705098 , so problem 1-2

# the following 3 lines are commands
#! start q0
#! end qf
#! fill B

# Now we specify some rules
q0 1 X R q1
q0 0 Y R q2
q1 0 0 R q1
q1 1 1 R q1
q2 0 0 R q2
q2 1 1 R q2
q1 Y Y L q3
q1 X X L q3
q1 B B L q3
q2 Y Y L q3
q2 X X L q3
q2 B B L q3

q3 1 X L q4
q3 0 Y L q5

q4 0 0 L q4
q4 1 1 L q4
q5 0 0 L q5
q5 1 1 L q5

q4 X X R q0
q4 Y Y R q0
q5 X X R q0
q5 Y Y R q0

q0 X X R q6
q0 Y Y R q6

q6 X X R q6
q6 Y Y R q6

q6 B B L qf


 
 
