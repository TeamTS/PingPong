#pragma once

#include "Session.h"

typedef struct tagFdSetEx
{
    u_int     fd_count = 0;						/* how many are SET? */
    SOCKET    fd_array[FD_SETSIZE];				/* an array of SOCKETs */
    Session*  session[FD_SETSIZE];				// Session

} fd_set_ex;

#define FD_CLR_EX(fd, set) do {													\
    u_int __i;																	\
    for (__i = 0; __i < ((fd_set_ex FAR *)(set))->fd_count ; __i++) {			\
        if (((fd_set_ex FAR *)(set))->fd_array[__i] == fd) {					\
            while (__i < ((fd_set_ex FAR *)(set))->fd_count-1) {				\
                ((fd_set_ex FAR *)(set))->fd_array[__i] =						\
                    ((fd_set_ex FAR *)(set))->fd_array[__i+1];					\
				((fd_set_ex FAR *)(set))->session[__i] =						\
					((fd_set_ex FAR *)(set))->session[__i+1];					\
                __i++;															\
            }																	\
            ((fd_set_ex FAR *)(set))->fd_count--;								\
            break;																\
        }																		\
    }																			\
} while(0, 0)

#define FD_SET_EX(fd, _session, set) do {										\
    u_int __i;																	\
    for (__i = 0; __i < ((fd_set_ex FAR *)(set))->fd_count; __i++) {			\
        if (((fd_set_ex FAR *)(set))->fd_array[__i] == (fd)) {					\
            break;																\
        }																		\
    }																			\
    if (__i == ((fd_set_ex FAR *)(set))->fd_count) {							\
        if (((fd_set_ex FAR *)(set))->fd_count < FD_SETSIZE) {					\
            ((fd_set_ex FAR *)(set))->fd_array[__i] = (fd);						\
            ((fd_set_ex FAR *)(set))->fd_count++;								\
			((fd_set_ex FAR *)(set))->session[__i] = _session;					\
        }																		\
    }																			\
} while(0, 0)

#define FD_ZERO_EX(set) (((fd_set_ex FAR *)(set))->fd_count=0)

#define FD_ISSET_EX(fd, set) __WSAFDIsSet((SOCKET)(fd), (fd_set FAR *)(set))