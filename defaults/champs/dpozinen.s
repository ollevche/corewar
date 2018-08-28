.name "dpozinen"
.comment "comment"

ld %0, r1
ld %4, r2
ld %50, r5

#add r1, r5, r3
#st r6,-4
# sti r6,-8, %2
#st r6,-9
#sti r6,-345, %10
st r2,-766
#sti r6, 987, %11

#xor	r2,r2,r2
fork	%2
fork	%-2
#fork	%-2
#fork	%-2
#lld	%-15, r3
#lldi	%1, r4, r4
zjmp %-510
#sti	r8, %-55, r2
#add	r2, r3, r2
#sub	r3,r5,r3
