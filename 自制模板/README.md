<!--
 * @Author: Kaizyn
 * @Date: 2020-06-13 10:34:02
 * @LastEditTime: 2020-10-12 21:49:32
-->
一天速成Latex制作的(自己的)模板可打印版本

使用正则表达式查找替换

```
^# (.*)
\part{$1}

^## (.*)
\section{$1}

^### (.*)
\subsection{$1}

^#### (.*)
\subsubsection{$1}

^##### (.*)
\paragraph{$1}

\[(.*)\]\((.*)\)
$1

`([^`])
\`$1
```

普通查找替换

```
{% spoiler "代码" %}
```cpp

{\setmainfont{Consolas}
\begin{lstlisting}
```
```
\```

{% endspoiler %}

\end{lstlisting}
```

另外注意某些特殊字符的转义如

```
& _ `
```