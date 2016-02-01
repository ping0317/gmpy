# Using gmpy2 and mpfr #

## Overview ##

MPFR is a library that provides correctly rounding multiple precision floating-point aithmetic. In addition to supporting the basic arithmetic operations, MPFR support a wide variety of both elementary and advanced functions. The precision and exponent range can be changed to suit the needs of a particular calculation.

## Examples ##

Some trivial examples.

```
>>> import gmpy2
>>> gmpy2.mpfr("1.2")
mpfr('1.2')
>>> gmpy2.sqrt(gmpy2.mpfr("3.2"))
mpfr('1.7888543819998317')
>>> gmpy2.sin(gmpy2.mpfr(".5"))
mpfr('0.47942553860420301')
>>> 
```

`help(gmpy2)` will display all the online documentation. Help for an individual function can also be displayed.

```
>>> help(gmpy2.sin)
Help on built-in function sin in module gmpy2:

sin(...)
    sin(x): returns sine of x; x in radians.

>>>
```

**gmpy2** uses a context manager to control the precision and exponent range, rounding mode, track the occurrence of any "exceptions", and to optionally raise a Python exception.

```
>>> gmpy2.get_context()
context(subnormalize=False,
        precision=53,
        round=RoundToNearest,
        emax=1073741823, emin=-1073741823,
        trap_underflow=False, underflow=False,
        trap_overflow=False, overflow=False,
        trap_inexact=False, inexact=True,
        trap_invalid=False, invalid=False,
        trap_erange=False, erange=False,
        trap_divzero=False, divzero=False)
>>>
```

The default precision is 53 bits, which corresponds to approximately 16 decimal digits. To change the working precision, just change the precision attribute of the current context.

```
>>> gmpy2.get_context().precision = 100
>>> gmpy2.sqrt(gmpy2.mpfr("3.2"))
mpfr('1.7888543819998318067780219999297',100)
>>> gmpy2.get_context()
context(subnormalize=False,
        precision=100,
        round=RoundToNearest,
        emax=1073741823, emin=-1073741823,
        trap_underflow=False, underflow=False,
        trap_overflow=False, overflow=False,
        trap_inexact=False, inexact=True,
        trap_invalid=False, invalid=False,
        trap_erange=False, erange=False,
        trap_divzero=False, divzero=False)
>>>
```

In the previous example, the precision was increased to 100 bits and then the sqrt(3.2) was calculated. Since sqrt(3.2) can not be calculated exactly, the inexact flag is set. The flags accumulate all the exceptional conditions that occur during a sequence of calculations. To clear all the flags, use `gmpy2.get_context().clear_flags()`. To clear an individual flag, use `gmpy2.get_context().inexact = False`.

When exceptional conditions are encountered, MPFR returns "nan", "inf", or "-inf" and sets the appropriate exception flag. This is the default behavior in **gmpy2**. Exceptions can be enabled by setting the corresponding trap attribute of the context.

```
>>> gmpy2.get_context()
context(subnormalize=False,
        precision=100,
        round=RoundToNearest,
        emax=1073741823, emin=-1073741823,
        trap_underflow=False, underflow=False,
        trap_overflow=False, overflow=False,
        trap_inexact=False, inexact=False,
        trap_invalid=False, invalid=False,
        trap_erange=False, erange=False,
        trap_divzero=False, divzero=False)
>>> 1/gmpy2.mpfr(0)
mpfr('inf')
>>> gmpy2.get_context()
context(subnormalize=False,
        precision=100,
        round=RoundToNearest,
        emax=1073741823, emin=-1073741823,
        trap_underflow=False, underflow=False,
        trap_overflow=False, overflow=False,
        trap_inexact=False, inexact=False,
        trap_invalid=False, invalid=False,
        trap_erange=False, erange=False,
        trap_divzero=False, divzero=True)
>>> gmpy2.get_context().trap_divzero = True
>>> 1/gmpy2.mpfr(0)
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
gmpy2.DivisionByZeroError: 'mpfr' division by zero
>>> 
```

By setting `gmpy2.get_context().trap_erange = True`, comparisons involving "nan" will generate an exception.

```
>>> gmpy2.get_context().trap_erange = True
>>> gmpy2.mpfr('nan') == gmpy2.mpfr('nan')
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
gmpy2.RangeError: comparison with NaN
```

Setting `trap_underflow` will generate an exception if a calculation underflows to 0. Setting `trap_overflow` will generate an exception if the result of a calculation exceeds the exponent range. Setting `trap_invalid` will generate an exception if an invalid operation, say `gmpy2.asin(34)`, is attempted.

`get_context()` creates a reference to the current context. A new context object can be created with `context()`. To activate a context object, use `set_context(context())`. The "with ..." statement can also be used.

```
>>> with gmpy2.local_context() as ctxt:
...     for i in range(4):
...         ctxt.precision += 10
...         print(gmpy2.mpfr(gmpy2.sqrt(2.0)))
... 
1.4142135623730950488
1.4142135623730950488017
1.4142135623730950488016887
1.4142135623730950488016887241
>>> 
```

Another example ...

```
>>> gmpy2.mpfr("1.2345") + gmpy2.mpfr("3.56789")
mpfr('4.8023899999999999999999999999987',100)
>>> gmpy2.mpfr("1.000000000000000000001") + gmpy2.mpfr("3.000000000000000000007")
mpfr('4.0000000000000000000079999999986',100)
>>>
```

The last examples illustrate that MPFR uses a binary, or power of 2, representation. Just like 1/3 = 0.3333... can not be represented exactly with decimal number, most decimal numbers can not be represented exactly in binary format. If you have a need for exact decimal math, financial calculation, for example, you should look at the Decimal module included with Python.

Values can be displayed to a specific number of digits.

```
>>> format(gmpy2.mpfr("1.2345") + gmpy2.mpfr("3.56789"), ".20")
'4.80239000000000000000'
```