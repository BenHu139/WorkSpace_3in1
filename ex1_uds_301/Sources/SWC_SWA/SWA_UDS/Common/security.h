/* 
*
* header file : security.h
*
* 
*/

#ifndef _SECURITY_H
#define  _SECURITY_H

/********************************************************头文件********************************************************/

#include <string.h>
#include <math.h>




/********************************************************类型定义********************************************************/

/********************************************************宏定义********************************************************/


/********************************************************全局变量声明********************************************************/
 


/********************************************************函数声明********************************************************/
 extern void _4byte_to_8byte(char src[4],char des[8]);
 extern void _8byte_to_4byte(char src[8],char des[4]);
 extern void decrypt(char ciphertext[8],char key[8],char plaintext[8]);
 extern void encryption(char plaintext[8],char key[8],char ciphertext[8]);
/********************************************************宏函数********************************************************/




 #endif




