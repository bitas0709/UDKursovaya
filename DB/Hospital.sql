-- phpMyAdmin SQL Dump
-- version 4.6.6deb5
-- https://www.phpmyadmin.net/
--
-- Хост: localhost:3306
-- Время создания: Янв 21 2020 г., 07:05
-- Версия сервера: 5.7.28-0ubuntu0.19.04.2
-- Версия PHP: 7.2.24-0ubuntu0.19.04.2

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- База данных: `Hospital`
--

DELIMITER $$
--
-- Процедуры
--
CREATE DEFINER=`bitas0709`@`%` PROCEDURE `CreateTableMedicWorkLoad` ()  NO SQL
CREATE TABLE `Hospital`.`TempTable` ( `НомерОперации` INT NOT NULL, `ДатаПроведенияОперации` DATE NOT NULL, `ВремяНачалаОперации` TIME NOT NULL, `ВремяПроведенияОперации` TIME NOT NULL, `ДатаПосещения` DATE NOT NULL, `ВремяНачалаПосещения` TIME NOT NULL, `ВремяПосещения` TIME NOT NULL) ENGINE = INNODB CHARSET=utf8mb4 COLLATE utf8mb4_unicode_ci$$

CREATE DEFINER=`bitas0709`@`%` PROCEDURE `FillTableMedicWorkLoad` (IN `MedNum` INT, IN `VisitTime` TIME)  NO SQL
INSERT INTO TempTable
SELECT a.НомерОперации, a.ДатаПроведенияОперации, a.ВремяНачалаОперации, b.ВремяПроведения, c.ДатаПосещения, c.ВремяПосещения, VisitTime FROM Операции a join ТипОперации b on a.НомерТипаОперации = b.НомерОперации join Посещение c ON a.НомерВрача = c.НомерВрача
where a.НомерИсторииБолезни in
(SELECT НомерЗаписи from ИсторияБолезни
where НомерПосещения in
(SELECT НомерПосещения from Посещение where НомерВрача = MedNum))$$

CREATE DEFINER=`bitas0709`@`%` PROCEDURE `WatchMedicsCard` ()  NO SQL
SELECT a.НомерВрача, a.Фамилия, a.Имя, a.Отчество, a.ДатаНайма, b.Профессия, a.НомерТелефона
FROM Врачи a join ПрофессииВрача b
WHERE a.НомерПрофессии = b.НомерПрофессии$$

CREATE DEFINER=`bitas0709`@`%` PROCEDURE `WatchMedicsCard1` (OUT `MedNum` INT, OUT `LastName` VARCHAR(30) CHARSET utf8mb4, OUT `FirstName` VARCHAR(30) CHARSET utf8mb4, OUT `HireDate` DATE, OUT `Profession` VARCHAR(30) CHARSET utf8mb4, OUT `MobileNum` VARCHAR(15) CHARSET utf8mb4)  NO SQL
SELECT a.НомерВрача, a.Фамилия, a.Имя, a.Отчество, a.ДатаНайма, b.Профессия, a.НомерТелефона
FROM Врачи a join ПрофессииВрача b
WHERE a.НомерПрофессии = b.НомерПрофессии
#set MedNum = a.НомерВрача#set LastName = a.Фамилия#set FirstName = a.Имя#set HireDate = a.ДатаНайма#set Profession = b.Профессия#set MobileNum = a.НомерТелефона$$

DELIMITER ;

-- --------------------------------------------------------

--
-- Структура таблицы `TempTable`
--

