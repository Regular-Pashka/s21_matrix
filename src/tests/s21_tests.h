#ifndef S21_TEST_H
#define S21_TEST_H

#include <check.h>
#include <stdio.h>

#include "../s21_matrix.h"

Suite *suiteCalcComplements(void);
Suite *suiteCreateMatrix(void);
Suite *suiteDeterminant(void);
Suite *suiteEqMatrix(void);
Suite *suiteInverseMatrix(void);
Suite *suiteMultMatrix(void);
Suite *suiteMultNumber(void);
Suite *suiteRemoveMatrix(void);
Suite *suiteSubMatrix(void);
Suite *suiteSumMatrix(void);
Suite *suiteTranspose(void);

void runTests(void);
void runTestcase(Suite *testcase);

#endif