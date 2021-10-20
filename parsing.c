#include "minishell.h"

char	*ft_strdup(char *s1, size_t i)
{
	int		n;
	size_t	k;
	size_t	j;
	char	*dest;

	n = 0;
	j = i;
	while (s1[i++] != '\0')
		n++;
	if (!(dest = malloc((n + 1) * sizeof(char))))
		return (0);
	k = 0;
	while (s1[j] != '\0')
		dest[k++] = s1[j++];
	dest[k] = '\0';
	return (dest);
}
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
int		*traitmask(const char *s, int c)
{
	int *env = malloc(sizeof(int) * strlen(s));

	int env_sq = 0;
	int env_dq = 0;
	unsigned int  i = 0;
	unsigned int j = strlen(s);
	while (i <  j)
	{
		env[i++] = 0;
	}
	i = 0;
	while (s[i] != '\0')
	{
		if(s[i] == '\'' && env_sq == 0)
			env_sq = 1;
		else if(s[i] == '\'' && env_sq == 1)
			env_sq = 0;
		else if(s[i] == '\"' && env_dq == 0)
			env_dq = 1;
		else if (s[i] == '\"' && env_dq == 1)
			env_dq = 0;
		if (c == 1)
			env[i] = env_dq;
		else
			env[i] = env_sq;
		i++;
	}
	return(env);
}


static	int		len_word(const char *s, char c , int *in_sgl, int *in_db , int k )
{
	int	i;
	size_t	len;

	len = 0;
	i = 0;
	while (s[i] == c && s[i] != '\0' && (in_sgl[k] == 0 || in_db[k] == 0))
	{
		i++;
		k++;
	}
	while((s[i] != c && s[i] != '\0') || (s[i] == c && (in_sgl[k] == 1 || in_db[k] == 1)))
	{
			len++;
			i++;
			k++;
	}
	printf("len == %zu\n",len);
	return (len);
}

int		ft_isdigit(int c)
{
	unsigned char k;

	k = (unsigned char)c;
	if (c <= 57 && c >= 48)
		return (1);
	else
		return (0);
}

int		ft_isalpha(int c)
{
	unsigned char k;

	k = (unsigned char)c;
	if (c <= 90 && c >= 65)
		return (1);
	else
		return (0);
}
char		*replaceenv(char *string, int start, int end, char **env)
{
	int		i;
	int		j;

	j = 0;
	i = 0;

	if (end == 0)
		end = ft_strlen(string);
	string = ft_substr(string, start + 1,(end - 1 )- start);
	//string = ft_strdup(string, 1);
	string = ft_strjoin(string, "=");
	while(env[i])
	{
		if (ft_strncmp(env[i], string, ft_strlen(string) )== 0)
		{
			j = 1;
			break;
		}	
		else
			i++;
	}
	if (j == 1)
	{
		return(ft_strdup(env[i], ft_strlen(string)));
	}
	return(NULL);


}
char			*handleenvir(char *string, char **env)
{
	int i;
	char *tmp;
	char *tmp2;
	int	start;
	int end ;

	start = 0;
	tmp = NULL;
	tmp2= NULL;
	end = 0;

	i = 0;
	while(string[i] != '\0')
	{
		if (string[i] == '\'')
		return(string);
	if(string[i] == '$')
	{
		if (i != 0)
		{
			start = i;
			tmp = ft_substr(string,0, i );
		}
		i++;
		if (string[i] >= 48 && string[i] <= 57)
			return (ft_substr(string,i + 1 ,ft_strlen(string) - (i + 1)));
		else if (string[i] == '_' || (string[i] >= 65 && string[i] <= 90))
		{
			i++;
			while(string[i] != '\0')
			{
				if(string[i] != '_' && (ft_isdigit(string[i]) == 0) && (ft_isalpha(string[i]) == 0))
				{
					end = i;
					tmp2 = ft_substr(string, end, ft_strlen(string) - end);
					break;
					//printf("lol i m here \n");
				}
				else
					i++;
			}
			string = replaceenv(string,start, end, env);
			if(tmp !=NULL && string != NULL)
				string = ft_strjoin(tmp, string);
			if (tmp2 != NULL &&string != NULL)
				string = ft_strjoin(string,tmp2);
			if(string == NULL)
			{
				if(tmp != NULL && tmp2 != NULL)
				string = ft_strjoin(tmp, tmp2);
				else if(tmp != NULL && tmp2 == NULL)
				string = ft_strdup(tmp, 0);
				else
				string = ft_strdup(tmp2,0);
			}
			return(string);
			
		}
	}
	i++;
	}
	return(string);
}


