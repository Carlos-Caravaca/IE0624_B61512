;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.0.0 #11528 (Linux)
;--------------------------------------------------------
; PIC port for the 14-bit core
;--------------------------------------------------------
;	.file	"lab_01.c"
	list	p=12f675
	radix dec
	include "p12f675.inc"
;--------------------------------------------------------
; config word(s)
;--------------------------------------------------------
	__config 0x3f14
;--------------------------------------------------------
; external declarations
;--------------------------------------------------------
	extern	_ANSEL
	extern	_TRISIO
	extern	_GPIO
	extern	_GPIObits
	extern	__sdcc_gsinit_startup
;--------------------------------------------------------
; global declarations
;--------------------------------------------------------
	global	_main
	global	_delay

	global PSAVE
	global SSAVE
	global WSAVE
	global STK12
	global STK11
	global STK10
	global STK09
	global STK08
	global STK07
	global STK06
	global STK05
	global STK04
	global STK03
	global STK02
	global STK01
	global STK00

sharebank udata_ovr 0x0020
PSAVE	res 1
SSAVE	res 1
WSAVE	res 1
STK12	res 1
STK11	res 1
STK10	res 1
STK09	res 1
STK08	res 1
STK07	res 1
STK06	res 1
STK05	res 1
STK04	res 1
STK03	res 1
STK02	res 1
STK01	res 1
STK00	res 1

;--------------------------------------------------------
; global definitions
;--------------------------------------------------------
;--------------------------------------------------------
; absolute symbol definitions
;--------------------------------------------------------
;--------------------------------------------------------
; compiler-defined variables
;--------------------------------------------------------
UDL_lab_01_0	udata
r0x1008	res	1
r0x1009	res	1
r0x100A	res	1
r0x100B	res	1
r0x100C	res	1
r0x1001	res	1
r0x1000	res	1
r0x1002	res	1
r0x1003	res	1
r0x1004	res	1
r0x1005	res	1
r0x1006	res	1
r0x1007	res	1
;--------------------------------------------------------
; initialized data
;--------------------------------------------------------
;--------------------------------------------------------
; initialized absolute data
;--------------------------------------------------------
;--------------------------------------------------------
; overlayable items in internal ram 
;--------------------------------------------------------
;	udata_ovr
;--------------------------------------------------------
; reset vector 
;--------------------------------------------------------
STARTUP	code 0x0000
	nop
	pagesel __sdcc_gsinit_startup
	goto	__sdcc_gsinit_startup
;--------------------------------------------------------
; code
;--------------------------------------------------------
code_lab_01	code
;***
;  pBlock Stats: dbName = M
;***
;has an exit
;functions called:
;   _delay
;   _delay
;   _delay
;   _delay
;   _delay
;   _delay
;   _delay
;   _delay
;   _delay
;   _delay
;   _delay
;   _delay
;   _delay
;   _delay
;   _delay
;   _delay
;   _delay
;   _delay
;   _delay
;   _delay
;   _delay
;   _delay
;   _delay
;   _delay
;   _delay
;   _delay
;   _delay
;   _delay
;6 compiler assigned registers:
;   r0x1008
;   r0x1009
;   r0x100A
;   r0x100B
;   r0x100C
;   STK00
;; Starting pCode block
S_lab_01__main	code
_main:
; 2 exit points
;	.line	26; "lab_01.c"	ANSEL = 0;
	BANKSEL	_ANSEL
	CLRF	_ANSEL
;	.line	27; "lab_01.c"	TRISIO = 0b00000000; // Configurar pines como salidas
	CLRF	_TRISIO
;	.line	28; "lab_01.c"	GPIO = 0b00001000; //Poner pines en bajo
	MOVLW	0x08
	BANKSEL	_GPIO
	MOVWF	_GPIO
