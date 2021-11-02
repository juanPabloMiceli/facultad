section .text
global suma_vector_asm
global diagonal_asm
global gris_asm
global primer_maximo_asm

;short suma_vector_asm(short* vector, short n)
;short* vector => rdi
;short  n      => esi
;return        => eax 
suma_vector_asm:
	push rbp
	mov rbp, rsp

	;eax va a ser la variable acumuladora
	;ecx va a ser el contador
	xor eax, eax
	xor ecx, ecx
  .ciclo:
  	add eax, [rdi + 2*rcx]
  	inc ecx
  	cmp ecx, esi
  	jnz .ciclo

	pop rbp
	ret

;extern void diagonal_asm(short* p, short n, short* vector);
;short* p		=> rdi
;short	n		=> esi
;short* vector 	=> rdx

diagonal_asm:
	push rbp
	mov rbp, rsp

	and rsi, 0xFFFF ; Limpio por si la parte alta tiene basura

	xor rcx, rcx ;indice de ciclo
	

	.ciclo:
	;Copio el valor de la matriz en el vector
	mov r8w, [rdi]
	mov [rdx], r8w

	;Muevo el puntero del vector
	add rdx, 2

	;Muevo el puntero de la matriz
	lea rdi, [rdi + rsi*2 + 2]
	mov r8, rdi


	inc rcx 
	cmp rcx, rsi
	jnz .ciclo

	pop rbp
	ret

;extern void gris_asm(struct pixel* matriz, short n, unsigned char* resultado)
;pixel* matriz = RDI
;short  n	   = ESI
;uchar*  res	   = RDX

gris_asm:
	push rbp
	mov rbp, rsp
	push rbx

	xor rcx, rcx	;indice de ciclo
	imul rsi, rsi 	;Guardamos en rsi la condicion de corte

	.ciclo:

	;Cuando llego aca estoy bien
	;parado en las 2 matrices
	xor rax, rax		;Limpio rax para usarla
	xor rbx, rbx		;Limpio rbx para usarla

	mov al, [rdi+1]		;Muevo el valor G a rax
	sal rax, 1			;Ahora tengo rax = 2G
	mov bl, [rdi]		;Muevo el valor R a rbx
	add rax, rbx		;Ahora rax = 2G + R
	mov bl, [rdi+2]		;Muevo el valor B a rbx
	add rax, rbx		;Ahora rax = R + 2G + B
	sar rax, 2

	mov [rdx], rax		;Muevo el valor a res

	;Muevo los 2 punteros
	inc rdx
	lea rdi, [rdi+3]

	inc rcx
	cmp rcx, rsi
	jnz .ciclo


	pop rbx
	pop rbp
	ret

;int32_t* primer_maximo_asm(int32_t* p, int32_t* f, int32_t* c);
;int32_t* p 	=>	RDI
;int32_t* rows	=>	RSI
;int32_t* cols	=>	RDX

;int32_t* res 	=> 	RAX

primer_maximo_asm:
	push rbp
	mov	 rbp, rsp
	push r12
	push rbx

	
	;RCX va a ser el contador
	;R8 el tamanio de la matriz
	;R9 va a tener al winner val
	xor r9, r9
  	mov r9d, [rdi]
	xor rcx, rcx
	mov r8d, [rsi]
	imul r8d, [rdx]
	

	xor r12, r12			;R12 va a tener a current value
  .ciclo:
  	mov r12d, [rdi + 4*rcx]
  	cmp r9d, r12d			;Comparo el valor en R9 con el proximo valor
  	jg  .encontre_maximo	;Si r9 es mayor entonces terminé
  	mov r9d, r12d  			;Si no, guardo ese valor en r9
  	inc rcx
  	cmp rcx, r8
  	jnz .ciclo

  .encontre_maximo:
  	dec rcx					;Vuelvo al rcx que andaba	
  	lea r12, [rdi + 4*rcx]  ;En R12 esta el resultado que quiero devolver
  	mov rbx, rdx			;Me guardo la pos de retorno de cols en RBX

  	xor rdx, rdx			;Seteo en 0 RDX
  	mov rax, rcx			;Ahora el dividendo es el indice

  	mov r9, [rbx]			;Paso a rdx el indice
  	div r9d			;divido el indice por la #columnas
  	;El cociente se guarda en RAX. (fila ganadora) => RSI
  	;El resto se guarda en RDX	   (col ganadora)  => RDX


  	mov [rsi], rax
  	mov rax, r12
  	;sal rcx, 2
  	;add rcx, rdi

  	;mov [rsi], rcx 

  	pop rbx
  	pop r12
	pop rbp

	ret
