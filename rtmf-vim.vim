if exists("b:current_syntax")
    finish
endif

" Заголовки
syntax match rtmfHeader /^\(=\+\)\s.\+\s\1$/
highlight default link rtmfHeader Title

" Списки
syntax match rtmfList /^\s*\d\+\.\s/
syntax match rtmfList /^\s*-\s/
highlight default link rtmfList Structure

" Чекбоксы
syntax match rtmfCheckboxTodo /^\s*\[\s\]/
syntax match rtmfCheckboxDone /^\s*\[[Vv]\]/
highlight default link rtmfCheckboxTodo Comment
highlight default link rtmfCheckboxDone Type

" Цитаты
syntax match rtmfQuoteLine /^\s*|.*$/
syntax match rtmfQuoteAuthor /^\s*--.*$/
highlight default link rtmfQuoteLine String
highlight default link rtmfQuoteAuthor Identifier

" Ссылки
syntax match rtmfLink /\[\d\+\]/
syntax match rtmfLinkAnchor /^\[\d\+\]\./
highlight default link rtmfLink Underlined
highlight default link rtmfLinkAnchor Debug

" Текст
syntax region rtmfBoldItalic start=/\*\*\*/ end=/\*\*\*/
syntax region rtmfBold start=/\*\*/ end=/\*\*/
syntax region rtmfItalic start=/\*/ end=/\*/
syntax region rtmfMono start=/`/ end=/`/
highlight rtmfBoldItalic cterm=bold,italic gui=bold,italic
highlight rtmfBold cterm=bold gui=bold
highlight rtmfItalic cterm=italic gui=italic
highlight default link rtmfMono Macro

" Блоки кода
syntax region rtmfCodeBlock start=/\/\/\/\*/ end=/\*([^\/]*)\/\/\// keepend
highlight default link rtmfCodeBlock PreProc

" словарь соответствий - название языка: название файла
let s:lang_map = {
    \ 'c': 'c',
    \ 'cpp': 'cpp',
    \ 'c++": "cpp',
    \ 'python': 'python',
    \ 'py': 'python',
    \ 'sh': 'sh',
    \ 'bash': 'sh',
    \ 'zsh': 'sh',
    \ 'go': 'go',
    \ 'golang': 'go',
    \ 'rust': 'rust',
    \ 'rustlang': 'rust',
    \ 'rs': 'rust',
    \ 'lua': 'lua',
    \ 'javascript': 'javascript',
    \ 'js': 'javascript',
    \ 'html': 'html',
    \ 'json': 'json',
    \ 'yaml': 'yaml',
    \ 'yml': 'yaml'
    \ }

if main_syntax == 'rtmf'
    for [s:alias, s:actual_syntax] in items(s:lang_map)
        let b:current_syntax = ''
        unlet b:current_syntax

        let s:safe_alias = substitute(s:aluias, '+', 'x', 'g')
        execute 'syntax include @rtmf_' . s:safe_alias . ' syntax/' . s:actual_syntax . '.vim'

        execute 'syntax region rtmfCodeBlock_' . s:safe_alias .
            \ ' start=/\/\/\/\*\s*\c\V' .
            \ escape(s:alias, '/\*') .
            \ '\>/' .
            \ ' end=/\*\/\/\//' .
            \ ' contains=@rmtf_' .
            \ s:safe_alias .
            \ ' keepend'
    endfor

    unlet! s:alias s:actual_syntax s:safe_alias s:lang_map
endif

let b:current_syntax = "rmtf"
