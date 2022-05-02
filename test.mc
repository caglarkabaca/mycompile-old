PRINT "a: "
GETINT $a
PRINT "b: "
GETINT $b
SET $buff #0
ADD $buff $a $b
PRINT "sum: "
PRINTLN $buff
SUB $buff $a $b
PRINT "sub: "
PRINTLN $buff
HLT