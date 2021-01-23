#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <string_view>
#include <vector>

using namespace std;

class DomainChecker {
public:
  DomainChecker(const std::set<std::string> &domains)
      : forbidden_domains(domains) {
    auto domain_it = forbidden_domains.begin();
    auto sub_domain_it = forbidden_domains.begin();
    ++sub_domain_it;

    while (sub_domain_it != forbidden_domains.end()) {
      if (DomainChecker::IsSubDomain(*domain_it, *sub_domain_it)) {
        forbidden_domains.erase(sub_domain_it);
      } else {
        domain_it = sub_domain_it;
      }
      sub_domain_it = domain_it;
      ++sub_domain_it;
    }
  }

public:
  static bool IsSubDomain(const string &rdomain, const string &rsub_domain) {
    auto rd_it = rdomain.begin();
    auto rsd_it = rsub_domain.begin();

    while (rd_it != rdomain.end() && rsd_it != rsub_domain.end()) {
      if (*rd_it != *rsd_it) {
        return false;
      }
      ++rd_it;
      ++rsd_it;
    }
    if (rd_it == rdomain.end() && rsd_it == rsub_domain.end()) {
      return true;
    }
    return rd_it == rdomain.end() && *rsd_it == '.';
  }

  bool IsGoodDomain(std::string &domain) const {
    std::reverse(domain.begin(), domain.end());
    auto l_it = forbidden_domains.lower_bound(domain);

    if (l_it != forbidden_domains.end() && IsSubDomain(*l_it, domain)) {
      return false;
    } else if (l_it-- != forbidden_domains.begin() &&
               IsSubDomain(*l_it, domain)) {
      return false;
    } else {
      return true;
    }
  }

private:
  std::set<std::string> forbidden_domains;
};

std::set<string> ReadBadDomains(istream &input) {
  std::set<string> domains;
  std::string line;
  size_t n;
  input >> n;
  for (size_t i = 0; i < n; ++i) {
    input >> line;
    reverse(line.begin(), line.end());
    domains.insert(line);
  }

  return domains;
}

int main() {
  std::set<string> banned_domains = ReadBadDomains(std::cin);
  DomainChecker Cheker(banned_domains);

  size_t n_doms;
  std::cin >> n_doms;
  string domain;
  for (size_t i = 0; i < n_doms; i++) {
    std::cin >> domain;
    if (Cheker.IsGoodDomain(domain)) {
      std::cout << "Good" << std::endl;
    } else {
      std::cout << "Bad" << std::endl;
    }
  }

  return 0;
}
