#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

using namespace std;

template <typename It> class Range {
public:
  Range(It begin, It end) : begin_(begin), end_(end) {}
  It begin() const { return begin_; }
  It end() const { return end_; }

private:
  It begin_;
  It end_;
};

pair<string_view, optional<string_view>>
SplitTwoStrict(string_view s, string_view delimiter = " ") {
  const size_t pos = s.find(delimiter);
  if (pos == s.npos) {
    return {s, nullopt};
  } else {
    return {s.substr(0, pos), s.substr(pos + delimiter.length())};
  }
}

vector<string_view> Split(string_view s, string_view delimiter = " ") {
  vector<string_view> parts;
  if (s.empty()) {
    return parts;
  }
  while (true) {
    const auto [lhs, rhs_opt] = SplitTwoStrict(s, delimiter);
    parts.push_back(lhs);
    if (!rhs_opt) {
      break;
    }
    s = *rhs_opt;
  }
  return parts;
}

class Domain {
public:
  explicit Domain(string_view text) {
    vector<string_view> parts = Split(text, ".");
    parts_reversed_.assign(rbegin(parts), rend(parts));
  }

  size_t GetPartCount() const { return parts_reversed_.size(); }

  auto GetParts() const {
    return Range(rbegin(parts_reversed_), rend(parts_reversed_));
  }
  auto GetReversedParts() const {
    return Range(begin(parts_reversed_), end(parts_reversed_));
  }

  bool operator==(const Domain &other) const {
    return parts_reversed_ == other.parts_reversed_;
  }

private:
  vector<string> parts_reversed_;
};

ostream &operator<<(ostream &stream, const Domain &domain) {
  bool first = true;
  for (const string_view part : domain.GetParts()) {
    if (!first) {
      stream << '.';
    } else {
      first = false;
    }
    stream << part;
  }
  return stream;
}

// domain is subdomain of itself
bool IsSubdomain(const Domain &subdomain, const Domain &domain) {
  const auto subdomain_reversed_parts = subdomain.GetReversedParts();
  const auto domain_reversed_parts = domain.GetReversedParts();
  return subdomain.GetPartCount() >= domain.GetPartCount() &&
         equal(begin(domain_reversed_parts), end(domain_reversed_parts),
               begin(subdomain_reversed_parts));
}

bool IsSubOrSuperDomain(const Domain &lhs, const Domain &rhs) {
  return lhs.GetPartCount() >= rhs.GetPartCount() ? IsSubdomain(lhs, rhs)
                                                  : IsSubdomain(rhs, lhs);
}

class DomainChecker {
public:
  template <typename InputIt>
  DomainChecker(InputIt domains_begin, InputIt domains_end) {
    sorted_domains_.reserve(distance(domains_begin, domains_end));
    for (const Domain &domain : Range(domains_begin, domains_end)) {
      sorted_domains_.push_back(&domain);
    }
    sort(begin(sorted_domains_), end(sorted_domains_), IsDomainLess);
    sorted_domains_ = AbsorbSubdomains(move(sorted_domains_));
  }

  // Check if candidate is subdomain of some domain
  bool IsSubdomain(const Domain &candidate) const {
    const auto it = upper_bound(begin(sorted_domains_), end(sorted_domains_),
                                &candidate, IsDomainLess);
    if (it == begin(sorted_domains_)) {
      return false;
    }
    return ::IsSubdomain(candidate, **prev(it));
  }

private:
  vector<const Domain *> sorted_domains_;

  static bool IsDomainLess(const Domain *lhs, const Domain *rhs) {
    const auto lhs_reversed_parts = lhs->GetReversedParts();
    const auto rhs_reversed_parts = rhs->GetReversedParts();
    return lexicographical_compare(
        begin(lhs_reversed_parts), end(lhs_reversed_parts),
        begin(rhs_reversed_parts), end(rhs_reversed_parts));
  }

  static vector<const Domain *>
  AbsorbSubdomains(vector<const Domain *> domains) {
    domains.erase(unique(begin(domains), end(domains),
                         [](const Domain *lhs, const Domain *rhs) {
                           return IsSubOrSuperDomain(*lhs, *rhs);
                         }),
                  end(domains));
    return domains;
  }
};

vector<Domain> ReadDomains(istream &in_stream = cin) {
  vector<Domain> domains;

  size_t count;
  in_stream >> count;
  domains.reserve(count);

  for (size_t i = 0; i < count; ++i) {
    string domain_text;
    in_stream >> domain_text;
    domains.emplace_back(domain_text);
  }
  return domains;
}

vector<bool> CheckDomains(const vector<Domain> &banned_domains,
                          const vector<Domain> &domains_to_check) {
  const DomainChecker checker(begin(banned_domains), end(banned_domains));

  vector<bool> check_results;
  check_results.reserve(domains_to_check.size());
  for (const Domain &domain_to_check : domains_to_check) {
    check_results.push_back(!checker.IsSubdomain(domain_to_check));
  }

  return check_results;
}

