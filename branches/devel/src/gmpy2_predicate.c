/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * gmpy2_predicate.c                                                       *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Python interface to the GMP or MPIR, MPFR, and MPC multiple precision   *
 * libraries.                                                              *
 *                                                                         *
 * Copyright 2000, 2001, 2002, 2003, 2004, 2005, 2006, 2007,               *
 *           2008, 2009 Alex Martelli                                      *
 *                                                                         *
 * Copyright 2008, 2009, 2010, 2011, 2012, 2013, 2014 Case Van Horsen      *
 *                                                                         *
 * This file is part of GMPY2.                                             *
 *                                                                         *
 * GMPY2 is free software: you can redistribute it and/or modify it under  *
 * the terms of the GNU Lesser General Public License as published by the  *
 * Free Software Foundation, either version 3 of the License, or (at your  *
 * option) any later version.                                              *
 *                                                                         *
 * GMPY2 is distributed in the hope that it will be useful, but WITHOUT    *
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or   *
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public    *
 * License for more details.                                               *
 *                                                                         *
 * You should have received a copy of the GNU Lesser General Public        *
 * License along with GMPY2; if not, see <http://www.gnu.org/licenses/>    *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


/* To work with the MPC_IS_ macros, NAN, INF, FINITE, and ZERO are
 * all upper-case.
 */

PyDoc_STRVAR(GMPy_doc_function_is_nan,
"is_nan(x) -> boolean\n\n"
"Return True if x is NaN (Not-A-Number).");

PyDoc_STRVAR(GMPy_doc_context_is_nan,
"context.is_nan(x) -> boolean\n\n"
"Return True if x is NaN (Not-A-Number).");

PyDoc_STRVAR(GMPy_doc_method_is_nan,
"x.is_nan() -> boolean\n\n"
"Return True if x is NaN (Not-A-Number).");

static PyObject *
GMPy_Real_Is_NAN(PyObject *x, CTXT_Object *context)
{
    MPFR_Object *tempx;
    int res;

    if (MPFR_Check(x)) {
        res = mpfr_nan_p(MPFR(x));
    }
    else {
        CHECK_CONTEXT(context);
        if (!(tempx = GMPy_MPFR_From_Real(x, 1, context))) {
            return NULL;
        }
        res = mpfr_nan_p(tempx->f);
        Py_DECREF((PyObject*)tempx);
    }
    
    if (res) {
        Py_RETURN_TRUE;
    }
    else {
        Py_RETURN_FALSE;
    }
}

static PyObject *
GMPy_MPFR_Is_NAN_Method(PyObject *self, PyObject *args)
{
    return GMPy_Real_Is_NAN(self, NULL);
}

static PyObject *
GMPy_Complex_Is_NAN(PyObject *x, CTXT_Object *context)
{
    MPC_Object *tempx;
    int res;
    
    if (MPC_Check(x)) {
        res = MPC_IS_NAN_P(x);
    }
    else {
        CHECK_CONTEXT(context);
        if (!(tempx = GMPy_MPC_From_Complex(x, 1, 1, context))) {
            return NULL;
        }
        res = MPC_IS_NAN_P(tempx);
        Py_DECREF((PyObject*)tempx);
    }
    
    if (res) {
        Py_RETURN_TRUE;
    }
    else {
        Py_RETURN_FALSE;
    }
}

static PyObject *
GMPy_MPC_Is_NAN_Method(PyObject *self, PyObject *args)
{
    return GMPy_Complex_Is_NAN(self, NULL);
}

/* This creates the following functions:
 *   GMPy_Number_Is_NAN(x, context)
 *   GMPy_Context_Is_NAN(self, other)
 * 
 * They assume the following functions have been defined above:
 *   GMPy_Real_Is_NAN(x, context)
 *   GMPy_Complex_Is_NAN(x, context)
 * 
 * In addition, the following function should also be defined:
 *   GMPy_Real_Is_NAN_Method(self, noargs)
 *   GMPy_Complex_Is_NAN_Method(self, noargs)
 */
 
