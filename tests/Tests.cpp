#include <gtest/gtest.h>

#include <cstddef>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <utility>

#include "Matrix.h"
#include "ConstantGenerator.h"
#include "ZeroGenerator.h"
#include "IStreamGenerator.h"
#include "RandomGenerator.h"
#include "Task1.h"
#include "Task2.h"

using namespace miit::algebra;

namespace
{
    const ZeroGenerator zeroGenerator;

    Matrix<int> makeMatrix(
        const std::size_t rows,
        const std::size_t columns,
        const char* values)
    {
        Matrix<int> matrix(rows, columns);
        std::istringstream input(values);
        input >> matrix;
        return matrix;
    }
}

TEST(MatrixConstruction, DefaultConstructorCreatesEmptyMatrix)
{
    const Matrix<int> matrix;
    EXPECT_EQ(matrix.rowsCount(), 0U);
    EXPECT_EQ(matrix.columnsCount(), 0U);
    EXPECT_TRUE(matrix.empty());
}

TEST(MatrixConstruction, SizedConstructorInitializesEveryElement)
{
    const Matrix<int> matrix(2U, 3U);
    EXPECT_EQ(matrix.rowsCount(), 2U);
    EXPECT_EQ(matrix.columnsCount(), 3U);
    EXPECT_EQ(matrix[1U][2U], 0);
}

TEST(MatrixConstruction, PreservesColumnsWhenThereAreNoRows)
{
    const Matrix<int> matrix(0U, 3U);
    EXPECT_EQ(matrix.rowsCount(), 0U);
    EXPECT_EQ(matrix.columnsCount(), 3U);
    EXPECT_TRUE(matrix.empty());
}

TEST(MatrixValueSemantics, CopyIsDeep)
{
    Matrix<int> source = makeMatrix(2U, 2U, "1 2 3 4");
    Matrix<int> copy(source);
    copy[0U][0U] = 99;

    EXPECT_EQ(source[0U][0U], 1);
    EXPECT_EQ(copy[0U][0U], 99);
}

TEST(MatrixValueSemantics, CopyAndMoveAssignmentsPreserveValues)
{
    const Matrix<int> expected = makeMatrix(2U, 2U, "1 2 3 4");
    Matrix<int> copyAssigned;
    copyAssigned = expected;
    EXPECT_EQ(copyAssigned, expected);

    Matrix<int> movable(expected);
    Matrix<int> moveAssigned;
    moveAssigned = std::move(movable);
    EXPECT_EQ(moveAssigned, expected);
    EXPECT_EQ(movable.rowsCount(), 0U);
    EXPECT_EQ(movable.columnsCount(), 0U);
}

TEST(MatrixValueSemantics, MoveConstructorPreservesValues)
{
    Matrix<int> source = makeMatrix(2U, 2U, "1 2 3 4");
    const Matrix<int> expected(source);
    Matrix<int> moved(std::move(source));
    EXPECT_EQ(moved, expected);
    EXPECT_EQ(source.rowsCount(), 0U);
    EXPECT_EQ(source.columnsCount(), 0U);
}

TEST(MatrixAccess, IndexOperatorsProvideCheckedRowAccess)
{
    Matrix<int> matrix = makeMatrix(2U, 2U, "1 2 3 4");
    const Matrix<int>& constant = matrix;

    EXPECT_EQ(matrix[1U][0U], 3);
    EXPECT_EQ(constant[0U][1U], 2);
    EXPECT_THROW((void)matrix[2U], std::out_of_range);
    EXPECT_THROW((void)constant[2U], std::out_of_range);
}

TEST(MatrixText, ConvertsToStringAndWritesToStream)
{
    const Matrix<int> matrix = makeMatrix(2U, 3U, "1 -2 3 4 5 6");
    EXPECT_EQ(matrix.toString(), "1 -2 3\n4 5 6");

    std::ostringstream output;
    output << matrix;
    EXPECT_EQ(output.str(), matrix.toString());
}

TEST(MatrixText, ReadsFromStream)
{
    Matrix<int> matrix(2U, 2U);
    std::istringstream input("1 2 3 4");
    input >> matrix;

    EXPECT_TRUE(input);
    EXPECT_EQ(matrix, makeMatrix(2U, 2U, "1 2 3 4"));
}

TEST(MatrixText, ReportsIncompleteInput)
{
    Matrix<int> matrix(2U, 2U);
    std::istringstream input("1 2 3");
    input >> matrix;
    EXPECT_FALSE(input);
}

TEST(Generators, ConstantGeneratorReturnsConfiguredValue)
{
    const ConstantGenerator generator(-17);
    EXPECT_EQ(generator.generate(), -17);
    EXPECT_EQ(generator.generate(), -17);
}

TEST(Generators, ZeroGeneratorReturnsZero)
{
    const ZeroGenerator generator;
    EXPECT_EQ(generator.generate(), 0);
}

TEST(Generators, RandomGeneratorUsesClosedRange)
{
    const RandomGenerator generator(-3, 4);
    for (std::size_t sample = 0U; sample < 200U; ++sample)
    {
        const int value = generator.generate();
        EXPECT_GE(value, -3);
        EXPECT_LE(value, 4);
    }
}

TEST(Generators, RandomGeneratorRejectsReversedRange)
{
    EXPECT_THROW((RandomGenerator(5, 4)), std::invalid_argument);
}

