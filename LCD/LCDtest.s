START: MOV   ACC,#0FEH   ;ACC����װ��LED1�������ݣ������Ƶ�11111110��
MOV   P1,ACC     ;��ACC��������P1��
MOV   R0,#7     ;���������ƶ�7�ξ����һ��8λ��ˮ����
LOOP:  RL   A       ;��ACC�е���������һλ 
MOV   P1,A      ;��ACC�ƶ�����������p1����ʾ 
ACALL  DELAY     ;������ʱ�ӳ��� 
DJNZ  R0,LOOP    ;û���ƶ���7�μ����ƶ�  
AJMP  START     ;�ƶ���7�κ�������ʼ�������Դﵽѭ������Ч��
;----- ��ʱ�ӳ��� -----  
DELAY: MOV   R0,#255    ;��ʱһ��ʱ��
D1:   MOV   R1,#255  
DJNZ  R1,$    
	DJNZ  R0,D1   
	RET          ;�ӳ��򷵻� 
    END          ;������� 
	  START: CLR   P1.0       ;P1.0����͵�ƽ,ʹLED1���� 
	  ACALL  DELAY      ;������ʱ�ӳ��� 
	  SETB  P1.0       ;P1.0����ߵ�ƽ,ʹLED1Ϩ��  
	  CLR   P1.1       ;P1.1����͵�ƽ,ʹLED2����   
	  ACALL  DELAY      ;������ʱ�ӳ���   
	  SETB  P1.1       ;P1.1����ߵ�ƽ,ʹLED2Ϩ��   
	  CLR   P1.2       ;P1.2����͵�ƽ,ʹLED3����   
	  ACALL  DELAY      ;������ʱ�ӳ���   
	  SETB  P1.2       ;P1.2����ߵ�ƽ,ʹLED3Ϩ��   
	  CLR   P1.3       ;P1.3����͵�ƽ,ʹLED4����   
	  ACALL  DELAY      ;������ʱ�ӳ���   
	  SETB  P1.3       ;P1.3����ߵ�ƽ,ʹLED4Ϩ��   
	  CLR   P1.4       ;P1.4����͵�ƽ,ʹLED5����   
	  ACALL  DELAY      ;������ʱ�ӳ���    
	  SETB  P1.4       ;P1.4����ߵ�ƽ,ʹLED5Ϩ��  
	  CLR   P1.5       ;P1.5����͵�ƽ,ʹLED6����    
	  ACALL  DELAY      ;������ʱ�ӳ���   
	  SETB  P1.5       ;P1.5����ߵ�ƽ,ʹLED6Ϩ��  
	  CLR   P1.6       ;P1.6����͵�ƽ,ʹLED7����    
	  ACALL  DELAY      ;������ʱ�ӳ���   
	  SETB  P1.6       ;P1.6����ߵ�ƽ,ʹLED7Ϩ��   
	  CLR   P1.7       ;P1.7����͵�ƽ,ʹLED8���� 
	  ACALL  DELAY      ;������ʱ�ӳ���  
	  SETB  P1.7       ;P1.7����ߵ�ƽ,ʹLED8Ϩ��   
	  ACALL  DELAY      ;������ʱ�ӳ���   
	  AJMP  START      ;8��LED����һ��󷵻ص����START����ѭ��   
	  ;----- ��ʱ�ӳ��� ----- 
	  DELAY: MOV   R0,#255     ;��ʱһ��ʱ��
	  D1:   MOV   R1,#255   
	  DJNZ  R1,$   
		  DJNZ  R0,D1   
		  RET            ;�ӳ��򷵻�  
		  END           ;�������             

  ORG   0000H       ;�ϵ縴λ�������0000H��ʼִ��
	  START: MOV   SP,#60H      ;��ջ��ʼ��Ϊ60H   
	  MOV   DPTR,#LIU_TAB   ;��ˮ�������׵�ַ��DPTR
	  LOOP:  CLR   A    
	  MOVC  A,@A+DPTR   
	  CJNE  A,#0FFH,SHOW   ;�����ˮ������־    
	  AJMP  START       ;���л�������,���ͷ��ʼ�ظ���
	  SHOW:  MOV   P1,A       ;�������͵�P1��   
	  ACALL  DELAY   
	  INC   DPTR  
   AJMP  LOOP    
   ;----- ��ʱ�ӳ��� ----- 
   DELAY: MOV   R0,#255     ;��ʱһ��ʱ��
   D1:   MOV   R1,#255   
   DJNZ  R1,$   
	   DJNZ  R0,D1   
	   RET            ;�ӳ��򷵻�     
	   ;----- ��������ˮ�������ݱ� -----
	   LIU_TAB:       DB 01111111B       ;�����Ʊ�ʾ����ˮ��������  
		   DB 10111111B   
			   DB 11011111B  
				   DB 11101111B  
					   DB 11110111B 
						   DB 11111011B   
							   DB 11111101B   
								   DB 11111110B  
									   DB 11111110B  
										   DB 11111101B   
											   DB 11111011B   
												   DB 11110111B   
													   DB 11101111B  
														   DB 11011111B  
															   DB 10111111B   
																   DB 01111111B   
																	   DB 7FH,0BFH,0DFH,0EFH,0F7H,0FBH,0FDH,0FEH ʮ�����Ʊ�ʾ  
																		   DB 0FEH,0FDH,0FBH,0F7H,0EFH,0DFH,0BFH,7FH   
																			   DB 7EH,0BDH,0DBH,0E7H,0E7H,0DBH,0BDH,7EH    
																				   DB 7FH,3FH,1FH,0FH,07H,03H,01H,00H   
																					   DB 0FFH          ;��ˮ����������־0FFH   
																						   END           ;�������
		DELAY: MOV R4,#2  L3: MOV R2 ,#250 L1: MOV R3 ,#250 L2: DJNZ R3 ,L2  DJNZ R2 ,L1 DJNZ R4 ,L3  RET
		
	   
	   