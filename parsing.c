#include "minishell.h"
#include <dirent.h>
char *ft_calloc(size_t count, size_t size)
{
	char *dest;
	size_t i;

	if (!(dest = (char *)malloc(count * size)))
		return (0);
	i = 0;
	while (i < (count * size))
		dest[i++] = 0;
	return (dest);
}

char *ft_strjoin(char *s1, char *s2)
{
	char *dest;
	unsigned long i;
	unsigned long j;
	size_t res_len;

	if (!(res_len = 0) && s1)
		res_len = ft_strlen(s1);
	j = 0;
	if (!(dest = (char *)malloc(res_len + ft_strlen(s2) + 1)))
		return (0);
	i = -1;
	if (s1 == 0 && s2 == 0)
		return (0);
	while (++i < res_len)
		dest[i] = s1[i];
	res_len = ft_strlen(s2);
	while (j < res_len)
		dest[i++] = s2[j++];
	dest[i] = '\0';
	//free(s1);
	//free(s2);
	return (dest);
}
char *ft_strdup(char *s, size_t i)
{
	// int     i;
	int n;
	int k;
	int j;
	char *dest;
	k = 0;

	j = i;
	while (s[j] != '\0')
	{
		j++;
	}
	k = j;
	n = 0;
	dest = malloc(sizeof(char) * (k + 1));
	while (s[i] != '\0')
	{
		dest[n] = s[i];
		n++;
		i++;
	}
	dest[n] = '\0';
	return (dest);
}

int ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int j;
	unsigned long k;

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
	t_linked_list *new_node = (t_linked_list *)malloc(sizeof(t_linked_list));
	t_linked_list *last = *head_ref; /* used in step 5*/
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

void *free_pre(char **split, int k)
{
	//int i = 0;
	while (split[k])
	{
		free(split[k]);
		k++;
	}
	free(split);
	split = NULL;
	return (NULL);
}

int *traitmask(const char *s, int c)
{
	int *env = (int *)malloc(sizeof(int) * (strlen(s)));
	int env_sq = 0;
	int env_dq = 0;
	unsigned int i = 0;
	unsigned int j = strlen(s);
	while (i < j)
	{
		env[i] = 0;
		i++;
	}
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'' && env_sq == 0)
			env_sq = 1;
		else if (s[i] == '\'' && env_sq == 1)
			env_sq = 0;
		else if (s[i] == '\"' && env_dq == 0)
			env_dq = 1;
		else if (s[i] == '\"' && env_dq == 1)
			env_dq = 0;
		if (c == 1)
			env[i] = env_dq;
		else
			env[i] = env_sq;
		i++;
	}
	return (env);
}

static int len_word(const char *s, char c, int *in_sgl, int *in_db, int k)
{
	int i;
	size_t len;

	len = 0;
	i = 0;
	while (s[i] == c && s[i] != '\0' && (in_sgl[k] == 0 || in_db[k] == 0))
	{
		i++;
		k++;
	}
	while ((s[i] != c && s[i] != '\0') || (s[i] == c && (in_sgl[k] == 1 || in_db[k] == 1)))
	{
		len++;
		i++;
		k++;
	}
	free(in_db);
	free(in_sgl);
//	printf("len == %zu\n", len);
	return (len);
}
char *ft_substr(char *s, unsigned int start, size_t len)
{
	char *dest;
	char *src;
	unsigned long j;

	if (s == 0)
		return (0);
	if (start > ft_strlen(s))
		return (dest = ft_calloc(1, 1));
	else
	{
		j = 0;
		src = (char *)s;
		if (!(dest = (char *)malloc(len + 1)))
			return (0);
		while (*src && j < len)
		{
			dest[j] = src[start];
			j++;
			start++;
		}
		dest[j] = '\0';
	}
	//free(s);
	return (dest);
}

size_t ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int ft_isdigit(int c)
{
	unsigned char k;

	k = (unsigned char)c;
	if (c <= 57 && c >= 48)
		return (1);
	else
		return (0);
}

