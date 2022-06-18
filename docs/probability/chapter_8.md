# 事件独立性

放回抽样时，$A_1$的发生对$A_2$的发生概率不影响

## 定义

> 设$A,B$是两个随机事件，如果
>
> $P(AB)=P(A)P(B)\Leftrightarrow P(B|A)=P(B)\Leftrightarrow P(A|B)=P(A)$
>
> 则称$A,B$相互独立

## 性质

$A,B$相互独立$\Leftrightarrow\overline{A},B$相互独立$\Leftrightarrow A,\overline{B}$相互独立$\Leftrightarrow\overline{A},\overline{B}$相互独立

## 推广

> $设A_1,A_2,\cdots,A_n$为$n$个随机事件
>
> 若对于$2\leq k\leq n$均有：$P(A_{i_1}A_{i_2}\cdots A_{i_k})=\prod_{j=1}^{k}{P(A_{i_j})}$
>
> 则称$A_1,A_2,\cdots,A_n$相互独立

???+ 注意
    两两独立$\not\Rightarrow$相互独立