#include <vector>
#include <utility>

#include "test_runner.h"

using namespace std;

template <typename Token>
using Sentence = vector<Token>;

template <typename Token>
std::vector<Sentence<Token>> SplitIntoSentences(std::vector<Token> tokens){
    Sentence<Token> sentence;
    std::vector<Sentence<Token>> result;
    bool sentenceEndFlag = false;
    
    for(auto it = tokens.begin(); it != tokens.end(); it++){
		if(it->IsEndSentencePunctuation()){
			sentenceEndFlag = true;
        }       
        if (sentenceEndFlag && !(it->IsEndSentencePunctuation())){
            sentenceEndFlag = false;
            result.push_back(std::move(sentence));
        }
        
        sentence.push_back(std::move(*it));
	}
    
    result.push_back(std::move(sentence));
    return result;
}


struct TestToken {
    string data;
    bool is_end_sentence_punctuation = false;

    bool IsEndSentencePunctuation() const {
        return is_end_sentence_punctuation;
    }
    bool operator==(const TestToken& other) const {
        return data == other.data && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
    }
};

ostream& operator<<(ostream& stream, const TestToken& token) {
    return stream << token.data;
}


void TestSplitting() {
    ASSERT_EQUAL(
        SplitIntoSentences(vector<TestToken>({ {"Split"}, {"into"}, {"sentences"}, {"!"} })),
        vector<Sentence<TestToken>>({
            {{"Split"}, {"into"}, {"sentences"}, {"!"}}
            })
    );

    ASSERT_EQUAL(
        SplitIntoSentences(vector<TestToken>({ {"Split"}, {"into"}, {"sentences"}, {"!", true} })),
        vector<Sentence<TestToken>>({
            {{"Split"}, {"into"}, {"sentences"}, {"!", true}}
            })
    );

    ASSERT_EQUAL(
        SplitIntoSentences(vector<TestToken>({ {"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"Without"}, {"copies"}, {".", true} })),
        vector<Sentence<TestToken>>({
            {{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}},
            {{"Without"}, {"copies"}, {".", true}},
            })
            );
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSplitting);
    return 0;
}
