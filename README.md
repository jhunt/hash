jhunt/hash
==========

Hashing.  It's one of _the fundamentals_ of Computer Science, but
how do you compare the **performance** of a given hash function to
another?

Here, you will find my attempts at solving that problem for
multiple personal projects.  I'm not (currently) in the business
of defining new hashing algorithms, so it just focuses on hash
functions built by smarter people than me, and attempts to portray
their behavior and performance characteristics.

Above all, this _test suite_ strives to be flexible, enabling new
tests corpora to be integrated with minimal effort.

I hope you find this useful.

Fitness Tests
-------------

In order to gauge the _fitness_ of a particular hash function, we
can check _simple uniformity_, or how evenly the algorithm
distributes output values.  A hash function that always returns
the value `42` is decidedly non-uniform.

_Simple_ uniformity must be differentiated from _random_
uniformity.  For simple uniformity, we don't care how random the
distribution appears, we just care that it is even.  Random
uniformity has important implications for
_cryptographically-secure_ hashing functions, but for simple hash
tables (my original problem space) it may not be worth the effort.

Results
-------

Hashing ~235k English words over 64 bins (calculated `H(s) % 64`),
we can look at the scatter plot of bin clustering to get a gut
feel for how uniform each hash is:

![Scatter Plot][viz/scatter-all.png]

Yeesh.  XOR looks terrible, but that's not unexpected.
Here's the same test, without XOR:

![Scatter Plot (without XOR this time)][viz/scatter-serious.png]

We can do better on judging variance by using a boxplot:

![Box Plot][viz/whisker-all.png]

As before, XOR is off the charts, and makes it difficut to see the
relative differences between the other, more serious hashing
algorithms.  Here's the same test without XOR:

![Box Plot (without XOR this time)][viz/whisker-serious.png]