int ft_isalpha(int c)
{
	unsigned char k;

	k = (unsigned char)c;
	if (c <= 90 && c >= 65)
		return (1);
		return (0);
}

char *replaceenv(char *string, int start, int end, char **env)
{
	int i;
	int j;
	char *tmp;

	j = 0;
	i = 0;
	tmp = NULL;
	if (end == 0)
		end = ft_strlen(string);
	tmp = string;
	string = ft_substr(string, start + 1, (end - 1) - start);
	free(tmp);
	tmp = string;
	string = ft_strjoin(string, "=");
	free(tmp);
	tmp = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], string, ft_strlen(string)) == 0)
		{
			j = 1;
			break;
		}
		else
			i++;
	}
	if (j == 1)
	{
		i =  ft_strlen(string);
		free(string);
		return (ft_strdup(env[i],i ));
	}
	return (NULL);
}

char *handleenvir2(char *string, char *tmp, char *tmp2)
{
		char *tmp3;

	if (tmp != NULL && string != NULL)
	{
		tmp3 = string;
		string = ft_strjoin(tmp, string);
		free(tmp3);

	}
	if (tmp2 != NULL && string != NULL)
	{
		tmp3 = string;
		string = ft_strjoin(string, tmp2);
		free(tmp3);
	}
	if (string == NULL)
	{
		if (tmp != NULL && tmp2 != NULL)
			string = ft_strjoin(tmp, tmp2);
		else if (tmp != NULL && tmp2 == NULL)
			string = ft_strdup(tmp, 0);
		else
			string = ft_strdup(tmp2, 0);
	}
	if (tmp2 != NULL)
		free(tmp2);
	return (string);
}

char *handleenvir1(char *string, int i, int start, char *tmp, char **env)
{
	char *tmp2;
	int end;

	tmp2 = NULL;
	end = 0;
	i++;
	while (string[i] != '\0')
	{
		if (string[i] != '_' && (ft_isdigit(string[i]) == 0) && (ft_isalpha(string[i]) == 0))
		{
			end = i;
			tmp2 = ft_substr(string, end, ft_strlen(string) - end);
			break;
		}
		else
			i++;
	}
	string = replaceenv(string, start, end, env);
	string = handleenvir2(string, tmp, tmp2);
	return (string);
}

char *handleenvir(char *string, char **env)
{
	int i;
	char *tmp;
	int start;

	start = 0;
	tmp = NULL;
	i = 0;
	while (string[i] != '\0')
	{
		if (string[i] == '\'')
			return (string);
		if (string[i] == '$')
		{
			if (i != 0)
			{
				start = i;
				tmp = ft_substr(string, 0, i);
			}
			i++;
			if (string[i] >= 48 && string[i] <= 57)
			{
				if (tmp)
					free(tmp);
				return (ft_substr(string, i + 1, ft_strlen(string) - (i + 1)));
			}
			else if (string[i] == '_' || (string[i] >= 65 && string[i] <= 90))
			{
				if (tmp)
					free(tmp);
				return(string = handleenvir1(string, i, start, tmp, env));
			}
		}
		if(tmp)
			free(tmp);
		i++;
	}
	return (string);
}

static int count_word(char *s, char c)
{
	size_t i;
	size_t count = 0;
	int *in_db;
	int *in_sgl;

	in_db = traitmask(s, 1);
	in_sgl = traitmask(s, 0);
	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
			count++;
		while ((s[i] != c && s[i] != '\0') || (s[i] == c && (in_sgl[i] == 1 || in_db[i] == 1)))
		{
			i++;
		}
		if (s[i] != '\0')
		{
			i++;
		}
	}
	free(in_db);
	free(in_sgl);
	return (count);
}

int splithelper(int i, const char *s, int k, char **split, char c)
{
	unsigned long j;
	int *in_db;
	int *in_sgl;

	in_db = traitmask(s, 1);
	in_sgl = traitmask(s, 0);
	split[i] = (char *)malloc(sizeof(char) * (len_word(&s[k], c, in_sgl, in_db, k) + 1));
	j = 0;
	while (s[k] == c && (in_sgl[k] == 0 || in_db[k] == 0))
		k++;
	while ((s[k] != c && s[k] != '\0') || (s[k] == c && (in_sgl[k] == 1 || in_db[k] == 1)))
	{
		split[i][j] = s[k];
		k++;
		j++;
	}
	split[i][j] = '\0';
	//free(in_sgl);
	//free(in_sgl);
	return (k);
}

