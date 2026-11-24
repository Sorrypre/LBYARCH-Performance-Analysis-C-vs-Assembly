section .text
bits 64
default rel
global saxpy_asm

saxpy_asm:
	push rsi
	push rbp
	mov rbp, rsp
	add rbp, 16
	; n@ecx, A@xmm1, X@r8, Y@r9, Z@rsp or Z@rbp+40
	
	; r10 is index, gets incremented every time ecx decreases
	; ecx 2 r10 0
	; ecx 1 r10 1
	; ecx 0 r10 2
	mov r10, 0 
	
	loop_through_vector:
		; add 4 to the pointers to move index
		; r11 is index*4 bytes for displacement
		mov r11, 0
		imul r11, r10, 4
	
		lea r13, [r8 + r11] ; r13 holds current X
		lea r14, [r9 + r11] ; r14 holds current Y
		
		mov r12, [rbp+ 40]
		lea r15, [r12 + r11] 	; holds current Z
		
		; Z[i] = A * X[i] + Y[i]	
		
		movss xmm4, xmm1 	; xmm4 = copy of A
		movss xmm6, [r14]	; xmm6 = Y[i]
		movss xmm5, [r13] 	; xmm5 = X[i] 
		mulss xmm4, xmm5; 	; xmm4 = A * X[i]
		addss xmm4, xmm6	; xmm4 = A * X[i] + Y[i]
		movss [r15], xmm4	; Z[i] <- xmm4 or current Z
		
		add r10, 1
		sub ecx, 1
		jnz loop_through_vector
	
	pop rbp
	pop rsi
    ret