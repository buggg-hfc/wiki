# 事件的相互关系及运算

## 事件的关系

- $A \subset B$：$A$发生$\to$$B$发生
- $A=B \Leftrightarrow \begin{cases}A \subset B\\ B \subset A\end{cases}$
- $A \cup B = \{x|x\in A 或 x\in B\}$：$A$与$B$至少有一个发生
- $A \cap B = \{x|x\in A 且 x\in B\}$，又作$A·B$，$AB$：$A$与$B$同时发生
- $AB=\phi$，称为$A$与$B$不相容或互斥
- $A-B=\{x|x\in A 且 x\notin B\}$
- $\overline{A}$
    - $A \cup \overline{A}=S,A\overline{A}=\phi,\overline{\overline{A}}=A$
    - $A-B=A\overline{B}=A \cup B-B=A-AB$

## 事件的运算定理

- 交换律：$A\cup B=B\cup A,A\cap B=B\cap A$
- 结合律：$A\cup(B\cup C)=(A\cup B)\cup C,A\cap(B\cap C)=(A\cap B)\cap C$
- 分配律：$A\cup(B\cap C)=(A\cup B)\cap(A\cup C),A\cap(B\cup C)=(A\cap B)\cup(A\cap C)$
- 对偶律：$\overline{A\cup B}=\overline{A}\cap\overline{B},\overline{A\cap B}=\overline{A}\cup\overline{B}$