char **ft_split(char *s, char c)
{
	int i;
	size_t k;
	char **split;

	i = -1;
	k = 0;
	if (!s || !(split = (char **)malloc(sizeof(char *) * (count_word(s, c) + 1))))
		return (NULL);
	while (++i < count_word(s, c))
	{
		k = splithelper(i, s, k, split, c);
	}
	split[i] = NULL;
	return (split);
}

int findtype(char *s)
{
	//pipe == 1
	if (ft_strncmp(s, "|", ft_strlen(s)) == 0)
		return (1);
	//redirection input
	if (ft_strncmp(s, "<", ft_strlen(s)) == 0)
		return (2);
	//redirection output
	if (ft_strncmp(s, ">", ft_strlen(s)) == 0)
		return (3);
	//here-doc output
	if (ft_strncmp(s, ">>", ft_strlen(s) + 1) == 0)
		return (4);
	//here-doc input
	if (ft_strncmp(s, "<<", ft_strlen(s) + 1) == 0)
		return (5);
	return (0);
}

int builtins(char *string)
{
	if (ft_strncmp(string, "echo", ft_strlen(string)) == 0)
		return (1);
	if (ft_strncmp(string, "cd", ft_strlen(string)) == 0)
		return (1);
	if (ft_strncmp(string, "pwd", ft_strlen(string)) == 0)
		return (1);
	if (ft_strncmp(string, "unset", ft_strlen(string)) == 0)
		return (1);
	if (ft_strncmp(string, "env", ft_strlen(string)) == 0)
		return (1);
	if (ft_strncmp(string, "exit", ft_strlen(string)) == 0)
		return (1);
	if (ft_strncmp(string, "export", ft_strlen(string)) == 0)
		return (1);
	return (0);
}

char *checkforpath(char *string, char *str)
{
	DIR *dir;
	struct dirent *sd;
	dir = opendir(string);
	//	printf("%s, %s ||\n",string, str);
	if (dir == NULL)
	{
		printf("there is no file\n");
		return (0);
	}
	while ((sd = readdir(dir)) != NULL)
	{
		//printf("sdname == %s\n",sd->d_name);
		if (strncmp(sd->d_name, str, ft_strlen(sd->d_name)) == 0)
		{
		
				(void)closedir(dir);
			
			return (string);
		}
		//printf(">> %s\n",sd->d_name);
	}
	(void)closedir(dir);
	return (NULL);
}

int thereisslach(char *string)
{
	int i;
	i = 0;
	while (string[i] != '\0')
	{
		if (string[i] == '/')
			return (1);
		i++;
	}
	return (0);
}
char *elsefunction(char *string, char **env)
{
	int i;
	char *tmp;
	char **tab;
	char *tmp2;
	char *tmp3;

	//char *tmp3 = NULL;

	tmp = NULL;
	tmp2 = NULL;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			break;
		i++;
	}
	tmp = ft_strdup(env[i], 5);
	tab = ft_split1(tmp, ':');
	// tmp = NULL;
	i = 0;
	while (tab[i] != NULL)
	{
	//	printf("string == |%s|\n", string);
		if ((tmp2 = checkforpath(tab[i], string)) != NULL)
		{
			tmp3 =tab[i];
			 tab[i] = ft_strjoin(tab[i], "/");
			 free(tmp3);
			 tmp3 = ft_strjoin(tab[i], string);
			 free_pre(tab, 0);
			 free(tmp);
			 free(string);
			return (tmp3);
		}
		if (!(tmp2))
			free(tmp2);
		i++;
	}
	i = 0;
