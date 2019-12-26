-- phpMyAdmin SQL Dump
-- version 4.6.6deb5
-- https://www.phpmyadmin.net/
--
-- Хост: localhost:3306
-- Время создания: Дек 26 2019 г., 09:42
-- Версия сервера: 5.7.28-0ubuntu0.19.04.2
-- Версия PHP: 7.2.24-0ubuntu0.19.04.1

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- База данных: `Hospital`
--

-- --------------------------------------------------------

--
-- Структура таблицы `DiseaseHistory`
--

CREATE TABLE `DiseaseHistory` (
  `DiseaseHistoryNum` int(11) NOT NULL,
  `DiseaseNum` int(11) NOT NULL,
  `PatientNum` int(11) NOT NULL,
  `MedicNum` int(11) NOT NULL,
  `DateOfIllness` date NOT NULL,
  `DateOfRecovery` date NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Дамп данных таблицы `DiseaseHistory`
--

INSERT INTO `DiseaseHistory` (`DiseaseHistoryNum`, `DiseaseNum`, `PatientNum`, `MedicNum`, `DateOfIllness`, `DateOfRecovery`) VALUES
(1, 2, 1, 3, '2019-05-15', '2019-06-02'),
(2, 4, 2, 1, '2019-06-11', '2019-06-24'),
(3, 3, 5, 3, '2019-04-29', '2019-05-12'),
(4, 2, 4, 2, '2019-03-12', '2019-03-21');

-- --------------------------------------------------------

--
-- Структура таблицы `DiseaseType`
--

CREATE TABLE `DiseaseType` (
  `DiseaseNum` int(11) NOT NULL,
  `Disease` varchar(50) COLLATE utf8mb4_unicode_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Дамп данных таблицы `DiseaseType`
--

INSERT INTO `DiseaseType` (`DiseaseNum`, `Disease`) VALUES
(1, 'Заболевание1'),
(2, 'Заболевание2'),
(3, 'Заболевание3'),
(4, 'Заболевание4');

-- --------------------------------------------------------

--
-- Структура таблицы `Medic`
--

CREATE TABLE `Medic` (
  `MedicNum` int(11) NOT NULL,
  `LastName` varchar(30) COLLATE utf8mb4_unicode_ci NOT NULL,
  `FirstName` varchar(30) COLLATE utf8mb4_unicode_ci NOT NULL,
  `FatherName` varchar(30) COLLATE utf8mb4_unicode_ci NOT NULL,
  `HireDate` date NOT NULL,
  `ProfessionNum` int(11) NOT NULL,
  `MobileNum` varchar(15) COLLATE utf8mb4_unicode_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Дамп данных таблицы `Medic`
--

INSERT INTO `Medic` (`MedicNum`, `LastName`, `FirstName`, `FatherName`, `HireDate`, `ProfessionNum`, `MobileNum`) VALUES
(1, 'Григорян', 'Александр', 'Владимирович', '2017-03-12', 1, '1415642451'),
(2, 'Жучков', 'Георгий', 'Викторович', '2010-05-04', 2, '1515436785'),
(3, 'Наумов', 'Николай', 'Алексеевич', '2019-01-15', 1, '9515745671'),
(4, 'Картавцева', 'Екатерина', 'Семёновна', '2018-11-01', 3, '9625642411'),
(5, 'Степнова', 'Любовь', 'Михайловна', '2011-04-20', 4, '9995762176');

-- --------------------------------------------------------

--
-- Структура таблицы `MedicProfession`
--

CREATE TABLE `MedicProfession` (
  `ProfessionNum` int(11) NOT NULL,
  `Profession` varchar(50) COLLATE utf8mb4_unicode_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Дамп данных таблицы `MedicProfession`
--

INSERT INTO `MedicProfession` (`ProfessionNum`, `Profession`) VALUES
(1, 'Профессия1'),
(2, 'Профессия2'),
(3, 'Профессия3'),
(4, 'Профессия4');

-- --------------------------------------------------------

--
-- Структура таблицы `Operation`
--

CREATE TABLE `Operation` (
  `OperationNum` int(11) NOT NULL,
  `OperationTypeNum` int(11) NOT NULL,
  `DiseaseHistoryNum` int(11) NOT NULL,
  `OperationDate` date NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Дамп данных таблицы `Operation`
--

INSERT INTO `Operation` (`OperationNum`, `OperationTypeNum`, `DiseaseHistoryNum`, `OperationDate`) VALUES
(1, 2, 1, '2019-05-25'),
(2, 3, 2, '2019-06-15'),
(3, 3, 3, '2019-04-30'),
(4, 1, 4, '2019-03-15');

-- --------------------------------------------------------

--
-- Структура таблицы `OperationType`
--

CREATE TABLE `OperationType` (
  `OperationNum` int(11) NOT NULL,
  `Operation` varchar(50) COLLATE utf8mb4_unicode_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Дамп данных таблицы `OperationType`
--

INSERT INTO `OperationType` (`OperationNum`, `Operation`) VALUES
(1, 'Операция1'),
(2, 'Операция2'),
(3, 'Операция3'),
(4, 'Операция4');

-- --------------------------------------------------------

--
-- Структура таблицы `Patient`
--

CREATE TABLE `Patient` (
  `PatientNum` int(11) NOT NULL,
  `LastName` varchar(30) COLLATE utf8mb4_unicode_ci NOT NULL,
  `FirstName` varchar(30) COLLATE utf8mb4_unicode_ci NOT NULL,
  `FatherName` varchar(30) COLLATE utf8mb4_unicode_ci NOT NULL,
  `Sex` varchar(10) COLLATE utf8mb4_unicode_ci NOT NULL,
  `BirthDate` date NOT NULL,
  `Address` varchar(255) COLLATE utf8mb4_unicode_ci NOT NULL,
  `MedPolisNum` int(16) NOT NULL,
  `PassportNum` varchar(10) COLLATE utf8mb4_unicode_ci NOT NULL,
  `MobileNum` varchar(15) COLLATE utf8mb4_unicode_ci DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Дамп данных таблицы `Patient`
--

INSERT INTO `Patient` (`PatientNum`, `LastName`, `FirstName`, `FatherName`, `Sex`, `BirthDate`, `Address`, `MedPolisNum`, `PassportNum`, `MobileNum`) VALUES
(1, 'Алексеев', 'Иван', 'Геннадьевич', 'Мужской', '1975-12-25', 'мкр. Комсомолец, д. 21', 23457654, '56НМ756498', '9516754726'),
(2, 'Мизынчук', 'Артём', 'Сергеевич', 'Мужской', '1985-02-16', 'ул. Приборостроителей, д. 121', 46573865, '56АУ574621', '9045764612'),
(3, 'Савайтан', 'Олег', 'Петрович', 'Мужской', '1991-05-12', 'ул. Конева, д. 16', 46572652, '67НА576486', '9245865746'),
(4, 'Кривошеев', 'Алексей', 'Сергеевич', 'Мужской', '1992-07-21', 'мкр. Дубрава, д. 5', 57461264, '86АУ869532', '9125742654'),
(5, 'Рыжикова', 'Светлана', 'Олеговна', 'Женский', '1962-03-01', 'мкр. Парковый, д. 1', 57625786, '75НА284757', '9543235891');

--
-- Индексы сохранённых таблиц
--

--
-- Индексы таблицы `DiseaseHistory`
--
ALTER TABLE `DiseaseHistory`
  ADD PRIMARY KEY (`DiseaseHistoryNum`),
  ADD KEY `DiseaseHistory_ifbk_1` (`DiseaseNum`),
  ADD KEY `DiseaseHistory_ifbk_2` (`PatientNum`),
  ADD KEY `DiseaseHistory_ifbk_3` (`MedicNum`);

--
-- Индексы таблицы `DiseaseType`
--
ALTER TABLE `DiseaseType`
  ADD PRIMARY KEY (`DiseaseNum`);

--
-- Индексы таблицы `Medic`
--
ALTER TABLE `Medic`
  ADD PRIMARY KEY (`MedicNum`),
  ADD KEY `Medic_ifbk_1` (`ProfessionNum`);

--
-- Индексы таблицы `MedicProfession`
--
ALTER TABLE `MedicProfession`
  ADD PRIMARY KEY (`ProfessionNum`);

--
-- Индексы таблицы `Operation`
--
ALTER TABLE `Operation`
  ADD PRIMARY KEY (`OperationNum`),
  ADD KEY `Operation_ifbk_1` (`OperationTypeNum`),
  ADD KEY `Operation_ifbk_2` (`DiseaseHistoryNum`);

--
-- Индексы таблицы `OperationType`
--
ALTER TABLE `OperationType`
  ADD PRIMARY KEY (`OperationNum`);

--
-- Индексы таблицы `Patient`
--
ALTER TABLE `Patient`
  ADD PRIMARY KEY (`PatientNum`);

--
-- Ограничения внешнего ключа сохраненных таблиц
--

--
-- Ограничения внешнего ключа таблицы `DiseaseHistory`
--
ALTER TABLE `DiseaseHistory`
  ADD CONSTRAINT `DiseaseHistory_ifbk_1` FOREIGN KEY (`DiseaseNum`) REFERENCES `DiseaseType` (`DiseaseNum`),
  ADD CONSTRAINT `DiseaseHistory_ifbk_2` FOREIGN KEY (`PatientNum`) REFERENCES `Patient` (`PatientNum`),
  ADD CONSTRAINT `DiseaseHistory_ifbk_3` FOREIGN KEY (`MedicNum`) REFERENCES `Medic` (`MedicNum`);

--
-- Ограничения внешнего ключа таблицы `Medic`
--
ALTER TABLE `Medic`
  ADD CONSTRAINT `Medic_ifbk_1` FOREIGN KEY (`ProfessionNum`) REFERENCES `MedicProfession` (`ProfessionNum`);

--
-- Ограничения внешнего ключа таблицы `Operation`
--
ALTER TABLE `Operation`
  ADD CONSTRAINT `Operation_ifbk_1` FOREIGN KEY (`OperationTypeNum`) REFERENCES `OperationType` (`OperationNum`),
  ADD CONSTRAINT `Operation_ifbk_2` FOREIGN KEY (`DiseaseHistoryNum`) REFERENCES `DiseaseHistory` (`DiseaseHistoryNum`);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
