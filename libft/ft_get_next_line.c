#include "libft.h"

static int	ft_fr(char **str)
{
	if (str)
	{
		free(*str);
		*str = NULL;
	}
	return (0);
}

static char	*ft_nstr(size_t cnt)
{
	char	*ptr;

	ptr = malloc(sizeof(char) * cnt + 1);
	if (!ptr)
		return (NULL);
	ptr[cnt] = '\0';
	while (cnt--)
		ptr[cnt] = '\0';
	return (ptr);
}

static void	ft_lnrec(char **st, char **ln, int fd)
{
	char	*tmp;
	char	*nl;

	nl = ft_strchr(st[fd], '\n');
	if (!nl)
	{
		*ln = ft_strdup(st[fd]);
		ft_fr(&st[fd]);
	}
	else
	{
		*nl = '\0';
		*ln = ft_strdup(st[fd]);
		tmp = ft_strdup(++nl);
		ft_fr(&st[fd]);
		st[fd] = tmp;
	}
}

int	ft_get_next_line(int fd, char **line)
{
	char		buf[BUF_GETNEXTLINE + 1];
	ssize_t		cnt;
	static char	*st[OPEN_MAX];
	char		*tmp;

	cnt = read(fd, buf, BUF_GETNEXTLINE);
	if (!line || fd < 0 || cnt < 0)
		return (-1);
	if (!st[fd])
		st[fd] = ft_nstr(1);
	while (line && fd >= 0 && cnt > 0)
	{
		buf[cnt] = '\0';
		tmp = ft_strjoin(st[fd], buf);
		ft_fr(&st[fd]);
		st[fd] = tmp;
		if ((ft_strchr(st[fd], '\n')))
			break ;
		cnt = read(fd, buf, BUF_GETNEXTLINE);
	}
	ft_lnrec(st, line, fd);
	if (!cnt && !st[fd])
		return (ft_fr(&st[fd]));
	return (1);
}