free_pre(tab, 0);
free(tmp);
	//printf("tmp == %s\n", tmp);
	return (string);
}
char *handleargs(char *string, char **env)
{
	char *ptr;
	char *ptr2;
	int i;
	int j;

	j = 0;
	i = 0;
	ptr = NULL;
	ptr2 = NULL;
	if (builtins(string) == 1)
		return (string);
	else if (thereisslach(string) == 1)
	{
		while (string[i] != '\0')
		{
			if (string[i] == '/')
				j = i;
			i++;
		}
		ptr = ft_substr(string, 0, j);
	//	printf(" -- %s\n", ptr);

		ptr2 = ft_strdup(string, j + 1);
	//	printf(" -- %s\n", ptr2);

		if (checkforpath(ptr, ptr2) == NULL)
		{
			free(ptr);
			free(ptr2);
			return (string);
		}
		free(ptr2);
		free(ptr);
		return (string);
	}
	else
	{
			printf("zaaaab im hereee \n");
		string = elsefunction(string, env);
		 printf("string == %s\n", string);
	}
	return (string);
}

void free_files_linked2(t_linked_list *files)
{
	if (!files)
		return;
	//free_files_linked(files->next);
	free(((t_file *)(files->data))->file);
	//free(files->data);
	//free(files);
}

t_linked_list *parser(t_linked_list *lexer, char **env)
{
	t_linked_list *head = NULL;
	t_command *command;
	t_file *token;
	int i;

	i = 0;
	command = (t_command *)malloc(sizeof(t_command));
	command->files = NULL;
	command->nameargs = NULL;

	while (lexer)
	{
		token = (t_file *)lexer->data;
		if (token->type == 0 && i == 0)
		{
			if ((token->file = (void *)handleargs((char *)token->file, env)) == NULL)
				return (NULL);
			append(&(command->nameargs), (void *)token->file);
			//printf("tokenfile === %s \n", (char *)token->file);

			i++;
		}
		else if (token->type == 0)
		{
			token->file = (void *)handleenvir((char *)token->file, env);
			append(&(command->nameargs), (void *)token->file);
		}
		else if (token->type != 0 && token->type != 1 && (lexer->next) && ((t_file *)(lexer->next->data))->type == 0)
		{
			t_file *f;
			t_file *tmp = (t_file *)(lexer->next->data);

			f = (t_file *)malloc(sizeof(t_file));
		//	f->file = strdup(tmp->file);
			f->file = tmp->file;
			free(token->file);
			f->type = token->type;
			append(&(command->files), (void *)f);
			lexer = lexer->next;
		}
		else if (token->type != 1)
			printf("error\n");
		printf("%s -- %d \n",(char *)token->file , (int) token->type);
		if (token->type == 1 || lexer->next == NULL)
		{
			append(&(head), (void *)command);
			if (token->type == 1)
			{
			command = (t_command *)malloc(sizeof(t_command));
			command->files = NULL;
			command->nameargs = NULL;\
			//free(lexer->data);
			//free(lexer);
			free_files_linked2(lexer);
			i = 0;
			}

			//	printf("lool im here \n");
		}
		lexer = lexer->next;
	}
	return (head);
}


int checkforpipe(char *s)
{
	int i;
	int *in_db;
	int *in_sgl;

	in_db = traitmask(s, 1);
	in_sgl = traitmask(s, 0);
	// check if this pipe inside double quotes or not
	i = 0;
	while (s[i] != '\0')
	{
		if ((s[i] == '|' || s[i] == '<' || s[i] == '>')  && in_db[i] == 0 && in_sgl[i] == 0)
		{
			free(in_db);
			free(in_sgl);
			return (1);
		}
		i++;
	}
	free(in_db);
	free(in_sgl);
	return (0);
}

int check_errors2(int j, int i, char *string)
{
	if (i == 2)
	{
		if (j > 1 && strlen(string) > 1)
		{
			printf("error here %s \n" , string);
			return (0);
		}
	}
	else
	{
		if (j > 2 && strlen(string) > 2)
		{
			printf("error here %s \n" , string);
			return (0);
		}
		else if (j == 1 && strlen(string) > 1)
		{
			printf("error here %s \n" , string);
			return (0);
		}
		else if (j == 2 && strlen(string) > 2)
		{
			printf("error here %s \n" , string);
			return (0);
		}
	}
	return (1);
}

