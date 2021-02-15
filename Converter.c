#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<math.h>

void printbinary(int number)
{
        for(int i=31;i>=0;i--)  // starting a loop so that go through each bit of 32 bits representation, i is set to 31 because we want to print in the correct order from MSB to LSB
            {
                printf("%d",( (number & (int)pow(2,i)) ? 1 : 0) ); // Doing bitwise ANDing  for each bit of the variable number with 2^i,
                                                                //thus verifying is a bit on position i of the variable number is set either to ONE or ZERO.
                                                                // Next, if it is positive value then return 1, if it is ZERO then return 0.
            }
            printf("\n"); // adding a new line

   return;
}


void convert_binary_to_signed(char *binary)
{
    int sign=((*binary == '0')? 0 : 1) ;  // Checking the sign of the binary number. 0 means positive and 1 means negative
    int number=0;   // variable for storing the result
    int bits=0;     // keeps the number of bits
    char *b = binary; // keep the starting address of the string

    for(bits;*binary!='\0';bits++)   // calculating the number of entered bits
            binary++;

   bits--; // because positions start at 0, like in an array
   binary=b; // restoring initial address of the pointer binary because now it points at '\0' due to the loop above

    if(sign){  // if we get the negative number then we have to properly convert two's complementary

        for(int i=bits;i>=0;i--) // converting binary number
              *(binary+i) =  *(binary+i)== '1' ? '0' : '1' ;

         if(*(binary+bits)!='0'){ // if LSB is not 0 we have to take care of possible carry out after adding 1
               *(binary+bits)='0';  // setting LSB to 0 because in binary adding 1+1=0
               int i=bits-1;   // moving to the next bit
               char carry_out='1';  // setting carry out after 1+1
                    while(carry_out!='0'){ // checking if there is a carry out
                            if(*(binary+i)=='1'){ // if next bit is also 1 then set it to 0 and keep carry out
                                    *(binary+i)='0'; // setting it to zero
                                    i--; // moving to the next bit
                                    }
                            else{ // if we have 1+0 case then there is no carry out
                                 *(binary+i)=carry_out; // set the current bit to carry out
                                 carry_out='0'; // set carry out to zero
                            }
                    }

            }
        else
            *(binary+bits)='1'; // if  overflow does not occur while adding 1 then just LSB to 1
    }

    for(bits;bits>=0;bits--){  // simple loop to convert binary representation to decimal
            number=number+((*binary == '1' ? 1 : 0) * pow(2,bits)); // first, identifying the bit state pointed to by binary,  next multiply by 2^i and add the result
             binary++;  // moving pointer binary to the next character
                }

    number=number *( sign == 1 ? -1 : 1); // adding sign to the result
    printf("Converted value is %d\n",number); // printing the result

   return;
}


void convert_binary_to_float(char *binary)
{
    float number=0; // variable for storing the result
    int sign=((*binary == '0')? 0 : 1) ; // Checking the sign of the binary number. 0 means positive and 1 means negative
    int E=0; // for keeping Exponent

    for(int i=1,j=7;i<=8;i++,j--)
        E= E + (*(binary+i) == '0' ? 0 : 1) * pow(2,j); // calculating an exponent


       if(E!=0)  // For Normalized case
            number=1; //setting lead digit to 1
        else            // For De-Normalized case
            number =0; // To represent 0 or some really small numbers

    for(int i=9,p=-1;i<=31;i++,p--) // calculating Fraction part of the 32 bit number
        number=number+((*(binary+i) == '1' ? 1 : 0) * pow(2,p));

    number=number*pow(2,E-127);   // multiplying by exponent
    number=number *( sign == 1 ? -1 : 1);  // assigning the sign
    printf("%lf",number);   // printing the result
   return;
}

int  main(){

    char binary[]="0101010011";
    char binary_float[]="11000001010001110100000001001111";
    int x=10;
    int y=-10;

    printf("%d in binary:",x);
    printbinary(x);
    printf("\n\n%d in binary:",y);
    printbinary(y);
    printf("\n\nbinary:%s ",binary);
    convert_binary_to_signed(binary);
    printf("\n\nfloat binary:%s\t float: ",binary_float);
    convert_binary_to_float(binary_float);





return 0;
}
