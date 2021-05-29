#include <stdlib.h>
#include <string.h>

#include "serialize.h"

/* Pack the user input provided in input into the appropriate message
 * type in the space provided by packed.  You can assume that input is a
 * NUL-terminated string, and that packed is a buffer of size
 * PACKET_SIZE.
 *
 * Returns the packet type for valid input, or -1 for invalid input.
 */
int pack(void *packed, char *input)
{
    // int flag1 = 0;
    //  if(strcmp(input,"/")==0 && (strcmp(*(input+1),"m")==0) && (strcmp(input+2,"e")==0) && (strcmp(input+3," ")==0)) // Packing Status
    if(input[0]=='/' && input[1]=='m' && input[2]== 'e'&&  input[3]==' ')
    {
            //      flag1 =1;
            int i;
            int flag = 0;
            for( i=4; i<MAX_MESSAGE_SIZE;i++) //finding first non space charachter
                {
                    if(input[i]!=' ')
                        {
                            flag = 1;
                            break;
                        }
                }
            if (flag==0)   // Invalid condition of all space characters
                {
                    return -1;
                }
            int slength=0;                   //length of status message from first nonspace character till last.

            //   char copyarr[MAX_MESSAGE_SIZE];  //array to which copying status message
            //  int j=0;

            while(input[i]!='\0')
                {
                    //  copyarr[j]=input[i];   //copying array

                    slength=slength+1; // 1 2 3 4//counting status length
                    i=i+1;            //5    6 7 8

                    //   j=j+1;
                }
            i=i-slength;
            *(int*)packed = STATUS;
            packed = packed + sizeof(int);
            // *(char**)packed = "manantiw00000000";               //since rest of the bytes are null bytes and max size is 16
            // packed = packed + (sizeof(char) * NAME_SIZE);

            *(char*)packed = 'm';
            packed = packed + sizeof(char);

            *(char*)packed = 'a';
            packed = packed + sizeof(char);

            *(char*)packed = 'n';
            packed = packed + sizeof(char);

            *(char*)packed = 'a';
            packed = packed + sizeof(char);

            *(char*)packed = 'n';
            packed = packed + sizeof(char);

            *(char*)packed = 't';
            packed = packed + sizeof(char);
    
            *(char*)packed = 'i';
            packed = packed + sizeof(char);

            *(char*)packed = 'w';
            packed = packed + sizeof(char);

            for (int i=0;i<8;i++)
                {
                    *(char*)packed = 0;
                    packed = packed + sizeof(char);
                }

            *(size_t*)packed = slength;
            packed = packed + sizeof(size_t);
            *(size_t*)packed = 0;
            packed = packed + sizeof(size_t);
            while(*(input+i)!='\0')
                {
                    *(char*)packed = *(input + i);   //copying status message
                    packed = packed + sizeof(char);
                    i = i+1;
                }
            // packed = packed + (sizeof(char) * slength);

            return STATUS;

        }

    if(input[0]=='@' && input[1] != ' ')  // Packing Labeled
        {
            int i;
            //int flag = 0;
            // int flag1 = 0;
            size_t count=0; //target length
            for(i=1;i<=NAME_SIZE+1;i++)
                {
                    if(input[i]==' ') //finding the first space position, the target ends at i-1
                        {
                            break;
                        }

                    count = count + 1; //target length

                    if(i==17 && input[i]!=' ') //the username exceeds the limit of 16 char (NAME_SIZE)

                        {
                            return -1;
                        }
                }

            /*for(int k=i; k<MAX_MESSAGE_SIZE; k++)
                {
                    if(input[k]!=' ')
                        {
                            flag1= 1;
                            break;
                        }
                }
            if(flag1==0)  // all the characters in the message are spaces
                {
                    return -1;
                    }*/

            *(int*)packed = LABELED;
            packed = packed + sizeof(int);
            // *(char**)packed = "manantiw00000000";//since rest of the bytes are null bytes and max size is 16
            // packed = packed + (sizeof(char) * NAME_SIZE);  // replaced this from packed = packed + NAME_SIZE

            *(char*)packed = 'm';
            packed = packed + sizeof(char);

            *(char*)packed = 'a';
            packed = packed + sizeof(char);

            *(char*)packed = 'n';
            packed = packed + sizeof(char);

            *(char*)packed = 'a';
            packed = packed + sizeof(char);

            *(char*)packed = 'n';
            packed = packed + sizeof(char);

            *(char*)packed = 't';
            packed = packed + sizeof(char);

            *(char*)packed = 'i';
            packed = packed + sizeof(char);

            *(char*)packed = 'w';
            packed = packed + sizeof(char);

            for (int i=0;i<8;i++)
                {
                    *(char*)packed = '\0';
                    packed = packed + sizeof(char);
                }

            int mlength=0;
            int np;

            for(int a = count + 2; a<MAX_MESSAGE_SIZE; a++) //first nonspace character after target length
                {
                    if(input[a]!= ' ')
                        {
                           np = a;
                            break;
                        }
                }
            int b = np;
            while(input[b] != '\0')  // np is the first  space position after ubit 
                {
                    //  copyarr[j]=input[i];   //copying array

                    mlength=mlength+1;    //counting message length
                    b=b+1;

                    //   j=j+1;
                }

            *(size_t*)packed = mlength;
            packed = packed + sizeof(size_t);

            int tlength = count;   //Target Length
            *(size_t*)packed = tlength;
            packed = packed + sizeof(size_t);

            *(size_t*)packed = 0;
            packed = packed + sizeof(size_t);

            while(*(input+np)!='\0')
                {
                    *(char*)packed = *(input + np);   //copying message to target
                    packed = packed + sizeof(char);
                    np = np + 1;
                }
            //  packed = packed + (sizeof(char) * mlength);

            for(int j=1; j<tlength+1;j++)
                {
                    *(char*)packed = *(input+j);
                    packed = packed + sizeof(char);
                }

            /*     int j = 1;
             while(*(input+j)  != ' ')  // copying the target (ubitname)
                {
                    *(char*)packed = *(input +j);
                    packed = packed + sizeof(char);
                    j = j+1;
                    }*/

            return LABELED;
        }

    if(input[0]=='/' && input[1]=='s' && input[2]=='t' && input[3]=='a' &&  input[4]=='t' && input[5]=='s')
        {
            if(*(input+6)!='\0')   // no input after "/stats"
                {
                    return -1;
                }
            *(int*)packed = STATISTICS;
            packed = packed + sizeof(int);
            
            *(char*)packed = 'm';
            packed = packed + sizeof(char);
            
            *(char*)packed = 'a';
            packed = packed + sizeof(char);
            
            *(char*)packed = 'n';
            packed = packed + sizeof(char);
            
            *(char*)packed = 'a';
            packed = packed + sizeof(char);
            
            *(char*)packed = 'n';
            packed = packed + sizeof(char);
            
            *(char*)packed = 't';
            packed = packed + sizeof(char);
            
            *(char*)packed = 'i';
            packed = packed + sizeof(char);
            
            *(char*)packed = 'w';
            packed = packed + sizeof(char);
            
            for (int i=0;i<8;i++)
                {
                    *(char*)packed = '\0';
                    packed = packed + sizeof(char);
                }



            // *(char**)packed = "manantiw00000000";
            //packed = packed+(sizeof(char) * NAME_SIZE);

            return STATISTICS;
        }

    else ////(input[0]!='/' && input[0]!='@') // Message Packet   IMPROVE/ADD IF CONDTS
        {
            
            int dlength=0;
            int i=0;
            int flag = 0;

            while(input[i]!='\0') //counting message length
                {
                    dlength = dlength + 1;
                    i++;
                }

            if(dlength>MAX_MESSAGE_SIZE) // sum of all data lengths should not be greater than MAX_MESSAGE_SIZE
                {
                    return -1;
                }

            for(i=0;i<dlength;i++)   //checking if all characters in message are spaces
                {
                    if(input[i]!=' ')
                        {
                            flag = 1;
                            break;
                        }
                }

            if(flag==0)
                {
                    return -1;
                }

            *(int*)packed = MESSAGE;
            packed = packed + sizeof(int);

            *(char*)packed = 'm';
            packed = packed + sizeof(char);
            
            *(char*)packed = 'a';
            packed = packed + sizeof(char);
            
            *(char*)packed = 'n';
            packed = packed + sizeof(char);
            
            *(char*)packed = 'a';
            packed = packed + sizeof(char);
            
            *(char*)packed = 'n';
            packed = packed + sizeof(char);

            *(char*)packed = 't';
            packed = packed + sizeof(char);
            
            *(char*)packed = 'i';
            packed = packed + sizeof(char);
            
            *(char*)packed = 'w';
            packed = packed + sizeof(char);
            
            for (int i=0;i<8;i++)
                {
                    *(char*)packed = 0;
                    packed = packed + sizeof(char);
        }

            // *(char**)packed = "manantiw00000000";
            // packed = packed + (sizeof(char) * NAME_SIZE);

            *(size_t*)packed = dlength;
            packed = packed + sizeof(size_t);

            *(size_t*)packed = 0;
            packed = packed + sizeof(size_t);

            for(i=0;i<dlength;i++)   // Copying Data to packed
                {
                    *(char*)packed = input[i];
                    packed = packed + sizeof(char);
                }
            return MESSAGE;
        }

    return -1;
}

/* Create a refresh packet for the given message ID.  You can assume
 * that packed is a buffer of size PACKET_SIZE.
 *
 * You should start by implementing this method!
 *
 * Returns the packet type.
 */
int pack_refresh(void *packed, int message_id)
{
    *(int*)packed = REFRESH;
    packed = packed + sizeof(int);

    *(char*)packed = 'm';
    packed = packed + sizeof(char);

    *(char*)packed = 'a';
    packed = packed + sizeof(char);

    *(char*)packed = 'n';
    packed = packed + sizeof(char);

    *(char*)packed = 'a';
    packed = packed + sizeof(char);

    *(char*)packed = 'n';
    packed = packed + sizeof(char);

    *(char*)packed = 't';
    packed = packed + sizeof(char);

    *(char*)packed = 'i';
    packed = packed + sizeof(char);

    *(char*)packed = 'w';
    packed = packed + sizeof(char);

    for (int i=0;i<8;i++)
        {
            *(char*)packed = 0;
            packed = packed + sizeof(char);
        }

    //*(char**)packed = "manantiw00000000";
    //acked = (packed + sizeof(char) * NAME_SIZE);

    *(int*)packed = message_id;
    packed = packed + sizeof(int);

    return REFRESH;
}
