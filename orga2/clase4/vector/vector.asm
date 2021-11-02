section .rodata
vSize: dq 128
cero: times 2 dq 0
A: 	dd 1.4142, 2.71, 3.14, 42.0
B:  dd 3.0, 1.0, 2.0, 4.0
; C:  dd 
; D:  dd 
section .text

global normalizar


;void normalizar(float *vector)
;float *vector	=> RDI
normalizar:
	push rbp
	mov rbp, rsp
	movups xmm0, [B]

	mov rdx, rdi				;Iniciamos puntero a vector
	mov rcx, [vSize] 			;El contador tiene el tamaño del vector
	shr rcx, 2					;Como en cada xmm entran 4 floats, vamos a hacer #vSize/4 iteraciones

	movaps xmm0, [rdx]			;En xmm0 voy a guardar los maximos
	movaps xmm1, xmm0			;En xmm1 voy a guardar los minimos	

  .ciclo_min_max:
  	movaps xmm2, [rdx]			;Muevo los siguientes 4 floats
  	maxps  xmm0, xmm2			;Actualizo los maximos
  	minps  xmm1, xmm2 			;Actualizo los minimos
  	add    rdx, 16				;Avanzo a los siguientes 4 floats
  	loop .ciclo_min_max

  .get_max:
  	movhlps xmm2, xmm0			;Guardo los 2 maximos del high de xmm0 en xmm2
  	maxps   xmm0, xmm2			;Ahora tengo en xmm0 los 2 maximos

  	movaps xmm2, xmm0			;Guardo los 2 maximos en xmm2
  	psrlq xmm2, 32				;Shifteo el max para low 32bits
  	maxss  xmm0, xmm2			;Ahora tengo en xmm0 el maximo
  

  .get_min:
  	movhlps xmm2, xmm1			;Guardo los 2 minimos del high de xmm1 en xmm2
  	minps  xmm1, xmm2			;Ahora tengo en xmm1 los 2 minimos

  	movaps xmm2, xmm1			;Guardo los 2 minimos en xmm2
  	psrldq xmm2, 4				;Shifteo el min para low 4 bytes
  	minss  xmm1, xmm2			;Ahora tengo en xmm1 el maximo

  .broadcast_max:
  	shufps xmm0, xmm0, 0x00		;Hago el broadcast desde low low hacia todo el vector


  .broadcast_min:
  	shufps xmm1, xmm1, 0x00		;Hago el broadcast desde low low hacia todo el vector


 	subps 	xmm0, xmm1			;Ahora en xmm0 tengo un broadcast de (max - min)

 	mov 	rdx, rdi			;Reiniciamos el puntero al vector
	mov 	rcx, [vSize] 		;El contador tiene el tamaño del vector
	shr 	rcx, 2				;Como en cada xmm entran 4 floats, vamos a hacer #vSize/4 iteraciones

  .ciclo_norm:
  	movaps 	xmm2, [rdx]			;Guardo en xmm2 los datos a normalizar
  	subps 	xmm2, xmm1			;Le resto a los datos el valor min
  	divps 	xmm2, xmm0			;Divido los datos por (max-min)
  	movaps 	[rdx], xmm2			;Devuelvo los valores normalizados al vector
  	add rdx, 16
  	loop .ciclo_norm



  .end:
	pop rbp
	ret

