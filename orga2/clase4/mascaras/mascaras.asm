section .rodata
; impar: times 8 dw 1
; ceros: times 8 dw 0
section .text

global sumarPares

%define vSize 128

;int32_t sumarPares(int16_t *v); (entran 8 datos por xmm)
;uint8_t *v => RDI
;ret		=> EAX
sumarPares:
	push rbp
	mov rbp, rsp

	mov 	rcx, vSize				;El contador tiene la cantidad de valores
	shr 	rcx, 2					;Ahora tiene la cantidad de pasos, vamos a armar 4 acumuladores de 32bits
	pxor 	xmm8, xmm8				;Seteo en 0 xmm8
	; movdqu 	xmm8, [impar]			;Guardo en xmm8 los numeros para comparar paridad
	; movdqu 	xmm7, [ceros]			;Me guardo todos ceros en xmm7 para usar en la mascara
  
  .ciclo:
   pmovsxwd xmm0, [rdi]			;Levanto 4 datos en xmm0
   	movdqu 	xmm1, xmm0 			;Me guardo una copia en xmm1
    pslld 	xmm1, 31			;Shifteo 31 bits para la izquierda. 
    							;Si el numero es par me queda un word con ceros
    							;Si no me queda un 1 en el bit mas significativo del double
  	psrad 	xmm1, 31			;Hago shift aritmetico 31bits a derecha.(llena con unos)
  								;Ahora tengo la mascara justo al reves
  	pandn 	xmm1, xmm0 			;Hace not a la mascara (dest) y despues hace el and
  	paddd 	xmm8, xmm1			;Acumulo en xmm8

  	add rdi, 8
  	loop .ciclo					;Hago el ciclo rcx veces

  	phaddd 	xmm8, xmm8			;Ahora tengo las 2 sumas parciales en low
  	phaddd 	xmm8, xmm8 			;Res final en el primer double de xmm8

  	movd 	eax, xmm8

	pop rbp
	ret

