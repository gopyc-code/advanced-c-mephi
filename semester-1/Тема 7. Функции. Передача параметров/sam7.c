#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

long three2ten(long x3);
int ten2three(long x10, long *x3);
int sum10over(long a, long b);
int mul10over(long a, long b);
int sum3(long a, long b, long *res);
int pow3(long a, long n, long *res);
int mul3(long a, long b, long *res);
int sum3lazy(long a, long b, long *res);
int sub3(long a, long b, long *res);
int div3(long a, long b, long *res);
int mod3(long a, long b, long *res);
int calc1(long a, long b);
int calc2(long a, long b);
int calc3(long a, long b);

int main(void) {
    long a, b, code;
    scanf("%ld%ld", &a, &b);

    if (code = calc1(a, b))
        printf("!%ld\n", code);

    if (code = calc2(a, b))
        printf("!%ld\n", code);

    if (code = calc3(a, b))
        printf("!%ld\n", code);

    return 0;
}

int calc1(long a, long b) {
    long f, p1, p2, p3, p4, p5, p6;
    if (f = pow3(b, 2, &p1))
        return f;
    if (f = mul3(a, p1, &p2))
        return f;
    if (f = sub3(b, a, &p3))
        return f;
    if (f = mul3(a, p3, &p4))
        return f;
    if (f = sub3(p2, p4, &p5))
        return f;
    if (f = sum3lazy(b, p5, &p6))
        return f;
    printf("%ld\n", p6);
    return 0;
}

int calc2(long a, long b) {
    long f, p1, p2, p3;
    if (f = pow3(a, 3, &p1))
        return f;
    if (f = sum3lazy(p1, b, &p2))
        return f;
    if (f = div3(p2, b, &p3))
        return f;
    printf("%ld\n", p3);
    return 0;
}

int calc3(long a, long b) {
    long f, p1, p2, p3;
    if (f = pow3(b, 3, &p1))
        return f;
    if (f = sum3lazy(a, p1, &p2))
        return f;
    if (f = mod3(p2, a, &p3))
        return f;
    printf("%ld\n", p3);
    return 0;
}

int mul10over(long a, long b) {
    long x = a * b;
    return (a != x / b);
}

int sum10over(long a, long b) {
    return (a > 2122222222 - b);
}

long three2ten(long x3) {
    long res = 0, fact = 1;

    while (x3) {
        res += x3 % 10 * fact;
        fact *= 3;
        x3 /= 10;
    }

    return res;
}

int ten2three(long x10, long *x3) {
    if (!x10) {
        *x3 = 0;
        return 0;
    }
    long fact = 1, sign = x10 / abs(x10);
    *x3 = 0, x10 = abs(x10);

    while (x10) {
        if (sum10over(x10 % 3, fact))
            return 1;
        *x3 += x10 % 3 * fact;
        x10 /= 3;
        if (x10 && mul10over(fact, 10))
            return 3;
        fact *= 10;
    }

    *x3 *= sign;
    return 0;
}

int sum3(long a, long b, long *res) {
    long p = 1, cur, x = 0;
    int first = 1;

    while (a || b) {
        if (!first) {
            if (mul10over(p, 10))
                return 1;
            p *= 10;
        } first = 0;
        cur = x / p + a % 10 + b % 10;
        if (cur < 3) {
            if (mul10over(cur, p) ||
                sum10over(x % p, p * cur))
                return 1;
            x = x % p + p * cur;
        } else {
            if (mul10over(10, p) ||
                mul10over(cur / 3, p * 10) ||
                sum10over(cur % 3 * p,
                cur / 3 * p * 10))
                return 1;
            x = x % p + cur % 3 * p +
            cur / 3 * p * 10;
        }
        a /= 10;
        b /= 10;
    }

    *res = x;
    return 0;
}

int mul3(long a, long b, long *res) {
    if (!a || !b) {
        *res = 0;
        return 0;
    }

    long sign = a / abs(a) * b / abs(b),
    acopy = abs(a);
    a = abs(a), b = abs(b);

    for (long i = 1; i < three2ten(b); i++)
        if (sum3(a, acopy, &a) == 1)
            return 3;

    *res = sign * a;
    return 0;
}

int pow3(long a, long n, long *res) {
    if (!n) {
        *res = 1;
        return 0;
    } if (!a) {
        *res = 0;
        return 0;
    }

    long sign = a / abs(a), acopy = abs(a);
    a = abs(a);

    for (long i = 1; i < n; i++)
        if (mul3(a, acopy, &a) == 3)
            return 4;

    if (n % 2 && sign < 0)
        a *= sign;
    *res = a;
    return 0;
}

int sum3lazy(long a, long b, long *res) {
    long a1 = three2ten(a), b1 = three2ten(b);
    long code;

    if ((a <= 0 && b >= 0) || (a >= 0 && b <= 0)) {
        code = ten2three(a1 + b1, res);
        if (code == 1 || code == 3)
            return 1;
        return 0;
    }

    long sign = 1;
    if (a <= 0 || b <= 0)
        sign = -1;

    a1 = abs(a1), b1 = abs(b1);

    code = ten2three(sign * (a1 + b1), res);
    if (code == 1 || code == 3)
        return 1;
    return 0;
}

int sub3(long a, long b, long *res) {
    b = -b;
    if (sum3lazy(a, b, res) == 1)
        return 2;
    return 0;
}

int div3(long a, long b, long *res) {
    long a1 = three2ten(a), b1 = three2ten(b);
    if (!b)
        return 5;
    long code = ten2three(a1 / b1, res);
    if (code == 1 || code == 3)
        return 5;
    return 0;
}

int mod3(long a, long b, long *res) {
    long a1 = three2ten(a), b1 = three2ten(b);
    if (!b)
        return 6;
    long code = ten2three(a1 % b1, res);
    if (code == 1 || code == 3)
        return 6;
    return 0;
}

