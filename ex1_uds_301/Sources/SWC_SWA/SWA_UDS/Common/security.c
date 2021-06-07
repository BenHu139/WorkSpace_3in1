#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <math.h>
#include "security.h"
#include "typedefs.h"



	//固定参数CK 0-5
	char CK[5][8] = {{0x00,0x00,0x00,0x07,0x00,0x0e,0x01,0x05},{0x01,0x0c,0x02,0x03,0x02,0x0a,0x03,0x01},
	{0x03,0x08,0x03,0x0f,0x04,0x06,0x04,0x0d},{0x05,0x04,0x05,0x0b,0x06,0x02,0x06,0x09},{0x07,0x00,0x07,0x07,0x07,0x0e,0x08,0x05}};
	//系统参数FK
	char FK[8] = {0x0a,0x03,0x0b,0x01,0x0b,0x0a,0x0c,0x06};

    char rK[5][8];

	//s盒  用来置换参数
	uint16_t S[16][16]={
			{0x0d06,0x0900,0x0e09,0x0f0e,0x0c0c,0x0e01,0x030d,0x0b07,0x0106,0x0b06,0x0104,0x0c02,0x0208,0x0f0b,0x020c,0x0005},
			{0x020b,0x0607,0x090a,0x0706,0x020a,0x0b0e,0x0004,0x0c03,0x0a0a,0x0404,0x0103,0x0206,0x0409,0x0806,0x0006,0x0909},
			{0x090c,0x0402,0x0500,0x0f04,0x0901,0x0e0f,0x0908,0x070a,0x0303,0x0504,0x000b,0x0403,0x0e0d,0x0c0f,0x0a0c,0x0602},
			{0x0e04,0x0b03,0x010c,0x0a09,0x0c09,0x0008,0x0e08,0x0905,0x0800,0x0d0f,0x0904,0x0f0a,0x0705,0x080f,0x030f,0x0a06},
			{0x0407,0x0007,0x0a07,0x0f0c,0x0f03,0x0703,0x0107,0x0b0a,0x0803,0x0509,0x030c,0x0109,0x0e06,0x0805,0x040f,0x0a08},
			{0x0608,0x060b,0x0801,0x0b02,0x0701,0x0604,0x0d0a,0x080b,0x0f08,0x0e0b,0x000f,0x040b,0x0700,0x0506,0x090d,0x0305},
			{0x010e,0x0204,0x000e,0x050e,0x0603,0x0508,0x0d01,0x0a02,0x0205,0x0202,0x070c,0x030b,0x0001,0x0201,0x0708,0x0807},
			{0x0d04,0x0000,0x0406,0x0507,0x090f,0x0d03,0x0207,0x0502,0x040c,0x0306,0x0002,0x0e07,0x0a00,0x0c04,0x0c08,0x090e},
			{0x0e0a,0x0b0f,0x080a,0x0d02,0x0400,0x0c07,0x0308,0x0b05,0x0a03,0x0f07,0x0f02,0x0c0e,0x0f09,0x0601,0x0105,0x0a01},
			{0x0e00,0x0a0e,0x050d,0x0a04,0x090b,0x0304,0x010a,0x0505,0x0a0d,0x0903,0x0302,0x0300,0x0f05,0x080c,0x0b01,0x0e03},
			{0x010d,0x0f06,0x0e02,0x020e,0x0802,0x0606,0x0c0a,0x0600,0x0c00,0x0209,0x0203,0x0a0b,0x000d,0x0503,0x040e,0x060f},
			{0x0d05,0x0d0b,0x0307,0x0405,0x0d0e,0x0f0d,0x080e,0x020f,0x0003,0x0f0f,0x060a,0x0702,0x060d,0x060c,0x050b,0x0501},
			{0x080d,0x010b,0x0a0f,0x0902,0x0b0b,0x0d0d,0x0b0c,0x070f,0x0101,0x0d09,0x050c,0x0401,0x010f,0x0100,0x050a,0x0d08},
			{0x000a,0x0c01,0x0301,0x0808,0x0a05,0x0c0d,0x070b,0x0b0d,0x020d,0x0704,0x0d00,0x0102,0x0b08,0x0e05,0x0b04,0x0b00},
			{0x0809,0x0609,0x0907,0x040a,0x000c,0x0906,0x0707,0x070e,0x0605,0x0b09,0x0f01,0x0009,0x0c05,0x060e,0x0c06,0x0804},
			{0x0108,0x0f00,0x070d,0x0e0c,0x030a,0x0d0c,0x040d,0x0200,0x0709,0x0e0e,0x050f,0x030e,0x0d07,0x0c0b,0x0309,0x0408}
	};

    void _4byte_to_8byte(char src[4],char des[8])
	{
	    des[0] = ((src[0]&0xf0)>>4);
		des[1] = (src[0]&0x0f);

		des[2] = ((src[1]&0xf0)>>4);
		des[3] = (src[1]&0x0f);

		des[4] = ((src[2]&0xf0)>>4);
		des[5] = (src[2]&0x0f);

		des[6] = ((src[3]&0xf0)>>4);
		des[7] = (src[3]&0x0f);
	}

	void _8byte_to_4byte(char src[8],char des[4])
	{
	    des[0] = ((src[0]<<4)|src[1]);
		des[1] = ((src[2]<<4)|src[3]);
		des[2] = ((src[4]<<4)|src[5]);
		des[3] = ((src[6]<<4)|src[7]);
	}

    //字节转换成二进制  
    int ByteToBit(char ch, char bit[8]){  
        int cnt;
	    char temp;
	  
        for(cnt = 0;cnt < 8; cnt++){  
		    temp = (((ch<<cnt)&0x80)>>7);
		    *(bit+cnt) =  temp;	  
        } 
		 
        return 0;  
    }  
	
  
    //二进制转换成字节  
    int BitToByte(char bit[8],char *ch){  
        int cnt;  

        for(cnt = 0;cnt < 8; cnt++){  
		    *ch |= *(bit + cnt)<<(7-cnt); 
        } 
		 
        return 0;  
    } 
	 	 
	 //16进制转二进制
    char* _16_to_2(char hexString[8],char bit[64]){  
        int cnt;  
	    
        for(cnt = 0; cnt < 8; cnt++){   
			ByteToBit(*(hexString+cnt),bit+(cnt<<3));  
        }  

        return bit;  
    }  

	char* _16_to_2_2(char hexString[4],char bit[32]){  
        int cnt;  
	    
        for(cnt = 0; cnt < 4; cnt++){   
			ByteToBit(*(hexString+cnt),bit+(cnt<<3));  
        }  

        return bit;  
    }  
	 //二进制转16进制
    char* _2_to_16(char *bit,char *ch){  
        int cnt; 

        memset(ch,0,8);  
        for(cnt = 0; cnt < 8; cnt++){  
            BitToByte(bit+(cnt<<3),ch+cnt);  
        }  

        return ch;  
    }  

	char* _2_to_16_2(char *bit,char *ch){  
        int cnt; 

        memset(ch,0,4);  //改为memset(ch,0,4);
        for(cnt = 0; cnt < 4; cnt++){  
            BitToByte(bit+(cnt<<3),ch+cnt);  
        }  

        return ch;  
    }  

	//二进制异或
	int _2_to_xor(char *R, char *L ,int count){  
        int cnt;  

        for(cnt = 0; cnt < count; cnt++){  
            R[cnt] ^= L[cnt];  
        }
	  
        return 0;  
    }  

	//16进制异或(先16进制转换为2进制，异或后，再转换成16进制)
    static char* _16_to_xor(char *a,char *b,char *e){
	    char c[64],d[64];

		_16_to_2(a,c);

		_16_to_2(b,d);

		_2_to_xor(c,d,64); 

		return _2_to_16(c,e);
    }
	
	//16进制循环左移多少位(先16进制转换为2进制，左移后，再转换成16进制)
    static char* _16_left(char a[8],int b,char e[8]){

		char c[32];
		char d[4];
		char f[4];
		
		char aL[32],ar[32];
		memset(aL,0,32);  
		memset(ar,0,32);  

		d[0] = ((a[0]<<4)|a[1]);
		d[1] = ((a[2]<<4)|a[3]);
		d[2] = ((a[4]<<4)|a[5]);
		d[3] = ((a[6]<<4)|a[7]);

		_16_to_2_2(d,c);

		memcpy(aL,c,b);
	
		memcpy(ar,c+b,32-b);

		memcpy(ar+32-b,aL,b);

	    _2_to_16_2(ar,f);
	
		e[0] = ((f[0]&0xf0)>>4);
		e[1] = (f[0]&0x0f);

		e[2] = ((f[1]&0xf0)>>4);
		e[3] = (f[1]&0x0f);

		e[4] = ((f[2]&0xf0)>>4);
		e[5] = (f[2]&0x0f);

		e[6] = ((f[3]&0xf0)>>4);
		e[7] = (f[3]&0x0f);

		return e;
    }

	//S盒置换16进制
    static uint16_t sbox(char *a){
		uint8_t i1 = 0;
		uint8_t i2 = 0;

		char a1 = a[0];
		char a2 = a[1];

		if(a1==0x0a){
			i1 = 10;
		}else if(a1==0x0b){
			i1 = 11;
		}else if(a1==0x0c){
			i1 = 12;
		}else if(a1==0x0d){
			i1 = 13;
		}else if(a1==0x0e){
			i1 = 14;
		}else if(a1==0x0f){
			i1 = 15;
		}else{
			i1 = a1;
		}
		if(a2==0x0a){
			i2 = 10;
		}else if(a2==0x0b){
			i2 = 11;
		}else if(a2==0x0c){
			i2 = 12;
		}else if(a2==0x0d){
			i2 = 13;
		}else if(a2==0x0e){
			i2 = 14;
		}else if(a2==0x0f){
			i2 = 15;
		}else{
			i2 = a2;
		}

		return S[i1][i2];
	}

	//T函数	 
    static char* getT(char *a,char *b){

        char aa0[2],aa1[2],aa2[2],aa3[2];
		char dd[8];
		char b1[8],b2[8],b3[8],b4[8],b5[8];

		memcpy(aa0,a,2);
		memcpy(aa1,a+2,2);
		memcpy(aa2,a+4,2);
		memcpy(aa3,a+6,2);

	    dd[0] = (uint8_t)((sbox(aa0)&0xff00)>>8);
		dd[1] = (uint8_t)(sbox(aa0)&0x00ff);
		dd[2] = (uint8_t)((sbox(aa1)&0xff00)>>8);
		dd[3] = (uint8_t)(sbox(aa1)&0x00ff);

		dd[4] = (uint8_t)((sbox(aa2)&0xff00)>>8);
		dd[5] = (uint8_t)(sbox(aa2)&0x00ff);
		dd[6] = (uint8_t)((sbox(aa3)&0xff00)>>8);
		dd[7] = (uint8_t)(sbox(aa3)&0x00ff);

		memcpy(b1,dd,8);

		_16_left(b1,2,b2);
		_16_left(b1,10,b3); 
		_16_left(b1,18,b4);
		_16_left(b1,24,b5);
		
	    _16_to_xor(b1,b2,b);
		_16_to_xor(b,b3,b);
		_16_to_xor(b,b4,b);	
		_16_to_xor(b,b5,b);

		return b;
	}

	
	//根据128位换算成16进制的加密密钥32个长度得到轮密钥
    void getRK(char *mk){
	    char MK[4][8];
		char K[8][8];
		int i=0;
		
		memcpy(MK[0],mk,8);
		_16_to_xor(MK[0],FK,K[0]);

		for( i=0;i<5;i++){
		    _16_to_xor(K[i],CK[i],K[i+1]);
			memcpy(rK[i],K[i+1],8);//可换为memcpy(rK[i],K[i+1],8);
		}
	}
	
	//解密算法   传入的参数都是4字节转换成16进制的数据
    void decrypt(char ciphertext[8],char key[8],char plaintext[8]){
		
		char X[7][8];
		char b[8];
		int i=0; 

		getRK(key);

		memcpy(X[0],ciphertext,8);

		for( i=0;i<5;i++){ 
			getT(rK[4-i],b);
			_16_to_xor(X[i],b,X[i+1]);	
		}

		memcpy(plaintext,X[5],8);
	}

	//加密算法
    void encryption(char plaintext[8],char key[8],char ciphertext[8]){	
		char X[7][8];
		int i=0;
		char b[8];
	
		getRK(key);

	    memcpy(X[0],plaintext,8);

		for( i=0;i<5;i++){
			getT(rK[i],b);
			_16_to_xor(X[i],b,X[i+1]);	
		}

		memcpy(ciphertext,X[5],8);
	}

	




	


	
	  
	   
