SET $a
PRINT "Lütfen bir sayı giriniz: "
GETINT $a
SET $b #0
SETPOS $loop
ADD $b $b #1
PRINT " - " $b " "
GOLT $loop $b $a
HLT