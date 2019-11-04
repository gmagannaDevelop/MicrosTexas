;-------------------------------------------------------------------------------
; MSP430 Assembler Code Template for use with TI Code Composer Studio
;
;
;-------------------------------------------------------------------------------
            .cdecls C,LIST,"msp430.h"       ; Include device header file
            
;-------------------------------------------------------------------------------
            .def    RESET                   ; Export program entry-point to
                                            ; make it known to linker.
;-------------------------------------------------------------------------------
            .text                           ; Assemble into program memory.
            .retain                         ; Override ELF conditional linking
                                            ; and retain current section.
            .retainrefs                     ; And retain any sections that have
                                            ; references to current section.

;-------------------------------------------------------------------------------
RESET       mov.w   #__STACK_END,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW|WDTHOLD,&WDTCTL  ; Stop watchdog timer


;-------------------------------------------------------------------------------
; Main loop here
;-------------------------------------------------------------------------------


;*********************************************************************
*********
;   #include  "msp430x11x1.h"
;   MSP-FET430x110 Demo - Software Output 6-bit R2R DAC
;
;   Description: Implement a 6-bit DAC using 6 P2.x outputs and an R2R
;   ladder.  A sine wave is generated using a 6-bit, 32-step sine
look-up
;   table Sin_Tab.  R5 is used as a pointer into Sin_Tab.  Any MSP430
;   outputs can be used for the DAC with ther bit-resolutions and
;   frequencies possible.  ACLK as an input to CCR2 is used to
trigger an
;   interrupt at exacty 32768Hz.  The ISR updates the DAC using
;   Sin_Tab.  The frequency of the sine wave in this example is ISR
;   frequency/steps = 32768/32 = 1024hz.
;   ACLK = LFXT1 = 32768, MCLK = SMCLK = default DCO ~ 800k
;   //*An external watch crystal on XIN XOUT is required for ACLK*//

;
;
;                MSP430F1121
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |             P2.5|--20k--+---> 1024hz sine wave
;            |                 |      10k
;            |             P2.4|--20k--+
;            |                 |      10k
;            |             P2.3|--20k--+
;            |                 |      10k
;            |             P2.2|--20k--+
;            |                 |      10k
;            |             P2.1|--20k--+
;            |                 |      10k
;            |             P2.0|--20k--+
;            |                 |      20k
;                                      |
;                                      V
;   M.Buccini
;   Texas Instruments, Inc
;   January 2002
;*********************************************************************
*********
;---------------------------------
---------
            ORG     0F000h                  ; Program Start
;---------------------------------
---------
RESET       mov.w   #0300h,SP               ; Initialize  stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop watchdog timer
SetupBC     bis.b   #RSEL2+RSEL0,&BCSCTL1   ; RSEL=5
SetupP2     mov.b   #03Fh,&P2DIR            ; P2.0 - 5 output
direction
            clr.w   R5                      ; Clear pointer
SetupTA     mov.w   #TASSEL1+TACLR,&TACTL    ; SMCLK, Clear TAR
Setup_CC2   mov.w   #CCIS0+CM0+CAP+CCIE,&CCTL2   ; CCR2,CAP on
CCxB,ACLK,int

            bis.w   #MC1,&TACTL             ; Continous Mode
            eint                            ; Enable interrupts
                                            ;
Mainloop    jmp     Mainloop                ; Do Nothing
                                            ;
;---------------------------------
---------
TAX_ISR;    Common ISR for CCR1-4 and overflow
;---------------------------------
---------
            add.w   &TAIV,PC                ; Add TA interrupt offset
to PC
            reti                            ; CCR0 - no source
            reti                            ; CCR1
            jmp     CCR2_ISR                ; CCR2
;            reti                            ; CCR3
;            reti                            ; CCR4
;TA_over     reti                            ; Timer_A overflow
                                            ;
CCR2_ISR    mov.b   Sin_tab(R5),&P2OUT      ; Move sine value to P2
            inc.b   R5                      ; Inc pointer
            and.b   #01Fh,R5                ; R5 = 0 - 31 only (32
bytes)
            reti                            ;
;---------------------------------
---------
Sin_tab;    Sine 6-bit Lookup table with 32 steps
;---------------------------------
---------
            DB   32
            DB   38
            DB   44
            DB   49
            DB   54
            DB   58
            DB   61
            DB   62
            DB   63
            DB   62
            DB   61
            DB   58
            DB   54
            DB   49
            DB   44
            DB   38
            DB   32
            DB   25
            DB   19
            DB   14
            DB   9
            DB   5
            DB   2
            DB   1
            DB   0
            DB   1
            DB   2
            DB   5
            DB   9
            DB   14
            DB   19
            DB   25
                                            ;
;---------------------------------
---------
;           Interrupt Vectors Used MSP430x11x1
;---------------------------------
---------
            ORG     0FFFEh                  ; MSP430 RESET Vector
            DW      RESET                   ;
            ORG     0FFF0h                  ; Timer_AX Vector
            DW      TAX_ISR                 ;
            END

                                            

;-------------------------------------------------------------------------------
; Stack Pointer definition
;-------------------------------------------------------------------------------
            .global __STACK_END
            .sect   .stack
            
;-------------------------------------------------------------------------------
; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET
            
