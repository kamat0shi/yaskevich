<!DOCTYPE html>
<html lang="ru">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Vape Shop Management System</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            line-height: 1.6;
            margin: 20px;
        }
        h1, h2 {
            font-family: 'Academy Engraved LET', sans-serif;
            font-weight: bold;
        }
        ul, ol {
            margin: 0;
            padding: 0;
            list-style: none;
        }
        ul li, ol li {
            margin-bottom: 10px;
        }
        code {
            font-family: monospace;
        }
        a {
            color: #1a0dab;
        }
    </style>
</head>
<body>
    <h1>Vape Shop Management System</h1>

    <h2>Описание</h2>
    <p>Проект представляет собой простую систему управления магазином, позволяющую управлять продавцами, товарами, продажами и вести финансовую отчетность. Приложение разработано с использованием C++ и поддерживает функционал для взаимодействия с пользователями через консоль.</p>

    <h2>Функциональные возможности</h2>
    <ol>
        <li><strong>Отображение информации о магазине:</strong>
            <ul>
                <li>Вывод информации обо всех продавцах и товарах магазина.</li>
                <li>Доступно как для обычных пользователей, так и для администраторов.</li>
            </ul>
        </li>
        <li><strong>Управление продавцами:</strong>
            <ul>
                <li><strong>Добавление продавца:</strong> Возможность добавлять новых продавцов с указанием имени, зарплаты и статуса администратора.</li>
                <li><strong>Удаление продавца:</strong> Удаление продавца по его имени.</li>
            </ul>
        </li>
        <li><strong>Управление товарами:</strong>
            <ul>
                <li><strong>Добавление товара:</strong> Добавление новых товаров с указанием названия, розничной и оптовой цены, а также количества.</li>
                <li><strong>Удаление товара:</strong> Удаление товара по его названию.</li>
            </ul>
        </li>
        <li><strong>Система продаж:</strong>
            <ul>
                <li>Продавцы могут выбирать товары для продажи.</li>
                <li>Функционал для проведения продажи с учётом количества товара.</li>
                <li>Количество товаров на складе уменьшается после продажи.</li>
            </ul>
        </li>
        <li><strong>Подсчёт финансов:</strong>
            <ul>
                <li><strong>Подсчёт выручки:</strong> Сумма всех продаж, совершённых через систему.</li>
                <li><strong>Подсчёт прибыли:</strong> Разница между розничной и оптовой ценой проданных товаров.</li>
                <li><strong>Подсчёт зарплаты продавцов:</strong> Зарплата продавцов рассчитывается в зависимости от объёма их продаж.</li>
            </ul>
        </li>
        <li><strong>Отчётность продаж:</strong>
            <ul>
                <li><strong>Отчёты по продажам:</strong> Сводка по проданным товарам с указанием суммы продаж и полученной прибыли.</li>
                <li><strong>Функции отчетности за периоды:</strong> Возможность генерировать отчёты за различные временные периоды, например, по месяцам.</li>
            </ul>
        </li>
    </ol>

    <h2>Структура проекта</h2>
    <ul>
        <li><strong>Product.h и Product.cpp:</strong> Класс <code>Product</code> управляет товарами в магазине. Включает информацию о названии товара, розничной и оптовой цене, а также количестве на складе.</li>
        <li><strong>Seller.h и Seller.cpp:</strong> Класс <code>Seller</code> представляет продавца магазина. Содержит данные о имени продавца, его зарплате и статусе администратора.</li>
        <li><strong>Shop.h и Shop.cpp:</strong> Класс <code>Shop</code> управляет продавцами, товарами и продажами. Реализует функции добавления, удаления, продажи и отображения информации о магазине.</li>
        <li><strong>main.cpp:</strong> Основной файл программы, содержащий логику работы с пользователем через консольное меню. Включает функции добавления, удаления, просмотра и продаж товаров и продавцов.</li>
    </ul>

    <h2>Как использовать</h2>
    <ol>
        <li>Скомпилируйте проект с помощью компилятора C++ (например, <code>g++</code>, <code>clang</code>).</li>
        <li>Запустите полученный исполняемый файл.</li>
        <li>Следуйте инструкциям в консоли для взаимодействия с системой:
            <ul>
                <li>Выбирайте действия через числовое меню.</li>
                <li>Для удаления продавцов или товаров введите имя или название, когда программа запросит это.</li>
                <li>Для проведения продажи выберите продавца, товар и укажите количество.</li>
            </ul>
        </li>
    </ol>

    <h2>Требования</h2>
    <ul>
        <li><strong>C++20</strong> или новее.</li>
    </ul>

    <h2>Возможности для расширения</h2>
    <ul>
        <li>Поддержка более сложных финансовых расчётов (например, налоги, скидки).</li>
        <li>Графический интерфейс для более удобного взаимодействия с системой.</li>
        <li>Поддержка базы данных для хранения информации о продавцах, товарах и продажах.</li>
    </ul>

    <h2>Ссылка на SonarCloud</h2>
    <p>Для анализа качества кода и проверки на ошибки вы можете перейти по следующей ссылке: <a href="https://sonarcloud.io/project/overview?id=kamat0shi_yaskevich_PonLHL">SonarCloud Overview</a></p>
</body>
</html>
