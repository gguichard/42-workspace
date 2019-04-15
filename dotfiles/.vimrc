" General
syntax on
set number
set mouse=a
set background=dark
set colorcolumn=80
set hlsearch

" Tabs
set autoindent
set smarttab
set shiftwidth=4
set tabstop=4

" Color scheme / theme
colorscheme hybrid
let g:hybrid_custom_term_colors=1
let g:hybrid_reduced_contrast=1
highlight LineNr ctermfg=grey

" Color spaces/tabs
highlight ExtraWhitespace ctermbg=darkblue guibg=darkblue
match ExtraWhitespace /\s\+$/
autocmd Syntax * syn match ExtraWhitespace /\s\+$\| \+\ze\t/

" Includes for completion
set path+=includes/,include/,../includes/,../include/
set path+=libft/includes/,libft/include/,../libft/includes/,../libft/include/,libft/,../libft/

" 42 Header
let g:hdr42user="gguichar"
let g:hdr42mail="gguichar@student.42.fr"
