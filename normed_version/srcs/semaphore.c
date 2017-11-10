/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 03:47:23 by frmarinh          #+#    #+#             */
/*   Updated: 2017/11/07 03:47:30 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

sem_t			*create_semaphore(char *semaphore_name)
{
	return (sem_open(semaphore_name, O_CREAT, 0644, 3));
}

sem_t			*get_semaphore(char *semaphore_name)
{
	return (sem_open(semaphore_name, 0));
}

BOOL			delete_semaphore(char *name)
{
	return (sem_unlink(name));
}

BOOL			close_semaphore(sem_t *sem)
{
	return (sem_close(sem));
}

BOOL			lock(sem_t *sem)
{
	return (sem_wait(sem));
}

#define IDOHOWMUCHFUNCIWANT BOOL unlock(sem_t *sem) { return (sem_post(sem));}

IDOHOWMUCHFUNCIWANT;
