## Задание по программированию: Макрос UPDATE_FIELD

Продолжим работу над сервисом поиска авиабилетов AviaScanner. Наш сервис хранит базу данных билетов в виде vector<AirlineTicket>, где AirlineTicket — такая же структура, как и в предыдущей задаче. Периодически наш сервис обходит сайты авиакомпаний, собирает свежую информацию о доступных билетах и обновляет записи в своей базе данных. Делается это с помощью функции void UpdateTicket(AirlineTicket& ticket, const map<string, string>& updates). Параметр updates содержит пары (имя поля; новое значение). При этом он содержит только те поля, которые поменялись. Пример работы функции UpdateTicket:

```cpp
void UpdateTicketExample() {
  AirlineTicket t;
  t.price = 5000;
  t.from = "DME";
  t.to = "AER";

  const map<string, string> updates = {
    {"price", "3500"},
    {"from", "VKO"}
  };
  UpdateTicket(t, updates);
  ASSERT_EQUAL(t.from, "VKO");
  ASSERT_EQUAL(t.to, "AER");
  ASSERT_EQUAL(t.price, 3500);
}
```
Функцию UpdateTicket можно было бы реализовать так:
```cpp
void UpdateTicket(AirlineTicket& ticket, const map<string, string>& updates) {
  map<string, string>::const_iterator it;

  it = updates.find("to");
  if (it != updates.end()) {
    ticket.to = it->second;
  }

  it = updates.find("from");
  if (it != updates.end()) {
    ticket.from = it->second;
  }

  it = updates.find("price");
  if (it != updates.end()) {
    istringstream is(it->second);
    is >> ticket.price;
  }

  ...
}
```
Здесь налицо дублирование кода — блоки кода внутри функции UpdateTicket отличаются только именем поля (конечно, первые два блока не такие, как третий, но их легко к нему свести). При этом имя поля используется не только для обращения к структуре AirlineTicket, но и как строковый литерал. Поэтому можно написать макрос, который существенно упростит функцию UpdateTicket:
```cpp
#define UPDATE_FIELD(ticket, field, values) ...

void UpdateTicket(AirlineTicket& ticket, const map<string, string>& updates) {
  UPDATE_FIELD(ticket, to, updates);
  UPDATE_FIELD(ticket, from, updates);
  UPDATE_FIELD(ticket, price, updates);
  UPDATE_FIELD(ticket, airline, updates);
  ...
}
```
Напишите макрос UPDATE_FIELD. Вам дан файл airline_ticket.h, содержащий объявления структур Time, Date и AirlineTicket, а также заготовка решения в виде cpp-файла update_field.cpp. Пришлите на проверку cpp-файл, который

* подключает заголовочный файл airline_ticket.h
* содержит макрос UPDATE_FIELD
* содержит определения операторов, необходимых для считывания классов Date и Time из потока istream и их использования в макросе ASSERT_EQUAL (формат ввода смотрите в юнит-тестах в файле update_field.cpp)

