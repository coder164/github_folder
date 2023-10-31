#ifndef __ERRSTAT_H__
#define __ERRSTAT_H__
/* 
Author: Lev.
Purpose: Define general errors and statuses for the 'Heart' project.
Date: 31-12-22.
*/

typedef enum ERRStat{
    FALSE = -1,
    ERROR_OK = 0,
    TRUE = 1,
    ERROR_POINTER_NULL,
    ERROR_NUM_PLAYERS,
    ERROR_ALLOCATION_FAILED,
    ERROR_TYPE,
    ERROR_SUCCESS,
    ERROR_SAME_ARGUMENT,
    ERROR_OUT_OF_MEMMORY,
    ERROR_GENERAL
} ERRStat;

#endif /* #ifndef __ERRSTAT_H__ */
