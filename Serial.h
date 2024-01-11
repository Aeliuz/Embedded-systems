
#ifndef SERIAL_H_
#define SERIAL_H_

//denna filen ska fungera som den ska

/* Inkluderingsdirektiv: */
#include "definitions.h"

/******************************************************************************
* F�r att aktivera seriell transmission s� ettst�lls biten TXCIE0 (Transfer 
* Channel Interrupt Enable 0) i kontrollregistret UCSR0B (USART Control and 
* Status Register 0B). 
* 
* F�r att s�tta bithastigheten / Baud Rate f�r seriell �verf�ring till 115 220 
* kbps (kilobits per second), s� skrivs talet 7.67 till registret UBBR0 
* (USART Baud Rate Register 0) enligt formeln
*
* UBRR0 = F_CPU / (16 * Baud Rate) - 1 = 16M / (16 * 9600) - 1 = 104- 1,
* vilket blir 103,
*
* d�r F_CPU �r mikrodatorns klockfrekvens och Baud Rate �r �nskad bithastighet.
*
* F�r att v�nta tills eventuellt f�reg�ende tecken har transmitterats, s�
* implementeras en while-sats, som exekverar s� l�nge dataregistret UDR0
* (USART Data Register 0) inte �r tomt, vilket unders�ks genom att kontrollera
* biten UDRE0 (USART Data Register Empty 0) i kontroll- och statusregistret
* UCSR0A (USART Control and Status Register A), som �r nollst�lld s� l�nge
* dataregister UDR0 inte �r tomt.
*
* F�r att transmittera ett vagsnreturtecken \r, vilket genomf�rs f�r att n�sta
* transmitterade tecken skall hamna l�ngst till v�nster p� aktuell rad, s�
* anropas funktionen write_byte, d�r tecknet \r s�tts till ing�ende argument.
* F�r att transmittera ett nolltecken \0, vilket genomf�rs f�r att indikera
* n�r ett givet textstycke �r slut, s� anropas funktionen write_byte, d�r
* tecknet \0 s�tts till ing�ende argument.
*
* Vid behov av att deklarera en str�ng, vilket sker d� text skall sammans�ttas
* med ett heltal, s� anv�nds makrot SIZE f�r att s�tta str�ngens kapacitet
* till 5 tecken (inklusive nolltecken).
******************************************************************************/
#define ENABLE_SERIAL_TRANSMISSION SET_BIT(UCSR0B, TXEN0)	//�ndrade fr�n TXCIE0 till TXEN0
#define SET_BAUD_RATE_TO_9600_KBPS UBRR0 = 103	//�ndrade baud-rate till 9600
#define SET_CHARACTER_SIZE_TO_8_BITS UCSR0C = ((1 << UCSZ00) | (1 << UCSZ01))
#define WAIT_FOR_PREVIOUS_TRANSMISSION_TO_FINISH while ((UCSR0A & (1 << UDRE0)) == 0)
#define CARRIAGE_RETURN write_byte('\r')
#define END_TRANSMISSION write_byte('\0')
#define SIZE 50

/* Funktionsdeklarationer: */
void init_serial(void);
void serial_print(char* s);
void serial_print_integer(char* s, const int32_t number);
void serial_print_unsigned(char* s, const uint32_t number);


#endif /* SERIAL_H_ */