GMPY_MPFR_MPC_UNIOP_TEMPLATE(Is_NAN, is_nan);

PyDoc_STRVAR(GMPy_doc_function_is_infinite,
"is_infinite(x) -> boolean\n\n"
"Return True if x is +Infinity or -Infinity. If x is an mpc, return True\n"
"if either x.real or x.imag is infinite. ");

PyDoc_STRVAR(GMPy_doc_context_is_infinite,
"context.is_infinite(x) -> boolean\n\n"
"Return True if x is +Infinity or -Infinity. If x is an mpc, return True\n"
"if either x.real or x.imag is infinite.");

PyDoc_STRVAR(GMPy_doc_method_is_infinite,
"x.is_infinite() -> boolean\n\n"
"Return True if x is +Infinity or -Infinity. If x is an mpc, return True\n"
"if either x.real or x.imag is infinite.");

static PyObject *
GMPy_Real_Is_Infinite(PyObject *x, CTXT_Object *context)
{
    MPFR_Object *tempx;
    int res;

    if (MPFR_Check(x)) {
        res = mpfr_inf_p(MPFR(x));
    }
    else {
        CHECK_CONTEXT(context);
        if (!(tempx = GMPy_MPFR_From_Real(x, 1, context))) {
            return NULL;
        }
        res = mpfr_inf_p(tempx->f);
        Py_DECREF((PyObject*)tempx);
    }
    
    if (res) {
        Py_RETURN_TRUE;
    }
    else {
        Py_RETURN_FALSE;
    }
}

static PyObject *
GMPy_MPFR_Is_Infinite_Method(PyObject *self, PyObject *args)
{
    return GMPy_Real_Is_Infinite(self, NULL);
}

static PyObject *
GMPy_Complex_Is_Infinite(PyObject *x, CTXT_Object *context)
{
    MPC_Object *tempx;
    int res;
    
    if (MPC_Check(x)) {
        res = MPC_IS_INF_P(x);
    }
    else {
        CHECK_CONTEXT(context);
        if (!(tempx = GMPy_MPC_From_Complex(x, 1, 1, context))) {
            return NULL;
        }
        res = MPC_IS_INF_P(tempx);
        Py_DECREF((PyObject*)tempx);
    }
    
    if (res) {
        Py_RETURN_TRUE;
    }
    else {
        Py_RETURN_FALSE;
    }
}

static PyObject *
GMPy_MPC_Is_Infinite_Method(PyObject *self, PyObject *args)
{
    return GMPy_Complex_Is_Infinite(self, NULL);
}

GMPY_MPFR_MPC_UNIOP_TEMPLATE(Is_Infinite, is_infinite);

PyDoc_STRVAR(GMPy_doc_function_is_finite,
"is_finite(x) -> boolean\n\n"
"Return True if x is an actual number (i.e. non NaN or Infinity). If x is\n"
"an mpc, return True if both x.real and x.imag are finite.");

PyDoc_STRVAR(GMPy_doc_context_is_finite,
"context.is_finite(x) -> boolean\n\n"
"Return True if x is an actual number (i.e. non NaN or Infinity). If x is\n"
"an mpc, return True if both x.real and x.imag are finite.");

PyDoc_STRVAR(GMPy_doc_method_is_finite,
"x.is_finite() -> boolean\n\n"
"Return True if x is an actual number (i.e. non NaN or Infinity). If x is\n"
"an mpc, return True if both x.real and x.imag are finite.");

static PyObject *
GMPy_Real_Is_Finite(PyObject *x, CTXT_Object *context)
{
    MPFR_Object *tempx;
    int res;

    if (MPFR_Check(x)) {
        res = mpfr_number_p(MPFR(x));
    }
    else {
        CHECK_CONTEXT(context);
        if (!(tempx = GMPy_MPFR_From_Real(x, 1, context))) {
            return NULL;
        }
        res = mpfr_number_p(tempx->f);
        Py_DECREF((PyObject*)tempx);
    }
    
    if (res) {
        Py_RETURN_TRUE;
    }
    else {
        Py_RETURN_FALSE;
    }
}

