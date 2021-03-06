set nocompatible
" allow backspacing over everything in insert mode
set backspace=indent,eol,start

" encodings
set fileencoding=utf-8
set fileencodings=ucs-bom,utf-8,latin1,gb18030,utf-16,big5,default

syntax on
"set hlsearch
"set background=dark
"set cindent
set autoindent
set nu
set nowrap
set nobackup

" Set to auto read when a file is changed from the outside
set autoread

" foldmethod
" set fdm=syntax
set nofoldenable

" Tab strategy
set tabstop=4
set softtabstop=4
set shiftwidth=4
set expandtab

" Uncomment the following to have Vim jump to the last position when
" reopening a file
if has("autocmd")
  au BufReadPost * if line("'\"") > 0 && line("'\"") <= line("$")
    \| exe "normal g'\"" | endif
endif

if has("autocmd")
    filetype plugin indent on
endif

set showcmd		" Show (partial) command in status line.
set showmatch		" Show matching brackets.
set ignorecase		" Do case insensitive matching
set smartcase		" Do smart case matching
set incsearch		" Incremental search
set hidden             " Hide buffers when they are abandoned

" In many terminal emulators the mouse works just fine, thus enable it.
"if has('mouse')
"  set mouse=a
"endif

" Convenient command to see the difference between the current buffer and the
" file it was loaded from, thus the changes you made.
" Only define it when not defined already.
if !exists(":DiffOrig")
  command DiffOrig vert new | set bt=nofile | r # | 0d_ | diffthis
		  \ | wincmd p | diffthis
endif

" CTRL-U in insert mode deletes a lot.  Use CTRL-G u to first break undo,
" so that you can undo CTRL-U after inserting a line break.
inoremap <C-U> <C-G>u<C-U>

" Jump between windows
nnoremap <C-j> <C-w>j
nnoremap <C-k> <C-w>k
nnoremap <C-h> <C-w>h
nnoremap <C-l> <C-w>l

" Use shortcut <\-cd> to cd current file's directory
nnoremap <leader>cd :cd %:h<CR>

iab xdate <c-r>=strftime("%d/%m/%Y %H:%M:%S")<cr>
iab xfname <c-r>=expand("%:t")<cr>
iab xhead <c-o>:r ~/.vim/xhead.txt<cr>

set guifont=Menlo\ Regular:h15
set history=50		" keep 50 lines of command line history
set ruler		" show the cursor position all the time
set wildmenu
set statusline=2

" guioptions
" remove toolbar
set guioptions-=T
" remove menubar
set guioptions-=m

" Use Q for formatting
nnoremap Q gq

if filereadable("./.vimrc.local")
  source ./.vimrc.local
endif

set laststatus=2
set statusline+=%f
