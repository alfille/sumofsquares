---
extensions:
  preset: ''
title: Sum Of Squares
author: Paul H Alfille

---

<blockquote>
<p>Written with <a href="https://stackedit.io/">StackEdit</a>.</p>
</blockquote>
<h2 id="sum-of-squares">Sum of Squares</h2>
<p>This is a program to explore the integer math of decomposing numbers into sums of squares.</p>
<p>Actually, since 1 is a square, there is a trivial decomposition all 1s. Instead we want the minimum number of terms.</p>
<p>Example:<br>
7 = 4 + 1 + 1 + 1 = 2<sup>2</sup> + 1<sup>2</sup> + 1<sup>2</sup> + 1<sup>2</sup><br>
Four terms</p>
<p>23 = 9 + 9 + 4 + 1 = 3<sup>2</sup> + 3<sup>2</sup> + 2<sup>2</sup> + 1<sup>2</sup><br>
Also 4 terms</p>
<p>40 = 36 + 4 = 6<sup>2</sup> + 2<sup>2</sup><br>
2 terms</p>
<p>In fact, is seems that 4 terms is the maximum, although that’s hard to prove.<br>
<img src="https://github.com/alfille/sumofsquares/blob/master/images/Square_terms.png?raw=true" alt="enter image description here"><br>
A note about the X axis in these graphs – each point is the interval between x<sup>2</sup> and (x+1)<sup>2</sup></p>
<h2 id="installation">Installation</h2>
<p><a href="https://github.com/alfille/sumofsquares">SumOfSquares</a> is hosted on Git Hub.<br>
The source code can be <a href="https://github.com/alfille/sumofsquares/archive/master.zip">downloaded</a> from the link on the page, or obtained via git:</p>
<pre><code>git clone https://github.com/alfille/sumofsquares.git
cd sumofsquares
gcc -O3 -o sos sos.c
chmod +x sos
</code></pre>
<h2 id="running-the-program">Running the program</h2>
<p>Simplest mode – should the decomposition for squares up to 4<sup>2</sup></p>
<pre><code>&gt; ./sos 4
1, 1
2, 1, 1   
3, 1, 1, 1
4, 2
5, 2, 1
6, 2, 1, 1
7, 2, 1, 1, 1
8, 2, 2
9, 3
10, 3, 1
11, 3, 1, 1
12, 2, 2, 2
13, 3, 2
14, 3, 2, 1
15, 3, 2, 1, 1  
16, 4
</code></pre>
<p>For example 10 = 3<sup>2</sup> + 1<sup>2</sup></p>
<hr>
<p>If you just want the count of terms in the decomposition:</p>
<pre><code>&gt; ./sos -c 4
1, 1
2, 2
3, 3
4, 1
5, 2
6, 3
7, 4
8, 2
9, 1
10, 2
11, 3
12, 3
13, 2
14, 3
15, 4
</code></pre>
<hr>
<p>Finally, if you want a summary for each interval between (n-1)<sup>2</sup>+1 and n<sup>2</sup> of the count of terms:</p>
<pre><code>&gt; ./sos 4 -s
1, 1, 0, 0, 0
2, 1, 1, 1, 0
3, 1, 2, 1, 1
4, 1, 2, 3, 1
</code></pre>
<p>Where, for instance, 3,1,2,1,1 means<br>
Interval 3: between (2<sup>2</sup>+1) and 3<sup>2</sup> = 5 to 9<br>
Term counts: 1 single, triple and quadruple term, and 2 dual term numbers.</p>
<hr>
<p>You can also explore other powers beside squares. For cubes:</p>
<pre><code>&gt; ./sos -p3 3
1, 1
2, 1, 1
3, 1, 1, 1
4, 1, 1, 1, 1
5, 1, 1, 1, 1, 1
6, 1, 1, 1, 1, 1, 1
7, 1, 1, 1, 1, 1, 1, 1
8, 2
9, 2, 1
10, 2, 1, 1
11, 2, 1, 1, 1
12, 2, 1, 1, 1, 1
13, 2, 1, 1, 1, 1, 1
14, 2, 1, 1, 1, 1, 1, 1
15, 2, 1, 1, 1, 1, 1, 1, 1
16, 2, 2
17, 2, 2, 1
18, 2, 2, 1, 1
19, 2, 2, 1, 1, 1
20, 2, 2, 1, 1, 1, 1
21, 2, 2, 1, 1, 1, 1, 1
22, 2, 2, 1, 1, 1, 1, 1, 1
23, 2, 2, 1, 1, 1, 1, 1, 1, 1
24, 2, 2, 2
25, 2, 2, 2, 1
26, 2, 2, 2, 1, 1
27, 3
</code></pre>
<p>Note that cube decomposition often needs many more terms.</p>
<pre><code>&gt; ./sos -p3 3 -s
1, 1, 0, 0, 0
2, 1, 1, 1, 1, 1, 1, 1
3, 1, 2, 3, 3, 3, 2, 2, 2, 1
</code></pre>
<h2 id="options">Options</h2>
<pre><code>&gt; ./sos -h
Sum-of-squares decomposition: Find the minimum number of integer squares that sum to a given number
{c} 2018 Paul H Alfille see https://github.com/alfille/sumofsquares
Usage ./sos number
look for sums up to &lt;number&gt; squared (default 100)
-m --max max_number used for squares
-3 --cube look for cubed number sums
-4 --fourth power sums
-5 --fifth power sums
-6 --sixth power sums
-p --power up to 10th
-c --count number of terms rather than list them
-s --summary of counts for each power interval
-h --help this summary
</code></pre>
<p>Integer Sequence<br>
The Online Encyplopedia of Integer Sequences calls this <a href="http://oeis.org/search?q=1,2,3,1,2,3,4,2,1&amp;language=english&amp;go=Search">Lagrange’s Four Squares Theorem</a>.</p>

