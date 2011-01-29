// Simple calculator for 1 digit number and single expression
// purposely obtuse for stack trace
// calculate() takes a length 3 string

function add(a, b) {
    return a + b;
}

function subtract(a, b) {
    return a - b;
}

function multiply(a, b) {
    return a * b;
}

function divide(a, b) {
    if( b == 0 )
        throw Error("Divide by Zero");
    
    return a / b;
}

function dispatch(op, a, b) {
    var lookup = {
        '+': add
      , '-': subtract
      , '*': multiply
      , '/': divide
    };

    var fun = lookup[op];
    return fun(a, b);
}

function calculate(expr) {
    var a = parseInt(expr[0]);
    var b = parseInt(expr[2]);

    var op = expr[1];
    return dispatch(op, a, b);
}
