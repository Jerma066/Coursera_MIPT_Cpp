#include "search_server.h"
#include "iterator_range.h"
#include "parse.h"
#include "profile_advanced.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>

InvertedIndex::InvertedIndex(istream& document_input) {
	for (string current_document; getline(document_input, current_document); ) {
		docs.push_back(move(current_document));
		size_t docid = docs.size() - 1;
		for (string_view word : SplitIntoWordsView(docs.back())) {
			auto& docids = index[word];
			if (!docids.empty() && docids.back().docid == docid) {
				++docids.back().hitcount;
			} 
			else {
				docids.push_back({docid, 1});
			}
		}
	}
}
const vector<InvertedIndex::Entry>& InvertedIndex::Lookup(string_view word) const {
	static const vector<Entry> empty;
	if (auto it = index.find(word); it != index.end()) {
		return it->second;
	} 
	else {
		return empty;
	}
}

SearchServer::SearchServer(istream& document_input) : 
	index(document_input) 
{
}

void SearchServer::UpdateDocumentBase(istream& document_input) {
  index = InvertedIndex(document_input);
}

void SearchServer::AddQueriesStream(istream& query_input, 
									ostream& search_results_output) 
{
  const auto& documents = index.GetDocuments();
  vector<size_t> docid_count(documents.size());
  vector<int64_t> docids(documents.size());

  TotalDuration words_split("  Words split");
  TotalDuration lookup("  Lookup");
  TotalDuration sorting("  Sort");
  TotalDuration build_results("  Build results");
  TotalDuration total_iteration("  Total loop iteration");

  for (string current_query; getline(query_input, current_query); ) {
    ADD_DURATION(total_iteration);

    vector<string_view> words;
    {
      ADD_DURATION(words_split);
      words = SplitIntoWordsView(current_query);
    };

    docid_count.assign(docid_count.size(), 0);
    {
      ADD_DURATION(lookup);
      for (const auto& word : words) {
        for (const auto& [docid, hit_count] : index.Lookup(word)) {
          docid_count[docid] += hit_count;
        }
      }
    }

    iota(docids.begin(), docids.end(), 0);
    {
      ADD_DURATION(sorting);
      partial_sort(
        begin(docids),
        Head(docids, 5).end(),
        end(docids),
        [&docid_count](int64_t lhs, int64_t rhs) {
          return make_pair(docid_count[lhs], -lhs) > make_pair(docid_count[rhs], -rhs);
        }
      );
    }

    ADD_DURATION(build_results);
    search_results_output << current_query << ':';
    for (size_t docid : Head(docids, 5)) {
      const size_t hit_count = docid_count[docid];
      if (hit_count == 0) {
        break;
      }

      search_results_output << " {"
          << "docid: " << docid << ", "
          << "hitcount: " << hit_count << '}';
    }
    search_results_output << '\n';
  }
}

