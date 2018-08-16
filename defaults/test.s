.name "it's a test"

.comment "live only"

	live %-1
	ld	%1, r3
	ld	%33, r6
forks:
	add	r2, r3, r2		;increment r2
	xor	r2, %15, r4		;if (r4) {carry = 0}
live2:
	live 	%4
	ld	%0, r4			;carry = 1
live:
	live %4
	or	r2, %15, r4		;if (r4) {carry = 0}
	and	r2, %15, r4		;if (r4) {carry = 0}
	sub	r2, r3, r2		;increment r2
	r2, %15, r4		;if (r4) {carry = 0}
	and	r2, %15, r4		;if (r4) {carry = 0}
	sub	r2, r3, r2		;increment r2
