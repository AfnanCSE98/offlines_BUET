# solution of problem 2(3)
# 1705013 mod 5 = 3

# the following 3 lines are commands
#! start q0
#! end q8
#! fill B

# Now we specify some rules
q0 0 * R [q1,0,B]
q0 1 * R [q1,1,B]
[q1,0,B] 0 0 R [q1,0,B]
[q1,0,B] 1 1 R [q1,0,B]
[q1,1,B] 0 0 R [q1,1,B]
[q1,1,B] 1 1 R [q1,1,B]
[q1,0,B] c c R [q2,0,B]
[q1,1,B] c c R [q2,1,B]
[q2,0,B] 0 * R [q3,0,0]
[q2,0,B] 1 * R [q3,0,1]
[q2,1,B] 0 * R [q3,1,0]
[q2,1,B] 1 * R [q3,1,1]
[q2,0,B] * * R [q2,0,B]
[q2,1,B] * * R [q2,1,B]
[q3,0,0] 0 0 R [q3,0,0]
[q3,0,0] 1 1 R [q3,0,0]
[q3,0,0] c c R [q3,0,0]
[q3,0,1] 0 0 R [q3,0,1]
[q3,0,1] 1 1 R [q3,0,1]
[q3,0,1] c c R [q3,0,1]
[q3,1,0] 0 0 R [q3,1,0]
[q3,1,0] 1 1 R [q3,1,0]
[q3,1,0] c c R [q3,1,0]
[q3,1,1] 0 0 R [q3,1,1]
[q3,1,1] 1 1 R [q3,1,1]
[q3,1,1] c c R [q3,1,1]
[q3,0,0] B 0 L q4
[q3,0,1] B 0 L q4
[q3,1,0] B 0 L q4
[q3,1,1] B 1 L q4
q4 0 0 L q4
q4 1 1 L q4
q4 c c L q5
q5 0 0 L q5
q5 1 1 L q5
q5 * * L q5
q5 c c L q6
q6 0 0 L q6
q6 1 1 L q6
q6 * * R q0
q0 c c R q7
q7 0 0 R q7
q7 1 1 R q7
q7 * * R q7
q7 c c R q7
q7 B B R q8
