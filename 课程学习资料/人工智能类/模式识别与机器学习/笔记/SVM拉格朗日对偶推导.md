# SVM 拉格朗日对偶推导

本笔记从一般不等式约束优化出发，先证明原问题与拉格朗日极小极大表达式的精确等价，再区分对偶变换、弱对偶和强对偶，最后推导硬间隔 SVM 的对偶问题并恢复分类器。

## 用零与正无穷表达约束

考虑一般问题

\[
p^*=\inf_{x\in C}f(x),\qquad C=\{x:g_i(x)\leq0,\ i=1,\ldots,m\}.
\]

定义可行域的扩展实值指示函数

\[
I_C(x)=\begin{cases}0,&x\in C,\\+\infty,&x\notin C.\end{cases}
\]

于是

\[
\inf_{x\in C}f(x)=\inf_x[f(x)+I_C(x)].
\]

可行点的目标值不变，不可行点的目标值变为正无穷；对所有点求下确界因此等价于仅在可行域内优化。

### 乘子表达式的逐点证明

关键恒等式是

\[
\boxed{I_C(x)=\sup_{\alpha\geq0}\sum_i\alpha_i g_i(x).}
\]

固定任意一个 x，仅对乘子取上确界。

若 x 可行，则所有约束值非正。任意非负乘子都满足

\[
\sum_i\alpha_i g_i(x)\leq0.
\]

取所有乘子为零即可达到零，所以上确界恰为零。

若 x 不可行，则存在 j 使 g_j(x)>0。令其他乘子为零，仅令该乘子趋向正无穷，有

\[
\alpha_j g_j(x)\longrightarrow+\infty.
\]

所以上确界为正无穷。两种情况合起来，得到上述恒等式。

### 原问题的拉格朗日表达

定义

\[
L(x,\alpha)=f(x)+\sum_i\alpha_i g_i(x).
\]

由于内层固定 x，f(x) 对乘子而言是常数，因此

\[
\begin{aligned}
p^*&=\inf_x[f(x)+I_C(x)]\\
&=\inf_x\left[f(x)+\sup_{\alpha\geq0}\sum_i\alpha_i g_i(x)\right]\\
&=\boxed{\inf_x\sup_{\alpha\geq0}L(x,\alpha)}.
\end{aligned}
\]

此等价关系不依赖凸性、求导或强对偶。这里没有交换优化顺序。内层对乘子取上确界负责精确编码约束，外层对原变量取下确界完成原来的最小化。

使用 inf 与 sup，是为了涵盖最值不取到及无界的情况；在最值取到时可相应写成 min 与 max。

## 对偶问题与弱对偶

定义对偶函数与对偶最优值

\[
q(\alpha)=\inf_x L(x,\alpha),\qquad
d^*=\sup_{\alpha\geq0}q(\alpha).
\]

对偶问题将操作顺序改为先固定乘子、对原变量求下确界，再对乘子求上确界。这个换序通常只保证不等式。

对任意非负乘子与任意可行点 x，有

\[
q(\alpha)\leq L(x,\alpha)\leq f(x).
\]

因此

\[
\boxed{d^*\leq p^*.}
\]

这就是弱对偶。可行方案给原问题最优值提供上界，对偶可行乘子给它提供下界；优化对偶函数是在提高可证明的下界，并没有改变原问题要最小化的目标。

## 强对偶与最优性证书

强对偶指 d^*=p^*。凸性结合适当的约束资格条件可以保证这一性质，不能对任意问题直接交换 inf 与 sup。

对可微凸目标与凸不等式约束，Slater 条件要求存在严格可行点，即所有 g_i(x)<0。硬间隔 SVM 在线性可分时满足此条件：从满足单位间隔约束的参数出发，将 w 与 b 同时乘以大于一的数即可严格满足所有约束。

如果原问题与对偶问题的最优解均取到，强对偶给出

\[
q(\alpha^*)=f(x^*).
\]

由 q(α*)≤L(x*,α*)≤f(x*)，中间的两个不等式都必须取等号。于是：

1. x* 最小化固定 α* 后的拉格朗日函数；可微时满足驻点条件。
2. 乘子项总和为零。由于各项 α_i*g_i(x*) 均非正，每一项都必须为零，即互补松弛。

结合原可行性与乘子非负性，即得到 KKT 条件。最优值相等是关于数值的结论；恢复原变量还需要利用这些条件。

## 硬间隔 SVM 的对偶推导

设训练样本为 (x_i,y_i)，标签 y_i∈{-1,+1}，两类均存在且数据线性可分。原问题为

\[
\min_{w,b}\frac12\|w\|^2,
\qquad 1-y_i(w^\top x_i+b)\leq0.
\]

构造

\[
\begin{aligned}
L(w,b,\alpha)
&=\frac12\|w\|^2+\sum_i\alpha_i[1-y_i(w^\top x_i+b)]\\
&=\frac12\|w\|^2-w^\top A-bB+\sum_i\alpha_i,
\end{aligned}
\]

其中

\[
A=\sum_i\alpha_i y_i x_i,\qquad B=\sum_i\alpha_i y_i.
\]

固定非负乘子后，若 B≠0，可通过选择 b 的符号并使其绝对值无限增大，将 -bB 降至负无穷。因此对偶函数有限必须满足 B=0。

在 B=0 时，配平方得

\[
L=\frac12\|w-A\|^2-\frac12\|A\|^2+\sum_i\alpha_i.
\]

最小值在 w=A 处取得，故

\[
q(\alpha)=\sum_i\alpha_i-\frac12\left\|\sum_i\alpha_i y_i x_i\right\|^2.
\]

展开范数平方：

\[
\begin{aligned}
\left\|\sum_i\alpha_i y_i x_i\right\|^2
&=\left(\sum_i\alpha_i y_i x_i\right)^\top\left(\sum_j\alpha_j y_j x_j\right)\\
&=\sum_{i,j}\alpha_i\alpha_jy_iy_jx_i^\top x_j.
\end{aligned}
\]

因此对偶问题为

\[
\boxed{
\begin{aligned}
\max_\alpha\quad&\sum_i\alpha_i-\frac12\sum_{i,j}\alpha_i\alpha_jy_iy_jx_i^\top x_j\\
\text{s.t.}\quad&\alpha_i\geq0,\qquad\sum_i\alpha_i y_i=0.
\end{aligned}}
\]

该问题仍需用有约束的二次规划算法求解，例如 SMO；不能忽略约束而将所有关于乘子的偏导直接设为零。

## 从最优乘子恢复分类器

求得最优乘子后，恢复

\[
w^*=\sum_i\alpha_i^* y_i x_i.
\]

完整 KKT 条件为

\[
\begin{aligned}
&y_i(w^{*\top}x_i+b^*)\geq1,\qquad\alpha_i^*\geq0,\\
&w^*=\sum_i\alpha_i^*y_ix_i,\qquad\sum_i\alpha_i^*y_i=0,\\
&\alpha_i^*[1-y_i(w^{*\top}x_i+b^*)]=0.
\end{aligned}
\]

选择 α_k*>0 的样本，由互补松弛得

\[
y_k(w^{*\top}x_k+b^*)=1,
\qquad
\boxed{b^*=y_k-w^{*\top}x_k.}
\]

最终分类器为

\[
\boxed{\hat y(x)=\operatorname{sgn}\left(\sum_i\alpha_i^*y_ix_i^\top x+b^*\right).}
\]

乘子为正的样本一定位于间隔边界；严格处于间隔外的样本乘子必为零。边界上的样本在退化情形下也可能乘子为零，不能将该逻辑反向推断。支持向量的数量不需要预先指定。
