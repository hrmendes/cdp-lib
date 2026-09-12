syntax on
set ts=4 sw=4 sta et nu rnu sc cindent autoread mouse=a is hls

inoremap {<CR> {<CR>}<Esc>O
nnoremap <C-down> :m+1<CR>
nnoremap <C-up> :m-2<CR>

nnoremap <F5> :w<CR>:!g++ -fsanitize=address -g % -o %:r && ./%:r<CR>
nnoremap <F6> :w<CR>:!g++ -fsanitize=address -g % -o %:r && ./%:r < <C-r>=input('file: ')<CR><CR>
