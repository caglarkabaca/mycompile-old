!test.mc
SET $a
PRINT "Lütfen bir sayı giriniz: "
GETINT $a ! bu bir test
SET $b #0
SETPOS $loop
ADD $b $b #1
PRINTLN $b
GOLT $loop $b $a
HLT