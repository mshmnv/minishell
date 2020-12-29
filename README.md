# minishell

- [X] search and launch the right executable
- [X] **echo** with option ’-n’
- [X] **cd** with only a relative or absolute path
- [X] **pwd** without any options
- [X] **export** without any options
- [X] **unset** without any options
- [X] **env** without any options and any arguments
- [X] **exit** without any options
- [X] Command separates with: **;**
- [X] **'** and **"** (except for multiline commands)
- [X] Redirections: **<> ">>"**
- [X] Pipes: **|**
- [X] Environmental variables: **$**
- [X] **$?**
- [X] Signals: **ctrl-C, ctrl-D, ctrl-\\**


### CASES

```
./shell запускает сам себя
```

*parser cases*
```
(done)ls ; ls ;  			  - > (ls ; ls)
ls ; ls ; ; ; 		- > (bash: syntax error near unexpected token `;')
; ls 				      - > (bash: syntax error near unexpected token `;')

export USER=name ; echo $USER   - > (name)
echo "    sksk   ls"

(done)ls;pwd
(done)ls > a | cat -e
(done)cat < file >> file2 | grep 111
(done)grep L < file | wc
(done)grep M < file | wc
(done)env | grep OG > s ; wc < s
(done)env grep OG > s ; cat s
(done)pwd ; ;

ls | |
ls | | | | cat -e			(bash: syntax error near unexpected token `|')

```

???
```
not close quotes ( echo "hhhh  ) - mb no (subj: ' and " except for multiline commands)
echo "$(echo "nnn")"
sssss^D   (don't let me delete anything before ^D)
```