_00126_DS_:
;	.line	36; "lab_01.c"	for (int i = 0; i < 7; i++) {
	CLRF	r0x1008
	CLRF	r0x1009
	CLRF	r0x100A
	CLRF	r0x100B
;;signed compare: left < lit(0x7=7), size=2, mask=ffff
_00118_DS_:
	MOVF	r0x100B,W
	ADDLW	0x80
	ADDLW	0x80
	BTFSS	STATUS,2
	GOTO	_00142_DS_
	MOVLW	0x07
	SUBWF	r0x100A,W
_00142_DS_:
	BTFSC	STATUS,0
	GOTO	_00126_DS_
;;genSkipc:3307: created from rifx:0x7ffc1cf5f140
;	.line	37; "lab_01.c"	contador++;
	INCF	r0x1008,F
	BTFSC	STATUS,2
	INCF	r0x1009,F
;;signed compare: left < lit(0x1=1), size=2, mask=ffff
;	.line	40; "lab_01.c"	switch (contador) 
	MOVF	r0x1009,W
	ADDLW	0x80
	ADDLW	0x80
	BTFSS	STATUS,2
	GOTO	_00143_DS_
	MOVLW	0x01
	SUBWF	r0x1008,W
_00143_DS_:
	BTFSS	STATUS,0
	GOTO	_00111_DS_
;;genSkipc:3307: created from rifx:0x7ffc1cf5f140
;;swapping arguments (AOP_TYPEs 1/2)
;;signed compare: left >= lit(0x7=7), size=2, mask=ffff
	MOVF	r0x1009,W
	ADDLW	0x80
	ADDLW	0x80
	BTFSS	STATUS,2
	GOTO	_00144_DS_
	MOVLW	0x07
	SUBWF	r0x1008,W
_00144_DS_:
	BTFSC	STATUS,0
	GOTO	_00111_DS_
;;genSkipc:3307: created from rifx:0x7ffc1cf5f140
	DECF	r0x1008,W
	MOVWF	r0x100C
	MOVLW	HIGH(_00145_DS_)
	MOVWF	PCLATH
	MOVLW	_00145_DS_
	ADDWF	r0x100C,W
	BTFSC	STATUS,0
	INCF	PCLATH,F
	MOVWF	PCL
_00145_DS_:
	GOTO	_00105_DS_
	GOTO	_00106_DS_
	GOTO	_00107_DS_
	GOTO	_00108_DS_
	GOTO	_00109_DS_
	GOTO	_00110_DS_
_00105_DS_:
;	.line	44; "lab_01.c"	GP0 = 0;
	BANKSEL	_GPIObits
	BCF	_GPIObits,0
;	.line	45; "lab_01.c"	GP2 = 0;
	BCF	_GPIObits,2
;	.line	46; "lab_01.c"	GP4 = 0;
	BCF	_GPIObits,4
;	.line	47; "lab_01.c"	GP5 = 0;
	BCF	_GPIObits,5
;	.line	48; "lab_01.c"	GP1 = 1;
	BSF	_GPIObits,1
;	.line	49; "lab_01.c"	delay(time);
	MOVLW	0x64
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_delay
	CALL	_delay
	PAGESEL	$
;	.line	50; "lab_01.c"	delay(time);
	MOVLW	0x64
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_delay
	CALL	_delay
	PAGESEL	$
;	.line	51; "lab_01.c"	break;
	GOTO	_00119_DS_
_00106_DS_:
;	.line	55; "lab_01.c"	GP0 = 0;
	BANKSEL	_GPIObits
	BCF	_GPIObits,0
;	.line	56; "lab_01.c"	GP1 = 0;
	BCF	_GPIObits,1
;	.line	57; "lab_01.c"	GP2 = 1;
	BSF	_GPIObits,2
;	.line	58; "lab_01.c"	GP4 = 0;
	BCF	_GPIObits,4
;	.line	59; "lab_01.c"	GP5 = 0;
	BCF	_GPIObits,5
;	.line	60; "lab_01.c"	delay(time);
	MOVLW	0x64
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_delay
	CALL	_delay
	PAGESEL	$
;	.line	61; "lab_01.c"	delay(time);
	MOVLW	0x64
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_delay
	CALL	_delay
	PAGESEL	$
;	.line	62; "lab_01.c"	break;
	GOTO	_00119_DS_
_00107_DS_:
;	.line	65; "lab_01.c"	GP0 = 0;
	BANKSEL	_GPIObits
	BCF	_GPIObits,0
;	.line	66; "lab_01.c"	GP2 = 1;
	BSF	_GPIObits,2
;	.line	67; "lab_01.c"	GP4 = 0;
	BCF	_GPIObits,4
;	.line	68; "lab_01.c"	GP5 = 0;
	BCF	_GPIObits,5
;	.line	69; "lab_01.c"	GP1 = 1;
	BSF	_GPIObits,1
;	.line	70; "lab_01.c"	delay(time);
	MOVLW	0x64
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_delay
	CALL	_delay
	PAGESEL	$
;	.line	71; "lab_01.c"	delay(time);
	MOVLW	0x64
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_delay
	CALL	_delay
	PAGESEL	$
;	.line	72; "lab_01.c"	break;
	GOTO	_00119_DS_
_00108_DS_:
;	.line	75; "lab_01.c"	GP0 = 0;
	BANKSEL	_GPIObits
	BCF	_GPIObits,0
;	.line	76; "lab_01.c"	GP1 = 0;
	BCF	_GPIObits,1
;	.line	77; "lab_01.c"	GP2 = 0;
	BCF	_GPIObits,2
;	.line	78; "lab_01.c"	GP4 = 1;
	BSF	_GPIObits,4
;	.line	79; "lab_01.c"	GP5 = 1;
	BSF	_GPIObits,5
;	.line	80; "lab_01.c"	delay(time);
	MOVLW	0x64
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_delay
	CALL	_delay
	PAGESEL	$
;	.line	81; "lab_01.c"	delay(time);
	MOVLW	0x64
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_delay
	CALL	_delay
	PAGESEL	$
;	.line	82; "lab_01.c"	break;
	GOTO	_00119_DS_
_00109_DS_:
;	.line	85; "lab_01.c"	GP0 = 0;
	BANKSEL	_GPIObits
	BCF	_GPIObits,0
;	.line	86; "lab_01.c"	GP2 = 0;
	BCF	_GPIObits,2
;	.line	87; "lab_01.c"	GP4 = 1;
	BSF	_GPIObits,4
;	.line	88; "lab_01.c"	GP5 = 1;
	BSF	_GPIObits,5
;	.line	89; "lab_01.c"	GP1 = 1;
	BSF	_GPIObits,1
;	.line	90; "lab_01.c"	delay(time);
	MOVLW	0x64
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_delay
	CALL	_delay
	PAGESEL	$
;	.line	91; "lab_01.c"	delay(time);
	MOVLW	0x64
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_delay
	CALL	_delay
	PAGESEL	$
;	.line	92; "lab_01.c"	break;
	GOTO	_00119_DS_
_00110_DS_:
;	.line	95; "lab_01.c"	GP0 = 0;
	BANKSEL	_GPIObits
	BCF	_GPIObits,0
;	.line	96; "lab_01.c"	GP1 = 1;
	BSF	_GPIObits,1
;	.line	97; "lab_01.c"	GP2 = 1;
	BSF	_GPIObits,2
;	.line	98; "lab_01.c"	GP4 = 1;
	BSF	_GPIObits,4
;	.line	99; "lab_01.c"	GP5 = 1;
	BSF	_GPIObits,5
;	.line	100; "lab_01.c"	delay(time);
	MOVLW	0x64
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_delay
	CALL	_delay
	PAGESEL	$
;	.line	101; "lab_01.c"	delay(time);
	MOVLW	0x64
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_delay
	CALL	_delay
	PAGESEL	$
;	.line	102; "lab_01.c"	break;
	GOTO	_00119_DS_
_00111_DS_:
;	.line	105; "lab_01.c"	GP0 = 0;
	BANKSEL	_GPIObits
	BCF	_GPIObits,0
;	.line	106; "lab_01.c"	GP1 = 0;
	BCF	_GPIObits,1
;	.line	107; "lab_01.c"	GP2 = 0;
	BCF	_GPIObits,2
;	.line	108; "lab_01.c"	GP4 = 0;
	BCF	_GPIObits,4
;	.line	109; "lab_01.c"	GP5 = 0;
	BCF	_GPIObits,5
;	.line	110; "lab_01.c"	delay(time);
	MOVLW	0x64
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_delay
	CALL	_delay
	PAGESEL	$
;	.line	111; "lab_01.c"	delay(time);
	MOVLW	0x64
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_delay
	CALL	_delay
	PAGESEL	$
_00119_DS_:
;	.line	36; "lab_01.c"	for (int i = 0; i < 7; i++) {
	INCF	r0x100A,F
	BTFSC	STATUS,2
	INCF	r0x100B,F
	GOTO	_00118_DS_
;	.line	119; "lab_01.c"	}
	RETURN	
; exit point of _main

;***
;  pBlock Stats: dbName = C
;***
;has an exit
;9 compiler assigned registers:
;   r0x1000
;   STK00
;   r0x1001
;   r0x1002
;   r0x1003
;   r0x1004
;   r0x1005
;   r0x1006
;   r0x1007
;; Starting pCode block
S_lab_01__delay	code
_delay:
; 2 exit points
;	.line	120; "lab_01.c"	void delay(unsigned int tiempo)
	MOVWF	r0x1000
	MOVF	STK00,W
	MOVWF	r0x1001
;	.line	125; "lab_01.c"	for(i=0;i<tiempo;i++)
	CLRF	r0x1002
	CLRF	r0x1003
_00156_DS_:
	MOVF	r0x1000,W
	SUBWF	r0x1003,W
	BTFSS	STATUS,2
	GOTO	_00177_DS_
	MOVF	r0x1001,W
	SUBWF	r0x1002,W
_00177_DS_:
	BTFSC	STATUS,0
	GOTO	_00158_DS_
;;genSkipc:3307: created from rifx:0x7ffc1cf5f140
;	.line	126; "lab_01.c"	for(j=0;j<1275;j++);
	MOVLW	0xfb
	MOVWF	r0x1004
	MOVLW	0x04
	MOVWF	r0x1005
_00154_DS_:
	MOVLW	0xff
	ADDWF	r0x1004,W
	MOVWF	r0x1006
	MOVLW	0xff
	MOVWF	r0x1007
	MOVF	r0x1005,W
	BTFSC	STATUS,0
	INCFSZ	r0x1005,W
	ADDWF	r0x1007,F
	MOVF	r0x1006,W
	MOVWF	r0x1004
	MOVF	r0x1007,W
	MOVWF	r0x1005
	MOVF	r0x1007,W
	IORWF	r0x1006,W
	BTFSS	STATUS,2
	GOTO	_00154_DS_
;	.line	125; "lab_01.c"	for(i=0;i<tiempo;i++)
	INCF	r0x1002,F
	BTFSC	STATUS,2
	INCF	r0x1003,F
	GOTO	_00156_DS_
_00158_DS_:
;	.line	127; "lab_01.c"	}
	RETURN	
; exit point of _delay


;	code size estimation:
;	  194+   37 =   231 instructions (  536 byte)

	end
