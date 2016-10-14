#include "../include/libft.h"
#include "../include/fillit.h"

char	*input_data(char *av)
{
	char	*ret;
	int		num_minos;
	int		i;

	i = -1;
	ret = read_data(av);
	if (ret == 0)
	{
		free(ret);
		return (0);
	}
	num_minos = tetrimino_count(ret);
	if (!(nl_check(ret)))
	{
		printf("**** nl check\n");
		return (0);
	}
	if (!(dot_hash_check(ret)))
	{
		printf("**** dot hash\n");
		return (0);
	}

	ret = rm_nl(ret);
	if (pre_shape_check(ret))
	{
		printf("**** shape check\n");
		return (0);	
	}

	ret = hash_to_letter(ret);
	return (ret);
}


char	*read_data(char *av)
{
	char	*buf;
	int		fd;
	int		ret;

	buf = (char *)malloc(sizeof(char) * 10000);
	fd = open(av, O_RDONLY);
	if (fd == -1)
	{
		error_check();
		ft_putstr("could not open input\n");
		return (0);
	}
	ret = read(fd, buf, 10000);
	close(fd);
	return (buf);
}


void	error_check(void)
{
	if (errno == ENAMETOOLONG)
		printf("File name too long\n");
	else if (errno == ENOENT)
		printf("No such file or directory\n");
	else if (errno == ETXTBSY)
		printf("Text file busy\n");
	else if (errno == EACCES)
		printf("Permission denied\n");
	else if (errno == EFBIG)
		printf("File too large\n");
	else if (errno == EISDIR)
		printf("Is a directory\n");
	else
		printf("Unknown error\n");
}


int		input_error(int	*check)
{
	int		i;

	i = 0;
	if (check[0] == 0)
		ft_putstr("failed new line check\n");
	if (check[1] == 0)
		ft_putstr("failed dot hash check\n");
	if (check[2] == 0)
		ft_putstr("failed shape check\n");
	while (i < 3)
	{
		if (check[i] == 0)
			return (0);
		i++;
	}
	return (1);
}


// gcc src/main.c src/read_data.c src/input_index.c src/input_helpers.c src/solve.c -I include/fillit.h include/libft.h -L. -lft
