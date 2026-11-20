#let book_setup(title: "", author: "", body) = {
  // Формат страницы
  set page(
    paper: "a5",
    margin: (
      inside: 20mm,
      outside: 15mm,
      top: 20mm,
      bottom: 20mm,
    ),
  )

  // Шрифт
  set text(
    font: "Liberation Serif",
    // font: "Times New Roman",
    size: 10pt,
    lang: "ru",
  )
  set par(
    justify: true,
    first-line-indent: (amount: 1.2em, all: true), // красная строка
    spacing: 0.5em, // интервал перед красной строкой
    leading: 0.5em, // межстрочный интервал
  )

  // Оформление заголовков глав с начала страницы
  show heading.where(level: 1): it => {
    pagebreak(weak: true)
    align(center)[
      // #v(3em)
      #text(size: 18pt, weight: "bold", it)
      #v(1.5em)
    ]
  }

  // Титульный лист
  // align(center + alignment.horizon)[
  align(center)[
    #set par(justify: false)
    #text(size: 14pt, author)
    #v(3em)
    #text(size: 24pt, weight: "bold", title)
    #set par(justify: true)
  ]
  pagebreak()

  set page(
    numbering: "1",
    number-align: top,
  )
  counter(page).update(1)

  // Оглавление
  outline(title: "Содержание", indent: auto)
  pagebreak()

  body
}
