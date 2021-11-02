section .rodata
diez: times 16 db 10
section .text

global incrementarBrillo10

;void incrementarBrillo10(uint8_t *imagen);
;uint8_t *imagen => RDI
incrementarBrillo10:
	push rbp
	mov rbp, rsp

	mov rcx, 64					;El contador tiene la cantidad de pasos
	movdqu xmm8, [diez]			;Guardo en xmm8 los incrementos
  
  .ciclo:
  	movdqu xmm0, [rdi]			;Levanto 16 pixeles
  	paddusb xmm0, xmm8			;Les sumo 10 a todos los pixeles
  	movdqu [rdi], xmm0			;Los devuelvo a la imagen

  	add rdi, 16
  	loop .ciclo					;Hago el ciclo rcx veces

	pop rbp
	ret

