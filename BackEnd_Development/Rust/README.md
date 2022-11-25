This is the blog about Rust.

filter:
https://stackoverflow.com/questions/50133735/string-equality-in-rust-how-does-referencing-and-dereferencing-work

string不可以通过index进行索引:
https://doc.rust-lang.org/stable/book/ch08-02-strings.html

map:
```text
Takes a closure and creates an iterator which calls that closure on each element.

`map()` is conceptually similar to a [`for`] loop. However, as `map()` is lazy, it is best used when you're already working with other iterators. If you're doing some sort of looping for a side effect, it's considered more idiomatic to use [`for`] than `map()`.
 ```