TEST(Generators, IStreamGeneratorReadsAndValidatesInput)
{
    std::istringstream input("8 -2");
    const IStreamGenerator generator(input);

    EXPECT_EQ(generator.generate(), 8);
    EXPECT_EQ(generator.generate(), -2);
    EXPECT_THROW(generator.generate(), std::runtime_error);
}

TEST(Generators, IStreamGeneratorSupportsApprovedDefaultConstructor)
{
    const IStreamGenerator generator;
    (void)generator;
}

TEST(MatrixFill, UsesGeneratorPolymorphically)
{
    Matrix<int> matrix(2U, 2U);
    const std::unique_ptr<Generator> generator = std::make_unique<ConstantGenerator>(6);
    matrix.fill(*generator);

    EXPECT_EQ(matrix, makeMatrix(2U, 2U, "6 6 6 6"));
}

TEST(Exercise, FillChangesAggregatedSourceMatrix)
{
    Matrix<int> matrix(1U, 3U);
    const ConstantGenerator generator(9);
    Task1 task(matrix, generator);
    task.Fill();

    EXPECT_EQ(matrix, makeMatrix(1U, 3U, "9 9 9"));
}

TEST(Task1, ReplacesOneMaximumInEachRow)
{
    Matrix<int> matrix = makeMatrix(3U, 3U, "3 7 1 5 -1 4 -8 -3 -5");
    Task1 task(matrix, zeroGenerator);

    EXPECT_EQ(task.Solve(), makeMatrix(3U, 3U, "3 0 1 0 -1 4 -8 0 -5"));
}

TEST(Task1, EqualMaximaUseFirstOccurrence)
{
    Matrix<int> matrix = makeMatrix(2U, 3U, "4 4 1 -2 -2 -5");
    Task1 task(matrix, zeroGenerator);

    EXPECT_EQ(task.Solve(), makeMatrix(2U, 3U, "0 4 1 0 -2 -5"));
}

TEST(Task1, DoesNotChangeSourceMatrix)
{
    Matrix<int> matrix = makeMatrix(2U, 2U, "1 9 7 2");
    const Matrix<int> original(matrix);
    Task1 task(matrix, zeroGenerator);
    (void)task.Solve();

    EXPECT_EQ(matrix, original);
}

TEST(Task1, RepeatedSolveStartsFromOriginalMatrix)
{
    Matrix<int> matrix = makeMatrix(2U, 2U, "1 9 7 2");
    Task1 task(matrix, zeroGenerator);
    const Matrix<int> first = task.Solve();
    EXPECT_EQ(task.Solve(), first);
}

TEST(Task1, SupportsEmptyAndZeroColumnMatrices)
{
    Matrix<int> empty;
    Task1 emptyTask(empty, zeroGenerator);
    EXPECT_TRUE(emptyTask.Solve().empty());

    Matrix<int> zeroColumns(2U, 0U);
    Task1 zeroColumnTask(zeroColumns, zeroGenerator);
    EXPECT_EQ(zeroColumnTask.Solve().rowsCount(), 2U);
    EXPECT_EQ(zeroColumnTask.Solve().columnsCount(), 0U);
}

TEST(Task2, InsertsZeroRowsBeforeMatchingRows)
{
    Matrix<int> matrix = makeMatrix(4U, 2U, "3 1 2 2 -6 5 7 8");
    Task2 task(matrix, zeroGenerator);

    EXPECT_EQ(task.Solve(), makeMatrix(6U, 2U, "0 0 3 1 2 2 0 0 -6 5 7 8"));
}

TEST(Task2, TreatsZeroAsDivisibleByThree)
{
    Matrix<int> matrix = makeMatrix(2U, 2U, "0 4 1 2");
    Task2 task(matrix, zeroGenerator);

    EXPECT_EQ(task.Solve(), makeMatrix(3U, 2U, "0 0 0 4 1 2"));
}

TEST(Task2, HandlesNoMatchesAndAllMatches)
{
    Matrix<int> noMatches = makeMatrix(2U, 2U, "1 2 5 6");
    Task2 noMatchTask(noMatches, zeroGenerator);
    EXPECT_EQ(noMatchTask.Solve(), noMatches);

    Matrix<int> allMatches = makeMatrix(2U, 2U, "3 1 6 2");
    Task2 allMatchTask(allMatches, zeroGenerator);
    EXPECT_EQ(allMatchTask.Solve(), makeMatrix(4U, 2U, "0 0 3 1 0 0 6 2"));
}

TEST(Task2, DoesNotChangeSourceMatrix)
{
    Matrix<int> matrix = makeMatrix(2U, 2U, "3 1 2 2");
    const Matrix<int> original(matrix);
    Task2 task(matrix, zeroGenerator);
    (void)task.Solve();

    EXPECT_EQ(matrix, original);
}

TEST(Task2, RepeatedSolveDoesNotInsertRowsTwice)
{
    Matrix<int> matrix = makeMatrix(2U, 2U, "3 1 2 2");
    Task2 task(matrix, zeroGenerator);
    const Matrix<int> first = task.Solve();
    EXPECT_EQ(task.Solve(), first);
}

TEST(Task2, SupportsEmptyAndZeroColumnMatrices)
{
    Matrix<int> empty;
    Task2 emptyTask(empty, zeroGenerator);
    EXPECT_TRUE(emptyTask.Solve().empty());

    Matrix<int> zeroColumns(2U, 0U);
    Task2 zeroColumnTask(zeroColumns, zeroGenerator);
    EXPECT_EQ(zeroColumnTask.Solve().rowsCount(), 2U);
    EXPECT_EQ(zeroColumnTask.Solve().columnsCount(), 0U);
}
