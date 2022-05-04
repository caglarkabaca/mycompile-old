SET $a
PRINT "Lütfen bir sayı giriniz: "
GETINT $a
SET $b #-1
SETPOS $loop
ADD $b $b #1
PRINTLN $b
GOLT $loop $b $a
HLT