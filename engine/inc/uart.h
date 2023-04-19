#ifndef _UART_H
#define _UART_H
int uart_init(void);
int set_opt(int fd);
int uart_send(int fd, char * str);
int uart_recv(int fd, char* buf);
#endif

