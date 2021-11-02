section .rodata
uno:  times 8 dw 1
dos:  times 4 dd 2
tres: times 8 dw 3
section .text

global suma1
global suma2
global suma3

;void suma1(uint16_t *vector, uint16_t *resultado, uint8_t n);
;uint16_t *vector 		=> RDI
;uint16_t *resultado	=> RSI
;uint8_t n				=> DL
suma1:
	push rbp
	mov rbp, rsp

	movzx rcx, dl					;Guardo en rcx la cantidad de datos
	shr ecx, 3						;Divido por 8 para usarlo como contador

	movdqu xmm8, [uno]				;Me guardo en xmm8 el vector de 8 unos

  .ciclo:
	movdqu xmm0, [rdi]				;Muevo a xmm0 los 8 datos a ser sumados
	paddw xmm0, xmm8				;Los sumo contra el vector de unos y los guardo en xmm0
	movdqu [rsi], xmm0				;Paso el resultado al vector resultado

	add rdi, 16						;Muevo el puntero a los proximos 8 datos
	add rsi, 16						;Muevo el puntero a los proximos 8 datos

	loop .ciclo						;Itero rcx veces, en este caso n/8 veces							

	pop rbp
	ret


;void suma2(int16_t  *vector, int32_t  *resultado, uint8_t n);
;int16_t *vector 		=> RDI
;int32_t *resultado`	=> RSI
;uint8_t n				=> DL
suma2:
	push rbp
	mov rbp, rsp

	movzx rcx, dl					;Guardo en rcx la cantidad de datos
	shr ecx, 2						;Divido la cantidad de datos por 4

	movdqu xmm8, [dos]				;Lleno de 2 el registro xmm8
  .ciclo: 
  	pmovsxwd xmm0, [rdi]			;Levanto en xmm0 4 datos del vector in
  	paddd  xmm0, xmm8				;Sumo los 4 datos
  	movdqu  [rsi], xmm0				;Guardo los 4 datos nuevos en el vector out
  	
  	add rdi, 8						;Avanzo a las proximas 4 datos de entrada
  	add rsi, 16						;Avanzo a las proximos 4 datos de salida
  	loop .ciclo						;Loopeo la cantidad de datos/4 veces

	pop rbp
	ret


;void suma3(int16_t  *vector, uint8_t n);
;int16_t *vector 		=> RDI
;uint8_t n				=> SIL
suma3:
	push rbp
	mov rbp, rsp

	movzx rcx, sil					;Guardo en rcx la cantidad de datos
	shr rcx, 3						;Divido la cantidad de datos por 8

	movdqu xmm8, [tres]				;Lleno de 3 el registro xmm8
  
  .ciclo:
  	movdqu xmm0, [rdi]				;Levanto 8 datos a xmm0
  	paddsw xmm0, xmm8				;Los sumo con saturacion y los dejo en xmm0
  	movdqu [rdi], xmm0				;Los devuelvo al lugar

  	add rdi, 16						;Avanzo a los siguientes 8 datos
  	loop .ciclo						;Loopeo la cantidad de datos/8 veces

	pop rbp
	ret