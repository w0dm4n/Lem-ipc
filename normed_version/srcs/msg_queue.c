/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_queue.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 08:34:48 by frmarinh          #+#    #+#             */
/*   Updated: 2017/11/10 08:34:53 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void		delete_all_messages_queues(void)
{
	int		msq_id;

	if ((msq_id = msgget(convert_to_key(MSGQ_KEY), 0666)) != -1)
		msgctl(msq_id, IPC_RMID, NULL);
}

int			create_message_queue(void)
{
	return (msgget(convert_to_key(MSGQ_KEY), IPC_CREAT | 0666));
}

int			get_message_queue(void)
{
	return (msgget(convert_to_key(MSGQ_KEY), 0666));
}

#define VARS msq_id, msg, ft_strlen(msg->m_text), IPC_NOWAIT
#define STRING "Something went wrong while sending a message queue:"

int			send_message_queue(int msq_id, t_msg_buf *msg)
{
	int		result;

	if ((result = msgsnd(VARS)) == MSQ_ERROR)
		printf("%s %s\n", STRING, strerror(errno));
	return (result);
}

void		build_message(int type, char *data, t_msg_buf *msg)
{
	msg->m_type = type;
	ft_strcpy(msg->m_text, data);
}