static	int		count_word(char *s, char c)
{
	size_t	i;
	size_t	count = 0;
	int *in_db ;
	int *in_sgl ;
	char *t;
	t = s;

	in_db = traitmask(s, 1);
	in_sgl = traitmask(s, 0);
	i = 0;
	
	while (s[i] != '\0')
	{
		if(s[i] != c )    
			count ++;
		while((s[i] != c && s[i] != '\0') || (s[i] == c && (*in_sgl == 1 || *in_db == 1)))
		{
			i++;
			in_sgl++;
			in_db++;
		}
		if(s[i] != '\0')
		{
			i++;  
			in_sgl++;
			in_db++;
		}
	}
	return (count);
}

int		splithelper(int i, const char *s, int k, char **split, char c)
{
	unsigned long j;
	int *in_db ;
	int *in_sgl ;

	in_db = traitmask(s, 1);
	in_sgl = traitmask(s, 0);
	split[i] = (char *)malloc(sizeof(char)
			* (len_word(&s[k], c, in_sgl, in_db, k)  + 1));
	j = 0;

	while (s[k] == c && (in_sgl[k] == 0 || in_db[k] == 0))
		k++;
	while((s[k] != c && s[k] != '\0') || (s[k] == c && (in_sgl[k] == 1 || in_db[k] == 1)))
	{
			split[i][j] = s[k];
			k++;
			j++;
	}
	split[i][j] = '\0';
	return(k);
}
char				**ft_split(char *s, char c)
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

}
t_linked_list *parser(t_linked_list *lexer , char **env){ 
	t_linked_list *head = NULL;
	t_command *command;
	t_file *token;

	command = (t_command *)malloc(sizeof(t_command));
	command->files = NULL;
	command->nameargs = NULL;

	while (lexer) {
		token = (t_file *)lexer->data;
		if (token->type == 0) 
		{	token->file = (void*)handleenvir((char *)token->file, env);
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

int		checkforpipe(char *s)
{
	int i;

	i = 0;
	while(s[i] != '\0')
	{
		if(s[i] == '|')
			return (1);
		i++;
	}
	return (0);
}
int		check_errors(t_linked_list *ptr)
{ 
	//t_linked_list *ptr2;
	//t_file *file;
	t_file *file;

	file = (t_file*)ptr->data;

	while(ptr !=NULL)
	{
		file = (t_file*)ptr->data;
		printf("%s | \n",file->file);
		ptr = ptr->next;
	}
	return(0);

}
int		main(int argc, char **argv, char **env)
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
	argc = 0;
	argv =  NULL;

	i = 0;
	while (1)
	{
	write(1, "Minishell:0.0> ", 15);
	buffer = malloc(sizeof(char) * (1025));
	n = read(STDIN_FILENO, buffer, 1024);
	buffer[n - 1] = '\0';
	split = ft_split(buffer, ' ');
	n = 0;
	while (split[n ] != '\0')
	{
		printf("%s\n",split[n]);
		n++;
	}
	//n = 0;
	n = 0;
	t_file *file2 = NULL;
	i = 0;
	int j = 0;
	while (split[n]){
		if (checkforpipe(split[n]) == 1)
		{
			while (split[n][i] != '\0')
			{
				while(split[n][i] != '|')
					i++;
				file2 = (t_file *)malloc(sizeof(t_file));
				type = findtype(ft_substr(split[n], 0, i ));
				file2->file = ft_substr(split[n], 0, i ); 
				file2->type = type;
				append(&head, file2);
				break;
	
			}
				while(split[n][i] == '|')
				{
					j++;
					i++;
				}
				printf(" j ===== %d\n",j);
				file2 = (t_file *)malloc(sizeof(t_file));
				type = findtype("|");
				file2->file = "|"; 
				file2->type = type;
				append(&head, file2);

				if(split[n][i] != '\0')
				{
					file2 = (t_file *)malloc(sizeof(t_file));
					type = findtype(ft_substr(split[n],i,strlen(split[n] )- i ));
					file2->file = ft_substr(split[n], i,strlen(split[n]) - i ); 
					file2->type = type;
					append(&head, file2);
				}	
		}
		else
		{
		file2 = (t_file *)malloc(sizeof(t_file));
		type = findtype(split[n]);
		file2->file = split[n]; 
		file2->type = type;
		append(&head, file2);
		}
		n++;
	}
	check_errors(head);
	t_linked_list *ptr;

	Parser = parser(head, env);
	ptr = (Parser);
	t_linked_list *Sl;
	Sl = ((t_command*)ptr->data)->nameargs;
//
	while (Sl != NULL)
	{
		printf("%s-- \n",(char *)Sl->data) ;
		Sl = Sl->next;
	}
	}
	//t_linked_list *Zl;
	//Zl = ((t_command*)ptr->data)->files;
	//while (Zl != NULL)
	//{	
	//	printf("%s--|\n",((t_file*)Zl->data)->file) ;
	//	Zl = Zl->next;
	//}
	return(0);

}

