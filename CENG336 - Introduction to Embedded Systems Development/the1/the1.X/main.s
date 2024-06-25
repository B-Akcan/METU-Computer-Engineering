PROCESSOR 18F8722

#include <xc.inc>

; CONFIGURATION (DO NOT EDIT)
; CONFIG1H
CONFIG OSC = HSPLL      ; Oscillator Selection bits (HS oscillator, PLL enabled (Clock Frequency = 4 x FOSC1))
CONFIG FCMEN = OFF      ; Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
CONFIG IESO = OFF       ; Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)
; CONFIG2L
CONFIG PWRT = OFF       ; Power-up Timer Enable bit (PWRT disabled)
CONFIG BOREN = OFF      ; Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
; CONFIG2H
CONFIG WDT = OFF        ; Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
; CONFIG3H
CONFIG LPT1OSC = OFF    ; Low-Power Timer1 Oscillator Enable bit (Timer1 configured for higher power operation)
CONFIG MCLRE = ON       ; MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)
; CONFIG4L
CONFIG LVP = OFF        ; Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
CONFIG XINST = OFF      ; Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))
CONFIG DEBUG = OFF      ; Disable In-Circuit Debugger


GLOBAL i
GLOBAL j
GLOBAL k
GLOBAL counter1
GLOBAL counter2
GLOBAL re0_toggle_flag
GLOBAL re0_button_state
GLOBAL re1_toggle_flag
GLOBAL re1_button_state

; Define space for the variables in RAM
PSECT udata_acs
i:
    DS 1
j:
    DS 1
k:
    DS 1
counter1:
    DS 1
counter2:
    DS 1
re0_toggle_flag:
    DS 1
re0_button_state:
    DS 1
re1_toggle_flag:
    DS 1
re1_button_state:
    DS 1

PSECT resetVec,class=CODE,reloc=2
resetVec:
    goto       main

PSECT CODE
main:
    call initialize
    
    main_loop:
	call blinking_LED
	call re0_button
	call re1_button
	bra main_loop

initialize:
    clrf TRISB
    clrf TRISC
    clrf TRISD
    setf TRISE
    
    setf LATB
    setf LATC
    setf LATD
    
    movlw 250
    movwf i
    loop_i_1:
	movlw 40
	movwf j
	loop_j_1:
	    movlw 0
	    movwf k
	    loop_k_1:
		incfsz k
		bra loop_k_1
	    incfsz j
	    bra loop_j_1
	incfsz i
	bra loop_i_1
    
    clrf LATB
    clrf LATC
    clrf LATD
    clrf PORTB
    clrf PORTC
    clrf PORTD
    clrf PORTE
    
    clrf counter1
    movlw 189
    movwf counter2
    clrf re0_toggle_flag
    clrf re0_button_state
    clrf re1_toggle_flag
    clrf re1_button_state
    
    return

blinking_LED:
    incfsz counter1
    return
    counter1_overflow:
	incfsz counter2
	return
	counter2_overflow:
	    movlw 189
	    movwf counter2
	    
	    btg LATD, 0
		
	    call re0_led
	    call re1_led
		
	    return
    
re0_button:
    movlw 0
    subwf re0_button_state
    bnz	case1_0	; if (re0_button_state != 0) goto case1
    
    case0_0:
	movlw 00000001B
	andwf PORTE, 0
	bz end1_0 ; if (RE0 == 0) goto end1
	
	bsf re0_button_state, 0	; else re0_button_state = 1
    
	return
	
    case1_0:
	movlw 00000001B
	andwf PORTE, 0
	bnz end1_0 ; if (RE0 != 0) goto end1
	
	; else
	clrf re0_button_state ; re0_button_state = 0
	btg re0_toggle_flag, 0 ; re0_toggle_flag ^= 1
    
    end1_0:
	return

re0_led:
    movlw 0
    subwf re0_toggle_flag
    bz end2_0
    
    btfsc LATC, 0
    bra end2_0
    
    rrcf LATC
    bra end3_0
    
    end2_0:
	clrf LATC
  
    end3_0:
	return

re1_button:
    movlw 0
    subwf re1_button_state
    bnz	case1_1	; if (re1_button_state != 0) goto case1
    
    case0_1:
	movlw 00000010B
	andwf PORTE, 0
	bz end1_1 ; if (RE1 == 0) goto end1
	
	bsf re1_button_state, 0	; else re1_button_state = 1
    
	return
	
    case1_1:
	movlw 00000010B
	andwf PORTE, 0
	bnz end1_1 ; if (RE1 != 0) goto end1
	
	; else
	clrf re1_button_state ; re1_button_state = 0
	btg re1_toggle_flag, 0 ; re1_toggle_flag ^= 1
    
    end1_1:
	return

re1_led:
    movlw 0
    subwf re1_toggle_flag
    bz end2_1
    
    btfsc LATB, 7
    bra end2_1
    
    rlcf LATB
    bra end3_1
    
    end2_1:
	clrf LATB
  
    end3_1:
	return
    
end resetVec