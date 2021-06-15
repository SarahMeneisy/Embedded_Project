void UART5_inti(void){

 
      SYSCTL_RCGCGPIO_R|=SYSCTL_RCGCGPIO_R4; // GPIO Port E Run Mode Clock
      SYSCTL_RCGCUART_R|= SYSCTL_RCGCUART_R5;//UART Module 5 Run Mode Clock

          GPIO_PORTE_LOCK_R=0x4C4F434B;
          GPIO_PORTE_CR_R|=0x30;
          GPIO_PORTE_CR_R|=0x30;             //unlock pinE4,pinE5
          GPIO_PORTE_AFSEL_R|=0x30;          //Alternative function for pinE4,pinE5
          GPIO_PORTE_PCTL_R=0x0011000;            //Unable UART for pinE4,pinE5
          GPIO_PORTE_DEN_R|=0x30;            //pinE4,pinE5 is Digital
          GPIO_PORTE_AMSEL_R =0;             //Disable Analog
          GPIO_PORTE_DIR_R =0x10;             //pinE4 is input

          UART5_CTL_R &= ~UART_CTL_UARTEN;
          UART5_FBRD_R=11;                 //FBRD =round(0.167*64)=round(10.688)
          UART5_IBRD_R=104;                //IBRD = int(16000000/(16*9600))=int(104.167);
          UART5_CC_R = UART_CC_CS_SYSCLK;
          UART5_LCRH_R=(UART_LCRH_WLEN_8|UART_LCRH_FEN); // Enable FIFO , 8-bit length
          UART5_CTL_R|=(UART_CTL_UARTEN | UART_CTL_RXE|UART_CTL_TXE); // Enable UART, RXE,TXE

}

char UART5_read(void){
    while((UART5_FR_R &0x10) !=0);  //wait until RX buffer is not full
    return (unsigned char) (UART5_DR_R&0xFF);
}
                                        
