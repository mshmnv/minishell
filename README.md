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
(done)ls;pwd
(done)ls > a | cat -e
(done)cat < file >> file2 | grep 111
(done)grep L < file | wc
(done)grep M < file | wc
(done)env | grep OG > s ; wc < s
(done)env grep OG > s ; cat s
(done)ls > file >> file2			(file-пустой, file2 - +ls)
ls <> file					(создает пустой файл, ls в терминале)

(done)ls | |						(syntax error)
(done)ls | | | | cat -e				(syntax error)
(done)ls >< file					(syntax error)
(done)pwd ; ;						(syntax error)
(done)ls ; ls ; 					(syntax error)
(done)ls ; ls ; ; ;					(syntax error)
(done); ls							(syntax error)

(done)wc < s | grep 4				(bash: s: No such file or directory)
wc<1 >2>3>4
ls -la | grep m | grep main >1>2>>3
```

???
```
not close quotes ( echo "hhhh  ) - mb no (subj: ' and " except for multiline commands)
echo "$(echo "nnn")"
sssss^D   (don't let me delete anything before ^D)
export USER=name ; echo $USER   - > (name)
echo "    sksk   ls"
cat Makefile | grep sjjd
```


```
- check strtok in pipes.c
- args in pipes.c check
```