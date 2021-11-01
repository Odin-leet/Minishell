#include "minishell.h"

void whoexec()
{

}

int exec(t_linked_list *head)
{
	int i;

	i = 0;
	t_linked_list *lcmd;
	t_linked_list *lfile;
	
	while (head != NULL)
	{
		lcmd = ((t_command*)head->data)->nameargs;
		lfile = ((t_command*)head->data)->files;
		while (lcmd != NULL || lfile != NULL)
		{
			if (lcmd != NULL)
			{
				printf("-%d\ncmd : %s\n",i,(char *)lcmd->data);
				whoexec();
				lcmd = lcmd->next;
			}	
			if (lfile != NULL)
			{
				printf("- %d \nfile : %s\ntype : %d\n",i,((t_file*)lfile->data)->file,((t_file*)lfile->data)->type);
				lfile = lfile->next;
			}
			i++;
		}
		printf("there is pipe here  \n");
		head = head->next;
	}
    return 0;
}