void storeinfos(char *string, t_linked_list **head)
{
	t_file *file2;
	int type;

	type = 0;
	file2 = (t_file *)malloc(sizeof(t_file));
	type = findtype(string);
	file2->file = string;
	file2->type = type;
	append(head, file2);
}

int check_errors(t_linked_list *ptr)
{
	t_file *file;
	char *checks;
	int i;
	int j;

	checks = malloc(sizeof(char) * 4);
	checks[1] = '<';
	checks[2] = '|';
	checks[0] = '>';
	j = 0;
	file = (t_file *)ptr->data;
	while (ptr != NULL)
	{
		i = 0;
		file = (t_file *)ptr->data;
		while (i < 3)
		{
			if (checks[i] == file->file[0])
			{
				while (file->file[j] != '\0')
				{
					while ((file->file[j] == checks[i]) && file->file[j] != '\0')
						j++;
					if (check_errors2(j, i, file->file) == 0)
						return (0);
				}
			}
			i++;
		}
		ptr = ptr->next;
	}
	free(checks);
	return (1);
}

int mainhelper2(int j, int i, t_linked_list **head, char *string)
{
	if (j > 1)
	{
		printf("error here \n");
		return (0);
	}
	if (string[i] != '\0')
		storeinfos(ft_substr(string, i, strlen(string) - i), head);
	return (1);
}

int mainhelper(char *string, int j, t_linked_list **head)
{
	int *in_db;
	int *in_sgl;
	char *pip= strdup("|");
	int i;
	int c;
	int t;
	int k;
	c = 0;
	k = 0;
	t = 0;
	i = 0;
	in_db = traitmask(string, 1);
	in_sgl = traitmask(string, 0);
	while (string[i] != '\0')
	{
			
			 t = i;
			 k = in_sgl[i];
		while (((in_db[i] == 1 || in_sgl[i] == 1) || (string[i] != '|' && string[i] !='>' &&  string[i] != '<') ) && string[i] != '\0')
		{
			i++;
		}
		if (i != 0)	
		{
			storeinfos(ft_substr(string, t, i - t), head);
			printf("''%s''\n", ft_substr(string, t, i - t));	
		}
	c = i;
	j = 0;
	 printf("im hereeeee\n");
	while (((string[i] =='>' ||  string[i] == '<' || string[i] == '|' )&& in_sgl[i] == 0 && in_sgl[i] == 0) && string[i] != '\0')
	{
		j++;
	//	printf()
		i++;
		if (string[i] != '|' &&  string[i]!='>' && string[i] != '<')
		{	//c = -1;
		//printf("%d ===== \n ",j);

				storeinfos(ft_substr(string, c, j), head);
			
			break;
		}
	}
	}
	if (c == -1)
	storeinfos(pip,head);
	free(in_db);
	free(in_sgl);
	free(pip);
	return (1);
}

void free_head2(t_linked_list *head)
{
	if (head == NULL)
		return;
	free_head2(head->next);
	//free(((t_file *)(head->data))->file); 
	   free(head->data);
	free(head);
}
void free_head(t_linked_list *head)
{
	if (head == NULL)
		return;
	free_head(head->next);
	// free(((t_file *)(head->data))->file);  
	   free(head->data);
	free(head);
}
void free_files_linked(t_linked_list *files)
{
	if (!files)
		return;
	free_files_linked(files->next);
	free(((t_file *)(files->data))->file);
	free(files->data);
	free(files);
}
void free_lin_command(t_linked_list *command)
{
	t_command *cmd;

	if (command == NULL)
		return;
	free_lin_command(command->next);
	cmd = (t_command *)(command->data);
	free_head(cmd->nameargs);
	free_files_linked(cmd->files);
	free(command->data);
	free(command);
}

