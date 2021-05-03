#include "../../../includes/minishell.h"

static int strcmp_ignorecase(const char* s1, const char* s2)
{
    // １文字ずつ、小文字に統一して比較する。
    // この比較が真になり続けた場合、２つの文字列は一致する。
    while (ft_tolower(*s1) == ft_tolower(*s2)) {

        // s1とs2 が同時に '\0' に到達したのなら、２つの文字列は一致している。
        // 一方が先に '\0' に到達するケースでは、while文の条件式を満たさなくなるため、
        // while文から脱出している。
        if (*s1 == '\0') {
            return 0;
        }

        ++s1;
        ++s2;
    }

    // 一致しなくなった文字同士で比較して、
    // s1 の側が小さいなら 0 より小さい値を、s1 の側が大きいなら 0 より大きい値を返す。
    return ft_tolower(*s1) - ft_tolower(*s2);
}

static void bubble_sort(char **tab)
{
	char *tmp;
	int i;
	int j;
	int n;

	n = 0;
	while (tab[n] != NULL)
		n++;
	i = -1;
	while (++i < n - 1)
	{
		j = n;
		while (--j > i)
		{
			if (strcmp_ignorecase(tab[j], tab[j - 1]) < 0)
			{
				tmp = tab[j - 1];
				tab[j - 1] = tab[j];
				tab[j] = tmp;
			}
		}
	}
}

/* マッチング関数 */
bool match( char * s1 , char * s2 ) {

  /* 収束条件 ① */
  if( s1[0] == '\0' && s2[0] == '\0' ) {
    return true;
  }

  /* '*'の処理 */
  if( s1[0] == '*' ) {
    if( s2[0] == '\0' ) {
      /* '*'は０文字以上とマッチするので ⑥ */
      return match( &s1[1] , &s2[0] );
    }
    else {
      /* '*'が１文字にマッチしたかチェック */
      if( match( &s1[1] , &s2[0] ) == true ) {
        /* 収束条件 ⑦ */
        return true;/* マッチしたのでtrue */
      }
      else {
        /* アンマッチだったのでバックトラック ⑧ */
        return match( &s1[0] , &s2[1] );
      }
    }
  }

  /* 同一文字同士で１文字マッチしたので次へ ③ */
  /* (ここでは既に'?'や'*'は排除されている) */
  if( s1[0] == s2[0] ) {
    return match( &s1[1] , &s2[1] );
  }

  /* 収束条件 ② */
  /* (異なる文字同士で１文字アンマッチだったのでfalse) */
  return false;

}

void wildcard(t_ip *ip, t_list **tokens)
{
	DIR				*dir;
	struct dirent	*dp;
	char			**store;
	int				i;

	if ((dir = opendir(".")) == NULL)
	{
		ft_putendl_fd(strerror(errno), 2);
		return ;
	}
	store = ft_calloc2(sizeof(char *), 1);
	while ((dp = readdir(dir)) != NULL)
	{
		if (dp->d_name[0] == '.')
			continue;
		if (match(ip->id_string, dp->d_name))
			store = ft_realloc2(store, ft_strdup(dp->d_name));
	}
	closedir(dir);
	bubble_sort(store);
	i = -1;
	while (store[++i] != NULL)
	{
		ip->sy = IDENTIFY;
		ip->id_string = store[i];
		if (store[i + 1] != NULL)
			save_token(ip, tokens);
	}
	free(store);
}
