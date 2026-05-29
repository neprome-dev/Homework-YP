#pragma once

/**
* @brief Класс-помощник для сравнения вещественных чисел
*/
class MathHelper
{
private:
	/**
	* @param defaultEpsilon - точность сравнения по умолчанию
	*/
	static const double defaultEpsilon;
public:
	/**
	* @brief Сравнивает два вещественных числа с заданной точностью
	* @param left - первое сравниваемое число
	* @param right - второе сравниваемое число
	* @param epsilon - точность сравнения
	* @return Если числа равны с заданной точностью - 1, иначе 0
	*/
	static bool isEqual(const double left, const double right, const double epsilon);

	/**
	* @brief Сравнивает два вещественных числа с точностью по умолчанию
	* @param left - первое сравниваемое число
	* @param right - второе сравниваемое число
	* @return Если числа равны с точностью по умолчанию - 1, иначе 0
	*/
	static bool isEqual(const double left, const double right);
};