void PrintCheckResults(const vector<bool> &check_results,
                       ostream &out_stream = cout) {
  for (const bool check_result : check_results) {
    out_stream << (check_result ? "Good" : "Bad") << "\n";
  }
}

void TestSimple() {
  vector<Domain> banned_domains;
  banned_domains.emplace_back("ya.ru");
  banned_domains.emplace_back("maps.me");

  vector<Domain> domains_to_check;
  domains_to_check.emplace_back("m.ya.ru");
  domains_to_check.emplace_back("google.com");
  domains_to_check.emplace_back("moscow.maps.me");

  auto results = CheckDomains(banned_domains, domains_to_check);
  ASSERT_EQUAL(results, (vector<bool>{0, 1, 0}));
}

void TestGetReversedParts() {
  Domain domain("www.ya.ru");
  vector<string> data = {"ru", "ya", "www"};
  auto box = domain.GetReversedParts();
  auto beginIt = box.begin();
  for (const auto &line : data) {
    ASSERT_EQUAL(line, *beginIt);
    ++beginIt;
  }
}

void TestDomainIsSelfSubDomain() {
  Domain domain("www.ya.ru");
  ASSERT(!CheckDomains({domain}, {domain})[0]);
}

void TestSwapParams() {
  Domain bad_domain("ya.ru");
  Domain check_domain("maps.ya.ru");

  ASSERT(!CheckDomains({bad_domain}, {check_domain})[0]);
  ASSERT(CheckDomains({check_domain}, {bad_domain})[0]);
}

void TestAbsorption() {
  {
    vector<Domain> bad_domains;
    for (const auto &line : {"ya.ru", "maps.ya.ru"}) {
      bad_domains.emplace_back(line);
    }
    DomainChecker checker(bad_domains.begin(), bad_domains.end());
    bad_domains[0] = Domain("google.com");
    ASSERT_EQUAL(checker.IsSubdomain(Domain("maps.ya.ru")), false);
  }

  {
    vector<Domain> bad_domains;
    for (const auto &line : {"maps.ya.ru", "ya.ru"}) {
      bad_domains.emplace_back(line);
    }
    DomainChecker checker(bad_domains.begin(), bad_domains.end());
    bad_domains[1] = Domain("google.com");
    ASSERT_EQUAL(checker.IsSubdomain(Domain("maps.ya.ru")), false);
  }
}

void TestCorrectness() {
  vector<Domain> bad_domains;
  for (const auto &line : {"facebook.com", "google.com"}) {
    bad_domains.emplace_back(line);
  }
  vector<Domain> check_domain;
  for (const auto &line : {"main.facebook.com", "news.facebook.com",
                           "twitter.com", "mail.google.com", "ya.ru"}) {
    check_domain.emplace_back(line);
  }
  ASSERT_EQUAL(CheckDomains(bad_domains, check_domain),
               (vector<bool>{0, 0, 1, 0, 1}));
}

void TestOutput() {
  vector<Domain> bad_domains;
  for (const auto &line : {"facebook.com", "google.com"}) {
    bad_domains.emplace_back(line);
  }
  vector<Domain> check_domain;
  for (const auto &line : {"main.facebook.com", "news.facebook.com",
                           "twitter.com", "mail.google.com", "ya.ru"}) {
    check_domain.emplace_back(line);
  }
  ostringstream sout;
  PrintCheckResults(CheckDomains(bad_domains, check_domain), sout);
  ASSERT_EQUAL(sout.str(), "Bad\nBad\nGood\nBad\nGood\n");
}

void TestReadDomains() {
  istringstream sin("2\nfacebook.com\ngoogle.com");
  const vector<Domain> banned_domains = ReadDomains(sin);
  auto it = banned_domains[0].GetParts().begin();
  ASSERT_EQUAL(*it, "facebook");
  ++it;
  ASSERT_EQUAL(*it, "com");
  ASSERT_EQUAL(banned_domains.size(), static_cast<size_t>(2));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSimple);
  RUN_TEST(tr, TestGetReversedParts);
  RUN_TEST(tr, TestDomainIsSelfSubDomain);
  RUN_TEST(tr, TestSwapParams);
  RUN_TEST(tr, TestAbsorption);
  RUN_TEST(tr, TestCorrectness);
  RUN_TEST(tr, TestOutput);
  RUN_TEST(tr, TestReadDomains);

  const vector<Domain> banned_domains = ReadDomains();
  const vector<Domain> domains_to_check = ReadDomains();
  PrintCheckResults(CheckDomains(banned_domains, domains_to_check));
  return 0;
}
