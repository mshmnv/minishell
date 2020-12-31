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
ls > file >> file2			(file-пустой, file2 - +ls)   -  не создает file
ls <> file					(создает пустой файл, ls в терминале)
?
wc<1 >2>3>4							(syntax error near 2)
ls -la | grep m | grep main >1>2>>3


(done)ls;pwd
(done)ls > a | cat -e
(done)cat < file >> file2 | grep 111
(done)grep L < file | wc
(done)grep M < file | wc
(done)env | grep OG > s ; wc < s
(done)env grep OG > s ; cat s
(done)ls | |						(syntax error)
(done)ls | | | | cat -e				(syntax error)
(done)ls >< file					(syntax error)
(done)pwd ; ;						(syntax error)
(done)ls ; ls ; ; ;					(syntax error)
(done); ls							(syntax error)
(done)wc < s | grep 4				(bash: s: No such file or directory)
(done)ls ; ls ;
(done)echo "   hello"
(done)echo "-n"
(done)ls ;  "   pwd"
(done)echo -n -n "-n"
(done)""							(bash: : command not found) 127
(done)"" ; ls						(bash: : command nor found   +   ls)
(done)ls "  " ss
(done)echo "" " s "
(done)echo"ss"
(done)echo "    sksk   ls"

```

???
```
not close quotes ( echo "hhhh  ) - mb no (subj: ' and " except for multiline commands)
echo "$(echo "nnn")"
sssss^D   (don't let me delete anything before ^D)
export USER=name ; echo $USER   - > (name)
cat Makefile | grep sjjd
```


```
- check strtok in pipes.c
- args in pipes.c check
```