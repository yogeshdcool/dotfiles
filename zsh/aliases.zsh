# Changing/copying/making/removing directory
alias -g ...='../..'
alias -g ....='../../..'
alias -g .....='../../../..'
alias -g ......='../../../../..'

alias md='mkdir -p'
alias rmd='rm -r'
alias rmf='rm -rf'

# List directory contents
# Changing "ls" to "exa"
alias ls='exa --color=always --group-directories-first'
alias ll='exa -a --color=always --group-directories-first'
alias la='exa -l --color=always --group-directories-first'
alias lh='exa -al --color=always --group-directories-first'
alias lt='exa -aT --color=always --group-directories-first'

alias cpr='cp -r'
alias cp="cp -i"                          # confirm before overwriting something
alias df='df -h'

# Package management
alias pac='sudo pacman -S'   # install
alias pak='sudo pacman -U'   # install a local package
alias ya='yay -S'            # install from aur
alias pipi='pip install'
alias pir='pip install -r'
alias pacu='sudo pacman -Syyy'
alias pacup='sudo pacman -Syu'    # update, add 'a' to the list of letters to update AUR packages if you use yaourt
alias pacr='sudo pacman -Rs'   # remove
alias pipu='pip uninstall'
alias pipr='pip3-autoremove'
alias pacs='pacman -Ss'      # search
alias yas='yay -Si'          # search aur
alias paci='pacman -Si'      # info
alias yai='yay -Si'      # info from aur
alias paclo='pacman -Qdt'    # list orphans
alias pacro='pacman -Qdt && sudo pacman -Rns $(pacman -Qtdq)' # remove orphans
alias pacc='sudo pacman -Scc'    # clean cache
alias paclf='pacman -Ql'   # list files
alias pacl='pacman -Qe'
alias pacli='pacman -Q'
alias pacla='pacman -Qm'   # list packages not found in official repos

# Editors
alias nano='nvim'
alias vim='nvim'
alias vi='nvim'
alias sim='sudo nvim'
alias code='vscodium'

#Git
alias gc='git clone'
alias gh='github-downloader'
alias gs='git status'
alias ga='git add'
alias gco='git commit'
alias gp='git push'
alias gpl='git pull'

# Colouring
alias grep='grep --colour=auto'

# Fzf
alias fai='pacman -Slq | fzf --multi --preview "pacman -Si {1}" | xargs -ro sudo pacman -S'
alias fay='yay -Slq | fzf --multi --preview "yay -Si {1}" | xargs -ro yay -S'
alias far='pacman -Qq | fzf --multi --preview "pacman -Qi {1}" | xargs -ro sudo pacman -Rs'

# Terminal rickroll!
alias rr='curl -s -L https://raw.githubusercontent.com/keroserene/rickrollrc/master/roll.sh | bash'

# Others
alias re='source ~/.zshrc'
alias cwm='cd ~/.config/dwm'
alias pyd='cd ~/Projects/python3'
alias nv='nvim ~/.config/nvim/init.vim'
alias sumake='sudo make clean install'
alias his='history'
alias py='python'
alias pi='ping -c 1 google.com'
alias dun='du -sh *'
alias duh='du -d 1 -h'
alias lin='ls | wc -lines'
alias lih='ls -a | wc -lines'
alias wion='nmcli radio wifi on'
alias wiof='nmcli radio wifi off'
alias tb='nc termbin.com 9999'
alias red='redshift -r -l 13.08:80.28 -t 4000:3500 '
alias redq='redshift -x'
alias sudo='sudo '
alias xp='chmod +x'
alias mx='mocp -x'
