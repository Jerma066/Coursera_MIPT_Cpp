#pragma once

#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <string>
#include <deque>
#include <map>
#include <algorithm>
#include <numeric>

using namespace std;

class InvertedIndex {
public:
	struct Entry {
		size_t docid, hitcount;
	};	

	InvertedIndex() = default;
	explicit InvertedIndex(istream& document_input);

public:	
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
  explicit SearchServer(istream& document_input);
  
public:
  void UpdateDocumentBase(istream& document_input);
  void AddQueriesStream(istream& query_input, ostream& search_results_output);

private:
  InvertedIndex index;
};
