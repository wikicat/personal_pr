# CPP 杂谈

## 正则表达式

`std::regex`是regular expression的库。

`std::regex`是class `std::basic_regex<>` char类型的特化。

| 符号   | 意义                           |
| ------ | ------------------------------ |
| ^      | 匹配行的开头                   |
| $      | 匹配行的末尾                   |
| .      | 匹配任意单个字符               |
| [...]  | 匹配[]中的任意一个字符         |
| (...)  | 设定分组                       |
| \      | 转移字符                       |
| \d     | 匹配数字[0-9]                  |
| \D     | \d取反                         |
| \w     | 匹配字母[a-z]，数字，下划线    |
| \W     | \w取反                         |
| \s     | 匹配空格                       |
| \S     | \s取反                         |
| +      | 前面的元素重复一次或多次       |
| *      | 前面的元素重复任意次           |
| ?      | 前面的元素重复零次或一次       |
| {n}    | 前面的元素重复n次              |
| {n,}   | 前面的元素至少重复n次          |
| {m, n} | 前面的元素至少重复n次，至多m次 |
| \|     | 逻辑或                         |

