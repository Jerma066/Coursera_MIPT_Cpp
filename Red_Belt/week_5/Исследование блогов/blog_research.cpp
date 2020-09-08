#include <vector>
#include <map>
#include <string>
#include <set>
#include <cmath>
#include <future>

#include "test_runner.h"

template <typename Iterator>
class IteratorRange
{
public:
    IteratorRange(Iterator begin, Iterator end)
        : first(begin)
        , last(end)
        , size_(distance(first, last))
    {
    }

    Iterator begin() const
    {
        return first;
    }

    Iterator end() const
    {
        return last;
    }

    size_t size() const
    {
        return size_;
    }

private:
    Iterator first, last;
    size_t size_;
};

template <typename Iterator>
class Paginator
{
private:
    std::vector<IteratorRange<Iterator>> pages;

public:
    Paginator(Iterator begin, Iterator end, size_t page_size)
    {
        for (size_t left = std::distance(begin, end); left > 0; )
        {
            size_t current_page_size = std::min(page_size, left);
            Iterator current_page_end = std::next(begin, current_page_size);
            pages.push_back({ begin, current_page_end });

            left -= current_page_size;
            begin = current_page_end;
        }
    }

    auto begin() const
    {
        return pages.begin();
    }

    auto end() const
    {
        return pages.end();
    }

    size_t size() const
    {
        return pages.size();
    }
};

template <typename C>
auto Paginate(C& c, size_t page_size)
{
    return Paginator(begin(c), end(c), page_size);
}

struct Stats{
    std::map<std::string, int> word_frequences;
    void operator += (const Stats& other){
        for(auto it = other.word_frequences.begin();  
				 it != other.word_frequences.end(); it++){
			word_frequences[it->first] += it->second;
		} 
    }
};

Stats ExploreLine(const std::set<std::string>& key_words, std::string_view line){
    Stats res;
    //std::cout << line << " : " << endl;
    while(true){
        size_t space = line.find(' ');
        std::string word(line.substr(0, space));

        if (key_words.count(word)){
			res.word_frequences[word]++;
        }

        if (space == line.npos){
            break;
        }
        line.remove_prefix(space + 1);
    }
    
    /*
    for (auto word = key_words.begin(); word != key_words.end(); word++){
		std::cout << "{ " << *word << " : " << res.word_frequences[*word] << " }" << std::endl;
	}
	*/
    
    return res;
}

Stats ExploreKeyWordsSingleThread(const std::set<std::string>& key_words, std::istream& input)
{
    Stats result;
    for (std::string line; std::getline(input, line);) {
        result += ExploreLine(key_words, line);
    }
    return result;
}

template <typename Container>
Stats TemplateExploreKeyWords(const std::set<std::string>& key_words, Container& input)
{
    Stats result;
    for(const auto& line : input){
        result += ExploreLine(key_words, line);
        /*
        std::cout << "line: " << line << std::endl;
		for (auto word = key_words.begin(); word != key_words.end(); word++){
			int token_num = result.word_frequences.count(*word) ? 
							result.word_frequences[*word] : 0;
			std::cout << "{ " << *word << " : " <<  token_num << " }" << std::endl;
		} 
		*/   
    }
    return result;
}

Stats ExploreKeyWords(const std::set<std::string>& key_words, std::istream& input)
{
    std::vector<std::string> lines;
    
	std::string line;
    while (std::getline(input, line)){
        lines.push_back(line);
    }

    double threads_count = 4.0;
    size_t page_size = std::min<size_t>(lines.size(), 
										std::ceil(lines.size() / threads_count));
    std::vector<std::future<Stats>> futures;

    for (const auto& page : Paginate(lines, page_size)){
        futures.push_back(std::async([&key_words, page]{
                return TemplateExploreKeyWords(key_words, page);
		}));
    }
    
    Stats result;
    
    for (auto& f : futures){
        result += f.get();
    }
    
    return result;    
}

void TestBasic()
{
    const std::set<std::string> key_words = { "yangle", "rocks", "sucks", "all" };

    std::stringstream ss;
    ss << "this new yangle service really rocks\n";
    ss << "It sucks when yangle isn't available\n";
    ss << "10 reasons why yangle is the best IT company\n";
    ss << "yangle rocks others suck\n";
    ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

    const auto stats = ExploreKeyWords(key_words, ss);
    const std::map<std::string, int> expected =
    {
        {"yangle", 6},
        {"rocks", 2},
        {"sucks", 1}
    };
    ASSERT_EQUAL(stats.word_frequences, expected);
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestBasic);
}
    
