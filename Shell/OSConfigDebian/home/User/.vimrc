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

" Color scheme.
" elflord, industry, koehler, murphy, pablo, torte
colo torte 

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
endif

