wow:      j label
add $3, $4, $8
label: addi $1, $2, 100
add $16, $7, $8
addi $5, $13, -3        # cool
mult $2, $3
mflo $1                 # hello:

floor3:

sra $18, $21, 4         # 000000 00000 10101 10010 00100 000011

                        # testing out just comments

label2: slt $1, $2, $3  # 000000 00010 00011 00001 00000 101010

lb $1, 100($2)          # 100000 00010 00001 0000000001100100

j 0x40b10c
j wow
j floor3                # :::::::::::
j 0x40001c
