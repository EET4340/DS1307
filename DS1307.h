/* 
 * File:   DS1307.h
 * Author: bmcgarvey
 *
 * Created on October 17, 2017, 9:49 AM
 */

#ifndef DS1307_H
#define	DS1307_H

#include <stdbool.h>

/*
 * Connections
 * Uses MSSP2
 * SCL = RD6
 * SDA = RD5
 * Pullups are already on the clock board
 */

#define I2C_ADDRESS 0b11010000
#define SW_1HZ      0
#define SW_4K       1
#define SW_8K       2
#define SW_32K      3

typedef union {

    struct {
        unsigned int seconds : 4;
        unsigned int seconds10 : 3;
        unsigned int CH : 1;
        unsigned int minutes : 4;
        unsigned int minutes10 : 4;
        unsigned int hour : 4;
        unsigned int hour10: 1;
        unsigned int AM_PM : 1;
        unsigned int _12_24 : 1;
        unsigned int : 1;
        unsigned int day : 3;
        unsigned int : 5;
        unsigned int date : 4;
        unsigned int date10 : 2;
        unsigned int : 2;
        unsigned int month : 4;
        unsigned int month10 : 1;
        unsigned int : 3;
        unsigned int year : 4;
        unsigned int year10 : 4;
    };
    unsigned char bytes[7];
} DateTime;

#ifdef	__cplusplus
extern "C" {
#endif

    void InitDS1307(void);
    unsigned char ReadClockRegister(unsigned char address);
    void WriteClockRegister(unsigned char address, unsigned char data);
    void ReadClockBytes(unsigned char address, unsigned char *buffer, int len);
    void WriteClockBytes(unsigned char address, unsigned char *buffer, int len);
    void ReadClock(DateTime *data);
    void SetClock(DateTime *data);
    void FormatDate(DateTime date, char *str, bool useDOW);
    void FormatTime(DateTime time, char *str);
    void FillTime(DateTime *dt, int hour, int minutes, int seconds, bool pm, bool _12hour);
    void FillDate(DateTime *dt, int month, int date, int year, int dayOfWeek);
    void EnableSWOut(bool out, unsigned char freq);
#ifdef	__cplusplus
}
#endif

#endif	/* DS1307_H */

