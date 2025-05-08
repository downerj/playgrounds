" Auto-detect syntax highlighting.
syntax on
" Add line numbers.
set number
" Add end-of-line characters.
"set list
" Disable word wrapping.
set nowrap
" Configure tabs.
filetype plugin indent on
set tabstop=2
set shiftwidth=2
set expandtab
" Configure backspace.
set backspace=indent,eol,start
" Set the swap directory.
set directory=~/.vim/swapfiles//
" Open vertical splits to the right.
set splitright
" Automatically change the directory to the current file's folder.
"set autochdir
autocmd BufEnter * silent! lcd %:p:h
" Highlight regex searches.
set hlsearch
" Color scheme.
" elflord, industry, koehler, murphy, pablo, torte
colo industry

" Enable the following if running GVim.
if has('gui_running')
  " ^Left and ^Right to move between tabs.  
  nnoremap <C-Left> :tabprevious<CR>
  nnoremap <C-Right> :tabnext<CR>

  " Alt+Left and Alt+Right to reposition tabs. 
  nnoremap <silent> <A-Left> :execute 'silent! tabmove ' . (tabpagenr()-2)<CR>
  nnoremap <silent> <A-Right> :execute 'silent! tabmove ' . (tabpagenr()+1)<CR>
  
  " GUI initial dimensions.
  set lines=20 columns=80

  " GUI font.
  set guifont=Terminus\ 12

  " Set the cursor.
  "set guicursor=n-v-c:block-Cursor/lCursor,ve:ver35-Cursor,o:hor50-Cursor,i-ci:ver25-Cursor/lCursor,r-cr:hor20-Cursor/lCursor,sm:block-Cursor-blinkwait175-blinkoff150-blinkon175
  highlight Cursor gui=reverse guifg=NONE guibg=NONE
  set guicursor=a:block-Cursor
endif

