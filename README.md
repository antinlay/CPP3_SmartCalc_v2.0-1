Реализация Calc v2.0.

## Introduction

В данном проекте реализована на языке программирования С++ в парадигме объектно-ориентированного программирования расширенная версия обычного калькулятора, с теми же функциями, что и разработанное ранее приложение в проекте [Calc v1.0](https://github.com/antinlay/C7_SmartCalc_v1.0-1) Помимо базовых арифметических операций, как плюс-минус и умножить-поделить, калькулятор наделен возможностью вычисления арифметических выражений с учетом приоритетов, а так же некоторыми математическими функциями (синус, косинус, логарифм и т.д.). Помимо вычисления выражений калькулятор так же должен поддерживать использование переменной x и построение графика соответствующей функции. Дополнительно реализован кредитный и депозитный калькулятор.

## Information

Для реализации калькулятора следует использовать *алгоритм Дейкстры* для перевода выражений в *обратную польскую нотацию*.

### Паттерн MVC

Паттерн MVC (Model-View-Controller, Модель-Представление-Контроллер) представляет из себя схему разделения модулей приложения на три отдельных макрокомпонента: модель, содержащую в себе бизнес-логику, представление - форму пользовательского интерфейса для осуществления взаимодействия с программой и контроллер, осуществляющий модификацию модели по действию пользователя.

![](misc/images/MVC-Process.png)

[Статья на vc.ru](https://vc.ru/u/2211350-lebowski/793635-kalkulyator-2-0-shkola-21)
