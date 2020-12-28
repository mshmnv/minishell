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
- [X] Pipes: **|**
- [X] Environmental variables: **$**
- [ ] **$?**
- [ ] Signals: **ctrl-C, ctrl-D, ctrl-\\**


### CASES

```
./shell запускает сам себя
```

*parser cases*
```
ls ; ls ;  			  - > (ls ; ls)
ls ; ls ; ; ; 		- > (bash: syntax error near unexpected token `;')
; ls 				      - > (bash: syntax error near unexpected token `;')

export USER=name ; echo $USER   - > (name)
echo " sksk   ls"
(done)ls;pwd
ls > a | cat -e
cat < file >> file2 | grep 111
grep L < file | wc
env | grep OG > s ; wc < s
env grep OG > s ; cat s
pwd ; ;
```

???
```
not close quotes ( echo "hhhh  ) - mb no (subj: ' and " except for multiline commands)
echo "$(echo "nnn")"
sssss^D   (don't let me delete anything before ^D)
```


