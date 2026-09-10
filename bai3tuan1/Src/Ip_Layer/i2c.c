#include "i2c.h"

void i2c_init(char i2c,unsigned short speed_mode)  
{
	RCC->APB2ENR |= 1;      
	if(i2c==1)
	{
		RCC->APB1ENR |= 0x200000;    
    	RCC->APB2ENR |= (1<<3);   
		GPIOB->CRL &= ~(0xF << 24);  
		GPIOB->CRL |=  (0xF << 24);   
		GPIOB->CRL &= ~(0xF << 28);
		GPIOB->CRL |=  (0xF << 28);
		I2C1->CR1 |= 0x8000;           
		I2C1->CR1 &= ~0x8000;             
		I2C1->CCR = 180;         
		I2C1->TRISE = 37;
		I2C1->CR1 |= 1;              
	}
	else if(i2c==2)
	{
		RCC->APB1ENR |= 0x400000;
   		RCC->APB2ENR |= (1<<3);
		GPIOB->CRH &= ~(0xF << 8);
		GPIOB->CRH |=  (0xF << 8);
		GPIOB->CRH &= ~(0xF << 12);
		GPIOB->CRH |=  (0xF << 12);
		I2C2->CR1 |= 0x8000;
		I2C2->CR1 &= ~0x8000;
		I2C2->CR2 =0x8;
		I2C2->CCR = speed_mode;
		I2C2->TRISE = 0x9;
		I2C2->CR1 |= 1;
	}

}
void i2c_start(char i2c) 
{
    if(i2c == 1)
    {
        I2C1->CR1 |= 0x100;           
        while (!(I2C1->SR1 & 1)){};   
    }
    else if(i2c == 2)
    {
        I2C2->CR1 |= 0x100;
        while (!(I2C2->SR1 & 1)){};
    }
}

void i2c_add(char i2c, char address, char RW) 
{
    volatile int tmp;
    if(i2c == 1)
    {
        I2C1->DR = (address | RW);    
        while((I2C1->SR1 & 2) == 0){}; 
        while((I2C1->SR1 & 2)){      
            tmp = I2C1->SR1;             
            tmp = I2C1->SR2;
            if((I2C1->SR1 & 2) == 0) break;
        }
    }
    else if(i2c == 2)
    {
        I2C2->DR = (address | RW);
        while((I2C2->SR1 & 2) == 0){};
        while((I2C2->SR1 & 2)){
            tmp = I2C2->SR1;
            tmp = I2C2->SR2;
            if((I2C2->SR1 & 2) == 0) break;
        }
    }
}

void i2c_data(char i2c,char data)  
{
	if(i2c==1)
	{
		while((I2C1->SR1 & 0x80) == 0){} 
			I2C1->DR = data;
		while((I2C1->SR1 & 0x80) == 0){}
	}
	else if(i2c==2)
	{
		while((I2C2->SR1 & 0x80) == 0){}
			I2C2->DR = data;
		while((I2C2->SR1 & 0x80) == 0){}
	}
}
void i2c_stop(char i2c) 
{
	volatile int tmp;
	if(i2c==1)
	{
		tmp = I2C1->SR1;  
		tmp = I2C1->SR2;
		I2C1->CR1 |= 0x200;  
	}
	else if(i2c==2)
	{
		tmp = I2C2->SR1;
		tmp = I2C2->SR2;
		I2C2->CR1 |= 0x200;
	}
}

void i2c_write(char i2c, char address,char data[])
{
	int i = 0;  
	
	i2c_start(i2c);  
	
	i2c_add(i2c, address,0);  
	
	while(data[i]!='\0') 
		{
			i2c_data(i2c,data[i]);
			i++;
		}
	i2c_stop(i2c); 
}