static PyObject *
GMPy_MPFR_Is_Finite_Method(PyObject *self, PyObject *args)
{
    return GMPy_Real_Is_Finite(self, NULL);
}

static PyObject *
GMPy_Complex_Is_Finite(PyObject *x, CTXT_Object *context)
{
    MPC_Object *tempx;
    int res;
    
    if (MPC_Check(x)) {
        res = MPC_IS_FINITE_P(x);
    }
    else {
        CHECK_CONTEXT(context);
        if (!(tempx = GMPy_MPC_From_Complex(x, 1, 1, context))) {
            return NULL;
        }
        res = MPC_IS_FINITE_P(tempx);
        Py_DECREF((PyObject*)tempx);
    }
    
    if (res) {
        Py_RETURN_TRUE;
    }
    else {
        Py_RETURN_FALSE;
    }
}

static PyObject *
GMPy_MPC_Is_Finite_Method(PyObject *self, PyObject *args)
{
    return GMPy_Complex_Is_Finite(self, NULL);
}

GMPY_MPFR_MPC_UNIOP_TEMPLATE(Is_Finite, is_finite);

PyDoc_STRVAR(GMPy_doc_function_is_zero,
"is_zero(x) -> boolean\n\n"
"Return True if x is equal to 0. If x is an mpc, return True if both x.real\n"
"and x.imag are equal to 0.");

PyDoc_STRVAR(GMPy_doc_context_is_zero,
"context.is_zero(x) -> boolean\n\n"
"Return True if x is equal to 0. If x is an mpc, return True if both x.real\n"
"and x.imag are equal to 0.");

PyDoc_STRVAR(GMPy_doc_method_is_zero,
"x.is_zero() -> boolean\n\n"
"Return True if x is equal to 0. If x is an mpc, return True if both x.real\n"
"and x.imag are equal to 0.");
    
static PyObject *
GMPy_Real_Is_Zero(PyObject *x, CTXT_Object *context)
{
    MPFR_Object *tempx;
    int res;

    if (MPFR_Check(x)) {
        res = mpfr_zero_p(MPFR(x));
    }
    else {
        CHECK_CONTEXT(context);
        if (!(tempx = GMPy_MPFR_From_Real(x, 1, context))) {
            return NULL;
        }
        res = mpfr_zero_p(tempx->f);
        Py_DECREF((PyObject*)tempx);
    }
    
    if (res) {
        Py_RETURN_TRUE;
    }
    else {
        Py_RETURN_FALSE;
    }
}

static PyObject *
GMPy_MPFR_Is_Zero_Method(PyObject *self, PyObject *args)
{
    return GMPy_Real_Is_Zero(self, NULL);
}

static PyObject *
GMPy_Complex_Is_Zero(PyObject *x, CTXT_Object *context)
{
    MPC_Object *tempx;
    int res;
    
    if (MPC_Check(x)) {
        res = MPC_IS_ZERO_P(x);
    }
    else {
        CHECK_CONTEXT(context);
        if (!(tempx = GMPy_MPC_From_Complex(x, 1, 1, context))) {
            return NULL;
        }
        res = MPC_IS_ZERO_P(tempx);
        Py_DECREF((PyObject*)tempx);
    }
    
    if (res) {
        Py_RETURN_TRUE;
    }
    else {
        Py_RETURN_FALSE;
    }
}

static PyObject *
GMPy_MPC_Is_Zero_Method(PyObject *self, PyObject *args)
{
    return GMPy_Complex_Is_Zero(self, NULL);
}

GMPY_MPFR_MPC_UNIOP_TEMPLATE(Is_Zero, is_zero);