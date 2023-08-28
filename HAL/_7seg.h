/*
 * _7seg.h
 *
 * Created: 21/09/2021 02:47:52 PM
 *  Author: Mohamed Sherif
 */ 

#ifndef _7SEG_H_
#define _7SEG_H_

/*
Function Name        : _7seg_vinit
Function Returns     : void
Function Arguments   : unsigned char port
Function Description : Initialize the PORT as an output PORT to connect the 7 Segment.
*/
void _7seg_vinit(unsigned char port);

/*
Function Name        : _7seg_vwrite
Function Returns     : void
Function Arguments   : unsigned char port,unsigned char number
Function Description : Write the number to all port pins.
*/
void _7seg_vwrite(unsigned char port,unsigned char number);

#endif /* _7SEG_H_ */