CREATE TABLE `TempTable` (
  `НомерОперации` int(11) NOT NULL,
  `ДатаПроведенияОперации` date NOT NULL,
  `ВремяНачалаОперации` time NOT NULL,
  `ВремяПроведенияОперации` time NOT NULL,
  `ДатаПосещения` date NOT NULL,
  `ВремяНачалаПосещения` time NOT NULL,
  `ВремяПосещения` time NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Дамп данных таблицы `TempTable`
--

INSERT INTO `TempTable` (`НомерОперации`, `ДатаПроведенияОперации`, `ВремяНачалаОперации`, `ВремяПроведенияОперации`, `ДатаПосещения`, `ВремяНачалаПосещения`, `ВремяПосещения`) VALUES
(1, '2019-05-20', '16:30:00', '00:30:00', '2019-05-12', '12:00:00', '00:30:00'),
(1, '2019-05-20', '16:30:00', '00:30:00', '2019-07-16', '12:00:00', '00:30:00');

-- --------------------------------------------------------

--
-- Структура таблицы `Врачи`
--

CREATE TABLE `Врачи` (
  `НомерВрача` int(11) NOT NULL,
  `Фамилия` varchar(30) COLLATE utf8mb4_unicode_ci NOT NULL,
  `Имя` varchar(30) COLLATE utf8mb4_unicode_ci NOT NULL,
  `Отчество` varchar(30) COLLATE utf8mb4_unicode_ci NOT NULL,
  `ДатаНайма` date NOT NULL,
  `НомерПрофессии` int(11) NOT NULL,
  `НомерТелефона` varchar(15) COLLATE utf8mb4_unicode_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Дамп данных таблицы `Врачи`
--

INSERT INTO `Врачи` (`НомерВрача`, `Фамилия`, `Имя`, `Отчество`, `ДатаНайма`, `НомерПрофессии`, `НомерТелефона`) VALUES
(1, 'Григорян', 'Александр', 'Владимирович', '2017-03-12', 1, '1415642451'),
(2, 'Жучков', 'Георгий', 'Викторович', '2010-05-04', 2, '1515436785'),
(3, 'Наумов', 'Николай', 'Алексеевич', '2019-01-15', 1, '9515745671'),
(4, 'Картавцева', 'Екатерина', 'Семёновна', '2018-11-01', 3, '9625642411'),
(5, 'Степнова', 'Любовь', 'Михайловна', '2011-04-20', 4, '9995762176');

-- --------------------------------------------------------

--
-- Структура таблицы `ИсторияБолезни`
--

CREATE TABLE `ИсторияБолезни` (
  `НомерЗаписи` int(11) NOT NULL,
  `НомерПосещения` int(11) NOT NULL,
  `НомерЗаболевания` int(11) NOT NULL,
  `ДатаЗаболевания` date NOT NULL,
  `ДатаВыздоровления` date NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Дамп данных таблицы `ИсторияБолезни`
--

INSERT INTO `ИсторияБолезни` (`НомерЗаписи`, `НомерПосещения`, `НомерЗаболевания`, `ДатаЗаболевания`, `ДатаВыздоровления`) VALUES
(1, 1, 1, '2019-05-12', '2019-05-30'),
(2, 2, 3, '2019-05-12', '2019-05-25'),
(3, 3, 4, '2019-05-20', '2019-05-31'),
(4, 7, 2, '2019-12-20', '2019-12-31');

-- --------------------------------------------------------

--
-- Структура таблицы `Операции`
--

CREATE TABLE `Операции` (
  `НомерОперации` int(11) NOT NULL,
  `НомерТипаОперации` int(11) NOT NULL,
  `НомерИсторииБолезни` int(11) NOT NULL,
  `НомерВрача` int(11) NOT NULL,
  `ДатаПроведенияОперации` date NOT NULL,
  `ВремяНачалаОперации` time NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Дамп данных таблицы `Операции`
--

INSERT INTO `Операции` (`НомерОперации`, `НомерТипаОперации`, `НомерИсторииБолезни`, `НомерВрача`, `ДатаПроведенияОперации`, `ВремяНачалаОперации`) VALUES
(1, 1, 1, 2, '2019-05-20', '16:30:00'),
(2, 3, 2, 1, '2019-05-18', '12:30:00'),
(3, 4, 3, 3, '2019-05-25', '14:00:00'),
(4, 2, 4, 2, '2019-12-23', '16:00:00');

-- --------------------------------------------------------

--
-- Структура таблицы `Пациенты`
--

CREATE TABLE `Пациенты` (
  `НомерПациента` int(11) NOT NULL,
  `Фамилия` varchar(30) COLLATE utf8mb4_unicode_ci NOT NULL,
  `Имя` varchar(30) COLLATE utf8mb4_unicode_ci NOT NULL,
  `Отчество` varchar(30) COLLATE utf8mb4_unicode_ci NOT NULL,
  `Пол` varchar(10) COLLATE utf8mb4_unicode_ci NOT NULL,
  `ДатаРождения` date NOT NULL,
  `Адрес` varchar(255) COLLATE utf8mb4_unicode_ci NOT NULL,
  `НомерМедПолиса` int(16) NOT NULL,
  `НомерПаспорта` varchar(10) COLLATE utf8mb4_unicode_ci NOT NULL,
  `НомерТелефона` varchar(15) COLLATE utf8mb4_unicode_ci DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Дамп данных таблицы `Пациенты`
--

INSERT INTO `Пациенты` (`НомерПациента`, `Фамилия`, `Имя`, `Отчество`, `Пол`, `ДатаРождения`, `Адрес`, `НомерМедПолиса`, `НомерПаспорта`, `НомерТелефона`) VALUES
(1, 'Алексеев', 'Иван', 'Геннадьевич', 'Мужской', '1975-12-25', 'мкр. Комсомолец, д. 21', 23457654, '56НМ756498', '9516754726'),
(2, 'Мизынчук', 'Артём', 'Сергеевич', 'Мужской', '1985-02-16', 'ул. Приборостроителей, д. 121', 46573865, '56АУ574621', '9045764612'),
(3, 'Савайтан', 'Олег', 'Петрович', 'Мужской', '1991-05-12', 'ул. Конева, д. 16', 46572652, '67НА576486', '9245865746'),
(4, 'Кривошеев', 'Алексей', 'Сергеевич', 'Мужской', '1992-07-21', 'мкр. Дубрава, д. 5', 57461264, '86АУ869532', '9125742654'),
(5, 'Рыжикова', 'Светлана', 'Олеговна', 'Женский', '1962-03-01', 'мкр. Парковый, д. 1', 57625786, '75НА284757', '9543235891'),
(6, 'Уваров', 'Альберт', 'Алексеевич', 'Мужской', '1996-01-22', 'ул. Молодогвардеец, д. 4', 47261263, '56АМ574612', ''),
(7, 'Халапян', 'Георгий', 'Александрович', 'Мужской', '1997-09-02', 'ул. Матросова, д.6', 74621823, '28НА741231', '9231238712'),
(8, 'Иванов', 'Сергей', 'Федорович', 'Мужской', '1962-09-21', 'ул. Приборостроителей, д.2', 47562162, '57ЙФ462172', '9421234212');

-- --------------------------------------------------------

--
-- Структура таблицы `Посещение`
--

CREATE TABLE `Посещение` (
  `НомерПосещения` int(11) NOT NULL,
  `НомерПациента` int(11) NOT NULL,
  `НомерВрача` int(11) NOT NULL,
  `ДатаПосещения` date NOT NULL,
  `ВремяПосещения` time NOT NULL,
  `Жалоба` varchar(2048) COLLATE utf8mb4_unicode_ci NOT NULL,
  `РезультатОбследования` varchar(4096) COLLATE utf8mb4_unicode_ci NOT NULL,
  `Цена` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Дамп данных таблицы `Посещение`
--

INSERT INTO `Посещение` (`НомерПосещения`, `НомерПациента`, `НомерВрача`, `ДатаПосещения`, `ВремяПосещения`, `Жалоба`, `РезультатОбследования`, `Цена`) VALUES
(1, 1, 2, '2019-05-12', '12:00:00', 'Жалоба', 'Всё Плохо', 2000),
(2, 4, 1, '2019-05-12', '13:00:00', 'Жалоба', 'Требуется Операция', 4000),
(3, 2, 4, '2019-05-20', '14:00:00', 'Жалоба', 'Требуется Операция', 3000),
(4, 7, 5, '2019-06-15', '11:30:00', 'Жалоба', 'Всё Плохо', 5000),
(5, 3, 3, '2012-08-20', '16:00:00', 'Жалоба', 'Все ясно', 3000),
(6, 5, 2, '2019-07-16', '12:00:00', 'Жалоба', 'Обследование', 3000),
(7, 6, 1, '2019-12-20', '11:00:00', 'Жалоба', 'Нужна операция', 2000);

--
-- Триггеры `Посещение`
--
DELIMITER $$
CREATE TRIGGER `RejectVisitIfMedicIsBusy` BEFORE INSERT ON `Посещение` FOR EACH ROW begin

if (new.ДатаПосещения = '2019-10-16') then
  SIGNAL sqlstate '45001' set message_text = "No way ! You cannot do this !";
end if;
end
$$
DELIMITER ;

-- --------------------------------------------------------

--
-- Структура таблицы `ПрофессииВрача`
--

CREATE TABLE `ПрофессииВрача` (
  `НомерПрофессии` int(11) NOT NULL,
  `Профессия` varchar(50) COLLATE utf8mb4_unicode_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Дамп данных таблицы `ПрофессииВрача`
--

INSERT INTO `ПрофессииВрача` (`НомерПрофессии`, `Профессия`) VALUES
(1, 'Профессия1'),
(2, 'Профессия2'),
(3, 'Профессия3'),
(4, 'Профессия4');

-- --------------------------------------------------------

--
-- Структура таблицы `ТипЗаболевания`
--

CREATE TABLE `ТипЗаболевания` (
  `НомерЗаболевания` int(11) NOT NULL,
  `Заболевание` varchar(50) COLLATE utf8mb4_unicode_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Дамп данных таблицы `ТипЗаболевания`
--

INSERT INTO `ТипЗаболевания` (`НомерЗаболевания`, `Заболевание`) VALUES
(1, 'Заболевание1'),
(2, 'Заболевание2'),
(3, 'Заболевание3'),
(4, 'Заболевание4');

-- --------------------------------------------------------

--
-- Структура таблицы `ТипОперации`
--

CREATE TABLE `ТипОперации` (
  `НомерОперации` int(11) NOT NULL,
  `Операция` varchar(50) COLLATE utf8mb4_unicode_ci NOT NULL,
  `ВремяПроведения` time NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Дамп данных таблицы `ТипОперации`
--

INSERT INTO `ТипОперации` (`НомерОперации`, `Операция`, `ВремяПроведения`) VALUES
(1, 'Операция1', '00:30:00'),
(2, 'Операция2', '01:00:00'),
(3, 'Операция3', '00:40:00'),
(4, 'Операция4', '06:00:00');

--
-- Индексы сохранённых таблиц
--

--
-- Индексы таблицы `Врачи`
--
ALTER TABLE `Врачи`
  ADD PRIMARY KEY (`НомерВрача`),
  ADD KEY `Medic_ifbk_1` (`НомерПрофессии`);

--
-- Индексы таблицы `ИсторияБолезни`
--
ALTER TABLE `ИсторияБолезни`
  ADD PRIMARY KEY (`НомерЗаписи`),
  ADD KEY `DiseaseHistory_ifbk_1` (`НомерПосещения`),
  ADD KEY `DiseaseHistory_ifbk_2` (`НомерЗаболевания`);

--
-- Индексы таблицы `Операции`
--
ALTER TABLE `Операции`
  ADD PRIMARY KEY (`НомерОперации`),
  ADD KEY `Operation_ifbk_1` (`НомерТипаОперации`),
  ADD KEY `Operation_ifbk_2` (`НомерИсторииБолезни`),
  ADD KEY `Operation_ifbk_3` (`НомерВрача`);

--
-- Индексы таблицы `Пациенты`
--
ALTER TABLE `Пациенты`
  ADD PRIMARY KEY (`НомерПациента`);

--
-- Индексы таблицы `Посещение`
--
ALTER TABLE `Посещение`
  ADD PRIMARY KEY (`НомерПосещения`),
  ADD KEY `Limit1` (`НомерПациента`),
  ADD KEY `Limit2` (`НомерВрача`);

--
-- Индексы таблицы `ПрофессииВрача`
--
ALTER TABLE `ПрофессииВрача`
  ADD PRIMARY KEY (`НомерПрофессии`);

--
-- Индексы таблицы `ТипЗаболевания`
--
ALTER TABLE `ТипЗаболевания`
  ADD PRIMARY KEY (`НомерЗаболевания`);

--
-- Индексы таблицы `ТипОперации`
--
ALTER TABLE `ТипОперации`
  ADD PRIMARY KEY (`НомерОперации`);

--
-- Ограничения внешнего ключа сохраненных таблиц
--

--
-- Ограничения внешнего ключа таблицы `Врачи`
--
ALTER TABLE `Врачи`
  ADD CONSTRAINT `Medic_ifbk_1` FOREIGN KEY (`НомерПрофессии`) REFERENCES `ПрофессииВрача` (`НомерПрофессии`);

--
-- Ограничения внешнего ключа таблицы `ИсторияБолезни`
--
ALTER TABLE `ИсторияБолезни`
  ADD CONSTRAINT `DiseaseHistory_ifbk_1` FOREIGN KEY (`НомерПосещения`) REFERENCES `Посещение` (`НомерПосещения`),
  ADD CONSTRAINT `DiseaseHistory_ifbk_2` FOREIGN KEY (`НомерЗаболевания`) REFERENCES `ТипЗаболевания` (`НомерЗаболевания`);

--
-- Ограничения внешнего ключа таблицы `Операции`
--
ALTER TABLE `Операции`
  ADD CONSTRAINT `Operation_ifbk_1` FOREIGN KEY (`НомерТипаОперации`) REFERENCES `ТипОперации` (`НомерОперации`),
  ADD CONSTRAINT `Operation_ifbk_2` FOREIGN KEY (`НомерИсторииБолезни`) REFERENCES `ИсторияБолезни` (`НомерЗаписи`),
  ADD CONSTRAINT `Operation_ifbk_3` FOREIGN KEY (`НомерВрача`) REFERENCES `Врачи` (`НомерВрача`);

--
-- Ограничения внешнего ключа таблицы `Посещение`
--
ALTER TABLE `Посещение`
  ADD CONSTRAINT `Limit1` FOREIGN KEY (`НомерПациента`) REFERENCES `Пациенты` (`НомерПациента`),
  ADD CONSTRAINT `Limit2` FOREIGN KEY (`НомерВрача`) REFERENCES `Врачи` (`НомерВрача`);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
