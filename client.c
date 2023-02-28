/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parrot <parrot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 22:13:10 by parrot            #+#    #+#             */
/*   Updated: 2023/02/27 22:45:49 by parrot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_char(char c, int bit_no, int pid)
{
	while (bit_no < 8)
	{
		if ((c & (1 << bit_no)) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		bit_no++;
		usleep(1200);	
	}
}

void	check_bit(int pid, char *msg)
{
	int	i;
	int	bit_no;

	i = 0;
	while (msg[i])
	{
		bit_no = 0;
		send_char(msg[i], bit_no, pid);
		i++;
	}
}

void	sig_sent(int i)
{
	(void)i;
	ft_printf("Message sent\n");
}

int	main(int ac, char **av)
{
    pid_t	c;
    
    c = 0;
    if (ac == 3)
    {
        c = ft_atoi(av[1]);
        signal(SIGUSR1, &sig_sent);
        check_bit(c, av[2]);
        send_char('\n', 0, c);
        send_char('\0', 0, c);
    }
    else
    {
        ft_printf("ERROR\nUsage: ./client PID_SERVER MESSAGE\n");
        exit(0);
    }
}