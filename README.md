# Вариант 5. «Музыкальный салон»
## Описание
Постоянно работающий музыкальный салон продает компакт-диски с записями 14 определенных исполнителей, поступающие от различных компаний-производителей. 
### Управление салона владеет информацией:
*О компакт-дисках:*
- код компакта
- дата изготовления
- компания-производитель
- цена одного компакта

*Об исполнителях музыкальных произведений:*
- название музыкального произведения
- автор
- исполнитель
- код компактa
  
*О поступлении и продаже компактов:*
- дата операции
- код операции (поступление или продажа)
- код компакта
- количество экземпляров

### Покупатель может узнать информацию:
Только данные - смотрите ниже по пункту, помеченному `*` *(звездочкой)*
Поле | Информация
------------ | -------------
по всем компактам | сведения о количестве проданных и оставшихся компактов одного вида по убыванию разницы
по указанному компакту | сведения о количестве и стоимости компактов, проданных за указанный период
по компакту, купленному максимальное количество раз | сведения о нем и музыкальных произведениях `*`
по наиболее популярному исполнителю | сведения о количестве проданных компактов с его произведениями `*`
по каждому автору | сведения о количестве проданных компактов с его записями и сумме полученных денег

### Выполнено: 
1. Таблицы БД с учетом ограничений целостности данных
2. Оператор Select 
3. С помощью операторов Insert, Update, Delete обновление информации в указанных таблицах
4. Функция, которая запрещает помещать информацию о продаже компактов в таблицу, если суммарное количество проданных компактов превысит суммарное количество поступивших
5. Функция, которая за указанный период определяет количество поступивших и проданных компактов по каждому виду. В качестве параметра передается начальная дата периода и конечная дата периода. Результаты заносятся в специальную таблицу
6. По заданному коду компакта выводит информацию о результатах его продажи за указанный период `*`

## Установка:
- Скачать с гитхаба проект
- Запустить через командную строку мейкфайл
- Запустить итоговый исполняемый файл

## Использование приложения после установки:
Запустите приложение в консоли. Далее следуйте указаниям.

## Сведения об авторах проекта и какие задачи реализовывали:
1. Аладко Анастасия
2. Будник Кирилл
3. Доброцкая Мария
4. Романовец Алексей
