#pragma once

#include "search_server.h"
#include "synchronized.h"

#include <istream>
#include <ostream>
#include <vector>
#include <string>
#include <string_view>
#include <queue>
#include <future>
#include <map>
using namespace std;

class InvertedIndex {
public:
  struct Entry {
    size_t docid, hitcount;
  };

  InvertedIndex() = default;
  explicit InvertedIndex(istream& document_input);

  const vector<Entry>& Lookup(string_view word) const;

  const deque<string>& GetDocuments() const {
    return docs;
  }

private:
  deque<string> docs;
  map<string_view, vector<Entry>> index;
};

class SearchServer {
public:
  SearchServer() = default;
  explicit SearchServer(istream& document_input)
    : index(InvertedIndex(document_input))
  {
  }

  void UpdateDocumentBase(istream& document_input);
  void AddQueriesStream(istream& query_input, ostream& search_results_output);

private:
  Synchronized<InvertedIndex> index;
  vector<future<void>> async_tasks;
};

