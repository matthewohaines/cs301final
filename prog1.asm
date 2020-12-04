add	$10, $8, $9        #Value in $10 shoud become 0x11
add     $12, $11, $12	   #value in $12 should become 0x4
sub     $14, $13, $14      #value in $14 should become -1 - 129 = -130 = 0xffffff7e
sub     $30, $28, $29      #value in $30 should become 16 - (-1) = 17 = 0x11
addi    $15, $15, 301      #value in $15 should become 301 + 301 = 602 = 0x25a
slt     $16, $16, $0       #value in $16 should be set to 1, since origina value in $16 is negative
slt     $17, $0, $0        #value in $17 should be set to 0, since 0 is not less than 0
lw	$18, -8($19)       #address in $19 is 0x1000004c. Value written to $18 should be 0x12345678
lw      $19, 0($19)        #value written to 19 should be 0x11223344
j target1	
add	$3, $4, $8         #never gets executed
target2: addi $1, $1, -1   # $1 should get value 0xf
beq $0, $20, target3	
target1: sub $20, $0, $0   #$20 gets value 0
j target2 
target3: add $22, $0, $0   #$22 gets value 0

	
	
