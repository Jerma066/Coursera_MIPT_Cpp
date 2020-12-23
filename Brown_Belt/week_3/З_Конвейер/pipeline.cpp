#include "test_runner.h"
#include <functional>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

struct Email {
  string from;
  string to;
  string body;
};

class Worker {
public:
  virtual ~Worker() = default;
  virtual void Process(unique_ptr<Email> email) = 0;
  virtual void Run() {
    // только первому worker-у в пайплайне нужно это имплементировать
    throw logic_error("Unimplemented");
  }

protected:
  // реализации должны вызывать PassOn, чтобы передать объект дальше
  // по цепочке обработчиков
  void PassOn(unique_ptr<Email> email) const {
    if (cur_worker) {
      cur_worker->Process(move(email));
    }
  }

public:
  void SetNext(unique_ptr<Worker> next) { cur_worker = move(next); }

private:
  unique_ptr<Worker> cur_worker;
};

class Reader : public Worker {
public:
  Reader(istream &input) : in(input) {}

public:
  void Process(unique_ptr<Email> email) override { PassOn(move(email)); }

  void Run() override {
    while (in) {
      auto email = make_unique<Email>();
      getline(in, email->from);
      if (!in)
        break;
      getline(in, email->to);
      if (!in)
        break;
      getline(in, email->body);
      if (!in)
        break;
      PassOn(move(email));
    }
  }

private:
  istream &in;
};

class Filter : public Worker {
public:
  using Function = function<bool(const Email &)>;

public:
  Filter(Function func) : filter(func) {}

public:
  void Process(unique_ptr<Email> email) override {
    if (filter(*email)) {
      PassOn(move(email));
    }
  }

private:
  Function filter;
};

class Copier : public Worker {
public:
  Copier(const string to) : recipient(to) {}

public:
  void Process(unique_ptr<Email> email) override {
    if (email->to != recipient) {
      auto copy = make_unique<Email>(*email);
      copy->to = recipient;
      PassOn(move(email));
      PassOn(move(copy));
    } else {
      PassOn(move(email));
    }
  }

private:
  string recipient;
};

class Sender : public Worker {
public:
  Sender(ostream &output) : out(output) {}

public:
  void Process(unique_ptr<Email> email) override {
    out << email->from << '\n';
    out << email->to << '\n';
    out << email->body << '\n';
    PassOn(move(email));
  }

private:
  ostream &out;
};

// реализуйте класс
class PipelineBuilder {
public:
  // добавляет в качестве первого обработчика Reader
  explicit PipelineBuilder(istream &in) {
    workers.push_back(make_unique<Reader>(in));
  }

  // добавляет новый обработчик Filter
  PipelineBuilder &FilterBy(Filter::Function filter) {
    workers.push_back(make_unique<Filter>(move(filter)));
    return *this;
  }

  // добавляет новый обработчик Copier
  PipelineBuilder &CopyTo(string recipient) {
    workers.push_back(make_unique<Copier>(recipient));
    return *this;
  }

  // добавляет новый обработчик Sender
  PipelineBuilder &Send(ostream &out) {
    workers.push_back(make_unique<Sender>(out));
    return *this;
  }

  // возвращает готовую цепочку обработчиков
  unique_ptr<Worker> Build() {
    for (size_t i = workers.size() - 1; i > 0; i--) {
      workers[i - 1]->SetNext(move(workers[i]));
    }
    return move(workers[0]);
  }

private:
  vector<unique_ptr<Worker>> workers;
};

void TestSanity() {
  string input = ("erich@example.com\n"
                  "richard@example.com\n"
                  "Hello there\n"

                  "erich@example.com\n"
                  "ralph@example.com\n"
                  "Are you sure you pressed the right button?\n"

                  "ralph@example.com\n"
                  "erich@example.com\n"
                  "I do not make mistakes of that kind\n");
  istringstream inStream(input);
  ostringstream outStream;

  PipelineBuilder builder(inStream);
  builder.FilterBy(
      [](const Email &email) { return email.from == "erich@example.com"; });

  builder.CopyTo("richard@example.com");
  builder.Send(outStream);
  auto pipeline = builder.Build();
  pipeline->Run();

  string expectedOutput = ("erich@example.com\n"
                           "richard@example.com\n"
                           "Hello there\n"

                           "erich@example.com\n"
                           "ralph@example.com\n"
                           "Are you sure you pressed the right button?\n"

                           "erich@example.com\n"
                           "richard@example.com\n"
                           "Are you sure you pressed the right button?\n");

  ASSERT_EQUAL(expectedOutput, outStream.str());
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSanity);
  return 0;
}
