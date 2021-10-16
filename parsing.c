#include "minishell.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	j;
	unsigned long	k;

	k = 1;
	j = 0;
	if (n == 0)
		return (0);
	while ((s1[j] != '\0' && s2[j] != '\0') && (k < n))
	{
		if (s1[j] == s2[j])
		{
			j++;
		}
		k++;
	}
	return ((unsigned char)s1[j] - (unsigned char)s2[j]);
}

void append(t_linked_list **head_ref, void *data)
{
	/* 1. allocate node */
	t_linked_list * new_node = (t_linked_list *) malloc(sizeof(t_linked_list));
	t_linked_list *last = *head_ref;  /* used in step 5*/
	/* 2. put in the data  */
	new_node->data = (void *)data;
	new_node->next = NULL;
	/* 4. If the Linked List is empty, then make the new node as head */
	if (*head_ref == NULL)
	{
		*head_ref = new_node;
		return;
	} 
	/* 5. Else traverse till the last node */
	while (last->next != NULL)
		last = last->next;
	/* 6. Change the next of last node */
	last->next = new_node;
	return;   
}
void				*free_pre(char **split, int k)
{
	while (k >= 0)
	{
		free(split[k]);
		k--;
	}
	free(split);
	split = NULL;
	return (NULL);
}

static	int		len_word(const char *s, char c)
{
	int	i;
	size_t	len;

	i = 0;
	len = 0;
	while (s[i] == c)
		i++;
	if (s[i] =='"')
		len++;
		while(s[++i] != '"')
			len++;
	while (s[++i] != c && s[i])
	{
		if (s[i] == '"')
		{
			len++;
			while(s[++i] != '"' )
				len++;
		}
		else if (s[i] != c && s[i])
			len++;
	} 
	return (len);
}
static	int		count_word(const char *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
			count++;
		if (s[i] == '"')
		{
			i++;
			while(s[i] != '"')
				i++;
		}
		while (s[i] != c && s[i + 1])
			i++;
		i++;
	}
	return (count);
}

int		splithelper(int i, const char *s, int k, char **split, char c)
{
	int j;

	split[i] = (char *)malloc(sizeof(char)
						* (len_word(&s[k], c) + 1));
			//return ((free_pre(split, k - 1)));
		j = 0;
		while (s[k] == c)
			k++;
		while (s[k] != c && s[k])
		{
			if (s[k] == '"')
			{
				split[i][j] = s[k];
				k++;
				j++;
				while (s[k] != '"')
					split[i][j++] = s[k++];                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
			}
			split[i][j] = s[k];
			j++;
			k++;
			if (s[k] == '"')
			{
				split[i][j] = s[k];
				while (s[++k] != '"')
					split[i][++j] = s[k];
			}
		}
	 	split[i][j] = '\0';
		return(k);
}
char				**ft_split(char const *s, char c)
{
	int	i;
	//size_t	j;
	size_t	k;
	char	**split;

	i = -1;
	k = 0;
	if (!s || !(split = (char **)malloc(sizeof(char *)
					* (count_word(s, c) + 1))))
		return (NULL);
	while (++i < count_word(s, c))
	{
		k = splithelper(i , s, k , split, c);
	}	
	split[i] = NULL;
	return (split);
}
int     findtype(char *s)
{
	if (ft_strncmp(s, "|",ft_strlen(s) ) == 0)
		return(1);
	//pipe == 1
	if (ft_strncmp(s, "<",ft_strlen(s)) == 0)
		return(2);
	//redirection input
	if (ft_strncmp(s, ">",ft_strlen(s) ) == 0)
		return(3);
	//redirection output
	if (ft_strncmp(s, ">>",  ft_strlen(s) + 1) == 0)
		return(4);
	if (ft_strncmp(s, "<<",  ft_strlen(s) + 1) == 0)
		return(5);
	return(0);
	//Appending Redirected Output

}
t_linked_list *parser(t_linked_list *lexer){ 
	t_linked_list *head = NULL;
	t_command *command;
	t_file *token;

	command = (t_command *)malloc(sizeof(t_command));
	command->files = NULL;
	command->nameargs = NULL;
	
	while (lexer) {
		printf("%d --  %s \n",((t_file*)lexer->data)->type,((t_file*)lexer->data)->file);
		token = (t_file *)lexer->data;
		if (token->type == 0) 
		{
			token->file = (void *)strdup((char *)token->file);
			append(&(command->nameargs), (void *)token->file);
		}
		else if (token->type != 0  && token->type != 1 && (lexer->next) && ((t_file *)(lexer->next->data))->type == 0){
			t_file *f;
			t_file *tmp = (t_file *)(lexer->next->data);
			f = (t_file *)malloc(sizeof(t_file));
			f->file = strdup(tmp->file);
			f->file = tmp->file;
			f->type = tmp->type;
			append(&(command->files), (void*)f);
			lexer = lexer->next;
		}
		else if (token->type != 1)
			printf("error\n");
		if (token->type == 1 || lexer->next == NULL)
			append(&(head),(void*)command);
		lexer = lexer->next;
	}
	return (head);
}

int    main()
{
	int i;                                    
	char *buffer;
	int n;
	int type;
	char **split;
//	char *string = "dsadsadasd";

	type = 0;
	split = NULL;
	t_linked_list *head =NULL;
	t_linked_list *Parser = NULL;
//	t_linked_list *shite;

//	shite = malloc(sizeof(t_linked_list));
	//shite->data = (void*)string;
//	printf("%s",(char*)string);
//	t_linked_list *nameargs2;
	i = 0;
	write(1, "Minishell:0.0> ", 15);
	buffer = malloc(sizeof(char) * (1025));
	n = read(STDIN_FILENO, buffer, 1024);
	buffer[n - 1] = '\0';
	split = ft_split(buffer, ' ');
	n = 0;
	while (split[n])
	{
		printf("%s\n",split[n]);
		n++;
	}
	n = 0;
	t_file *file2 = NULL;
	while (split[n]){
		file2 = (t_file *)malloc(sizeof(t_file));
		type = findtype(split[n]);
		file2->file = split[n];
		file2->type = type;
		append(&head, file2);
		n++;
	}
	t_linked_list *ptr;

	Parser = parser(head);
	ptr = (Parser);
	t_linked_list *Sl;
	Sl = ((t_command*)ptr->data)->nameargs;

	while (Sl != NULL)
	{
		printf("%s-- \n",(char *)Sl->data) ;
		Sl = Sl->next;
	}
	t_linked_list *Zl;
	Zl = ((t_command*)ptr->data)->files;
	while (Zl != NULL)
	{	
		printf("%s--|\n",((t_file*)Zl->data)->file) ;
		Zl = Zl->next;
	}
	return(0);

}

