! => WIP (ne kadar ! o kadar öncelikli)

### ekrana yazı yazdırmak için

* PRINT "Hello world!"
* PRINT $var

* PRINTLN "Hello world!"
* PRINTLN $var

### değişken tanımlamak için

* VALID $var !
* VALID $var 5 !

* SET $var #10
* SET $var "Test"

### kullanıcıdan veri almak için

* GETINT $var
* GETTXT $var !

### artimetik işlemler için

* ADD $x $y #10 | x = y + 10
* ADD $x $y $z  | x = y + z
* ADD $x #10 #2 | x = 10 + 2

* SUB $x $y #10 | x = y - 10
* SUB $x $y $z  | x = y - z
* SUB $x #10 #2 | x = 10 - 2

* MUL $x $y #10 | x = y * 10
* MUL $x $y $z  | x = y * z
* MUL $x #10 #2 | x = 10 * 2

* DIV $x $y #10 | x = y / 10
* DIV $x $y $z  | x = y / z
* DIV $x #10 #2 | x = 10 / 2

### döngü olayları

* !!!SETPOS $var
* !!!GOTO $var
* !!!GOGT $var $a $b | a > b
* !!!GOLT $var $a $b | a < b

### programı bitirmek için

* HLT