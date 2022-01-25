# How to in Ubuntu

## Midnight commander : go to parent dir with Backspace

```
$ cd
$ ln -s ~/.config/mc .mc
$ cd .mc
$ cp /etc/mc/mc.keymap .
$ vi mc.keymap
```
Modify this line:

`# new value:
` CdParentSmart = backspace

## Usefull link for Midnight commander

https://klimer.eu/2015/05/01/use-midnight-commander-like-a-pro/

##