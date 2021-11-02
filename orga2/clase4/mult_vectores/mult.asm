section .rodata

section .text

global mulvec

%define vSize 128

;void mulvec(int16_t *v1, int16_t *v2, int32_t* res);
;uint16_t *v1   => RDI
;uint16_t *v1	  => RSI
;uint32_t *res  => RDX
mulvec:
	push rbp
	mov rbp, rsp

	mov 	rcx, vSize				;El contador tiene la cantidad de valores
	shr 	rcx, 3				  	;Ahora tiene la cantidad de pasos.

  .ciclo:
    movdqa  xmm0, [rdi]   ;Levanto 8 valores de v1 a xmm0
    movdqa  xmm1, [rsi]   ;Levanto 8 valores de v2 a xmm1
    movdqa  xmm2, xmm1    ;Me hago una copia de lo que tengo en v2 en xmm2

    pmulhw  xmm1, xmm0    ;Parte alta de multiplicar v1 y v2 guardada en xmm1
    pmullw  xmm0, xmm2    ;Parte baja de multiplicar v1 y v2 guardada en xmm0

    movdqa  xmm2, xmm0    ;Me guardo la parte baja de v1*v2 en xmm2

    punpcklwd xmm0, xmm1  ;Me guardo los 4 v1*v2 parte baja en xmm0  
    punpckhwd xmm2, xmm1  ;Me guardo los 4 v1*v2 parte alta en xmm2

    movdqa [rdx], xmm0    ;Guardo los primeros 4 numeros
    movdqa [rdx+16], xmm2 ;Guardo los segundos 4 numeros

    add rdx, 32           ;Incremento a los proximos 8 resultados
    add rsi, 16           ;Incremento a los proximos 8 elems de v2
    add rdi, 16           ;Incremento a los proximos 8 elems de v1
    loop .ciclo

	pop rbp
	ret

