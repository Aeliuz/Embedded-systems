
#ifndef SERIAL_H_
#define SERIAL_H_

//denna filen ska fungera som den ska

/* Inkluderingsdirektiv: */
#include "definitions.h"

/******************************************************************************
* För att aktivera seriell transmission så ettställs biten TXCIE0 (Transfer 
* Channel Interrupt Enable 0) i kontrollregistret UCSR0B (USART Control and 
* Status Register 0B). 
* 
* För att sätta bithastigheten / Baud Rate för seriell överföring till 115 220 
* kbps (kilobits per second), så skrivs talet 7.67 till registret UBBR0 
* (USART Baud Rate Register 0) enligt formeln
*
* UBRR0 = F_CPU / (16 * Baud Rate) - 1 = 16M / (16 * 9600) - 1 = 104- 1,
* vilket blir 103,
*
* där F_CPU är mikrodatorns klockfrekvens och Baud Rate är önskad bithastighet.
*
* För att vänta tills eventuellt föregående tecken har transmitterats, så
* implementeras en while-sats, som exekverar så länge dataregistret UDR0
* (USART Data Register 0) inte är tomt, vilket undersöks genom att kontrollera
* biten UDRE0 (USART Data Register Empty 0) i kontroll- och statusregistret
* UCSR0A (USART Control and Status Register A), som är nollställd så länge
* dataregister UDR0 inte är tomt.
*
* För att transmittera ett vagsnreturtecken \r, vilket genomförs för att nästa
* transmitterade tecken skall hamna längst till vänster på aktuell rad, så
* anropas funktionen write_byte, där tecknet \r sätts till ingående argument.
* För att transmittera ett nolltecken \0, vilket genomförs för att indikera
* när ett givet textstycke är slut, så anropas funktionen write_byte, där
* tecknet \0 sätts till ingående argument.
*
* Vid behov av att deklarera en sträng, vilket sker då text skall sammansättas
* med ett heltal, så används makrot SIZE för att sätta strängens kapacitet
* till 5 tecken (inklusive nolltecken).
******************************************************************************/
#define ENABLE_SERIAL_TRANSMISSION SET_BIT(UCSR0B, TXEN0)	//ändrade från TXCIE0 till TXEN0
#define SET_BAUD_RATE_TO_9600_KBPS UBRR0 = 103	//ändrade baud-rate till 9600
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