t_linked_list *mainhelper3(char **split)
{
	int n;
	int j;
	t_linked_list *head;

	n = 0;
	head = NULL;
	j = 0;
	while (split[n] != NULL)
	{
		if (checkforpipe(split[n]) == 1)
		{
			mainhelper(split[n], j, &head);
			free(split[n]);
		}
		else
		{
			storeinfos(split[n], &head);
			//free(split[n]);
		}
		n++;
	}
	return (head);
}

int thereisequ(char *env)
{
	int i;

	i = 0;
	while(env[i] != '\0')
	{
		if (env[i] == '=')
			return(i);
		i++;
	}
	return(-1);
}
char *traitement1(char *str, int j)
{
	char *tmp1;
	char *tmp2;
	char *tmp3;
	char *str2;

	str2 = malloc(sizeof(char) * 2);
	str2[0] = '\"';
	str2[1] = '\0';
	tmp1 = ft_substr(str, 0, j + 1);
	tmp2 = ft_substr(str, j + 1, ft_strlen(str) - (j + 1) );
	//free(str); decommenter quand str ca sera un string deja allouer 
	tmp3 = tmp2;
	tmp2 = ft_strjoin(str2, tmp2);
	free(tmp3);
    //free(str);
	tmp3 = tmp2;
	tmp2 =ft_strjoin(tmp2,str2);
	free(tmp3);
	tmp3 = tmp2;
	tmp2 = ft_strjoin(tmp1, tmp2);
	free(tmp3);
	free(tmp1);
    tmp3 = tmp2;
	tmp2 = ft_strjoin("declare -x ", tmp2);
    free(tmp3);
	free(str2);
	return(tmp2);

}

char *traitement2(char *str)
{
	char *tmp;

	tmp = ft_strjoin("declare -x ", str);
	return(tmp);
}
char **transferenv(char **tmp)
{
	int i;
	int j;
	char **tmp1 =NULL;

	i = 0;
	j = 0;
	while(tmp[i])
		i++;
	tmp1 = malloc(sizeof(char*) * i +1);
	i = 0;
	while(tmp[i] != NULL)
	{
		if ((j = thereisequ(tmp[i])) != -1)
		{
			tmp1[i] = traitement1(tmp[i], j);
		}
		else
			tmp1[i] = traitement2(tmp[i]);
		i++;
	}
	tmp1[i] = NULL;
	return(tmp1);
}
void 	get_env(t_vars *pl, char **env)
{
	int i = 0;
	int j = 0;
	while (env[i] != NULL)
		i++;
	pl->envprinc = malloc(sizeof (char *) * (i + 1));
	//printf("%d -- \n",i);
	i = 0;
	while(env[i])
	{
		j = 0;
		j = ft_strlen(env[i]);
		pl->envprinc[i] = malloc(sizeof(char) * (j  + 1));
		i++;
	}
	i = 0;
	while (env[i] != NULL)
	{
		j = 0;
		while (env[i][j] != '\0')
		{
			pl->envprinc[i][j] = env[i][j];
			j++;
		}
		pl->envprinc[i][j] = '\0';
		i++;
	}
	pl->envprinc[i] = NULL;
    pl->env1 =  transferenv(pl->envprinc);
}
int main(int argc, char **argv, char **env)
{
	char *buffer;
	char **split;
	t_linked_list *head;
	t_linked_list *Parser;
	t_vars	v;

	get_env(&v, env);
	g_count = 0;
	argc = 2;
	split = NULL;
	argc = 0;
	argv = NULL;
	while (1)
	{
		head = NULL;
		Parser = NULL;
		buffer = readline("Minishell 0.0$ ");
		if (buffer[0] != '\0')
		{
			split = ft_split(buffer, ' ');
			head = mainhelper3(split);
			if (check_errors(head) == 0)
				return (0);
			Parser = parser(head, v.envprinc);
			free_head2(head);
            exec(Parser, &v);
			free(split);
			free_lin_command(Parser);
		}
	}
	int i =0;
	 while(v.env1[i])
		{
			//printf("%d -- \n", i);
			free(v.env1[i++]);
		}
			free(v.env1);
		i = 0;
		while(v.envprinc[i])
		{
//
			free(v.envprinc[i++]);
		}	
		free(v.envprinc);
	return (0);
}
