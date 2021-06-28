call plug#begin()

Plug 'sainnhe/gruvbox-material'
Plug 'ryanoasis/vim-devicons'
Plug 'mhinz/vim-startify'
Plug 'jiangmiao/auto-pairs'
Plug 'ap/vim-css-color'
Plug 'junegunn/goyo.vim'
Plug 'junegunn/limelight.vim'
Plug 'numirias/semshi'
Plug 'preservim/nerdtree'
Plug 'junegunn/fzf', { 'do': { -> fzf#install() } }
Plug 'junegunn/fzf.vim'
Plug 'Chiel92/vim-autoformat'
Plug 'EvanQuan/vim-executioner'

call plug#end()

filetype plugin indent on

set mouse=a
set number " Show absolute line numbers on the left.
set clipboard=unnamedplus       " Copy/paste between vim and other programs.
set nowrap
syntax on " Turn syntax highlighting on
set ai " Sets auto-indentation
set si " Sets smart-indentation
set noswapfile " Prevent vim from creating .swp files
set hlsearch " When searching (/), highlights matches as you go
set incsearch " When searching (/), display results as you type (instead of only upon ENTER)
set ignorecase
set smartcase " When searching (/), automatically switch to a case-sensitive search if you use any capital letters
set showmatch " Show matching brackets when text indicator is over them
set noswapfile                  " No swap
set number relativenumber       " Display line numbers

" Disables automatic commenting on newline:
autocmd FileType * setlocal formatoptions-=c formatoptions-=r formatoptions-=o
let g:python3_host_prog="/usr/bin/python"
let g:python_highlight_all = 1

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => Text, tab and indent related
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
set expandtab                   " Use spaces instead of tabs.
set smarttab                    " Be smart using tabs ;)
set shiftwidth=4                " One tab == four spaces.
set tabstop=4                   " One tab == four spaces.

" Remap splits navigation to just CTRL + hjkl
nnoremap <C-h> <C-w>h
nnoremap <C-j> <C-w>j
nnoremap <C-k> <C-w>k
nnoremap <C-l> <C-w>l

" Make adjusing split sizes a bit more friendly
noremap <silent> <C-Left> :vertical resize +3<CR>
noremap <silent> <C-Right> :vertical resize -3<CR>
noremap <silent> <C-Up> :resize +3<CR>
noremap <silent> <C-Down> :resize -3<CR>

nnoremap S :%s//g<Left><Left>
nnoremap <CR> :noh<CR><CR>

let mapleader  =","
map <silent> <leader>e  :Executioner<CR>
map <silent> <leader>n  :NERDTreeToggle<CR>
map <silent> <leader>f  :Files<CR>
map <silent> <leader>s  :Startify<CR>
map <silent> <leader>g  :Goyo<CR>
map <silent> <leader>l  :Limelight<CR>
map <silent> <leader>q  :Limelight!<CR>
map <silent> <leader>a  :Autoformat<CR>
map <silent> <leader>u  :set number! relativenumber!<CR>
map <silent> <leader>r  :source ~/.config/nvim/init.vim<CR>\

" Automatically deletes all trailing whitespace and newlines at end of file on save.
autocmd BufWritePre * %s/\s\+$//e
autocmd BufWritePre * %s/\n\+\%$//e
autocmd BufWritePre *.[ch] %s/\%$/\r/e

colorscheme gruvbox-material
highlight Normal guibg=NONE ctermbg=NONE
highlight NonText guibg=NONE ctermbg=NONE
highlight EndOfBuffer guibg=NONE ctermbg=NONE
highlight StatusLine ctermbg=NONE cterm=NONE

" Color name (:help cterm-colors) or ANSI code
let g:limelight_conceal_ctermfg = 'gray'
let g:limelight_conceal_ctermfg = 240

" Restore cursor shape to beam on exit
augroup restore_cursor_shape
    autocmd!
    au VimLeave * set guicursor=a:ver10-blinkoff0
augroup END

autocmd! User GoyoEnter Limelight
autocmd! User GoyoLeave Limelight!|highlight Normal guibg=NONE ctermbg=NONE|highlight NonText guibg=NONE ctermbg=NONE|highlight EndOfBuffer guibg=NONE ctermbg=NONE|highlight StatusLine ctermbg=NONE cterm=NONE

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => Fix Sizing Bug With Alacritty Terminal
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
autocmd VimEnter * :silent exec "!kill -s SIGWINCH $PPID"
