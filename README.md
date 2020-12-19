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
- [ ] Redirections: **<> ">>"**
- [ ] Pipes: **|**
- [X] Environmental variables: **$**
- [ ] **$?**
- [ ] Signals: **ctrl-C, ctrl-D, ctrl-\\**


### CASES

```
e'c'h'o' hello -> (hello)
./shell запускает сам себя
```

*parser cases*
```
ls ; ls ;  			- > (ls ; ls)
ls ; ls ; ; ; 		- > (bash: syntax error near unexpected token `;')
; ls 				- > (bash: syntax error near unexpected token `;')

export USER=name ; echo $USER   - > (name)
echo " sksk   ls"

```

???
```
not close quotes ( echo "hhhh  ) - mb no (subj: ' and " except for multiline commands)
echo "$(echo "nnn")"
```


