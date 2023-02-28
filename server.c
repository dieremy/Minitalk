/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parrot <parrot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 22:11:22 by parrot            #+#    #+#             */
/*   Updated: 2023/02/27 22:23:50 by parrot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
//control headerZZZ

void    sig_handler(int sig, siginfo_t *info, void *context)
{
    static int  value;
    static int  bit_no;

    (void)context;
    if (sig == SIGUSR1)
        value += 1 << bit_no;
    bit_no++;
    if (bit_no == 8)
    {
        write(1, &value, 1);
        if (value == '\0')
            kill(info->si_pid, SIGUSR1);
        value = 0;
        bit_no = 0;
    }
}

int main(void)
{
    struct sigaction    act;
    pid_t               pid;

    pid = getpid();
    ft_printf("Server attivo\nPID: [%d]\n", pid);
    act.sa_sigaction = &sig_handler;
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &act, NULL);
    sigaction(SIGUSR2, &act, NULL);
    sigemptyset(&act.sa_mask);
    while (1)
        pause();
}