# Enable colors and change prompt:
autoload -U colors && colors

PS1="%{$fg[red]%}➜  %{$fg[yellow]%}%2~ "

PATH=~/.bin:~/.local/.bin:$PATH
EDITOR=nvim

# History in cache directory:
HISTSIZE=5000
SAVEHIST=5000
HISTFILE=~/.cache/zsh-history

# Basic auto/tab complete:
autoload -U compinit

zstyle ':completion:*' menu select

# Colorize completions using default `ls` colors.
zstyle ':completion:*' list-colors ''
zstyle ':completion:*' list-colors "${(s.:.)LS_COLORS}"

zstyle ':completion:*' matcher-list '' \
  'm:{a-z\-}={A-Z\_}' \
  'r:[^[:alpha:]]||[[:alpha:]]=** r:|=* m:{a-z\-}={A-Z\_}' \
  'r:|?=** m:{a-z\-}={A-Z\_}'

zmodload zsh/complist
compinit
#_comp_options+=(globdots)		# Include hidden files.

setopt auto_cd
setopt correct_all
setopt hist_ignore_dups

# Coloured man pages
export LESS_TERMCAP_mb=$'\e[1;32m'
export LESS_TERMCAP_md=$'\e[1;32m'
export LESS_TERMCAP_me=$'\e[0m'
export LESS_TERMCAP_se=$'\e[0m'
export LESS_TERMCAP_so=$'\e[01;33m'
export LESS_TERMCAP_ue=$'\e[0m'
export LESS_TERMCAP_us=$'\e[1;4;31m'
