//============================================================================
// Name        : NewMounthTask.cpp
// Author      : Ragimov Islam
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// глобальные (доступные во всей программе) константы
// часто прин€то называть «ј√Ћј¬Ќџћ»_Ѕ” ¬јћ»
const vector<int> MONTH_LENGTHS =
  {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const int MONTH_COUNT = MONTH_LENGTHS.size();

int main() {
  int q;
  cin >> q;

  // номер текущего мес€ца (от 0 до 11)
  int month = 0;

  // внешний вектор должен иметь длину, равную количеству дней в первом мес€це;
  // все внутренние векторы по умолчанию пусты, потому что дел изначально нет
  vector<vector<string>> days_concerns(MONTH_LENGTHS[month]);

  for (int i = 0; i < q; ++i) {
    string operation_code;
    cin >> operation_code;

    if (operation_code == "ADD") {

      int day;
      string concern;
      cin >> day >> concern;
      --day;  // элементы вектора нумеруютс€ с нул€
      days_concerns[day].push_back(concern);

    } else if (operation_code == "NEXT") {

      // перед переходом к следующему мес€цу запомним длину предыдущего
      // обь€вл€ем эту переменную константной, потому что мен€ть еЄ не планируем
      const int old_month_length = MONTH_LENGTHS[month];

      // номер мес€ца должен увеличитьс€ на 1, но после декабр€ идЄт €нварь:
      // например, (5 + 1) % 12 = 6, но (11 + 1) % 12 = 0
      month = (month + 1) % MONTH_COUNT;

      const int new_month_length = MONTH_LENGTHS[month];

      // если новый мес€ц больше предыдущего, достаточно сделать resize;
      // иначе перед resize надо переместить дела с Ђлишнихї последних дней
      if (new_month_length < old_month_length) {

        // далее понадобитс€ добавл€ть новые дела в последний день нового мес€ца
        // чтобы не писать несколько раз days_concerns[new_month_length - 1],
        // создадим ссылку с более коротким названием дл€ этого вектора
        vector<string>& last_day_concerns = days_concerns[new_month_length - 1];

        // перебираем все Ђлишниеї дни в конце мес€ца
        for (int day = new_month_length; day < old_month_length; ++day) {
          // копируем вектор days_concerns[day]
          // в конец вектора last_day_concerns
          last_day_concerns.insert(
              end(last_day_concerns),
              begin(days_concerns[day]), end(days_concerns[day]));
        }
      }
      days_concerns.resize(new_month_length);

    } else if (operation_code == "DUMP") {

      int day;
      cin >> day;
      --day;

      // выводим список дел в конкретный день в нужном формате
      cout << days_concerns[day].size() << " ";
      for (const string& concern : days_concerns[day]) {
        cout << concern << " ";
      }
      cout << endl;

    }
  }

  return 0;
}
