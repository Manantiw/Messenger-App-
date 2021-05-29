#include <stdlib.h>
#include <string.h>

#include "serialize.h"

/* Unpack the given packet into the buffer unpacked.  You can assume
 * that packed points to a packet buffer large enough to hold the
 * packet described therein, but you cannot assume that the packet is
 * otherwise valid.  You can assume that unpacked points to a character
 * buffer large enough to store the unpacked packet, if it is a valid
 * packet.
 *
 * Returns the packet type that was unpacked, or -1 if it is invalid.
 */
int unpack(char *unpacked, void *packed)
{
    if(*(int*)packed == MESSAGE)            //UNPACKING MESSAGE
        {
            packed = packed + sizeof(int);
            int namesize=0;
            for(int i=0;*((char*)packed+i)!='\0';i++)
                {
                    namesize=namesize+1; //ubit name length
                }
            int i = 0;
            //   int j = 0;
            // int k = 0;
            for(i=0; i<namesize;i++)  //copying ubit
                {
                    /* if(*((char*)packed + i) == '0') //not copying the null bytes ?
                        {
                            break;
                            }*/
                    //  j = i;
                    *(unpacked + i) = *((char*)packed + i);
                }
            unpacked = unpacked + (sizeof(char)*namesize);
            //   *unpacked='\0';
            // unpacked = unpacked + sizeof(char);

            *unpacked = ':';
            unpacked = unpacked + sizeof(char);

            *unpacked = ' ';
            unpacked = unpacked + sizeof(char);

            packed = packed + (sizeof(char)*NAME_SIZE);
            size_t size = *(size_t*)packed;   // size is the message length


            packed = packed + (sizeof(size_t)*2);

             while(size>0)
                {
                    *unpacked = *(char*)packed;
                    packed = packed + sizeof(char);
                    unpacked = unpacked + sizeof(char);
                    size=size-1;
                }
             *unpacked='\0';
             unpacked = unpacked +sizeof(char);
            return MESSAGE;
        }

    if(*(int*)packed == STATUS)               //UNPACKING STATUS
        {
            packed = packed + sizeof(int);
            int namesize=0;
            for(int i=0;*((char*)packed+i)!='\0';i++)
                {
                    namesize = namesize+1;
                }
            int i = 0;
            // int j = 0;
            // int k = 0;
             for (i=0;i<namesize;i++) // copying ubit
                 {
                    // if(*((char*)packed + i) == '0') //not copying null bytes
                        //{
                            //    break;
                            //                }
                     //  j = i;
                    *(unpacked + i)= *((char*)packed + i);
                }
            unpacked = unpacked + (sizeof(char) * namesize);
            *unpacked = ' ';
            unpacked = unpacked + sizeof(char);

            packed = packed + (sizeof(char)*NAME_SIZE);

            size_t size = *(size_t*)packed;

            packed = packed + (sizeof(size_t)*2);

            while(size>0)
                {
                    *unpacked = *(char*)packed;
                    packed = packed + sizeof(char);
                    unpacked = unpacked + sizeof(char);
                    size = size - 1;
                }
            *unpacked='\0';
            unpacked = unpacked + sizeof(char);
            return STATUS;
        }

    if(*(int*)packed == LABELED)
        {
            packed = packed + sizeof(int);
            int i;
            int namesize=0;
            // int j = 0;
            //int k = 0;
            int mlength;
            int tlength;

            for(int i=0;*((char*)packed+i)!='\0';i++)
                {
                    namesize = namesize+1;
                }

            for (i=0;i<namesize;i++)  //copying ubit
                {
                    /*   if(*((char*)packed + i) == 0) // not copying null bytes 
                        {
                            break;
                        }
                        j = i;*/
                    *(unpacked + i) = *((char*)packed + i);
                }
            unpacked = unpacked + (sizeof(char)*namesize);
            packed = packed + (sizeof(char)*NAME_SIZE);

            *unpacked = ':';
            unpacked = unpacked + sizeof(char);

            *unpacked = ' ';
            unpacked = unpacked + sizeof(char);

            *unpacked = '@';
            unpacked = unpacked + sizeof(char);

            mlength = *(size_t*)packed;
            packed = packed + sizeof(size_t);

            tlength = *(size_t*)packed;
            packed = packed + (sizeof(size_t)*2); //since last size_t type holds zero in labeled

            char arr[mlength];

            for(int z=0; z<mlength;z++) //storing the message in arr[]
                {
                    arr[z] = *((char*)packed+z);
                }

            packed = packed + (sizeof(char)*mlength);

            for(int a =0; a<tlength;a++)
                {
                    *(unpacked+a) = *((char*)packed + a);
                }
            
            unpacked = unpacked + (sizeof(char)*tlength); //incrementing unpacked till after the target

            *unpacked = ' ';  //adding space after target

            unpacked = unpacked + sizeof(char);

            //  char *message;
            // char *target;

            for(int b = 0; b<mlength;b++)
                {
                    *(unpacked + b) = *(arr + b);
                }
            unpacked = unpacked + (sizeof(char)*mlength);

            *unpacked= '\0';
            unpacked = unpacked + sizeof(char);

            /*    while(*(char*)packed != '\0') //for (k=0;k<mlength;k++) // since packed points at the message string, adding the message
                {
                    *unpacked  = *(char*)packed;
                    unpacked = unpacked + 1;
                    packed = packed + 1;
                    }

            packed = packed + (sizeof(char)*mlength);
            unpacked = unpacked - (sizeof(char)*tlength) - (sizeof(char)*2);

            for(int k=0;k<tlength;k++)
                {
                    *(unpacked+k) = *((char*)packed+k);
                    //  unpacked = unpacked + 1;
                    //  packed = packed + 1;
                    }*/

            return LABELED;

            //packed = packed + (sizeof(size_t)*3);
        }
    return -1;
}

/* Unpack the given packed packet into the given statistics structure.
 * You can assume that packed points to a packet buffer large enough to
 * hold the statistics packet, but you cannot assume that it is
 * otherwise valid.  You can assume that statistics points to a
 * statistics structure.
 *
 * Returns the packet type that was unpacked, or -1 if it is invalid.
 */
int unpack_statistics(struct statistics *statistics, void *packed)
{
    packed = packed + sizeof(int);
    // char name[NAME_SIZE+1];
    int i;
    for(i=0;i<NAME_SIZE;i++)
        {
           
            (statistics->sender[i])=*((char*)packed);
            packed = packed + 1;
        }
    
    
    
    // strcpy(statistics->sender,name);
    
    for(i=0;i<NAME_SIZE;i++)
        {
          
            (statistics->most_active[i])=*((char*)packed);
            packed = packed + 1;
        }
   
    // strcpy(statistics->most_active,name);
    i=*(int*)packed;
    packed+=sizeof(int);
    statistics->most_active_count=i;
    i=*(long*)packed;
    packed+=sizeof(long);
    statistics->invalid_count=i;
    i=*(long*)packed;
    packed+=sizeof(long);
    statistics->refresh_count=i;
    i=*(int*)packed;
    packed+=sizeof(int);
    statistics->messages_count=i;
    
    return STATISTICS;
}
