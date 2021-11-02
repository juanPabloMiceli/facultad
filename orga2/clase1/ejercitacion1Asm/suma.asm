section .data
    formato_printf: db "entero: %d, double: %f, string: %s", 10, 0

    hello_world:	db "Hello World!",10
    hello_world_size EQU $ - hello_world


section .text
; global sumarEnteros
; global sumarDoubles
; global imprimirParametros
; global sumaParametros
global _start
_start:
    	mov	rdi,1			; fd
        mov	rsi,hello_world		; buffer
        mov	rdx,hello_world_size 	; count
        mov	rax,1	 		; write(2)
        syscall

        ; exit(result)
        mov	rdi,0			; result
        mov	rax,60			; exit(2)
        syscall





sumarEnteros:
    push rbp
    mov  rbp, rsp
    ;entero1 => rdi
    ;entero2 => rsi
    mov  eax, edi
    add  eax, esi
    pop  rbp
    ret

sumarDoubles:
    push rbp
    mov  rbp, rsp
    ;double1 => xmm0
    ;double2 => xmm1
    addpd xmm0, xmm1
    pop  rbp
    ret

;parametros: int, double, char*
;int    => edi
;double => xmm0
;char*  => rsi

; extern printf
imprimirParametros:
    push rbp
    mov rbp, rsp

    ;printf("entero: %d, double: %f, string: %s", entero, double, string)
    ;formato_printf => rdi
    ;entero => esi
    ;double => xmm0
    ;char* => rdx
    mov rdx, rsi
    mov esi, edi
    mov rdi, formato_printf
    mov rax, 1 ;cantidad de parametros de punto flotante
    ; call printf


    pop rbp
    ret
;int sumaParametros( int a0, int a1, int a2, int a3, int a4, int a5 ,int a6, int a7);
;a0 => edi
;a1 => esi
;a2 => edx
;a3 => ecx
;a4 => e8
;a5 => e9
;a6 => [rsp+0]
;a7 => [rsp+8]

sumaParametros:
    push rbp
    mov rbp, rsp

    mov eax, edi
    sub eax, esi
    add eax, edx
    sub eax, ecx
    add eax, r8d
    sub eax, r9d
    add eax, [rbp+16]
    sub eax, [rbp+24]

    pop rbp
    ret

