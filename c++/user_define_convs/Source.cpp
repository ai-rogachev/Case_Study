
// User-defined conversions
// https://ravesli.com/urok-140-peregruzka-operatsij-preobrazovaniya-tipov-dannyh/

struct X {
    //implicit conversion
    operator int() const { return 7; }
 
    // explicit conversion
    explicit operator int*() const { return nullptr; }
 
//  Error: array operator not allowed in conversion-type-id
//  operator int(*)[3]() const { return nullptr; }
    using arr_t = int[3];
    operator arr_t*() const { return nullptr; } // OK if done through typedef
//  operator arr_t () const; // Error: conversion to array not allowed in any case
};

// https://stackoverflow.com/questions/8239356/can-a-cast-operator-be-explicit
// https://www.ibm.com/docs/en/zos/2.2.0?topic=only-user-defined-conversions-c

/*
!!! Оператор преобразования типов данных возвращает объект по значению. !!!
Это значит, что будет вызывать один из конструкторов возвращаемого объекта. 
И если это будет конструктор копирования класса, в котором есть массив данных, то жди беды! 
*/