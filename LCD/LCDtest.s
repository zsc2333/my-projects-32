START: MOV   ACC,#0FEH   ;ACC中先装入LED1亮的数据（二进制的11111110）
MOV   P1,ACC     ;将ACC的数据送P1口
MOV   R0,#7     ;将数据再移动7次就完成一个8位流水过程
LOOP:  RL   A       ;将ACC中的数据左移一位 
MOV   P1,A      ;把ACC移动过的数据送p1口显示 
ACALL  DELAY     ;调用延时子程序 
DJNZ  R0,LOOP    ;没有移动够7次继续移动  
AJMP  START     ;移动完7次后跳到开始重来，以达到循环流动效果
;----- 延时子程序 -----  
DELAY: MOV   R0,#255    ;延时一段时间
D1:   MOV   R1,#255  
DJNZ  R1,$    
	DJNZ  R0,D1   
	RET          ;子程序返回 
    END          ;程序结束 
	  START: CLR   P1.0       ;P1.0输出低电平,使LED1点亮 
	  ACALL  DELAY      ;调用延时子程序 
	  SETB  P1.0       ;P1.0输出高电平,使LED1熄灭  
	  CLR   P1.1       ;P1.1输出低电平,使LED2点亮   
	  ACALL  DELAY      ;调用延时子程序   
	  SETB  P1.1       ;P1.1输出高电平,使LED2熄灭   
	  CLR   P1.2       ;P1.2输出低电平,使LED3点亮   
	  ACALL  DELAY      ;调用延时子程序   
	  SETB  P1.2       ;P1.2输出高电平,使LED3熄灭   
	  CLR   P1.3       ;P1.3输出低电平,使LED4点亮   
	  ACALL  DELAY      ;调用延时子程序   
	  SETB  P1.3       ;P1.3输出高电平,使LED4熄灭   
	  CLR   P1.4       ;P1.4输出低电平,使LED5点亮   
	  ACALL  DELAY      ;调用延时子程序    
	  SETB  P1.4       ;P1.4输出高电平,使LED5熄灭  
	  CLR   P1.5       ;P1.5输出低电平,使LED6点亮    
	  ACALL  DELAY      ;调用延时子程序   
	  SETB  P1.5       ;P1.5输出高电平,使LED6熄灭  
	  CLR   P1.6       ;P1.6输出低电平,使LED7点亮    
	  ACALL  DELAY      ;调用延时子程序   
	  SETB  P1.6       ;P1.6输出高电平,使LED7熄灭   
	  CLR   P1.7       ;P1.7输出低电平,使LED8点亮 
	  ACALL  DELAY      ;调用延时子程序  
	  SETB  P1.7       ;P1.7输出高电平,使LED8熄灭   
	  ACALL  DELAY      ;调用延时子程序   
	  AJMP  START      ;8个LED流了一遍后返回到标号START处再循环   
	  ;----- 延时子程序 ----- 
	  DELAY: MOV   R0,#255     ;延时一段时间
	  D1:   MOV   R1,#255   
	  DJNZ  R1,$   
		  DJNZ  R0,D1   
		  RET            ;子程序返回  
		  END           ;程序结束             

  ORG   0000H       ;上电复位，程序从0000H开始执行
	  START: MOV   SP,#60H      ;堆栈初始化为60H   
	  MOV   DPTR,#LIU_TAB   ;流水花样表首地址送DPTR
	  LOOP:  CLR   A    
	  MOVC  A,@A+DPTR   
	  CJNE  A,#0FFH,SHOW   ;检查流水结束标志    
	  AJMP  START       ;所有花样流完,则从头开始重复流
	  SHOW:  MOV   P1,A       ;将数据送到P1口   
	  ACALL  DELAY   
	  INC   DPTR  
   AJMP  LOOP    
   ;----- 延时子程序 ----- 
   DELAY: MOV   R0,#255     ;延时一段时间
   D1:   MOV   R1,#255   
   DJNZ  R1,$   
	   DJNZ  R0,D1   
	   RET            ;子程序返回     
	   ;----- 下面是流水花样数据表 -----
	   LIU_TAB:       DB 01111111B       ;二进制表示的流水花样数据  
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
																	   DB 7FH,0BFH,0DFH,0EFH,0F7H,0FBH,0FDH,0FEH 十六进制表示  
																		   DB 0FEH,0FDH,0FBH,0F7H,0EFH,0DFH,0BFH,7FH   
																			   DB 7EH,0BDH,0DBH,0E7H,0E7H,0DBH,0BDH,7EH    
																				   DB 7FH,3FH,1FH,0FH,07H,03H,01H,00H   
																					   DB 0FFH          ;流水花样结束标志0FFH   
																						   END           ;程序结束
		DELAY: MOV R4,#2  L3: MOV R2 ,#250 L1: MOV R3 ,#250 L2: DJNZ R3 ,L2  DJNZ R2 ,L1 DJNZ R4 ,L3  RET
		
	   
	   